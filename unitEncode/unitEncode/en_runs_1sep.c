#include <stdio.h>
#include "all.h"
#include "encoding.h"

#define uint unsigned int
#define uchar unsigned char


/** @brief
  * @param   r[IN/OUT]
  * @param   p[IN]
  * @param   cbook[IN]
  * @param   lenz[IN]
  * @param   sep[OUT]:�������Ҫ��ֱ�Ӵ�NULL
  * @retval  none
  * @note    r�����ݻᱻ�޸ģ���������Ҫ�������ȱ���
  */
void en_runs_1sep(Uint32_Dat* r, float p, unsigned char cbook, int lenz, SEP* sep)
{

	union data {
		uint a;
		uchar b[4];
	} rem;
	extern int ptr;
	extern uchar *bin;
	int x = 0;
	int *n = NULL;
	int thd = 0;
	int sum = 0;
	float pw = 0;
	SFC sfc1;
	GOL gol;
	SEP temp;
	if (sep == NULL) {
		sep = &temp;
	}
	if (lenz > 600) {
		/* biny=[biny 0]; */
		ptr++;

		/*! %separating r into rk and rw ------------------------------ */
		/* n=hist(r,[1:max(r)]); */
		n = hist(r->dat, r->len);
		thd = find_thd(r->len, n, p);

		/* bin = encode_stationary_source(thd,cbook);  biny=[uint8(biny) bin]; */
		/* Hint:�˴�Ҫ��cbookΪ���� */
		encode_stationary_source_bin((unsigned int *)&thd, 1, cbook, 0, 0, 0, 0, 0);
		/* [sep,rw,rk]=separate(r,thd); + rw=rw-thd; */
		*sep = separate0((int *)r->dat, thd, r->len, 1);
		/* nk=n(1:thd); */
		Int32_Dat nk;
		nk.len = thd;
		nk.dat = (int *)malloc(sizeof(int)*nk.len);
		memcpy(nk.dat, n + 1, sizeof(int)*nk.len);

		/*! %encoding sep --------------------------------------------- */
		/* [rs,lastBit,ps]=Golomb0(sep); */
		gol = Golomb0(sep->sep, sep->lensepbit);

		/* biny=[biny lastBit]; */
		x = ptr & 7;
		bin[ptr >> 3] |= gol.lastBit << (7 - x);
		ptr++;

		/** ���´����MATLAB�Ĵ���������ͬ�����д��ģ˳���ϵĵ���
		  * �����ĵط���Ҫ����:
		  * 1 -�����Ǹ���p���з���,��0��1֮��Ϊ1�࣬
		  *    ����1���ߵ���0Ϊ��һ��
		  * 2 - ��ƴ��codebook����ƴ��bin
		  */
		  /* biny = [biny  codebook bin]; */
		if (gol.p < 1 && gol.p != 0) {
			ESSC essc1;
			essc1 = encode_stationary_source_cbook(gol.p);
			//printf("codebook = %d\n", essc1.codebook);


			/* codebook */
			sfc1 = SFcode(essc1.codebook + 1, 5);
			x = ptr & 7;
			rem.a = sfc1.code;
			rem.a = rem.a << (16 - x - sfc1.lb);
			bin[ptr >> 3] |= rem.b[1];
			bin[(ptr >> 3) + 1] |= rem.b[0];
			ptr += sfc1.lb; x += sfc1.lb; x &= 7;
			/* bin */
			encode_stationary_source_bin(gol.r, gol.lenr, essc1.codebook, essc1.k, essc1.m, essc1.m1, essc1.m2, essc1.cls);

		}
		else {
			/* codebook */
			sfc1 = SFcode((int)gol.p + 1, 5);
			x = ptr & 7;
			rem.a = sfc1.code;
			rem.a = rem.a << (16 - x - sfc1.lb);
			bin[ptr >> 3] |= rem.b[1];
			bin[(ptr >> 3) + 1] |= rem.b[0];
			ptr += sfc1.lb; x += sfc1.lb; x &= 7;
			/* bin */
			encode_stationary_source_bin(gol.r, gol.lenr, gol.p, 0, 0, 0, 0, 0);
		}

		/*! ���en_runs_sep_sub��������� */
#if 0
		printf("thd = %d\n", thd);
		printf("rk:\n");
		for (int i = 0; i < sep.lrk; i++) {
			printf("(%3d):%3d  ", i + 1, r->dat[i]);
			if ((i + 1) % 8 == 0) printf("\n");
		}
		printf("\n");
		printf("nk:\n");
		for (int i = 0; i < thd; i++) {
			printf("(%3d):%3d  ", i + 1, nk.dat[i]);
			if ((i + 1) % 8 == 0) printf("\n");
		}
		printf("\n");
		printf("rw:\n");
		for (int i = 0; i < sep.lrw; i++) {
			printf("(%3d):%3d  ", i + 1, sep.rw[i]);
			if ((i + 1) % 8 == 0) printf("\n");
		}
		printf("\n");
#endif
		en_runs_sep_sub(thd, r->dat, (unsigned int *)nk.dat, sep->rw, sep->lrk, sep->lrw);

#if 0
		�ڴ��ͷţ�
			1 - n
			2 - nk.dat
			3 - gol�µ�����
#endif
			/* �ͷ��ڴ� */
			free(n);
		free(nk.dat);
		free(gol.r);
		if (sep == &temp) {
			free((*sep).rw);
			free((*sep).sep);
		}
	}
	else {

		/* biny=[biny 1]; */
		x = ptr & 7;
		bin[ptr >> 3] |= 1 << (7 - x);
		ptr++;
		/* sum(r) */
		sum = 0;
		for (int i = 0; i < r->len; i++)
			sum += r->dat[i];
		/* length(r)/sum(r) */
		pw = (float)r->len / sum;
		//printf("pw = %f\n", pw);

  /** ���´����MATLAB�Ĵ���������ͬ�����д��ģ˳���ϵĵ���
	* �����ĵط���Ҫ����:
	* 1 -�����Ǹ���length(r)/sum(r)(��pw)���з���,��0��1֮��Ϊ1�࣬
	*    ����1���ߵ���0Ϊ��һ��
	* 2 - ���pw����5����ǿ�ƽ����޸�Ϊ5
	* 3 - ��ƴ��codebook����ƴ��bin
	*/
	/* biny = [biny  codebook bin]; */
		if (pw < 1 && pw != 0) {
			ESSC essc1;
			essc1 = encode_stationary_source_cbook(pw);
			/* codebook */
			if (essc1.codebook > 5) {
				x = ptr & 7;
				sfc1 = SFcode(6, 6);
				rem.a = sfc1.code;
				rem.a = rem.a << (16 - x - sfc1.lb);
				bin[ptr >> 3] |= rem.b[1];
				bin[(ptr >> 3) + 1] |= rem.b[0];
				ptr += sfc1.lb; x += sfc1.lb; x &= 7;
				encode_stationary_source_bin(r->dat, r->len, 5, 0, 0, 0, 0, 0);
			}
			else {
				x = ptr & 7;
				sfc1 = SFcode(essc1.codebook + 1, 6);
				rem.a = sfc1.code;
				rem.a = rem.a << (16 - x - sfc1.lb);
				bin[ptr >> 3] |= rem.b[1];
				bin[(ptr >> 3) + 1] |= rem.b[0];
				ptr += sfc1.lb; x += sfc1.lb; x &= 7;
				/* bin */
				encode_stationary_source_bin(r->dat, r->len, essc1.codebook, essc1.k, essc1.m, essc1.m1, essc1.m2, essc1.cls);
			}
		}
		else {
			/* codebook */
			if (pw > 5) pw = 5;
			x = ptr & 7;
			sfc1 = SFcode((int)pw + 1, 6);
			rem.a = sfc1.code;
			rem.a = rem.a << (16 - x - sfc1.lb);
			bin[ptr >> 3] |= rem.b[1];
			bin[(ptr >> 3) + 1] |= rem.b[0];
			ptr += sfc1.lb; x += sfc1.lb; x &= 7;
			/* bin */
			encode_stationary_source_bin(r->dat, r->len, pw, 0, 0, 0, 0, 0);
		}

		sep->sep = 0;
		sep->lensepbit = 1;
	}


	return;
}

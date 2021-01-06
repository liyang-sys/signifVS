#include <stdio.h>
#include "all.h"
#include "parameter_setting.h"
#include "encoding.h"

#define uint unsigned int
#define uchar unsigned char

/** @brief
  * @param   sep[IN]
  * @param   cbook[IN]
  * @retval  none
  * @note    sep->len�洢����sep->dat�Ķ��������ݳ��ȣ�
  *          �����ֽڳ���
  */
void en_runs_0seps(Uint8_Dat* sep, unsigned char cbook)
{
	union data {
		uint a;
		uchar b[4];
	} rem;
	extern int ptr;
	extern uchar *bin;

	GOL gol;
	SFC sfc1;
	int x;
	int lenrs = 0;

	/* [rs,lastBit,ps]=Golomb0(sep); */
	gol = Golomb0(sep->dat, sep->len);
	/* biny=[biny lastBit]; */
	x = ptr & 7;
	bin[ptr >> 3] |= gol.lastBit << (7 - x);
	ptr++;
	/* lenrs=length(rs); */
	lenrs = gol.lenr;

	/* bin = encode_stationary_source(lenrs,cbook); biny=[uint8(biny) bin]; */
	encode_stationary_source_bin((unsigned int *)&lenrs, 1, cbook, 0, 0, 0, 0, 0);

	/** ���´����MATLAB�Ĵ���������ͬ�����д��ģ˳���ϵĵ���
	  * �����ĵط���Ҫ����:
	  * 1 -�����Ǹ���p���з���,��0��1֮��Ϊ1�࣬
	  *    ����1���ߵ���0Ϊ��һ��
	  * 2 - ��ƴ��codebook����ƴ��bin
	  */
	if (gol.p < 1 && gol.p != 0) {
		ESSC essc1;
		essc1 = encode_stationary_source_cbook(gol.p);
		if (essc1.codebook > 9) {
			/* codebook */
			essc1.codebook = 9;
			sfc1 = SFcode(essc1.codebook + 1, 10);
			x = ptr & 7;
			rem.a = sfc1.code;
			rem.a = rem.a << (16 - x - sfc1.lb);
			bin[ptr >> 3] |= rem.b[1];
			bin[(ptr >> 3) + 1] |= rem.b[0];
			ptr += sfc1.lb; x += sfc1.lb; x &= 7;
			/* bin */
			encode_stationary_source_bin(gol.r, gol.lenr, essc1.codebook, 0, 0, 0, 0, 0);
		}
		else {
			/* codebook */
			sfc1 = SFcode(essc1.codebook + 1, 10);
			x = ptr & 7;
			rem.a = sfc1.code;
			rem.a = rem.a << (16 - x - sfc1.lb);
			bin[ptr >> 3] |= rem.b[1];
			bin[(ptr >> 3) + 1] |= rem.b[0];
			ptr += sfc1.lb; x += sfc1.lb; x &= 7;
			/* bin */
			encode_stationary_source_bin(gol.r, gol.lenr, essc1.codebook, essc1.k, essc1.m, essc1.m1, essc1.m2, essc1.cls);
		}
	}
	else {
		/* codebook */
		if (gol.p > 9) gol.p = 9;
		sfc1 = SFcode((int)gol.p + 1, 10);
		x = ptr & 7;
		rem.a = sfc1.code;
		rem.a = rem.a << (16 - x - sfc1.lb);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr += sfc1.lb; x += sfc1.lb; x &= 7;
		/* bin */
		encode_stationary_source_bin(gol.r, gol.lenr, gol.p, 0, 0, 0, 0, 0);
	}
#if 0
	�ڴ��ͷţ�
		1 - gol.r
#endif
		// �ͷ��ڴ�
		free(gol.r);
	return;
}

#include <stdio.h>
#include <math.h>
#include "all.h"
#include "encoding.h"
#include "parameter_setting.h"

void en_sub3d_sub2(Int32_Dat* cf0, Uint8_Dat* sn, int maxcf0)
{

	/* Hint:nc以及thd的0索引保留不使用 */

	extern unsigned char *bin;
	extern int ptr;
	/* 初始化 */
	//bin = NULL;
	//ptr = 0;
	/* 为后面bin_iter的编码腾出空间 */
	int tempPtr = ptr;
	ptr += 3;
	//bin = (unsigned char *)malloc(sizeof(unsigned char)*((cf0->len) / 8 + 1));  // 分配绝对足够的空间
	//memset(bin, 0, sizeof(unsigned char)*((cf0->len) / 8 + 1));
	//if (bin == NULL) {
	//	perror("bin");
	//	exit(-1);
	//}

	union data {
		uint a;
		uchar b[4];
	} rem;
	int x = 0;
	SFC se;

	int maxcf = 0;
	//unsigned int len = 0;
	unsigned int len = cf0->len;//修改的
	unsigned int *nc = NULL;
	unsigned int Nidx = 0;
	float p = 0, p1 = 0, p2 = 0.8;
	unsigned int lenw = 0, lenc = 0;
	Int32_Dat cf;
	int iter = 0, idx0 = 0, crc = 20;
	int thd1 = 0;

	int thdidx = 0, lB = 0;
	Uint32_Dat r, nr, cf1, cf1k, nc1, nc1k;
	float pr = 0, scr = 0, scrc = 0;
	Uint8_Dat z;
	Int32_Dat thd_arr_temp;
	Uint32_Dat nc_temp;
	int nc_len = 0;



	/*!  %<=== treat cf0 as runs! */
	/* maxcf=double(maxcf0+1); */
	maxcf = maxcf0 + 1;
	nc = (unsigned int *)malloc(sizeof(unsigned int)*(maxcf + 1));
	if (nc == NULL) {
		perror("n");
		exit(-1);
	}
	memset(nc, 0, sizeof(unsigned int)*(maxcf + 1));

	/* cf0=cf0+1; nc=hist(double(cf0),[1:maxcf]); */
	for (int i = 0; i < cf0->len; i++) {
		cf0->dat[i] += 1;
		nc[(unsigned int)cf0->dat[i]] += 1;
	}

	/* th=[cumprod(2*ones(1,11)); 3*cumprod([1 2*ones(1,10)])]; th=reshape(th,1,22); thd_arr=[1 th]; */
	int thd_arr[24] = { 0, 1, 2, 3, 4, 6, 8,
					  12, 16, 24, 32, 48, 64, 96, 128,
					  192, 256, 384, 512, 768, 1024, 2048, 3072 };
	/* Nidx=length(thd_arr); */
	Nidx = 23;
	/* p=0.7; p1=0.7; p2=0.8; */
	p = 0.7; p1 = 0.7; p2 = 0.8;
	p = p;   p1 = p1; p2 = p2;   // 保留，防止编译器报警告

/* 调试代码段 */
#if 0
	printf("nc");
	for (int i = 1; i <= maxcf; i++) {
		printf("(%3d):%5d ", i, nc[i]);
		if (i % 8 == 0) printf("\n");
	}
	while (1);
#endif // 0

	/*! %first round ========================================================================== */
	/* lenw=len; */
	lenw = len;
	/* lenc=1600; */
	lenc = 1600;

	/* iter=1; cf=cf0; biny=[]; idx0=1; maxcf=max(cf); crc=20; */
	iter = 1;
	cf.dat = cf0->dat;
	cf.len = cf0->len;
	idx0 = 1;
	maxcf = maxcf;
	crc = 20;

	nc_len = maxcf;
	unsigned int *temp = (unsigned int *)malloc(sizeof(unsigned int)*maxcf);
	memcpy(temp, nc + 1, sizeof(unsigned int)*maxcf);
	free(nc);
	nc = temp;

	while ((lenw > lenc || crc >= 12) && iter <= 8 && maxcf >= 2) {
		/* [thdidx,r,lB,pr,nr,scr,scrc,cf1,cf1k,nc1,nc1k,z] = find_thd4subs(cf,thd_arr,nc,idx0);  */
		thd_arr_temp.dat = thd_arr + 1;
		thd_arr_temp.len = Nidx;
		nc_temp.dat = nc;
		nc_temp.len = nc_len;
		find_thd4subs(&cf, &thd_arr_temp, &nc_temp, idx0, &thdidx, &r, &lB, &pr, &nr, &scr, &scrc, &cf1, &cf1k, &nc1, &nc1k, &z);

#if 0
		printf("cf1:\n");
		for (int i = 0; i < cf1.len; i++) {
			printf("(%3d):%5d ", i + 1, cf1.dat[i]);
			if (i % 8 == 0) printf("\n");
		}
		printf("\n");
		while (1);
#endif

		/* thd1=thd_arr(thdidx); */
		thd1 = thd_arr[thdidx];
		thd1 = thd1;                 // 保留，防止编译器报警告
		/* idx0=thdidx; */
		idx0 = thdidx;
		/* biny=[biny SFcode(thdidx,Nidx)]; */
		x = ptr & 7;
		se = SFcode(thdidx, Nidx);
		rem.a = se.code;
		rem.a = rem.a << (16 - x - se.lb);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr += se.lb; x += se.lb; x &= 7;
		//printf("(1)ptr = %d\n", ptr);
		Uint32_Dat nrPlus;
		nrPlus.dat = nr.dat + 1;
		nrPlus.len = nr.len;
		en_sub3d_sub2_sub(&z, &r, lB, pr, &nrPlus, scr, scrc, &cf1k, &nc1k, thd1);
		/* iter=iter+1; */
		iter += 1;
		/* lenw=length(cf1); */
		lenw = cf1.len;
		/* cf=cf1; */
		free(cf.dat);
		cf.dat = (int *)cf1.dat;
		cf.len = cf1.len;

		/* nc=nc1; */
		free(nc);
		nc = nc1.dat;
		nc_len = nc1.len;
		/* maxcf=max(cf); */
		maxcf = 0;
		for (int i = 0; i < cf.len; i++) maxcf = maxcf > cf.dat[i] ? maxcf : cf.dat[i];
		//printf("maxcf = %d len = %d\n", maxcf, cf.len);

		//代填

		if (maxcf >= 2) {
			
			k_criterion((void *)&cf, NULL, &crc, NULL, NULL, NULL, &nc_temp, NULL, 0);
			nc = nc_temp.dat;
			nc_len = nc_temp.len;

			free(nc_temp.dat);//修改
			//printf("crc = %d\n", crc);
		}
		else {
			break;
		}
	}
	iter += -1;

	/* biny=[bin_iter biny ]; */
	//bin[0] |= (iter - 1) << 5;


	rem.a = iter - 1;
	rem.a = rem.a << (16 - (tempPtr & 7) - 3);
	bin[tempPtr >> 3] |= rem.b[1];
	bin[(tempPtr >> 3) + 1] |= rem.b[0];

	/* 调试代码段 */
#if 0
	printf("cf:\n");
	for (int i = 0; i < cf.len; i++) {
		printf("(%3d):%5d ", i + 1, cf.dat[i]);
		if ((i + 1) % 8 == 0) printf("\n");
	}
	printf("\n");
	while (1);
#endif

	//printf("(3)ptr = %d\n", ptr);
	/* biny=[biny bin ]; */
	en_r0((unsigned int *)cf.dat, cf.len);

	/* biny=[biny  sn]; */
	x &= ptr;
	printf("\n-----------------------------------------------\n");
	//for (int i = 0, j = 0; i < sn->len; i++) {
	//	j = i & 7;
	//	j = 7 - j;
	//	printf("%d ", ((sn->dat[i / 8] << (7 - j)) >> 7) << (7 - x));
	//	bin[ptr >> 3] |= ((sn->dat[i / 8] << (7 - j)) >> 7) << (7 - x);
	//	x++; x &= 7; ptr++;
	//}

	//int tempBit = 0;
	//for (int i = 0; i < sn->len; i++)
	//{

	//	tempBit = (sn->dat[ptr >> 3] >> (7 - (i & 7))) & 1;
	//	if (tempBit == 1)
	//	{
	//		bin[ptr >> 3] |= (1 << (7 - (ptr&7)));
	//	}
	//	ptr++;
	//}
	bin_add(bin,sn->dat , sn->len);

	//printf("(4)ptr = %d\n", ptr);

	return;
}

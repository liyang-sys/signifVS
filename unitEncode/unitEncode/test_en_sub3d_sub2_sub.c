#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "all.h"
#include "encoding.h"
#include "parameter_setting.h"

int ptr;
uchar *bin;
void test_en_sub3d_sub2_sub()
{
	ptr = 0;
	bin = calloc(102400, sizeof(uchar));
	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	int zLen = 262144;
	unsigned int *bigZ = (unsigned int *)calloc(zLen, sizeof(unsigned int));
	FILE *fp = fopen("Z.txt", "rb");
	fread(bigZ, sizeof(unsigned int), zLen, fp);
	int index = 0;
	int indexZ = 0;
	Uint8_Dat z;
	z.len = zLen;
	z.dat = (unsigned char *)calloc(zLen, sizeof(unsigned char));
	int sumZ = 0;
	for (int i = 0; i < zLen; i++)
	{
		if (bigZ[i] == 1)
		{
			rem.a = 1;
			rem.a = rem.a << (15 - index);
			z.dat[indexZ >> 3] |= rem.b[1];
			z.dat[(indexZ >> 3) + 1] |= rem.b[0];
			sumZ++;
		}
		index++;
		indexZ++;
		index &= 7;
		//printf("%d ", bigZ[i]);
	}
	printf("\n------------------------------------------------------------------------------------------\n");
	///从matlab读取runs数组
	Uint32_Dat r;
	r.len = 48728;
	r.dat = (unsigned int *)calloc(r.len, sizeof(unsigned int));
	fp = fopen("R.txt", "rb");
	fread(r.dat, sizeof(unsigned int), r.len, fp);
	fclose(fp);

	Uint32_Dat nr;
	nr.len = 4329;
	nr.dat = (unsigned int *)calloc(nr.len, sizeof(unsigned int));
	fp = fopen("NR.txt", "rb");
	fread(nr.dat, sizeof(unsigned int), nr.len, fp);
	fclose(fp);

	Uint32_Dat cfk;
	cfk.len = 213417;
	cfk.dat = (unsigned int *)calloc(cfk.len, sizeof(unsigned int));
	fp = fopen("CFK.txt", "rb");
	fread(cfk.dat, sizeof(unsigned int), cfk.len, fp);
	fclose(fp);

	Uint32_Dat nck;
	nck.len =6;
	nck.dat = (unsigned int *)calloc(nck.len, sizeof(unsigned int));
	fp = fopen("NCK.txt", "rb");
	fread(nck.dat, sizeof(unsigned int), nck.len, fp);
	fclose(fp);
	//for (int i = 0; i < cf0.len; i++)
	//{
	//	printf("%d ", cf0.dat[i]);
	//}

	int lB = 0;
	//float pr = 0.0072;
	//float pr = 0.1815;
	//float pr = 0.3020;
	//float pr = 0.5361;
	//float pr = 0.3082;
	//float pr = 0.3110;
	//float pr = 0.3367;
	//float pr = 0.2383;
	//float pr = 0.5339;
	//float pr = 0.3680;
	//float pr = 0.3760;
	//float pr = 0.2837;
	float pr = 0.3985;
	//float scr = 53.0452;
	//float scr = 24.6226;
	//float scr = 976.9947;
	//float scr = 661.5757;
	//float scr = 6.9021;
	float scr = 22744.6;
	//float scr = 414.8284;
	//float scr = 976.0139;
	//float scr = 190.4475;
	//float scr = 187.0473;
	//float scr = 61.9152;
	//float scr = 71.5786;
	//float scr = 21.8553;
	//float scrc = 31;
	//float scrc = 17;
	//float scrc = 185;
	//float scrc = 174;
	//float scrc = 634;
	float scrc = 1541;
	//float scrc = 77;
	//float scrc = 189;
	//float scrc = 60;
	//float scrc = 70;
	//float scrc = 27;
	//float scrc = 26;
	//float scrc = 16;
	//int nck = 8134;
	//int thd = 1;
	int thd = 6;
	en_sub3d_sub2_sub(&z, &r, lB, pr, &nr, scr, scrc, &cfk, &nck, thd);
	fp = fopen("encodeZThd4.txt", "wb");
    fwrite(bin, sizeof(unsigned char), (ptr / 8) + 1, fp);
    fclose(fp);
	printf("\n编码结束后ptr = %d\n", ptr);
	//ptr = 0;
	//DEC dec = de_z0_r0(bin, 8192);
	//fp = fopen("CDecodeZElse.txt", "wb");
	//fwrite(dec.z, sizeof(unsigned char), (8192 / 8) + 1, fp);
	//fclose(fp);
}
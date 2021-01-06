#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "all.h"
#include "encoding.h"
#include "parameter_setting.h"

int ptr;
uchar *bin;
void test_en_z0_r0()
{
	ptr = 0;
	bin = calloc(4096, sizeof(uchar));
	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	int zLen = 8192;
	unsigned int *bigZ = (unsigned int *)calloc(zLen, sizeof(unsigned int));
	FILE *fp = fopen("ElseZ.txt", "rb");
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
		printf("%d ", bigZ[i]);
	}
	printf("\n------------------------------------------------------------------------------------------\n");
	///从matlab读取runs数组
	Uint32_Dat runs;
	runs.len = 59;
	runs.dat = (unsigned int *)calloc(runs.len, sizeof(unsigned int));
	fp = fopen("ElseRuns.txt", "rb");
	//fp = fopen("wunsDAYUlenf1C2N.txt","rb");
	fread(runs.dat, sizeof(unsigned int), runs.len, fp);
	//    printf("c2n = %p",c2n.dat);
	fclose(fp);
	for (int i = 0; i < runs.len; i++)
	{
		printf("%d ", runs.dat[i]);
	}
	//en_z0_r0(&z, &runs, 1, sumZ,0.3707);
	//en_z0_r0(&z, &runs, 1, sumZ, 0.4345);
	//en_z0_r0(&z, &runs, 1, sumZ, 0.3813);
	en_z0_r0(&z, &runs, 0, sumZ, 0.0072);
	printf("\n编码结束后ptr = %d\n", ptr);
	ptr = 0;
	DEC dec = de_z0_r0(bin, 8192);
	fp = fopen("CDecodeZElse.txt", "wb");
	fwrite(dec.z, sizeof(unsigned char), (8192 / 8) + 1, fp);
	fclose(fp);
}
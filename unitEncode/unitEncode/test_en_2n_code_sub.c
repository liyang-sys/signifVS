#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "encoding.h"
#include "parameter_setting.h"
#include "all.h"
int ptr;
uchar *bin;


void test_en_2n_code_sub()
{
	ptr = 0;
	bin = calloc(2048, sizeof(uchar));
	FILE *fp;
	///从matlab读取c2n数组
	Uint32_Dat c2n;
	c2n.len = 106;
	c2n.dat = (unsigned int *)calloc(c2n.len, sizeof(unsigned int));
	fp = fopen("C.txt", "rb");
	//fp = fopen("wunsDAYUlenf1C2N.txt","rb");
	fread(c2n.dat, sizeof(unsigned int), c2n.len, fp);
	//    printf("c2n = %p",c2n.dat);
	fclose(fp);
	for (int i = 0; i < c2n.len; i++)
	{
		printf("%d ", c2n.dat[i]);
	}

	en_2n_code_sub(&c2n, NULL, 2);


	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	int zLen = 212;
	unsigned int *bigZ = (unsigned int *)calloc(zLen, sizeof(unsigned int));
	fp = fopen("CODEC.txt", "rb");
	fread(bigZ, sizeof(unsigned int), zLen, fp);
	//for (int i = 0; i < zLen; i++)
	//{
	//	printf("%d", bigZ[i]);
	//}
	//printf("\n");
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
	}

	for (int i = 0; i <= zLen / 8; i++)
	{
		if ((bin[i] - z.dat[i]) != 0)
		{
			printf("i = %d bin[i] = %d z.dat[i] = %d\n", i, bin[i], z.dat[i]);
		}
	}

}
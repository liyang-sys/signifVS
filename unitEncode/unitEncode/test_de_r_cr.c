#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "encoding.h"
#include "parameter_setting.h"
#include "all.h"
int ptr;
uchar *bin;

void test_de_r_cr()
{
	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	int zLen = 5210;
	unsigned int *bigZ = (unsigned int *)calloc(zLen, sizeof(unsigned int));
	FILE *fp = fopen("binRCR.txt", "rb");
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
	printf("\n bin:-----------------------------------------------------------------------------------\n");
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
	printf("\n-----------------------------------------------------------------------------------\n");
	ptr = 13;
	DEC dec = de_r_cr(z.dat, 65536, 5210);

}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "encoding.h"
#include "parameter_setting.h"
#include "all.h"
int ptr;
uchar *bin;

void test_de_2n_code_new()
{
	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	int zLen = 20394;
	unsigned int *bigZ = (unsigned int *)calloc(zLen, sizeof(unsigned int));
	FILE *fp = fopen("CODEBIN.txt", "rb");
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
	ptr = 5880;
	DEC dec = de_2n_code_new(z.dat, 1915, 3, 2);

	///从matlab读取c2n数组
	Uint32_Dat c2n;
	c2n.len = 1915;
	c2n.dat = (unsigned int *)calloc(c2n.len, sizeof(unsigned int));
	fp = fopen("C2N.txt", "rb");
	//fp = fopen("wunsDAYUlenf1C2N.txt","rb");
	fread(c2n.dat, sizeof(unsigned int), c2n.len, fp);
	//    printf("c2n = %p",c2n.dat);
	fclose(fp);
	if (dec.lenr != c2n.len)
	{
		printf("\n解码出来长度不一致\n");
	}
	for (int i = 0; i < c2n.len; i++)
	{
		if (dec.r[i] != c2n.dat[i])
		{
			printf("\n index= %d dec.r[i] = %d  c2n.dat[i] = %d\n", i, dec.r[i],c2n.dat[i]);
		}
		
	}
	printf("所有编码结束的ptr = %d\n", ptr);
}
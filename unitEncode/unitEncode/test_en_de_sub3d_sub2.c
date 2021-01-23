#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "all.h"
#include "encoding.h"
#include "parameter_setting.h"

int ptr;
uchar *bin;
void test_en_de_sub3d_sub2()
{
	ptr = 0;
	bin = calloc(40960, sizeof(uchar));
	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	int snLen = 8192;
	unsigned int *bigZ = (unsigned int *)calloc(snLen, sizeof(unsigned int));
	FILE *fp = fopen("snCCC.txt", "rb");
	fread(bigZ, sizeof(unsigned int), snLen, fp);
	int index = 0;
	int indexZ = 0;
	Uint8_Dat sn;
	sn.len = snLen;
	sn.dat = (unsigned char *)calloc(snLen, sizeof(unsigned char));
	int sumZ = 0;
	for (int i = 0; i < snLen; i++)
	{
		if (bigZ[i] == 1)
		{
			rem.a = 1;
			rem.a = rem.a << (15 - index);
			sn.dat[indexZ >> 3] |= rem.b[1];
			sn.dat[(indexZ >> 3) + 1] |= rem.b[0];
			sumZ++;
		}
		index++;
		indexZ++;
		index &= 7;
		//printf("%d ", bigZ[i]);
	}
	printf("\n------------------------------------------------------------------------------------------\n");
	///从matlab读取runs数组
	fclose(fp);

	Int32_Dat cf0;
	cf0.len = 8192;
	cf0.dat = (int*)calloc(cf0.len, sizeof(int));
	fp = fopen("cf0CCC.txt", "rb");
	fread(cf0.dat, sizeof(int), cf0.len, fp);
	fclose(fp);

	Int32_Dat qcf;
	qcf.len = 8192;
	qcf.dat = (int*)calloc(qcf.len, sizeof(int));
	fp = fopen("qcfCCC.txt", "rb");
	fread(qcf.dat, sizeof(int), qcf.len, fp);
	fclose(fp);

	int maxcf0 = 61;
	en_sub3d_sub2(&cf0, &sn, maxcf0);

	//printf("\n%d %d %d\n", bin[639], bin[640], bin[641]);
	//printf("\n编码结束后ptr = %d\n", ptr);
	//fp = fopen("encodeZThd4.txt", "wb");
	//fwrite(bin, sizeof(unsigned char), (ptr / 8) + 1, fp);
	//fclose(fp);
	int binLen = ptr;
	ptr = 0;
	DE_S_SUB decode = de_sub3d_sub2(bin, 8192, 0, binLen);
	for (int i = 0; i < decode.cf.len; i++)
	{
		if ((decode.cf.dat[i] - qcf.dat[i]) != 0)
		{
			printf("\n cf0解码出来不对 编码前cf0 = %d 解码的cf0 = %d\n", qcf.dat[i], decode.cf.dat[i]);

		}
	}
	printf("编码和解码比对结束\n");
	//DEC dec = de_z0_r0(bin, 8192);
	//fp = fopen("CDecodeZElse.txt", "wb");
	//fwrite(dec.z, sizeof(unsigned char), (8192 / 8) + 1, fp);
	//fclose(fp);
}
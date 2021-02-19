#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "encoding.h"
#include "parameter_setting.h"
#include "all.h"
int ptr;
uchar *bin;

void test_de_sub3d_sub2()
{
	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	int zLen = 3414;
	unsigned int *bigZ = (unsigned int *)calloc(zLen, sizeof(unsigned int));
	FILE *fp = fopen("binM.txt", "rb");
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
		//if (i == 1590 || i == 1591 || i == 1592 || i == 1593)
		//{
		//	printf("%d ", bigZ[i]);
		//}
		index++;
		indexZ++;
		index &= 7;

	}
	printf("\n-----------------------------------------------------------------------------------\n");
	ptr = 0;
	int qctr = 1;
	DE_S_SUB sub = de_sub3d_sub2(z.dat, 2040, qctr, zLen);
	fp = fopen("cfC.txt", "wb");
	fwrite(sub.cf.dat, sizeof(int), sub.cf.len, fp);
	fclose(fp);
	fp = fopen("snC.txt", "wb");
	fwrite(sub.sn.dat, sizeof(int), sub.sn.len, fp);
	fclose(fp);
	fp = fopen("cfwC.txt", "wb");
	fwrite(sub.cfw.dat, sizeof(unsigned int), sub.cfw.len, fp);
	fclose(fp);
	int zz = 0;
}
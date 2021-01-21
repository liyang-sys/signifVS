#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "encoding.h"
#include "parameter_setting.h"
#include "all.h"
int ptr;
uchar *bin;

void test_de_sub3d_sub2_sub()
{
	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	//int zLen = 438253;
	//int zLen = 290246;
	//int zLen = 218780;
	//int zLen = 419491;
	int zLen = 391250;
	unsigned int *bigZ = (unsigned int *)calloc(zLen, sizeof(unsigned int));
	FILE *fp = fopen("MBiny.txt", "rb");
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
	//ptr = 228732;
	//ptr = 16;
	//ptr = 118057;
	//ptr = 209703;
	ptr = 242264;
	//DEC dec = de_r_cr(z.dat, 65536, 5210);
	//DE_S_S_SUB sub = de_sub3d_sub2_sub(z.dat, 3, 16384, 53135);
	//DE_S_S_SUB sub = de_sub3d_sub2_sub(z.dat, 4, 3787, 53135);
	//DE_S_S_SUB sub = de_sub3d_sub2_sub(z.dat, 6, 4096, 20394);
	//DE_S_S_SUB sub = de_sub3d_sub2_sub(z.dat, 8, 1274, 20394);
	//DE_S_S_SUB sub = de_sub3d_sub2_sub(z.dat, 12, 1024, 5774);
	//DE_S_S_SUB sub = de_sub3d_sub2_sub(z.dat, 12, 16384, zLen);
	DE_S_S_SUB sub = de_sub3d_sub2_sub(z.dat, 6, 5971, zLen);
	fp = fopen("zC.txt", "wb");
	fwrite(sub.z.dat, sizeof(unsigned char), ((sub.z.len) / 8) + 1, fp);
	fclose(fp);

	fp = fopen("cfkC.txt", "wb");
	fwrite(sub.cfk.dat, sizeof(unsigned int), sub.cfk.len, fp);
	fclose(fp);
	int zz = 0;
}
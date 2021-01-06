#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "all.h"
#include "encoding.h"
#include "parameter_setting.h"

int ptr;
uchar *bin;

void test_en_zone_sub2()
{
	ptr = 0;
	bin = calloc(4096, sizeof(uchar));
	//union data
	//{
	//	unsigned short int a;
	//	uchar b[4];
	//} rem;
	Uint32_Dat runs;
	runs.len = 877;
	runs.dat = (unsigned int *)calloc(runs.len, sizeof(unsigned int));
	FILE * fp = fopen("R.txt", "rb");
	//fp = fopen("wunsDAYUlenf1C2N.txt","rb");
	fread(runs.dat, sizeof(unsigned int), runs.len, fp);
	//    printf("c2n = %p",c2n.dat);
	fclose(fp);
	for (int i = 0; i < runs.len; i++)
	{
		printf("%d ", runs.dat[i]);
	}
	//en_zone_sub2(&runs);
	Uint32_Dat nr;
	nr.len = 16763;
	nr.dat = (unsigned int *)calloc(nr.len, sizeof(unsigned int));
	fp = fopen("NR.txt", "rb");
	//fp = fopen("wunsDAYUlenf1C2N.txt","rb");
	fread(nr.dat, sizeof(unsigned int), nr.len, fp);
	//    printf("c2n = %p",c2n.dat);
	fclose(fp);

	//en_r_cr(&runs, 0, NULL, 170.1092, 124, 0.0016, NULL);
	en_r_cr(&runs, 0, &nr, 631.2965, 251, 0.0134, NULL);
	int lenBin = ptr;
	ptr = 0;
	de_r_cr(bin, 131072,lenBin);
	//fp = fopen("ENRCRBIN.txt", "wb");
	//fwrite(bin, sizeof(unsigned char), (ptr / 8) + 1, fp);
	//fclose(fp);
}
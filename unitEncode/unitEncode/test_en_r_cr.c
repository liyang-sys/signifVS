#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "all.h"
#include "encoding.h"
#include "parameter_setting.h"

int ptr;
uchar *bin;

void test_en_r_cr()
{
	ptr = 0;
	bin = calloc(4096, sizeof(uchar));
	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	Uint32_Dat runs;
	runs.len = 208;
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

}
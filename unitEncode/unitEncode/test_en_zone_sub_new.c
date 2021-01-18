#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "encoding.h"
#include "parameter_setting.h"
#include "all.h"
int ptr;
uchar *bin;
void test_en_zone_sub_new()
{
	ptr = 0;
	bin = calloc(4096, sizeof(uchar));
	FILE *fp;
	///从matlab读取c2n数组
	Uint32_Dat rw2;
	rw2.len = 3093;
	rw2.dat = (unsigned int *)calloc(rw2.len, sizeof(unsigned int));
	fp = fopen("rw2M.txt", "rb");
	//fp = fopen("wunsDAYUlenf1C2N.txt","rb");
	fread(rw2.dat, sizeof(unsigned int), rw2.len, fp);
	//    printf("c2n = %p",c2n.dat);
	fclose(fp);
	float crw2 = 1170.8631;
	SEP* sepTemp1;
	en_zone_sub_new(&rw2, crw2, &sepTemp1);
	fp = fopen("binwC.txt", "wb");
	fwrite(bin, sizeof(unsigned char), (ptr / 8) + 1, fp);
	fclose(fp);
	printf("\n编码结束后ptr = %d\n", ptr);
	return;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "encoding.h"
#include "parameter_setting.h"
#include "all.h"
int ptr;
uchar *bin;
void test_en_and_de_2n_code_new()
{
	ptr = 0;
	bin = calloc(4096, sizeof(uchar));
	FILE *fp;
	///从matlab读取c2n数组
	Uint32_Dat c2n;
	c2n.len = 1915;
	c2n.dat = (unsigned int *)calloc(c2n.len, sizeof(unsigned int));
	fp = fopen("C2N3.txt", "rb");
	//fp = fopen("wunsDAYUlenf1C2N.txt","rb");
	fread(c2n.dat, sizeof(unsigned int), c2n.len, fp);
	//    printf("c2n = %p",c2n.dat);
	fclose(fp);
	for (int i = 0; i < c2n.len; i++)
	{
		printf("%d ", c2n.dat[i]);
	}


	///从matlab读取nc数组
	Uint32_Dat nc;
	nc.len = 3;
	nc.dat = (unsigned int *)calloc(nc.len, sizeof(unsigned int));
	fp = fopen("NC3.txt", "rb");
	//fp = fopen("wunsDAYUlenf1NC.txt","rb");
	fread(nc.dat, sizeof(unsigned int), nc.len, fp);
	fclose(fp);
	printf("\n--------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < nc.len; i++)
	{
		printf("%d ", nc.dat[i]);
	}
	//en_2n_code_new(&c2n, &nc, 1, 2);
	//en_2n_code_new(&c2n,&nc,1,16); //编码
	//en_2n_code_new(&c2n,&nc,2,6);
	en_2n_code_new(&c2n, &nc, 2, 3);
	fp = fopen("cEncodeBIN3.txt", "wb");
	fwrite(bin, sizeof(unsigned char), (ptr / 8) + 1,fp);
	fclose(fp);

	printf("所有编码结束的ptr = %d\n", ptr);
	//en_2n_code_new(&c2n,&nc,2,6);
	//en_2n_code_new(&c2n, &nc, 2, 3);
	//en_2n_code_new(&c2n, &nc, 1, 2);

	//fp = fopen("binbyte_c.dat", "wb");
	//fwrite(bin, sizeof(uchar), ptr/8+1, fp);
	//fclose(fp);
	ptr = 0;
	//DEC dec = de_2n_code_new(bin, 203, 16, 1);//解码
	//DEC dec = de_2n_code_new(bin, 2349, 2, 1);//解码
	//DEC dec = de_2n_code_new(bin, 581, 6, 2);//解码
	DEC dec = de_2n_code_new(bin, 1915, 3, 2);//解码
	fp = fopen("c2nRecon3.txt", "wb");
	fwrite(dec.r, sizeof(unsigned int),dec.lenr , fp);
	fclose(fp);

	Uint32_Dat src;
	src.len = 1915;
	src.dat = (unsigned int *)calloc(src.len, sizeof(unsigned int));
	fp = fopen("C2N3.txt", "rb");
	//fp = fopen("wunsDAYUlenf1C2N.txt","rb");
	fread(src.dat, sizeof(unsigned int), c2n.len, fp);
	//    printf("c2n = %p",c2n.dat);
	fclose(fp);


	if (dec.lenr != src.len)
	{
		printf("\n解码出来长度不一致\n");
	}
	for (int i = 0; i < src.len; i++)
	{
		if (dec.r[i] != src.dat[i])
		{
			printf("\n index= %d dec.r[i] = %d  src.dat[i] = %d\n", i, dec.r[i], src.dat[i]);
		}

	}
	printf("所有解码结束的ptr = %d\n", ptr);
}
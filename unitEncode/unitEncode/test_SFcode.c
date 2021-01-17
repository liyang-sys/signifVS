#include "all.h"
#include <stdio.h>
#include <math.h>

#define uint unsigned int
#define uchar unsigned char

int ptr;
uchar *bin;
void test_SFcode()
{
	ptr = 0;
	bin = calloc(4096, sizeof(uchar));
	//SFC se = SFcode(35887, 61659);
	SFC se = SFcode(3, 1);

	//int ptr = 0;
	//int x = ptr & 7;
	//rem.a = rem.a << (15);
	//rem.a = rem.a << (2);
	//rem.a = rem.a << (3);
	//rem.a = rem.a << (4);
	//rem.a = rem.a << (5);
	//rem.a = rem.a << (6);
	//rem.a = rem.a << (7);
	//rem.a = rem.a << (8);
	//rem.a = rem.a << (10);
	//printf("%f\n", (log(3) / log(2)));
	//printf("%f\n", (log(1) / log(2)));
/*	bin[ptr >> 3] |= rem.b[1];
	bin[(ptr >> 3) + 1] |= rem.b[0];
	ptr += se.lb; x += se.lb; x &= 7*/;
	//int t = 1024;
	//int*p = &t;


	//union var {
	//	char c[4];
	//	int i;
	//};

	//	union var data;
	//	data.c[0] = 0x04;//因为是char类型，数字不要太大，算算ascii的范围~
	//	data.c[1] = 0x03;//写成16进制为了方便直接打印内存中的值对比
	//	data.c[2] = 0x02;
	//	data.c[3] = 0x11;
	//	//数组中下标低的，地址也低，按地址从低到高，内存内容依次为：04,03,02,11。总共四字节！
	//	//而把四个字节作为一个整体（不分类型，直接打印十六进制），应该从内存高地址到低地址看，0x11020304，低位04放在低地址上。
	//	printf("%x\n", data.i);

	return;
}
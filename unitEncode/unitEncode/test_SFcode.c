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
	//	data.c[0] = 0x04;//��Ϊ��char���ͣ����ֲ�Ҫ̫������ascii�ķ�Χ~
	//	data.c[1] = 0x03;//д��16����Ϊ�˷���ֱ�Ӵ�ӡ�ڴ��е�ֵ�Ա�
	//	data.c[2] = 0x02;
	//	data.c[3] = 0x11;
	//	//�������±�͵ģ���ַҲ�ͣ�����ַ�ӵ͵��ߣ��ڴ���������Ϊ��04,03,02,11���ܹ����ֽڣ�
	//	//�����ĸ��ֽ���Ϊһ�����壨�������ͣ�ֱ�Ӵ�ӡʮ�����ƣ���Ӧ�ô��ڴ�ߵ�ַ���͵�ַ����0x11020304����λ04���ڵ͵�ַ�ϡ�
	//	printf("%x\n", data.i);

	return;
}
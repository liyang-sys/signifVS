#define _CRT_SECURE_NO_WARNINGS
#include "all.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define uint unsigned int
#define uchar unsigned char

SFC SFcode(uint sym, uint Nsym)
{
	union data {
		unsigned int a;
		uchar b[4];
	} rem;
	extern int ptr;
	extern uchar *bin;
	int binBytePos = ptr & 7;
	SFC sfc1;
	uint Msym = 1, Ngap;
	sfc1.lb = 0;
	Ngap = Nsym;
	int lb2 = 0;

	/* sym=sym-1; */
	sym--;

	/* 计算出Nsym二进制的长度 */
	while (Nsym > 0) {
		Nsym >>= 1;
		sfc1.lb++;
	}
	lb2 = sfc1.lb;

	/** 向二的阶乘靠拢，并计算出其补偿，比如现在Ngap等于30，
	  *  那(Msym >>= (8 - sfc1.lb)) = 32，此后Ngap=2
	  */
	Ngap = ( Msym <<= lb2)- Ngap;

	if (sym <= (Ngap - 1)) {
		sfc1.code = sym;
		sfc1.lb--;
		if (sfc1.lb <= 8)
		{
			rem.a = sfc1.code;
			rem.a = rem.a << (16 - binBytePos- sfc1.lb);
			bin[ptr >> 3] |= rem.b[1];
			bin[(ptr >> 3) + 1] |= rem.b[0];
		}
		else if (sfc1.lb <= 16 && sfc1.lb >8)
		{
			rem.a = sfc1.code;
			rem.a = rem.a << (24 - binBytePos - sfc1.lb);
			bin[ptr >> 3] |= rem.b[2];
			bin[(ptr >> 3) + 1] |= rem.b[1];
			bin[(ptr >> 3) + 2] |= rem.b[0];
		}
		else if (sfc1.lb <= 24 && sfc1.lb > 16)
		{
			printf("SFcode超过了24位\n");
			rem.a = sfc1.code;
			rem.a = rem.a << (32 - binBytePos - sfc1.lb);
			bin[ptr >> 3] |= rem.b[3];
			bin[(ptr >> 3) + 1] |= rem.b[2];
			bin[(ptr >> 3) + 2] |= rem.b[1];
			bin[(ptr >> 3) + 3] |= rem.b[0];
		}
		else
		{
			printf("SFcode超过了32位\n");
		}
		ptr+= (sfc1.lb);
	}
	else {
		sfc1.code = (sym + Ngap);
		Nsym = sfc1.code;
		sfc1.lb = 0;
		while (Nsym > 0) {
			Nsym >>= 1;
			sfc1.lb++;
		}
		if (sym + Ngap < (1 << lb2)) sfc1.lb = lb2;

		if (sfc1.lb <= 8)
		{
			rem.a = sfc1.code;
			rem.a = rem.a << (16 - binBytePos - sfc1.lb);
			bin[ptr >> 3] |= rem.b[1];
			bin[(ptr >> 3) + 1] |= rem.b[0];
		}
		else if (sfc1.lb <= 16 && sfc1.lb > 8)
		{
			rem.a = sfc1.code;
			rem.a = rem.a << (24 - binBytePos - sfc1.lb);
			bin[ptr >> 3] |= rem.b[2];
			bin[(ptr >> 3) + 1] |= rem.b[1];
			bin[(ptr >> 3) + 2] |= rem.b[0];
		}
		else if (sfc1.lb <= 24 && sfc1.lb > 16)
		{
			printf("SFcode超过了24位\n");
			rem.a = sfc1.code;
			rem.a = rem.a << (32 - binBytePos - sfc1.lb);
			bin[ptr >> 3] |= rem.b[3];
			bin[(ptr >> 3) + 1] |= rem.b[2];
			bin[(ptr >> 3) + 2] |= rem.b[1];
			bin[(ptr >> 3) + 3] |= rem.b[0];
		}
		else
		{
			printf("SFcode超过了32位\n");
		}
		ptr += (sfc1.lb);
	}

	//printf("sfc1.lb = %d\n", sfc1.lb);
	sfc1.code = 0;
	sfc1.lb = 0;
	return sfc1;
}
//
//SFC SFcode(uint sym, uint Nsym)
//{
//	extern int ptr;
//	extern uchar *bin;
//	int binBytePos = ptr & 7;
//	SFC sfc1;
//	sfc1.lb = 0;
//	sfc1.code = 0;
//
//	int code = 0;
//	int lb = (int)floor(log(Nsym) / log(2));
//	int lb2 = lb + 1;
//	int Ngap = (int)(pow(2, lb2) - Nsym);
//	sym--;
//	if (sym <= (Ngap-1))
//	{
//		code = sym;
//
//		
//		if (code == 0 || code == 1)
//		{
//			if ( lb > 1)
//			{
//				ptr += (lb - 1);
//			}
//			binBytePos = ptr & 7;
//			bin[ptr >> 3] |= code << (7 - binBytePos);
//			ptr++;
//		}
//		else
//		{
//			int bits = 0;
//			if (code == 2)
//			{
//				bits = 2;
//			}
//			else
//			{
//				bits = (int)ceil(log(code) / log(2));
//			}
//			if (lb > bits)
//			{
//				printf("出现前面是0,此时ptr = %d\n", ptr);
//				ptr += (lb - bits);
//			}
//			//char* biny = (char*)calloc(bits*2, sizeof(char));
//			//_itoa_s(code, biny, bits + 1,2);
//			//itoa(code, biny, 2);
//			int temp = 0;
//			for (int i = (bits - 1); i >=0; i--)
//			{	
//				temp = code % 2;
//				code >>= 1;
//
//				if (temp == 1 )
//				{
//					binBytePos = (ptr+i) & 7;
//					bin[(ptr + i) >> 3] |= 1 << (7 - binBytePos);
//				}
//			}
//			ptr+=bits;
//			//free(biny);
//		}
//	}
//	else
//	{
//		code = sym + Ngap;
//		lb = lb2;
//
//		if (code == 0 || code == 1)
//		{
//			if (lb > 1)
//			{
//				ptr += (lb - 1);
//			}
//			binBytePos = ptr & 7;
//			bin[ptr >> 3] |= code << (7 - binBytePos);
//			ptr++;
//		}
//		else
//		{
//			//int bits = (int)ceil(log(code) / log(2));
//			int bits = 0;
//			if (code == 2)
//			{
//				bits = 2;
//			}
//			else
//			{
//				bits = (int)ceil(log(code) / log(2));
//			}
//
//			if (lb > bits)
//			{
//				printf("出现前面是0,此时ptr = %d\n", ptr);
//				ptr += (lb - bits);
//			}
//			//char* biny = (char*)calloc(bits*2, sizeof(char));
//			////_itoa_s(code, biny, bits + 1, 2);
//			//itoa(code, biny, 2);
//			//for (int i = 0; i < bits; i++)
//			//{
//			//	if (biny[i] == '1')
//			//	{
//			//		binBytePos = ptr & 7;
//			//		bin[ptr >> 3] |= 1 << (7 - binBytePos);
//			//	}
//			//	ptr++;
//			//}
//			//free(biny);
//			int temp = 0;
//			for (int i = (bits - 1); i >= 0; i--)
//			{
//				temp = code % 2;
//				code >>= 1;
//
//				if (temp == 1)
//				{
//					binBytePos = (ptr + i) & 7;
//					bin[(ptr + i) >> 3] |= 1 << (7 - binBytePos);
//				}
//			}
//			ptr += bits;
//		}
//	}
//
//	return sfc1;
//}
//#include "all.h"
//#include <stdio.h>
//
//#define uint unsigned int
//#define uchar unsigned char
//
//
//SFC SFcode(uchar sym, uchar Nsym)
//{
//	SFC sfc1;
//	uchar Msym = 255, Ngap;
//	sfc1.lb = 0;
//	Ngap = Nsym;
//	sym--;
//
//	/* 计算出Nsym二进制的长度 */
//	while (Nsym > 0){
//		Nsym >>= 1;
//		sfc1.lb++;
//	}
//
//	/** 向二的阶乘靠拢，并计算出其补偿，比如现在Ngap等于30，
//	  *  那(Msym >>= (8 - sfc1.lb)) = 32，此后Ngap=2
//      */
//	Ngap = (Msym >>= (8 - sfc1.lb)) + 1 - Ngap;
//
//	if (sym <= (Ngap - 1)){
//		sfc1.code = (uchar)sym;
//		sfc1.lb--;
//	}
//	else{
//		sfc1.code = (uchar)(sym + Ngap);
//		Nsym = sfc1.code;
//		sfc1.lb = 0;
//        while (Nsym > 0){
//		  Nsym >>= 1;
//		  sfc1.lb++;
//	    }
//	}
//
//	return sfc1;
//}
//
//SFC SFcode(uchar sym, uchar Nsym)//1，3


//SFC SFcode(uint sym, uint Nsym)
//{
//	SFC sfc1;
//	sfc1.lb = floor(log(Nsym) / log(2));
//	int lb2 = sfc1.lb + 1;
//	int Ngap = pow(2, lb2) - Nsym;
//	sym--;
//	if (sym <= Ngap)
//	{
//		sfc1.code = sym;
//	}
//	else
//	{
//		sfc1.code = sym + Ngap;
//		sfc1.lb = lb2;
//	}
//
//	return sfc1;
//}


//SFC SFcode(uchar sym, int Nsym)
//{
//	SFC sfc1;
//	uchar Msym = 255, Ngap;
//	sfc1.lb = 0;
//	Ngap = Nsym;
//	int lb2 = 0;
//
//	/* sym=sym-1; */
//	sym--;
//
//	/* 计算出Nsym二进制的长度 */
//	while (Nsym > 0) {
//		Nsym >>= 1;
//		sfc1.lb++;
//	}
//	lb2 = sfc1.lb;
//
//	/** 向二的阶乘靠拢，并计算出其补偿，比如现在Ngap等于30，
//	  *  那(Msym >>= (8 - sfc1.lb)) = 32，此后Ngap=2
//	  */
//	Ngap = (Msym >>= (8 - sfc1.lb)) + 1 - Ngap;
//
//	if (sym <= (Ngap - 1)) {
//		sfc1.code = (uchar)sym;
//		sfc1.lb--;
//	}
//	else {
//		sfc1.code = (uchar)(sym + Ngap);
//		Nsym = sfc1.code;
//		sfc1.lb = 0;
//		while (Nsym > 0) {
//			Nsym >>= 1;
//			sfc1.lb++;
//		}
//		if (sym + Ngap < (1 << lb2)) sfc1.lb = lb2;
//	}
//
//	//printf("sfc1.lb = %d\n", sfc1.lb);
//
//	return sfc1;
//}
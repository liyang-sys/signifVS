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
//	/* �����Nsym�����Ƶĳ��� */
//	while (Nsym > 0){
//		Nsym >>= 1;
//		sfc1.lb++;
//	}
//
//	/** ����Ľ׳˿�£����������䲹������������Ngap����30��
//	  *  ��(Msym >>= (8 - sfc1.lb)) = 32���˺�Ngap=2
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

#include "all.h"
#include <stdio.h>

#define uint unsigned int
#define uchar unsigned char


SFC SFcode(uint sym, uint Nsym)//1��3
{
	SFC sfc1;
	uint Msym = 1, Ngap;
	sfc1.lb = 0;
	Ngap = Nsym;
	int lb2 = 0;

	/* sym=sym-1; */
	sym--;

	/* �����Nsym�����Ƶĳ��� */
	while (Nsym > 0) {
		Nsym >>= 1;
		sfc1.lb++;
	}
	lb2 = sfc1.lb;

	/** ����Ľ׳˿�£����������䲹������������Ngap����30��
	  *  ��(Msym >>= (8 - sfc1.lb)) = 32���˺�Ngap=2
	  */
	Ngap = (Msym <<= lb2) - Ngap;

	if (sym <= (Ngap - 1)) {
		sfc1.code = sym;
		sfc1.lb--;
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
	}

	//printf("sfc1.lb = %d\n", sfc1.lb);

	return sfc1;
}



#include "all.h"
#include <stdio.h>

#define uint unsigned int
#define uchar unsigned char

DES deSFcode(uchar *bin, uchar Nsym)
{
    union data {
      unsigned int a;
      uchar b[4];
    } rem;
    extern int ptr;
	//ptr = 15;
    int x;
	DES des1;
	int lb = 0;
	uint Msym = 255, Ngap;
	Ngap = Nsym;
	while (Nsym > 0){
		Nsym >>= 1;
		lb++;
	}
	Ngap = (Msym >> (8 - lb)) + 1 - Ngap;
	lb--;
	rem.b[3] = bin[ptr >> 3];
	rem.b[2] = bin[(ptr >> 3) + 1];
	x = ptr & 7;
	des1.sym = ((rem.a << x) >> (32 - lb));
	ptr += lb;  x += lb; x &= 7;

	if (des1.sym > (Ngap - 1)){
        des1.sym = des1.sym << 1;
        des1.sym += ((bin[ptr >> 3] >> (7 - x)) & 1);
        des1.sym = des1.sym - Ngap;
		ptr++;
	}
	des1.sym++;
	return des1;
}

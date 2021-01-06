#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "encoding.h"
#include "parameter_setting.h"
#include "all.h"

int ptr;
uchar *bin;
void test_en_z0()
{
    union data
    {
        unsigned short int a;
        uchar b[4];
    } rem;
    FILE *fp;
    ptr = 0;
    bin = calloc(2048,sizeof(uchar));
    int zLen = 319;
    unsigned int *bigZ = (unsigned int *) calloc (zLen, sizeof(unsigned int));
    fp = fopen("MZ.txt","rb");
    fread(bigZ, sizeof(unsigned int), zLen, fp);
	for (int i = 0; i < zLen; i++)
	{
		printf("%d", bigZ[i]);
	}
	printf("\n");
    int index = 0;
    int indexZ = 0;
    Uint8_Dat z;
    z.len = zLen;
    z.dat = (unsigned char *) calloc (zLen, sizeof(unsigned char));
    int sumZ = 0;
    for(int i = 0 ; i < zLen; i++)
    {
        if(bigZ[i] == 1)
        {
            rem.a = 1;
            rem.a = rem.a << (15 - index);
            z.dat[indexZ >> 3 ] |= rem.b[1];
            z.dat[(indexZ >>3) + 1] |= rem.b[0];
            sumZ++;
        }
        index++;
        indexZ++;
        index &=7;
    }
    en_z0(&z,sumZ);
	printf("\n±àÂëÖ®ºóµÄptr = %d\n bin =%p ", ptr, bin);
	int temp = 0;
	fclose(fp);
}

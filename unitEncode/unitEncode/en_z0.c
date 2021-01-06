#include <stdio.h>
#include <math.h>
#include "all.h"
#include "encoding.h"
#include "parameter_setting.h"

void en_z0(Uint8_Dat* z, int wuns)
{
	union data
	{
		unsigned short int a;
		uchar b[4];
	} rem;
	extern int ptr;
	extern uchar *bin;
	double f0 = 0.4219, f1 = 0.3750, f2 = 0.3125;
	printf("\n en_z0 ��ptr = %d\n", ptr);
	int inv = 0, index = ptr & 7;
	if (2 * wuns > z->len)
	{
		for (int i = 0; i < (((z->len) >> 3) + 1); i++) //��1��Ϊ0�������Ϊ1.
		{
			z->dat[i] ^= 0xff;
		}
		wuns = z->len - wuns;
		inv = 1;
	}
	//printf("\n����ǰz------------------------------------------------------------------\n");
	//for (int i = 0; i < z->len / 8 + 1; i++)
	//{
	//	printf("%x ", z->dat[i]);
	//}
	//printf("\n�����bin------------------------------------------------------------------\n");
	if (wuns >= (z->len) *f0)
	{
		ptr += 3;
		index += 3;
		//index &= 7; //��000 ǰ��:bin��calloc������

		//for (int i = 0; i < (((z->len) >> 3) + 1); i++)//��z������ȥ
		//{
		//	rem.a = z->dat[i];
		//	rem.a = rem.a << (8 - index);
		//	bin[ptr >> 3] |= rem.b[1];
		//	bin[(ptr >> 3) + 1] |= rem.b[0];
		//	ptr += 8; index += 8;
		//	index &= 7;
		//}
		//ptr = ptr - (((z->len) >> 3) + 1) * 8 + z->len;//������ptr

		//rem.a = inv;//��inv
		//rem.a = rem.a << (15 - index);
		//bin[ptr >> 3] |= rem.b[1];
		//bin[(ptr >> 3) + 1] |= rem.b[0];
		//ptr++; index++;
		//index &= 7;

		int t1, t0,t;
		for (int i = 0; i < z->len; i++) {   //copy��ǰʦ�ֵ�
			t1 = i & 7;
			t0 = ptr & 7;
			t = ((z->dat[i >> 3]) >> (7 - t1)) & 1;   
			bin[ptr >> 3] |= (t << (7 - t0));
			ptr++;
		}

		t = ptr & 7;             //inv
		bin[ptr >> 3] |= inv << (7 - t);
		ptr++;
	}
	else if (wuns > (z->len) *f1)
	{
		rem.a = 1;//��001
		rem.a = rem.a << (13 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr += 3; index += 3;
		index &= 7;

		encode_block3(z->dat, z->len);
		index = ptr & 7;

		rem.a = inv;//��inv
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

	}
	else if (wuns > (z->len) *f2)
	{
		rem.a = 2;//��010
		rem.a = rem.a << (13 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr += 3; index += 3;
		index &= 7;

		encode_block5(z->dat, z->len);
		index = ptr & 7;

		//printf("enblock5֮�� ptr = %d\n", ptr);
		rem.a = inv;//��inv
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;
	}
	else if (wuns > (z->len) * 0.2421)
	{
		rem.a = 3;//��011
		rem.a = rem.a << (13 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr += 3; index += 3;
		index &= 7;

		GOL gol = Golomb0(z->dat, z->len);

		rem.a = gol.lastBit;//��lastbit
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		encode_stationary_source_bin(gol.r, gol.lenr, 0, 0, 0, 0, 0, 0);
		index = ptr & 7;//�����ֽ�λ��

		rem.a = inv;//��inv
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		free(gol.r);//����ǵ��ͷ�
	}
	else if (wuns > (z->len) * 0.1797)
	{
		rem.a = 4;//��100
		rem.a = rem.a << (13 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr += 3; index += 3;
		index &= 7;

		GOL gol = Golomb0(z->dat, z->len);

		rem.a = gol.lastBit;//��lastbit
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		encode_stationary_source_bin(gol.r, gol.lenr, 1, 0, 0, 0, 0, 0);
		index = ptr & 7;//�����ֽ�λ��

		rem.a = inv;//��inv
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		free(gol.r);//����ǵ��ͷ�
	}
	else if (wuns > (z->len) * 0.1294)
	{
		rem.a = 5;//��101
		rem.a = rem.a << (13 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr += 3; index += 3;
		index &= 7;

		GOL gol = Golomb0(z->dat, z->len);

		rem.a = gol.lastBit;//��lastbit
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		encode_stationary_source_bin(gol.r, gol.lenr, 2, 0, 0, 0, 0, 0);
		index = ptr & 7;//�����ֽ�λ��

		rem.a = inv;//��inv
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		free(gol.r);//����ǵ��ͷ�
	}
	else if (wuns > (z->len) * 0.0943)
	{
		rem.a = 6;//��110
		rem.a = rem.a << (13 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr += 3; index += 3;
		index &= 7;

		GOL gol = Golomb0(z->dat, z->len);

		rem.a = gol.lastBit;//��lastbit
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		encode_stationary_source_bin(gol.r, gol.lenr, 3, 0, 0, 0, 0, 0);
		index = ptr & 7;//�����ֽ�λ��

		rem.a = inv;//��inv
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		free(gol.r);//����ǵ��ͷ�
	}
	else
	{
		rem.a = 7;//��111
		rem.a = rem.a << (13 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr += 3; index += 3;
		index &= 7;

		GOL gol = Golomb0(z->dat, z->len);

		rem.a = gol.lastBit;//��lastbit
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		encode_stationary_source_bin(gol.r, gol.lenr, 4, 0, 0, 0, 0, 0);
		index = ptr & 7;//�����ֽ�λ��

		rem.a = inv;//��inv
		rem.a = rem.a << (15 - index);
		bin[ptr >> 3] |= rem.b[1];
		bin[(ptr >> 3) + 1] |= rem.b[0];
		ptr++; index++;
		index &= 7;

		free(gol.r);//����ǵ��ͷ�
	}

	//for(int i = 0; i < ((ptr>>3) +1 );i++) 
	//{
	//    printf("%x ",bin[i]);
	//}
}


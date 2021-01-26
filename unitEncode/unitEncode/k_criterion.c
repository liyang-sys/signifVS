//#include <stdio.h>
//#include "all.h"
//#include "encoding.h"
//
//#define uint unsigned int
//#define uchar unsigned char
//
//
///**
// * @brief
// * @param  z[IN]         : �����ͣ�����sep_flg���������ͣ�ΪUint32_Dat����Uint8_dat,�ᱻ���٣�����ǰ����
// * @param  cr[OUT]
// * @param  cr_count[OUT] : ������Ҫ�˱���������NULL
// * @param  r[OUT]        : ������Ҫ�˱���������NULL
// * @param  _1B[OUT]      : ������Ҫ�˱���������NULL
// * @param  p[OUT]        : ������Ҫ�˱���������NULL
// * @param  nc[OUT]       : ������Ҫ�˱���������NULL
// * @param  k[OUT]        : ������Ҫ�˱���������NULL //��Dע�ͣ������ʵ�ʳ��ȶ�1���������һ����ʱ��û������
// * @param  sep_flg[IN]   : ����1����Ϊsep 0 1����������������0������r����
// * @retval none
// * @note
// */
////void K_Criterion(Uint8_Dat* z, float* cr, int* cr_count, Uint32_Dat* r, int* lB, float* p, Uint32_Dat* nc, int* k, int flg)
//void k_criterion(void* z, float* cr, int* cr_count, Uint32_Dat* r, int* lB, float* p, Uint32_Dat* nc, int* k, int sep_flg)
//{
//	float q = 0;
//	int dn = 0;
//	float an = 0;
//	int N0 = 0;
//	GOL gol;
//	int sum = 0;
//	int max = 0;
//
//	//int         k_temp = 0;
//	//Uint32_Dat  nc_temp;
//	//float       p_temp = 0;
//	//Uint32_Dat  r_temp;
//	//int         cr_count_temp = 0;
//	///* �������Ҫ��Щ�����ķ���ֵ���򴫲δ�NULL */
//	//if (k == NULL)          k = &k_temp;
//	//if (nc == NULL)         nc = &nc_temp;
//	//if (p == NULL)          p = &p_temp;
//	//if (r == NULL)          r = &r_temp;
//	//if (cr_count == NULL)   cr_count = &cr_count_temp;
//	int         k_temp = 0;
//	Uint32_Dat  nc_temp;
//	float       p_temp = 0;
//	Uint32_Dat  r_temp;
//	int         cr_count_temp = 0;
//	int         lB_temp = 0;
//	/* �������Ҫ��Щ�����ķ���ֵ���򴫲δ�NULL */
//	if (k == NULL)          k = &k_temp;
//	if (nc == NULL)         nc = &nc_temp;
//	if (p == NULL)          p = &p_temp;
//	if (r == NULL)          r = &r_temp;
//	if (cr_count == NULL)   cr_count = &cr_count_temp;
//	if (lB == NULL)         lB = &lB_temp;
//
//	/* if max(z)<=1 */
//	if (sep_flg == 1) {
//		/* [r,lB,p]=Golomb0(z) ; */
//		gol = Golomb0(((Uint8_Dat *)z)->dat, ((Uint8_Dat *)z)->len);
//		r->dat = gol.r;
//		r->len = gol.lenr;
//		*lB = gol.lastBit;
//		*p = gol.p;
//		/* N0=length(r); */
//		N0 = r->len;
//		//�޸ĵ�
//		//free(((Uint8_Dat *)z)->dat);
//		//((Uint8_Dat *)z)->dat = NULL;
//	}
//	else {
//		/* r=z; */
//		r->dat = ((Uint32_Dat *)z)->dat;
//		r->len = ((Uint32_Dat *)z)->len;
//		//((Uint32_Dat *)z)->dat = NULL; �޸ĵ�
//		/* N0=length(r); */
//		N0 = r->len;
//		/* sum(r); */
//		sum = 0;
//		for (int i = 0; i < r->len; i++) sum += r->dat[i];
//		*p = (float)N0 / sum;
//		*lB = 0;
//	}
//
//	/* q=1-p; */
//	q = 1 - *p;
//
//	/* һЩ������������Ϊlog������Ҫ��ʱ��ȽϾã�������Щ�̶�������ֵ������������һ������� */
//	/* ���ٵ���log�����Ĵ��� */
//	float log_q = log(q);
//
//	/* max(r) */
//	max = 0;
//	for (int i = 0; i < r->len; i++) {
//		if (max < r->dat[i]) max = r->dat[i];
//	}
//
//	/* nc=hist(r, [1:max(r)]); */
//	nc->len = max + 1;
//	nc->dat = (unsigned int *)malloc(sizeof(unsigned int)*(nc->len + 1));
//	memset(nc->dat, 0, sizeof(unsigned int)*(nc->len + 1));
//	for (int i = 0; i < r->len; i++) {
//		nc->dat[(unsigned int)(r->dat[i])] += 1;
//	}
//
//	/* ���Դ���� */
//#if 0
//	int sum = 0;
//	STDOUT_DEBUG("nc�������\n");
//	for (int i = 0; i < nc->len; i++) {
//		STDOUT_DEBUG("%4d:%2d\n", i + 1, nc->dat[i]);
//		sum += nc->dat[i];
//	}
//	STDOUT_DEBUG("���ȣ�%d ��Ϊ%d\n", nc->len, sum);
//	while (1);
//#endif
//
//	/* k=floor(-log(N0)/log(q)); */
//	*k = floor(-log(N0) / log_q);
//
//	/* cr_count=sum(nc(k+1:length(nc))); */
//	*cr_count = 0;
//	for (int i = (*k) + 1; i < nc->len; i++)
//		*cr_count += nc->dat[i];
//
//	/* cr=0; dn=0; */
//	*cr = 0; dn = 0;
//	for (int n = (*k) + 1; n < nc->len; n++) {
//		/* if nc(n)>0 */
//		if (nc->dat[n] > 0) {
//			/* if dn==0 */
//			if (dn == 0) {
//				/* an=nc(n)/N0; */
//				an = (float)nc->dat[n] / N0;
//				/* cr = cr + log(an/p) -(n-1)*log(q) ; */
//				*cr += log(an / (*p)) - (n - 1)*log_q;
//				//STDOUT_DEBUG("(1)cr = %f\n", *cr);
//			}
//			else {
//				/* an=(nc(n)/N0)/(dn+1);   */
//				an = ((float)nc->dat[n] / N0) / (dn + 1);
//				/*  cr = cr + log(an/p) -(n-1-ceil(dn/2))*log(q) ; */
//				*cr += log(an / (*p)) - (n - 1 - ceil((float)dn / 2))*log_q;
//				//STDOUT_DEBUG("(2)cr = %f dn=%d log(q)=%f\n", *cr, dn, log_q);
//			}
//			/* dn=0; */
//			dn = 0;
//		}
//		else {
//			/* dn=0; */
//			dn += 1;
//		}
//	}
//
//	/* ���Դ���� */
//#if 0
//	STDOUT_DEBUG("cr = %f\n", *cr);
//	STDOUT_DEBUG("cr_count = %d\n", *cr_count);
//#endif
//	if (nc == &nc_temp) {
//		free(nc->dat);
//	}
//	if (sep_flg == 1)
//	{
//		if (r == &r_temp) {
//			free(r->dat);
//		}
//	}
//
//	//�޸ĵ�
//	//if (sep_flg == 1)
//	//{
//	//	free(r->dat);
//	//}
//	return;
//}

#include <stdio.h>
#include "all.h"
#include "encoding.h"

#define uint unsigned int
#define uchar unsigned char


/**
 * @brief
 * @param  z[IN]         : �����ͣ�����sep_flg���������ͣ�ΪUint32_Dat����Uint8_dat,�ᱻ���٣�����ǰ����
 * @param  cr[OUT]       : ������Ҫ�˱���������NULL
 * @param  cr_count[OUT] : ������Ҫ�˱���������NULL
 * @param  r[OUT]        : ������Ҫ�˱���������NULL
 * @param  _1B[OUT]      : ������Ҫ�˱���������NULL
 * @param  p[OUT]        : ������Ҫ�˱���������NULL
 * @param  nc[OUT]       : ������Ҫ�˱���������NULL, ʵ��ʹ��������1��ʼ
 * @param  k[OUT]        : ������Ҫ�˱���������NULL //��Dע�ͣ��������û�����ݶ�һ���������һ����ʱ��û������
 * @param  sep_flg[IN]   : ����1����Ϊsep 0 1����������������0������r����
 * @retval none
 * @note
 */
void k_criterion(void* z, float* cr, int* cr_count, Uint32_Dat* r, int* lB, float* p, Uint32_Dat* nc, int* k, int sep_flg)
{
	float   q = 0;
	int     dn = 0;
	float   an = 0;
	int     N0 = 0;
	GOL     gol;
	int     sum = 0;
	int     max = 0;

	int         k_temp = 0;
	Uint32_Dat  nc_temp;
	float       p_temp = 0;
	Uint32_Dat  r_temp;
	int         cr_count_temp = 0;
	int         lB_temp = 0;
	float       cr_temp;
	/* �������Ҫ��Щ�����ķ���ֵ���򴫲δ�NULL */
	if (cr == NULL)         cr = &cr_temp;
	if (k == NULL)          k = &k_temp;
	if (nc == NULL)         nc = &nc_temp;
	if (p == NULL)          p = &p_temp;
	if (r == NULL)          r = &r_temp;
	if (cr_count == NULL)   cr_count = &cr_count_temp;
	if (lB == NULL)         lB = &lB_temp;

	/* if max(z)<=1 */
	if (sep_flg == 1) {
		/* [r,lB,p]=Golomb0(z) ; */
		gol = Golomb0(((Uint8_Dat *)z)->dat, ((Uint8_Dat *)z)->len);
		r->dat = gol.r;
		r->len = gol.lenr;
		*lB = gol.lastBit;
		*p = gol.p;
		/* N0=length(r); */
		N0 = r->len;
	}
	else {
		/* r=z; */
		r->dat = ((Uint32_Dat *)z)->dat;
		r->len = ((Uint32_Dat *)z)->len;
		/* N0=length(r); */
		N0 = r->len;
		/* sum(r); */
		sum = 0;
		for (int i = 0; i < r->len; i++) sum += r->dat[i];
		*p = (float)N0 / sum;
		*lB = 0;
	}

	/* q=1-p; */
	q = 1 - *p;

	/* һЩ������������Ϊlog������Ҫ��ʱ��ȽϾã�������Щ�̶�������ֵ������������һ������� */
	/* ���ٵ���log�����Ĵ��� */
	float log_q = log(q);

	/* max(r) */
	max = 0;
	for (int i = 0; i < r->len; i++) {
		if (max < r->dat[i]) max = r->dat[i];
	}

	/* nc=hist(r, [1:max(r)]); */
	nc->len = max;
	nc->dat = (unsigned int *)malloc(sizeof(unsigned int)*(nc->len + 1));
	memset(nc->dat, 0, sizeof(unsigned int)*(nc->len + 1));
	for (int i = 0; i < r->len; i++) {
		nc->dat[(unsigned int)(r->dat[i])] += 1;
	}

	/* ���Դ���� */
#if 0
	int sum = 0;
	STDOUT_DEBUG("nc�������\n");
	for (int i = 1; i <= nc->len; i++) {
		STDOUT_DEBUG("%4d:%2d\n", i + 1, nc->dat[i]);
		sum += nc->dat[i];
	}
	STDOUT_DEBUG("���ȣ�%d ��Ϊ%d\n", nc->len, sum);
	while (1);
#endif

	/* k=floor(-log(N0)/log(q)); */
	*k = floor(-log(N0) / log_q);

	/* cr_count=sum(nc(k+1:length(nc))); */
	*cr_count = 0;
	for (int i = (*k) + 1; i <= nc->len; i++)
		*cr_count += nc->dat[i];

	/* cr=0; dn=0; */
	*cr = 0; dn = 0;
	for (int n = (*k) + 1; n <= nc->len; n++) {
		/* if nc(n)>0 */
		if (nc->dat[n] > 0) {
			/* if dn==0 */
			if (dn == 0) {
				/* an=nc(n)/N0; */
				an = (float)nc->dat[n] / N0;
				/* cr = cr + log(an/p) -(n-1)*log(q) ; */
				*cr += log(an / (*p)) - (n - 1)*log_q;
				//STDOUT_DEBUG("(1)cr = %f\n", *cr);
			}
			else {
				/* an=(nc(n)/N0)/(dn+1);   */
				an = ((float)nc->dat[n] / N0) / (dn + 1);
				/*  cr = cr + log(an/p) -(n-1-ceil(dn/2))*log(q) ; */
				*cr += log(an / (*p)) - (n - 1 - ceil((float)dn / 2))*log_q;
				//STDOUT_DEBUG("(2)cr = %f dn=%d log(q)=%f\n", *cr, dn, log_q);
			}
			/* dn=0; */
			dn = 0;
		}
		else {
			/* dn=0; */
			dn += 1;
		}
	}

	/* ���Դ���� */
#if 0
	STDOUT_DEBUG("cr = %f\n", *cr);
	STDOUT_DEBUG("cr_count = %d\n", *cr_count);
#endif
	if (nc == &nc_temp) {
		free(nc->dat);
	}


	return;
}


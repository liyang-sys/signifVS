#include <stdio.h>
#include "all.h"

#define uint unsigned int
#define uchar unsigned char

DEC de_Kside (uchar *bin, int lenr, int thd, int lenby)
{
   extern int ptr;
   int i, t, t1, tcb;
   int flg;
   DEC DeKsideSub;
   DEC DeKside;
   DEC DSSNsLenr;
   int codebook = 0, lastBit;
   int sum = 0, sum1 = 0, sum2 = 0;
   int *rA, *rA1, *rA2, *rB, *rB1;
   int tlenc;
   uchar *tempc, *tempc1, *tempc2;
   DEC dec1;
   GOLINV golinv1;

   switch (thd)
   {
   case 2:
      DeKside.r = calloc(lenr, sizeof(int));   //�ǲ��ǿ��Բ�������ռ�
      t = ptr & 7;
      flg = (bin[ptr >> 3] >> (7 - t)) & 1;
      ptr++;
      if (!flg)
      {
         printf("de_Kside 1:\n");
         DeKsideSub = de_KsideSub(bin, lenr);
         for (i = 0; i < DeKsideSub.lenzbit; i++)
         {
            t = i & 7;
            t1 = (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
            DeKside.r[i] = ++t1;
         }
         free(DeKsideSub.z);
      }
      else
      {
         printf("de_Kside 2:\n");
         t = ptr & 7;
         tcb = (bin[ptr >> 3] >> (7 - t)) & 1;    //ȡbin�е�ĳһλ(cbook�ĸ�λ)
         tcb = tcb << 1;
         ptr++;
         t = ptr & 7;
         codebook = ((bin[ptr >> 3] >> (7 - t)) & 1) + tcb + 1;  //(cbook�ĵ�λ����һ
         ptr++;

         t = ptr & 7;
         lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
         ptr++;


         dec1 = decode_stationary_source_sumr(bin, codebook, lenr);
         golinv1 = GolombInv(dec1.r, lastBit, dec1.lenr);

         for (i = 0; i < golinv1.lenzbit; i++)
         {
            t = i & 7;
            t1 = (golinv1.z[i >> 3] >> (7 - t)) & 1;
            DeKside.r[i] = ++t1;
         }
         free(golinv1.z);
      }


      break;
   case 3:
      printf("de_Kside 3:\n");
      DeKsideSub = de_KsideSub(bin, lenr);

      tempc = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);


      rB = malloc((lenr - sum)*sizeof(int));
      for (i = 0; i < (lenr - sum); i++) rB[i] = 1;

      DeKsideSub = de_KsideSub(bin, sum);

      rA = malloc(DeKsideSub.lenzbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.z[(i >> 3)] >> (7 - t)) & 1;
         rA[i] = t1 + 2;
      }
      free(DeKsideSub.z);

      DeKside.r = separate_inv(tempc, rA, rB, lenr,0);

      free(tempc); free(rA); free(rB);
      break;
   case 4:
      printf("de_Kside 4:\n");
      DeKsideSub = de_KsideSub(bin, lenr);
      tempc = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);


      DeKsideSub = de_KsideSub(bin, sum);
      tempc1 = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc1[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum1 += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);

      rB = malloc((sum - sum1)*sizeof(int));
      for (i = 0; i < (DeKsideSub.lenzbit - sum1); i++) rB[i] = 1;

      DeKsideSub = de_KsideSub(bin, sum1);
      rA1 = malloc(DeKsideSub.lenzbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.z[(i >> 3)] >> (7 - t)) & 1;
         rA1[i] = t1 + 2;
      }
      free(DeKsideSub.z);


      rA = separate_inv(tempc1, rA1, rB, sum,0);
      free(rA1); free(tempc1); free(rB);

      rB = malloc((lenr - sum)*sizeof(int));
      for (i = 0; i < (lenr - sum); i++) rB[i] = 1;
      DeKside.r = separate_inv(tempc, rA, rB, lenr,1);

      free(tempc); free(rA); free(rB);
      break;

   case 5:
      printf("de_Kside 5:\n");
      DeKsideSub = de_KsideSub(bin, lenr);


      tempc = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);


      DeKsideSub = de_KsideSub(bin, sum);
      tlenc = DeKsideSub.lenzbit;
      tempc1 = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc1[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum1 += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);


      DeKsideSub = de_KsideSub(bin, sum1);  //3
      int tlens2 = DeKsideSub.lenzbit;
      tempc2 = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc2[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum2 += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);


      DeKsideSub = de_KsideSub(bin, sum2);  //4
      rA2 = malloc(DeKsideSub.lenzbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
         rA2[i] = t1 + 2;
      }
      free(DeKsideSub.z);

      rB = malloc((tlens2 - sum2)*sizeof(int));
      for (i = 0; i < (tlens2 - sum2); i++) rB[i] = 1;

      rA1 = separate_inv(tempc2, rA2, rB, tlens2,0);  //1

      free(tempc2); free(rA2); free(rB);

      rB = malloc((tlenc - sum1)* sizeof(int));
      for (i = 0; i < (tlenc - sum1); i++) rB[i] = 1;

      rA = separate_inv(tempc1, rA1, rB, tlenc,1);  //2

      free(tempc1); free(rA1); free(rB);

      rB = malloc((lenr - sum)*sizeof(int));
      for (i = 0; i < (lenr - sum); i++) rB[i] = 1;

      DeKside.r = separate_inv(tempc, rA, rB, lenr,1);

      free(tempc); free(rA); free(rB);
      break;
   case 6:
      printf("de_Kside 6:\n");
      DeKsideSub = de_KsideSub(bin, lenr);
      tempc = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);


      rB = malloc((lenr - sum)*sizeof(int));
      DeKsideSub = de_KsideSub(bin, DeKsideSub.lenzbit - sum);
      for (i = 0; i < DeKsideSub.lenzbit; i++)  {
         t = i & 7;
         t1 = (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
         rB[i] = ++t1;
      }
      free(DeKsideSub.z);


      DeKsideSub = de_KsideSub(bin, sum);
      tlenc = DeKsideSub.lenzbit;
      tempc1 = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc1[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum1 += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);


      DeKsideSub = de_KsideSub(bin, sum1);
      int lens2 = DeKsideSub.lenzbit;
      tempc2 = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc2[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum2 += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);


      DeKsideSub = de_KsideSub(bin, sum2);

      rA2 = malloc(DeKsideSub.lenzbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
         rA2[i] = t1 + 2;
      }
      free(DeKsideSub.z);


      rB1 = malloc((lens2 - sum2)*sizeof(int));
      for (i = 0; i < (lens2 - sum2); i++) rB1[i] = 1;
      rA1 = separate_inv(tempc2, rA2, rB1, lens2,0);

      free(tempc2); free(rA2); free(rB1);

      rB1 = malloc((tlenc - sum1)*sizeof(int));
      for (i = 0; i < (tlenc - sum1); i++) rB1[i] = 1;
      rA = separate_inv(tempc1, rA1, rB1, tlenc,1);

      free(tempc1); free(rA1); free(rB1);

      DeKside.r = separate_inv(tempc, rA, rB, lenr,2);

      free(tempc); free(rA); free(rB);
      break;

   default:
      printf("de_Kside 7:\n");
      DeKsideSub = de_KsideSub(bin, lenr);

      int s1 = 0;
      for (i = 0; i < (DeKsideSub.lenzbit - 1); i++)
         s1 += DeKsideSub.z[i];

      tempc = calloc((DeKsideSub.lenzbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.z[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.z);

      DeKsideSub = de_KsideSub(bin, DeKsideSub.lenzbit - sum);

      rB = malloc(DeKsideSub.lenzbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lenzbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.z[i >> 3] >> (7 - t)) & 1;
         rB[i] = t1 + 1;
      }
      free(DeKsideSub.z);


      for (i = 0; i < 4; i++)
      {
         t = ptr & 7;
         tcb = ((bin[ptr >> 3] >> (7 - t)) & 1) << (3 - i);
         codebook += tcb;
         ptr++;
      }

      DSSNsLenr = decode_stationary_source_Nsym_lenr(bin, codebook, sum, thd - 2, lenby);

      DeKside.r = separate_inv(tempc, DSSNsLenr.r, rB, lenr,2);

      free(tempc); free(DSSNsLenr.r); free(rB);
      break;
   }
   DeKside.lenr = lenr;

   return DeKside;

}

/*
DEK de_Kside(uchar *bin, int lenr, int thd, int lenb)
{
   extern int ptr;
   int i, t, t1, tcb;
   int flg;
   DEK DeKsideSub;
   DEK DeKside;
   DSSNL DeSNsLr;
   DEC dec1;
   GOLINV golinv1;
   int codebook = 0, lastBit;
   int sum = 0, sum1 = 0, sum2 = 0;
   int *rA, *rA1, *rA2, *rB, *rB1;
   int *runs, lenrs;
   int tlenc;
   uchar *tempc, *tempc1, *tempc2;
   uchar *z;
   int lenz;
   z = calloc((lenr >> 3) + 1, sizeof(int));

   switch (thd)
   {
   case 2:
      DeKside.r = calloc(lenr, sizeof(int));   //�ǲ��ǿ��Բ�������ռ�
      t = ptr & 7;
      flg = (bin[ptr >> 3] >> (7 - t)) & 1;
      ptr++;
      if (!flg)
      {
         printf("de_Kside 1:\n");
         DeKsideSub = de_KsideSub(bin, lenr);
         for (i = 0; i < DeKsideSub.lencbit; i++)
         {
            t = i & 7;
            t1 = (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
            DeKside.r[i] = ++t1;
         }
         free(DeKsideSub.c);
      }
      else
      {
         printf("de_Kside 2:\n");
         t = ptr & 7;
         tcb = (bin[ptr >> 3] >> (7 - t)) & 1;    //ȡbin�е�ĳһλ(cbook�ĸ�λ)
         tcb = tcb << 1;
         ptr++;
         t = ptr & 7;
         codebook = ((bin[ptr >> 3] >> (7 - t)) & 1) + tcb + 1;  //(cbook�ĵ�λ����һ
         ptr++;

         t = ptr & 7;
         lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
         ptr++;

         runs = calloc(lenb, sizeof(int));
         dec1 = decode_stationary_source_sumr (bin, codebook, lenr);
         runs = dec1.r;
         lenrs = dec1.lenr;

         golinv1 = GolombInv(runs, lastBit, lenrs);
         z = golinv1.z;
         lenz = golinv1.lenzbit;
         for (i = 0; i < lenz; i++)
         {
            t = i & 7;
            t1 = (z[i >> 3] >> (7 - t)) & 1;
            DeKside.r[i] = ++t1;
         }
      }

      free(z);
      break;
   case 3:
      printf("de_Kside 3:\n");
      DeKsideSub = de_KsideSub(bin, lenr);
      tempc = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.c);


      rB = malloc((lenr - sum)*sizeof(int));
      for (i = 0; i < (lenr - sum); i++) rB[i] = 1;

      DeKsideSub = de_KsideSub(bin, sum);
      rA = malloc(DeKsideSub.lencbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.c[(i >> 3)] >> (7 - t)) & 1;
         rA[i] = t1 + 2;
      }
      free(DeKsideSub.c);

      DeKside.r = separate_inv(tempc, rA, rB, lenr);

      free(tempc); free(rA); free(rB);
      break;
   case 4:
      printf("de_Kside 4:\n");
      DeKsideSub = de_KsideSub(bin, lenr);            //printf("DeKsideSub.lencbit = %d\n", DeKsideSub.lencbit);
      tempc = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }                                               //printf("sum = %d\n", sum);
      free(DeKsideSub.c);

      DeKsideSub = de_KsideSub(bin, sum);           //printf("DeKsideSub.lencbit = %d\n", DeKsideSub.lencbit);
      tempc1 = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc1[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum1 += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }                                            //printf("sum1 = %d\n", sum1);
      free(DeKsideSub.c);


      DeKsideSub = de_KsideSub(bin, sum1);
      rA1 = malloc(DeKsideSub.lencbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.c[(i >> 3)] >> (7 - t)) & 1;
         rA1[i] = t1+2;
      }
      free(DeKsideSub.c);


      rB = malloc((sum - sum1)*sizeof(int)); //printf("(sum - sum1) = %d\n", (sum - sum1));
      for (i = 0; i < (sum - sum1); i++)
      {
          rB[i] = 1;
      }

      rA = separate_inv(tempc1, rA1, rB, sum);
      for (i = 0; i < sum; i++)
      {
          rA[i] += 1;
      }

      free(rA1); free(tempc1); free(rB);

      rB = malloc((lenr - sum)*sizeof(int));
      for (i = 0; i < (lenr - sum); i++) rB[i] = 1;
      DeKside.r = separate_inv(tempc, rA, rB, lenr);

      free(tempc); free(rA); free(rB);
      break;

   case 5:
      printf("de_Kside 5:\n");
      DeKsideSub = de_KsideSub(bin, lenr);
      tempc = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.c);


      DeKsideSub = de_KsideSub(bin, sum);
      tlenc = DeKsideSub.lencbit;
      tempc1 = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc1[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum1 += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.c);


      DeKsideSub = de_KsideSub(bin, sum1);  //3
      int tlens2 = DeKsideSub.lencbit;
      tempc2 = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc2[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum2 += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.c);


      DeKsideSub = de_KsideSub(bin, sum2);  //4
      rA2 = malloc(DeKsideSub.lencbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
         rA2[i] = t1+2;
      }
      free(DeKsideSub.c);

      rB = malloc((tlens2 - sum2)*sizeof(int));
      for (i = 0; i < (tlens2 - sum2); i++) rB[i] = 1;

      rA1 = separate_inv(tempc2, rA2, rB, tlens2);  //1
      for (i = 0; i < tlens2; i++) rA1[i] += 1;
      free(tempc2); free(rA2); free(rB);

      rB = malloc((tlenc - sum1)* sizeof(int));
      for (i = 0; i < (tlenc - sum1); i++) rB[i] = 1;

      rA = separate_inv(tempc1, rA1, rB, tlenc);  //2
      for (i = 0; i < tlenc; i++) rA[i] += 1;
      free(tempc1); free(rA1); free(rB);

      rB = malloc((lenr - sum)*sizeof(int));
      for (i = 0; i < (lenr - sum); i++) rB[i] = 1;

      DeKside.r = separate_inv(tempc, rA, rB, lenr);

      free(tempc); free(rA); free(rB);
      break;
   case 6:
      printf("de_Kside 6:\n");
      DeKsideSub = de_KsideSub(bin, lenr);
      tempc = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.c);


      rB = malloc((lenr - sum)*sizeof(int));
      DeKsideSub = de_KsideSub(bin, DeKsideSub.lencbit - sum);
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
         rB[i] = ++t1;
      }
      free(DeKsideSub.c);


      DeKsideSub = de_KsideSub(bin, sum);
      tlenc = DeKsideSub.lencbit;
      tempc1 = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc1[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum1 += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.c);


      DeKsideSub = de_KsideSub(bin, sum1);
      int lens2 = DeKsideSub.lencbit;
      tempc2 = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc2[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum2 += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.c);


      DeKsideSub = de_KsideSub(bin, sum2);
      rA2 = malloc(DeKsideSub.lencbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
         rA2[i] = t1 + 2;
      }
      free(DeKsideSub.c);


      rB1 = malloc((lens2 - sum2)*sizeof(int));
      for (i = 0; i < (lens2 - sum2); i++) rB1[i] = 1;
      rA1 = separate_inv(tempc2, rA2, rB1, lens2);
      for (i = 0; i < lens2; i++) rA1[i] += 1;
      free(tempc2); free(rA2); free(rB1);


      rB1 = malloc((tlenc - sum1)*sizeof(int));
      for (i = 0; i < (tlenc - sum1); i++) rB1[i] = 1;
      rA = separate_inv(tempc1, rA1, rB1, tlenc);
      for (i = 0; i < tlenc; i++) rA[i] += 2;
      free(tempc1); free(rA1); free(rB1);

      DeKside.r = separate_inv(tempc, rA, rB, lenr);
      free(tempc); free(rA); free(rB);
      break;

   default:
      printf("de_Kside 7:\n");
      DeKsideSub = de_KsideSub(bin, lenr);
      tempc = calloc((DeKsideSub.lencbit >> 3) + 1, sizeof(uchar));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         tempc[i >> 3] = DeKsideSub.c[i >> 3];
         t = i & 7;
         sum += (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
      }
      free(DeKsideSub.c);

      DeKsideSub = de_KsideSub(bin, DeKsideSub.lencbit - sum);
      rB = malloc(DeKsideSub.lencbit*sizeof(int));
      for (i = 0; i < DeKsideSub.lencbit; i++)
      {
         t = i & 7;
         t1 = (DeKsideSub.c[i >> 3] >> (7 - t)) & 1;
         rB[i] = t1 + 1;
      }
      free(DeKsideSub.c);


      for (i = 0; i < 4; i++)
      {
         t = ptr & 7;
         tcb = ((bin[ptr >> 3] >> (7 - t)) & 1)<<(3-i);
         codebook += tcb;
         ptr++;
      }

     DeSNsLr = decode_stationary_source_Nsym_lenr(bin, codebook, sum, thd - 2, lenb);
      for (i = 0; i < DeSNsLr.lenr; i++)
         DeSNsLr.r[i] += 2;
      DeKside.r = separate_inv(tempc, DeSNsLr.r, rB,lenr);

      free(tempc); free(DeSNsLr.r); free(rB);
      break;
   }
   DeKside.lenr = lenr;

   return DeKside;
}
*/

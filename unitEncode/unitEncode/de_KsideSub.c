#include <stdio.h>
#include "all.h"

#define uint unsigned int
#define uchar unsigned char

DEC de_KsideSub (uchar *bin, int len)
{
   extern int ptr;
   int bn = 0;
   int i, t, t0, t1;
   DEC DeKsideSub;
   int lastBit, inv;
   DEC dec1;
   GOLINV golinv1;

   DeKsideSub.z = calloc((len), sizeof(int));

   t = ptr & 7;
   t0 = (bin[ptr >> 3] >> (7 - t)) & 1;    //ȡbin�е�ĳһλ(cbook�ĸ�λ)
   t0 = t0 << 1;
   ptr++;
   t = ptr & 7;
   bn = ((bin[ptr >> 3] >> (7 - t)) & 1) + t0;  //(cbook�ĵ�λ����һ
   ptr++;


   switch (bn)
   {
   case 0:
      printf("de_KsideSub 1:\n");
      for (i = 0; i < len; i++)         //��c�Ƶ�bin
      {
         t1 = ptr & 7;
         t0 = i & 7;
         t = (bin[ptr >> 3] >> (7 - t1)) & 1;   //ȡbin�е�һλ
         DeKsideSub.z[i >> 3] |= (t << (7 - t0));
         ptr++;
      }
      DeKsideSub.lenzbit = len;
      break;
   case 1:
      printf("de_KsideSub 2:\n");
      dec1 = decode_block3 (bin, len);
      DeKsideSub.z = dec1.z;
      DeKsideSub.lenzbit = dec1.lenzbit;
      break;
   case 2:
      printf("de_KsideSub 3:\n");
      dec1 = decode_block5(bin, len);
      DeKsideSub.z = dec1.z;
      DeKsideSub.lenzbit = dec1.lenzbit;
      break;
   case 3:
      t = ptr & 7;
      bn = (bin[ptr >> 3] >> (7 - t)) & 1;
      ptr++;
      if (!bn)
      {
         printf("de_KsideSub 4:\n");
         t = ptr & 7;
         lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
         ptr++;

         dec1 = decode_stationary_source_sumr(bin, 0, len);

         golinv1 = GolombInv(dec1.r, lastBit, dec1.lenr);
         DeKsideSub.z = golinv1.z;
         DeKsideSub.lenzbit = golinv1.lenzbit;
      }
      else
      {
         t = ptr & 7;
         bn = (bin[ptr >> 3] >> (7 - t)) & 1;
         ptr++;
         if (!bn)
         {
            printf("de_KsideSub 5:\n");
            t = ptr & 7;
            lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
            ptr++;

            dec1 = decode_stationary_source_sumr(bin, 1, len);

            golinv1 = GolombInv(dec1.r, lastBit, dec1.lenr);
            DeKsideSub.z = golinv1.z;
            DeKsideSub.lenzbit = golinv1.lenzbit;
         }
         else
         {
            t = ptr & 7;
            bn = (bin[ptr >> 3] >> (7 - t)) & 1;
            ptr++;
            if (!bn)
            {
               printf("de_KsideSub 6:\n");
               t = ptr & 7;
               lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
               ptr++;

               dec1 = decode_stationary_source_sumr(bin, 2, len);
               golinv1 = GolombInv(dec1.r, lastBit, dec1.lenr);
               DeKsideSub.z = golinv1.z;
               DeKsideSub.lenzbit = golinv1.lenzbit;

            }
            else
            {
               printf("de_KsideSub 7:\n");
               t = ptr & 7;
               lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
               ptr++;

               dec1 = decode_stationary_source_sumr(bin, 3, len);
               golinv1 = GolombInv(dec1.r, lastBit, dec1.lenr);
               DeKsideSub.z = golinv1.z;
               DeKsideSub.lenzbit = golinv1.lenzbit;
            }
         }
      }
      break;
   default: break;
   }

   t = ptr & 7;
   inv = (bin[ptr >> 3] >> (7 - t)) & 1;
   ptr++;

   if (inv)
   for (i = 0; i <= DeKsideSub.lenzbit>>3; i++)   //�Զ೤������ȡ������
   {
        DeKsideSub.z[i] = ~DeKsideSub.z[i];
   }

   return DeKsideSub;
}

/*
DEK de_KsideSub(uchar *bin, int len)
{
   extern int ptr;
   int bn = 0;
   int i, t, t0, t1;
   DEK DeKsideSub;
   DEC dec1;
   GOLINV golinv1;
   int lastBit, inv;
   int *runs, lenrs;
   runs = calloc(len<<3, sizeof(int));
   DeKsideSub.c = calloc((len), sizeof(int));


   t = ptr & 7;
   t0 = (bin[ptr >> 3] >> (7 - t)) & 1;    //ȡbin�е�ĳһλ(cbook�ĸ�λ)
   t0 = t0 << 1;
   ptr++;
   t = ptr & 7;
   bn = ((bin[ptr >> 3] >> (7 - t)) & 1) + t0;  //(cbook�ĵ�λ����һ
   ptr++;

   switch (bn)
   {
   case 0:
      printf("de_KsideSub 1:\n");
      for (i = 0; i < len; i++)   //��c�Ƶ�bin
      {
         t1 = ptr & 7;
         t0 = i & 7;
         t = (bin[ptr >> 3] >> (7 - t1)) & 1;   //ȡbin�е�һλ
         DeKsideSub.c[i >> 3] |= (t << (7 - t0));
         ptr++;
      }
      DeKsideSub.lencbit = len;
      break;
   case 1:
      printf("de_KsideSub 2:\n");
      dec1 = decode_block3 (bin, len);
      DeKsideSub.c = dec1.z;
      DeKsideSub.lencbit = dec1.lenzbit;
      break;
   case 2:
      printf("de_KsideSub 3:\n");
      dec1 = decode_block5(bin, len);
      DeKsideSub.c = dec1.z;
      DeKsideSub.lencbit = dec1.lenzbit;
      break;
   case 3:
      t = ptr & 7;
      bn = (bin[ptr >> 3] >> (7 - t)) & 1;
      ptr++;
      if (!bn)
      {
         printf("de_KsideSub 4:\n");
         t = ptr & 7;
         lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
         ptr++;

         dec1 = decode_stationary_source_sumr(bin, 0, len);
         runs = dec1.r;
         lenrs = dec1.lenr;
         golinv1 = GolombInv(runs, lastBit, lenrs);
         DeKsideSub.c = golinv1.z;
         DeKsideSub.lencbit = golinv1.lenzbit;
      }
      else
      {
         t = ptr & 7;
         bn = (bin[ptr >> 3] >> (7 - t)) & 1;
         ptr++;
         if (!bn)
         {
            printf("de_KsideSub 5:\n");
            t = ptr & 7;
            lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
            ptr++;
            dec1 = decode_stationary_source_sumr(bin, 1, len);
            runs = dec1.r;
            lenrs = dec1.lenr;
            golinv1 = GolombInv(runs, lastBit, lenrs);
            DeKsideSub.c = golinv1.z;
            DeKsideSub.lencbit = golinv1.lenzbit;
         }
         else
         {
            t = ptr & 7;
            bn = (bin[ptr >> 3] >> (7 - t)) & 1;
            ptr++;
            if (!bn)
            {
               printf("de_KsideSub 6:\n");
               t = ptr & 7;
               lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
               ptr++;

               dec1 = decode_stationary_source_sumr(bin, 2, len);
               runs = dec1.r;
               lenrs = dec1.lenr;
               golinv1 = GolombInv(runs, lastBit, lenrs);
               DeKsideSub.c = golinv1.z;
               DeKsideSub.lencbit = golinv1.lenzbit;
            }
            else
            {
               printf("de_KsideSub 7:\n");
               t = ptr & 7;
               lastBit = (bin[ptr >> 3] >> (7 - t)) & 1;
               ptr++;

               dec1 = decode_stationary_source_sumr(bin, 3, len);
               runs = dec1.r;
               lenrs = dec1.lenr;
               golinv1 = GolombInv(runs, lastBit, lenrs);
               DeKsideSub.c = golinv1.z;
               DeKsideSub.lencbit = golinv1.lenzbit;
            }
         }
      }
      break;
   default: break;
   }

   t = ptr & 7;
   inv = (bin[ptr >> 3] >> (7 - t)) & 1;
   ptr++;

   if (inv)
   {
       for (i = 0; i < DeKsideSub.lencbit; i++)   //�Զ೤������ȡ������
       {
           DeKsideSub.c[i] = ~DeKsideSub.c[i];
       }
   }

   free(runs);
   return DeKsideSub;
}
*/

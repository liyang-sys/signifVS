/**
  ******************************************************************************
  * @file    parameter_setting.h
  * @author  H.R
  * @version V1.0.0
  * @date    2020-08-30
  * @brief   ����ͼ���ʽ��һЩȫ�ֲ����궨��
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __PARAMETER_SETTING_H
#define __PARAMETER_SETTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define        FLOAT_FlAG                    0x80000000       //������������˺����룬Ȼ������31λ
                                                              //��0��Ϊ��������Ϊ0,1��Ϊ����
#define        FLOAT_ABS                     0x7FFFFFFF       //������������˺����룬�����ȡ������ֵ

//#define        STDOUT_INFO(fmt, arg...)       printf("  "fmt,##arg)
//#define        STDOUT_ERROR(fmt, arg...)      printf("\n  <<-ERROR->>\n" "  " fmt "\n",##arg)
//#define        STDOUT_DEBUG(fmt, arg...)      printf("  "fmt,##arg)
/************************************* ϣ��������غ궨��(END) ************************************************/

/*************************************** �Զ���ṹ��(START) *******************************************/
typedef struct{
   unsigned char *dat;
   unsigned int  len;
}Uint8_Dat;

typedef struct{
            char *dat;
   unsigned int  len;
}Int8_Dat;

typedef struct{
   unsigned int  *dat;
   unsigned int  len;
}Uint32_Dat;

typedef struct{
            int  *dat;
   unsigned int  len;
}Int32_Dat;

typedef struct{
          float *dat;
   unsigned int  len;
}Float_Dat;

typedef struct {
	Uint32_Dat r;
	int lB;
	Uint32_Dat nr;
	float sumcr;
	float sumcrc;
	Uint32_Dat cf1;
	Uint32_Dat nc1;
	Uint32_Dat cf2;
	Uint32_Dat nc2;
	Uint8_Dat z;
	float pr;
	float cr;
	float cri;
}CR_TEST_RET;

typedef struct {
	Uint8_Dat z;
	Uint32_Dat cfk;
}DE_S_S_SUB;

typedef struct {
	Int32_Dat cf;
	Int32_Dat sn;
	Uint32_Dat cfw;
}DE_S_SUB;
/*************************************** �Զ���ṹ�� (END)  ********************************************/

#endif // __PARAMETER_SETTING_H

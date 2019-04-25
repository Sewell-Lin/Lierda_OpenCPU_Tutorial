/*
 * lierdaDAC.h
 *
 *  Created on: 2018��10��31��
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDADAC_PUBLIC_LIERDADAC_H_
#define SRC_LIB_LIERDADAC_PUBLIC_LIERDADAC_H_

#include <string.h>
#include <stdlib.h>
#include "neulfw.h"
#include "aio_manager.h"
#include "aio_pin.h"
#include "dac.h"


typedef enum{

	LIERDA_DAC_OK   			=  	0,
	LIERDA_DAC_FAILED			=	-1,
	LIERDAS_DAC_ERROR_BAD_PARAMS	=	-3,

}LIERDA_DAC_RET;


/******************************************************************************
 * @������:lierdaDACInit�����ڳ�ʼ��DAC
 * @����:��
 * @����ֵ:���ɹ�������LIERDA_DAC_OK
 * 		 ��ʧ�ܣ�����LIERDA_DAC_FAILED����LIERDAS_DAC_ERROR_BAD_PARAMS
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
LIERDA_DAC_RET lierdaDACInit(void);


/******************************************************************************
 * @������:lierdaDACDeinit������ȡ����ʼ��DAC
 * @����:��
 * @����ֵ:���ɹ�������LIERDA_DAC_OK
 * 		 ��ʧ�ܣ�����LIERDA_DAC_FAILED����LIERDAS_DAC_ERROR_BAD_PARAMS
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
LIERDA_DAC_RET lierdaDACDeinit(void);


/******************************************************************************
 * @������:lierdaDACWriteRaw���������DACֵ
 * @����:uint32 value�������ֵ����Χ(0-1023)
 * @����ֵ:���ɹ�������LIERDA_DAC_OK
 * 		 ��ʧ�ܣ�����LIERDA_DAC_FAILED����LIERDAS_DAC_ERROR_BAD_PARAMS
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
LIERDA_DAC_RET lierdaDACWriteRaw(uint32 value);


/******************************************************************************
 * @������:lierdaDACConnect���������ӵ�AIO����
 * @����:uint32 aio��Ҫ���ӵ�AIO���źţ�0��1��
 * @����ֵ:���ɹ�������LIERDA_DAC_OK
 * 		 ��ʧ�ܣ�����LIERDA_DAC_FAILED����LIERDAS_DAC_ERROR_BAD_PARAMS
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
LIERDA_DAC_RET lierdaDACConnect(uint32 aio);

/******************************************************************************
 * @������:lierdaDACSetRange����������DAC��ѹ��Χ
 * @����:DAC_VOLTAGE_RANGE range����Ҫ���õķ�Χ0-3,0��Ӧ1.2V��1��Ӧ2V��2��Ӧ2.8V��3��Ӧ3.6V
 * @����ֵ:���ɹ�������LIERDA_DAC_OK
 * 		 ��ʧ�ܣ�����LIERDA_DAC_FAILED����LIERDAS_DAC_ERROR_BAD_PARAMS
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
LIERDA_DAC_RET lierdaDACSetRange(DAC_VOLTAGE_RANGE range);


#endif /* SRC_LIB_LIERDADAC_PUBLIC_LIERDADAC_H_ */

/*
 * lierdaADC.h
 *
 *  Created on: 2018��10��15��
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDAADC_PUBLIC_LIERDAADC_H_
#define SRC_LIB_LIERDAADC_PUBLIC_LIERDAADC_H_

#include "aio_functions.h"

typedef enum{

	LIERDA_ADC_OK   			=  	0,
	LIERDA_ADC_FAILED			=	-1,
	LIERDAS_ERROR_BAD_PARAMS	=	-3,

}LIERDA_ADC_RET;



/******************************************************************************
 * @������:lierdaADCInit�����ڳ�ʼ��ADC
 * @����:��
 * @����ֵ:���ɹ�������AIO_FUNC_RET_OK
 * 		 ��ʧ�ܣ�����AIO_FUNC_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
extern LIERDA_ADC_RET lierdaADCInit(void);

/******************************************************************************
 * @������:lierdaADCDeinit������ȡ����ʼ��ADC
 * @����:��
 * @����ֵ:���ɹ�������AIO_FUNC_RET_OK
 * 		 ��ʧ�ܣ�����AIO_FUNC_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
extern LIERDA_ADC_RET lierdaADCDeinit(void);


/******************************************************************************
 * @������:lierdaADCGetRaw�����ڻ�ȡ��ǰvbat��ѹ��ԭʼ��ֵ
 * @����:��ȡ������ֵ
 * @����ֵ:���ɹ�������AIO_FUNC_RET_OK
 * 		 ��ʧ�ܣ�����AIO_FUNC_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
extern LIERDA_ADC_RET lierdaADCGetRaw(uint32 *voltage);


/******************************************************************************
 * @������:lierdaReadAIOPin�����ڻ�ȡ��ǰPIO�ĵ�ѹ
 * @����:uint32 *voltage ��ȡ���ĵ�ѹֵ
 * 		uint8 aio_pin_number ��Ҫ��ȡ��ѹ������
 * @����ֵ:���ɹ�������AIO_FUNC_RET_OK
 * 		 ��ʧ�ܣ�����AIO_FUNC_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
extern AIO_FUNC_RET lierdaReadAIOPin(uint32 *voltage, uint8 aio_pin_number);


/******************************************************************************
 * @������:lierdaAIOCalibrateADC�����ڵ�ѹ��У׼��
 * @����:��
 * @����ֵ:���ɹ�������AIO_FUNC_RET_OK
 * 		 ��ʧ�ܣ�����AIO_FUNC_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
extern AIO_FUNC_RET lierdaAIOCalibrateADC(void);


/******************************************************************************
 * @������:lierdaAIOTempVolt�����ڻ�ȡVBat�ĵ�ѹ���Լ���ǰ�¶ȡ�
 * @����:int16 *temp���¶ȵ���ֵ��
 * 		 uint32 *voltage����ѹ����ֵ
 * @����ֵ:���ɹ�������AIO_FUNC_RET_OK
 * 		 ��ʧ�ܣ�����AIO_FUNC_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
extern AIO_FUNC_RET lierdaAIOTempVolt(int16 *temp,uint32 *voltage);

#endif /* SRC_LIB_LIERDAADC_PUBLIC_LIERDAADC_H_ */

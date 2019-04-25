/*
 * LierdaAdcTest.c
 *
 *  Created on: 2019��4��25��
 *      Author: Administrator
 */
#include "LierdaAdcTest.h"

/******************************************************************************
* @������ ADC������ʼ��
* @����	param : �ղ���
* @����ֵ  ��
******************************************************************************/
void AdcSampInit(void)
{
	lierdaADCInit();  //ADC��ʼ��
	lierdaAIOCalibrateADC();  //��ѹУ׼
}

/******************************************************************************
* @������ Vbat�ŵ�ѹ�ɼ�����
* @����	param : �ղ���
* @����ֵ  ��
******************************************************************************/
void AdcSampTest(void)
{
	uint32 Adc_voltage=0;
	if(lierdaReadAIOPin(&Adc_voltage, AIO0)==AIO_FUNC_RET_OK)
		lierdaLog("AIO0�ŵ�ѹΪ��%d mV",Adc_voltage);
	else
		lierdaLog("AIO0�ŵ�ѹ����ʧ��");
	Adc_voltage=0;
	if(lierdaReadAIOPin(&Adc_voltage, AIO1)==AIO_FUNC_RET_OK)
		lierdaLog("AIO1�ŵ�ѹΪ��%d mV",Adc_voltage);
	else
		lierdaLog("AIO1�ŵ�ѹ����ʧ��");
}


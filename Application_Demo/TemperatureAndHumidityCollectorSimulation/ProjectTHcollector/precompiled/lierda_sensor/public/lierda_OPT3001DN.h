/******************************************************************************
 * @����	OPT3001DN���մ�����ͷ�ļ�
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_OPT3001DN_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_OPT3001DN_H_

#include "neulfw.h"

#define OPT3001_RESULT		     0x00
#define OPT3001_CONFIGURATION	 0x01
#define OPT3001_LOW_LIMIT   	 0x02
#define OPT3001_HIGH_LIMIT  	 0x03
#define OPT3001_MANUFACTURER_ID	 0x7e
#define OPT3001_DEVICE_ID     	 0x7f

#define OPT3001DN_I2C_ADDRESS    0x88

#define OPT3001DN_MANUFACTURER_ID   0x5449
#define OPT3001DN_DEVICE_IDNum      0x3001

/******************************************************************************
* @������	OPT3001DN��ʼ������
* @����	��
* @����ֵ   1���ɹ�  0��ʧ��
******************************************************************************/
uint8 lierda_OPT3001_Init(void);

/******************************************************************************
* @������	��ȡ�������ݺ���
* @����	*Lux  : �����������ֵ�ַ
* @����ֵ  ��
******************************************************************************/
void lierda_OPT3001_UpdataInfo(uint32 *Lux);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_OPT3001DN_H_ */




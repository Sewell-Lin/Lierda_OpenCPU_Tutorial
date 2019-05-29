/******************************************************************************
 * @����	��ʪ�ȴ������������ͷ�ļ�
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/

#ifndef _HDC1000_H_
#define _HDC1000_H_
#include "string.h"
#include "neulfw.h"
#include "lierdaI2C.h"
#include "lierda_app_main.h"
#include "cmsis_os2.h"


typedef struct
{
  uint8   Serial_ID[6];    //5���ֽ�16��������   serial ID of the part
  uint16   Manufacture;
  uint16   Device_ID;
  uint16   Config_Val;
  int16  Temperature;
  int16  Humidity;
}USER_THS_DEV_Typedef;
/////////���㹫ʽ///////////////////////////////////////////
//temper=[(d15:d0)/2^16]*165c-40c
//relative=[(d15:d0)/2^16]*100%
///////////HDC1000�Ĵ���˵��////////////////////////////////

#define I2C_SCL PIN_14
#define I2C_SDA PIN_15

#define HDC1000_I2C_ADDRESS         0x80//0x81 0x82 0x83
#define HDC1000_Read_Temperature    0x00
#define HDC1000_Read_Humidity       0x01
#define HDC1000_Read_Conf           0x02

#define HDC1000_Manufacturer_ID     0xfe
#define HDC1000_DEVICE_ID           0xff      // Pointer
#define HDC1000_ID                  0x1000    // Reset value   DEVICE
//////////////////////////////////////////////////////////////
#define HDC1000_Rst                 15//0x8000��λ
#define HDC1000_Enht                13//0x2000//ʹ�ܼ���
#define HDC1000_Mode                12//0x1000//����ģʽ-Ϊ0ʱ�ֿ�������Ϊ1ʱ�����������¶���ǰ
#define HDC1000_Trest               10//0x0000  0Ϊ�¶�14bit 1Ϊ11bit
#define HDC1000_Rhres               8 //0x0000 14 11 7bit �¶�


/******************************************************************************
* @������	I2C��ʼ������
* @����	��
* @����ֵ   ��
******************************************************************************/
void I2C_init(void);
/********************************************************
 *����: uint8 lierda_HDC1000_Init(void);
 *���: None
 *����: None
 *����: HDC1000��ʼ��, �ɹ� ���� 1��ʧ�ܷ��� 0
 ********************************************************/
uint8 HDC1000_Init(void);

/********************************************************
 *����: void lierda_HDC1000_UpdateInfo
 *���: None
 *����: None
 *����: �û���ȡHDC1000���ݣ��¶ȣ�ʪ�ȣ��з������ͣ�
 ********************************************************/
void HDC1000_UpdateInfo(int16 *Temper,int16 *Humidity);


#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_HDC1000_H_ */


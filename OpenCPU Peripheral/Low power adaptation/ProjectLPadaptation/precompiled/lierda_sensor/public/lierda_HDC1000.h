/******************************************************************************
 * @����	��ʪ�ȴ������������ͷ�ļ�
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_HDC1000_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_HDC1000_H_

#include "neulfw.h"
#include "lierdaI2C.h"

typedef struct
{
  uint8   Serial_ID[6];   //5�ֽ�16��������
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

#define HDC1000_I2C_ADDRESS         0x80//0x81 0x82 0x83
#define HDC1000_Read_Temperature    0x00
#define HDC1000_Read_Humidity       0x01
#define HDC1000_Read_Conf           0x02

#define HDC1000_DEVICE_ID           0xff
#define HDC1000_ID                  0x1000
//////////////////////////////////////////////////////////////
#define HDC1000_Rst                 15//0x8000��λ
#define HDC1000_Enht                13//0x2000//ʹ�ܼ���
#define HDC1000_Mode                12//0x1000//����ģʽ-Ϊ0ʱ�ֿ�������Ϊ1ʱ�����������¶���ǰ
#define HDC1000_Trest               10//0x0000  0Ϊ�¶�14bit 1Ϊ11bit
#define HDC1000_Rhres               8 //0x0000 14 11 7bit �¶�

/********************************************************
 *����: uint8 lierda_HDC1000_Init(void);
 *���: None
 *����: None
 *����: HDC1000��ʼ��, �ɹ� ���� 1��ʧ�ܷ��� 0
 ********************************************************/
uint8 lierda_HDC1000_Init(void);

/********************************************************
 *����: void lierda_HDC1000_UpdateInfo
 *���: None
 *����: None
 *����: �û���ȡHDC1000���ݣ��¶ȣ�ʪ�ȣ��з������ͣ�
 ********************************************************/
void lierda_HDC1000_UpdateInfo(int16 *Temper,int16 *Humidity);

/********************************************************
 *����: void lierda_sensor_I2C_init
 *���: SCL_pin, SDA_pin
 *����: None
 *����: �û���ʼ��I2C�ӿں���
 ********************************************************/
void lierda_sensor_I2C_init(uint8 SCL_pin, uint8 SDA_pin);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_HDC1000_H_ */


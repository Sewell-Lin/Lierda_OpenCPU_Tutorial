/*
 * LierdaLight.c
 *
 *  Created on: 2019��4��24��
 *      Author: Def_Lin
 */
#include "LierdaLight.h"

/******************************************************************************
 * @������	I2c_Init
 * @����    I2C��ʼ��
 * @����    ��
 * @����ֵ  ��
 ******************************************************************************/
static void I2c_Init(void)
{
	sensorI2CHandle.i2c_bus = I2C_BUS1;
	sensorI2CHandle.pin_scl = 14;
	sensorI2CHandle.pin_sda = 15;
	sensorI2CHandle.i2c_address_type = HAL_I2C_ADDRESS_TYPE_7_BIT;
	sensorI2CHandle.i2c_half_time = 256;
	sensorI2CHandle.i2c_mode = HAL_I2C_BUS_MODE_MASTER;
	lierdaI2CInit(&sensorI2CHandle); //��ʼ��I2C
}

/******************************************************************************
 * @������	lierdaOPT3001read
 * @����    ���մ��������Ĵ�������
 * @����    ��
 * @����ֵ  ��
 ******************************************************************************/
static void lierdaOPT3001read(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr,uint8 reg,uint8 *response,uint8 res_len)
{

	lierdaI2CWrite(hi2c,i2c_slave_addr,&reg,1);

	lierdaI2CRead(hi2c,i2c_slave_addr,response,res_len);

}

/******************************************************************************
 * @������	OPT3001Config
 * @����    ���մ������Ĵ������ú���
 * @����    ��
 * @����ֵ  ��
 ******************************************************************************/
static void OPT3001Config(void)
{
    uint8 temp[3] = {0};

    temp[2] = 0x10;
    temp[1] = 0xC4;
    temp[0] = OPT3001_CONFIGURATION;

    lierdaI2CWrite(&sensorI2CHandle,OPT3001DN_I2C_ADDRESS,temp,3);

    osDelay(15);
}

/******************************************************************************
 * @������	GetOPT3001ManufacturerID
 * @����    ��ȡ���մ���������ID
 * @����    ��
 * @����ֵ  �޷���16λ����ID��
 ******************************************************************************/
static uint16 GetOPT3001ManufacturerID(void)
{
    uint8 buffer[2] = {0};

    lierdaOPT3001read(&sensorI2CHandle,OPT3001DN_I2C_ADDRESS, OPT3001_MANUFACTURER_ID, buffer,2);

    return ((buffer[0]<<8)|buffer[1]);
}

/******************************************************************************
 * @������	OPT3001DN_Read_DeviceID
 * @����    ��ȡ���մ������豸ID
 * @����    ��
 * @����ֵ  �޷���16λ����ID��
 ******************************************************************************/
static uint16 OPT3001DN_Read_DeviceID(void)
{
    uint8 buffer[2] = {0};

    lierdaOPT3001read(&sensorI2CHandle,OPT3001DN_I2C_ADDRESS, OPT3001_DEVICE_ID, buffer,2);

    return ((buffer[0]<<8)|buffer[1]);
}


/******************************************************************************
 * @������	lierda_OPT3001_Init
 * @����    ��ʼ�����մ������������
 * @����    ��
 * @����ֵ  0��ʾ�ɹ���1��ʾʧ��
 ******************************************************************************/
uint8 lierda_OPT3001_Init(void)
{

   uint8 ucCount = 0;
   uint16 id = 0;

   I2c_Init();

   OPT3001Config();  // IIC д������

   ucCount = 6;
   do
   {
       id = GetOPT3001ManufacturerID();


       osDelay(20);

   }while((id != OPT3001DN_MANUFACTURER_ID) && ((ucCount -- ) > 1));

   if(ucCount == 0)
   {
       return 0;
   }

   ucCount = 6;

   do
   {
       id = OPT3001DN_Read_DeviceID();

       osDelay(20);

   }while((id != OPT3001DN_DEVICE_IDNum) && ((ucCount--)>1));

   if(ucCount == 0)
   {
       return 0;
   }

   return 1;
}

/******************************************************************************
 * @������	lierda_OPT3001_UpdataInfo
 * @����    ���¹���ǿ������
 * @����    ��
 * @����ֵ  ��
 ******************************************************************************/
void lierda_OPT3001_UpdataInfo(uint32 *Lux)
{
	uint8 buffer[2] = {0};
	uint32 Result = 0;
	uint32 Result1 = 0;

	lierdaOPT3001read(&sensorI2CHandle,OPT3001DN_I2C_ADDRESS, OPT3001_RESULT, buffer,2);

	Result1 = buffer[0];

	Result1 = (Result1 << 8) | buffer[1];

	Result = (1 << ((Result1 & 0xF000) >> 12)) * (Result1 & 0x0FFF); //�õ������ֵ����ʵֵ��100��

	*Lux = Result;
}


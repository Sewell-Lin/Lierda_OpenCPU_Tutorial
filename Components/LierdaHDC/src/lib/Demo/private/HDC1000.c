/******************************************************************************
 * @����	��ʪ�ȴ����������������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "HDC1000.h"


void   HDC1000_Soft_Reset(void);
uint16 HDC1000_Read_DeviceID(void);
void   HDC1000_Setting(void);
uint16 HDC1000_Read_Config(void);
uint16 HDC1000_Read_ManufacturerID(void);
uint8  HDC1000_Read_Temper_Humidity(int16 *nTemper,int16 *nHumidity);
uint8 HDC1000_Writereg(uint8 reg_addr,uint8 *data,uint8 len);
uint8 HDC1000_Rradreg(uint8 reg_addr,uint8 *data_buff,uint8 len);

USER_THS_DEV_Typedef  thsDeviceInfo;

I2C_HandleTypeDef  sensorI2CHandle;  // ������  I2C����� I2C��д����ʹ��


/******************************************************************************
* @������	I2C��ʼ������
* @����	��
* @����ֵ   ��
******************************************************************************/
void I2C_init(void)
{
	sensorI2CHandle.i2c_bus = I2C_BUS1;
	sensorI2CHandle.pin_scl = I2C_SCL;
	sensorI2CHandle.pin_sda = I2C_SDA;
	sensorI2CHandle.i2c_address_type = HAL_I2C_ADDRESS_TYPE_7_BIT;
	sensorI2CHandle.i2c_half_time = 256;
	sensorI2CHandle.i2c_mode = HAL_I2C_BUS_MODE_MASTER;
	lierdaI2CInit(&sensorI2CHandle);
}

/******************************************************************************
* @������	HDC1000��ʼ������
* @����	��
* @����ֵ   1���ɹ�  0��ʧ��
******************************************************************************/
uint8 HDC1000_Init(void)
{
	uint8 ucCount;
	HDC1000_Soft_Reset();
	ucCount = 6;
	do {
		thsDeviceInfo.Device_ID = HDC1000_Read_DeviceID();
		osDelay(20);
	} while ((thsDeviceInfo.Device_ID != HDC1000_ID) && ((ucCount--) > 1));
	   if(ucCount==0)
	     return 0;
	HDC1000_Setting();
	osDelay(10);
	thsDeviceInfo.Config_Val = HDC1000_Read_Config();
	osDelay(10);
	thsDeviceInfo.Manufacture = HDC1000_Read_ManufacturerID();
	osDelay(10);
	//Read Serial ID
	HDC1000_Rradreg(0xfb,thsDeviceInfo.Serial_ID,2);
	osDelay(10);
	HDC1000_Rradreg(0xfc,thsDeviceInfo.Serial_ID+2,2);
	osDelay(10);
	HDC1000_Rradreg(0xfd,thsDeviceInfo.Serial_ID+4,2);
	osDelay(10);
	return 1;
}

/******************************************************************************
* @������    ��ʪ�ȴ��������ݻ�ȡ����
* @����	*Temper      :�¶����ݵ�ַ
* @����	*Humidity    :ʪ�����ݵ�ַ
* @����ֵ   ��
******************************************************************************/
void HDC1000_UpdateInfo(int16 *Temper,int16 *Humidity)
{
	uint8 value = 0x00;
	lierdaI2CWrite(&sensorI2CHandle,HDC1000_I2C_ADDRESS,&value,1);
	osDelay(50);
	HDC1000_Read_Temper_Humidity((int16*) &thsDeviceInfo.Temperature,(int16*) &thsDeviceInfo.Humidity);
	*Temper  =thsDeviceInfo.Temperature;
	*Humidity=thsDeviceInfo.Humidity;
}

uint8 HDC1000_Read_Temper_Humidity(int16 *nTemper,int16 *nHumidity)
{
	uint8 buffer[4];   // ��ȡ4���ֽ����ݣ�ǰ2���ֽ�Ϊ�¶����ݣ���2���ֽ�Ϊʪ������
	uint8 xStatus;
	xStatus=lierdaI2CRead(&sensorI2CHandle,HDC1000_I2C_ADDRESS,buffer, 4);
    *nTemper = (int16)(((((buffer[0]<<8)|buffer[1])/65536.0)*165-40)*100);  // ����100�����
    *nHumidity = (int16)((((buffer[2]<<8)|buffer[3])/65536.0)*100);         // ����100�����
    return xStatus;
}

void HDC1000_Setting(void)
{
    uint16 tempcom = 0;
    uint8 temp[2];
    tempcom = (1<<HDC1000_Mode) ;
    temp[0] = (uint8)(tempcom >> 8);
    temp[1] = (uint8)tempcom;
    HDC1000_Writereg(HDC1000_Read_Conf, temp, 2);
}

uint16 HDC1000_Read_ManufacturerID(void)
{
    uint8 buffer[2];
    HDC1000_Rradreg(HDC1000_Manufacturer_ID, buffer,2);
    return ((buffer[0]<<8)|buffer[1]);
}

uint16 HDC1000_Read_Config(void)
{
    uint8 buffer[2];
    HDC1000_Rradreg(HDC1000_Read_Conf, buffer,2);
    return ((buffer[0]<<8)|buffer[1]);
}
/******************************************************************************
* @������    HDC1000д�Ĵ�������
* @����	reg_addr      :�Ĵ�����ַ
* @����	*data    :���ݵ�ַ
* @����ֵ   0���ɹ�  1��ʧ��
******************************************************************************/
uint8 HDC1000_Writereg(uint8 reg_addr,uint8 *data,uint8 len)
{
	uint8 buff[4]={0};
	buff[0]=reg_addr;
	memcpy(buff+1,data,len);
	if(lierdaI2CWrite(&sensorI2CHandle,HDC1000_I2C_ADDRESS,buff,len+1))
		return 1;
	return 0;
}
/******************************************************************************
* @������    HDC1000���Ĵ�������
* @����	reg_addr      :�Ĵ�����ַ
* @����	*data_buff    :������������buff��ַ
* @����ֵ   0���ɹ�  1��ʧ��
******************************************************************************/
uint8 HDC1000_Rradreg(uint8 reg_addr,uint8 *data_buff,uint8 len)
{
	if(lierdaI2CWrite(&sensorI2CHandle,HDC1000_I2C_ADDRESS,&reg_addr,1))
		return 1;
	if(lierdaI2CRead(&sensorI2CHandle,HDC1000_I2C_ADDRESS,data_buff, len))
		return 1;
	return 0;
}
void HDC1000_Soft_Reset(void)
{
	uint8 temp[2];
	temp[0]=0x80;
	temp[1]=0x00;
	HDC1000_Writereg(HDC1000_Read_Conf,temp,2);
	osDelay(30);  //���������ʱ15ms����
}

uint16 HDC1000_Read_DeviceID(void)
{
    uint8 buffer[2];
    HDC1000_Rradreg(HDC1000_DEVICE_ID,buffer,2);
    return ((buffer[0]<<8)|buffer[1]);
}



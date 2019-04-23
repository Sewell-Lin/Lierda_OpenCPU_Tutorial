
#ifndef SRC_LIB_LIERDAI2C_PUBLIC_LIERDAI2C_H_
#define SRC_LIB_LIERDAI2C_PUBLIC_LIERDAI2C_H_

#include "neulfw.h"
#include "i2c.h"



typedef enum
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;



typedef struct
{
	I2C_BUS       				i2c_bus;
	uint8         				pin_scl;
	uint8         				pin_sda;
	HAL_I2C_ADDRESS_TYPE   		i2c_address_type;
	uint16						i2c_half_time;
	HAL_I2C_BUS_MODE			i2c_mode;
}I2C_HandleTypeDef;

/******************************************************************************
 * @������:lierdaI2CInit�����ڳ�ʼ��i2c
 * @����:I2C_HandleTypeDef *hi2c��ʼ�������þ��
 * @����ֵ:�ɹ�����HAL_OK
 * ʧ�ܷ���HAL_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
HAL_StatusTypeDef lierdaI2CInit(I2C_HandleTypeDef *hi2c);
/******************************************************************************
 * @������:lierdaI2CReadreg������i2c��ȡ�Ĵ���ֵ
 * @����:*hi2c ���þ����
 * 		i2c_slave_addr ��������ַ��
 * 		i2c_rx_reg_addr ��Ҫ��ȡ�ļĴ�����ַ��
 * 		*data ��ȡ����ֵ��
 * 		len ��ȡ�ĳ��ȣ�
 * 		readOnly �Ƿ�ֻ�������ͼĴ�����ַ
 * @����ֵ:����ȡ�ɹ�����0��ʧ�ܷ���1
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
uint8 lierdaI2CReadreg(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr,uint16 i2c_rx_reg_addr, uint8 *data, uint8 len,uint8 readOnly);

/******************************************************************************
 * @������:lierdaI2CWritereg������i2cд��Ĵ���ֵ
 * @����:*hi2c ���þ����
 * 		i2c_slave_addr ��������ַ��
 * 		i2c_rx_reg_addr ��Ҫд��ļĴ�����ַ��
 * 		*data д�����ֵ��
 * 		len ��ȡ�ĳ���
 * @����ֵ:����ȡ�ɹ�����0��ʧ�ܷ���1
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
uint8 lierdaI2CWritereg(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr, uint8 i2c_tx_reg_addr,uint8 *data,uint8 len);

/******************************************************************************
 * @������:lierdaI2CRead������i2c��ȡ�Ĵ���ֵ
 * @����:*hi2c ���þ����
 * 		i2c_slave_addr ��������ַ��
 * 		*data ��ȡ����ֵ��
 * 		data_len ��ȡ�ĳ��ȣ�
 * @����ֵ:����ȡ�ɹ�����0��ʧ�ܷ���1
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
I2C_RET lierdaI2CRead(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr,uint8 *data, uint8 data_len);

/******************************************************************************
 * @������:lierdaI2CWrite������i2cд��Ĵ���ֵ
 * @����:*hi2c ���þ����
 * 		i2c_slave_addr ��������ַ��
 * 		i2c_rx_reg_addr ��Ҫд��ļĴ�����ַ��
 * 		*data д�����ֵ�������Ĵ�����д����ֵ���򽫼Ĵ�����ַ������λ�������Ҫд�����ֵ��
 * 		data_len д��ĳ��ȣ��ó��Ȱ����Ĵ�����ַ��
 * @����ֵ:����ȡ�ɹ�����0��ʧ�ܷ���1
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
I2C_RET lierdaI2CWrite(I2C_HandleTypeDef *hi2c,uint8 i2c_slave_addr,uint8 *data,uint8 data_len);

/******************************************************************************
 * @������:lierdaI2CDeinit������ȡ����ʼ��i2c
 * @����:*hi2c��ʼ�����þ��
 * @����ֵ:�ɹ�����0��ʧ�ܷ���1
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
uint8 lierdaI2CDeinit(I2C_HandleTypeDef *hi2c);





#endif /* SRC_LIB_LIERDAI2C_PUBLIC_LIERDAI2C_H_ */

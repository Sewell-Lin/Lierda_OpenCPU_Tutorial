/******************************************************************************
 * @���� lierda SPI����ͷ�ļ�
 * @��� Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/

#ifndef SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_SOFT_H_
#define SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_SOFT_H_
//include
#include "lierdaGPIO.h"
#include "neulfw.h"
#include "lierda_app_main.h"

typedef enum
{
 LierdaSPI_RET_OK,
 LierdaSPI_RET_ERROR
}LierdaSPI_RET;

typedef struct
{
  uint32 Mode;               /*ָ��SPI����ģʽ */
  uint32 DataSize;          /*ָ��SPI���ݴ�С */
  PIN LierdaSPI_CS;         /*����SPI  CS���� */
  PIN LierdaSPI_SCK;       /*����SPI  SCK���� */
  PIN LierdaSPI_MISO;      /*����SPI  MISO���� */
  PIN LierdaSPI_MOSI;      /*����SPI  MOSI���� */
}SPI_InitTypeDef;


/************************************************
�������� �� lierdaSPISoftInit
��    �� �� SPI��ʼ������
��    �� �� *SPI_Init  SPI��ʼ�������ַ
�� �� ֵ �� �ɹ��� LierdaSPI_RET_OK  ʧ�ܣ�SPI_RET_ERROR
*************************************************/
uint8 lierdaSPISoftInit(SPI_InitTypeDef *SPI_Init);


/************************************************
�������� �� lierdaSPIWriteByte
��    �� �� SPIдһ�ֽ�����
��    �� ��*SPI_Init  SPI�����ַ     TxData  ��������
�� �� ֵ �� �ɹ��� LierdaSPI_RET_OK  ʧ�ܣ�SPI_RET_ERROR
*************************************************/
uint8 lierdaSPIWriteByte(SPI_InitTypeDef *lierda_spi,uint8 TxData);

/************************************************
�������� �� lierdaSPIReadByte
��    �� �� SPI��һ�ֽ�����
��    �� �� *SPI_Init  SPI�����ַ
�� �� ֵ �� ���������ֽ�����
*************************************************/
uint8 lierdaSPIReadByte(SPI_InitTypeDef *lierda_spi);

/************************************************
�������� �� Lierda_SPIDeInit
��    �� �� SPIȡ����ʼ������
��    �� �� *SPI_Init  SPI��ʼ�������ַ
�� �� ֵ ����
*************************************************/
void Lierda_SPIDeInit(SPI_InitTypeDef *SPI_Init);

#endif /* SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_SOFT_H_ */

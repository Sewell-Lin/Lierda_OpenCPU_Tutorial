/*
 * lierdaSPI.h
 *
 *  Created on: 2018��10��18��
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_H_
#define SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_H_



#include "spi.h"
#include "hal_ssp.h"

SPI_BUS       spi_bus;

/******************************************************************************
 * @������:lierdaADCInit�����ڳ�ʼ��SPI
 * @����:SPI_CONFIGURATION spi_config:SPI�������
 * 		SPI_PIN spi_pin��SPI����
 * @����ֵ:���ɹ�������SPI_RET_OK
 * 		 ��ʧ�ܣ�����SPI_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
SPI_RET lierdaSPIInit(SPI_CONFIGURATION spi_config, SPI_PIN spi_pin);

/******************************************************************************
 * @������:lierdaSPIDeinit������ȡ����ʼ��SPI
 * @����:SPI_CONFIGURATION spi_config:SPI�������
 * 		SPI_PIN spi_pin��SPI����
 * @����ֵ:���ɹ�������SPI_RET_OK
 * 		 ��ʧ�ܣ�����SPI_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
SPI_RET lierdaSPIDeinit(void);

/******************************************************************************
 * @������:lierdaSPISendData������д��SPI����
 * @����:SPI_BUS bus:������SPI����
 * 		uint8* cmd_buff������buffer������ĳЩ����Ҫ���豸ʹ��ʱ��NULL����Ӧ��"cmd_len"Ҳ��0
 * 		uint16 cmd_len�������
 * 		uint8* data_buff��д�������
 * 		uint16 data_len��д������ݳ���
 * 		SPI_CALLBACK callback���ص�����
 * @����ֵ:���ɹ�������SPI_RET_OK
 * 		 ��ʧ�ܣ�����SPI_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
SPI_RET lierdaSPISendData(SPI_BUS bus, uint8* cmd_buff,uint16 cmd_len, uint8* data_buff, uint16 data_len, SPI_CALLBACK callback);


/******************************************************************************
 * @������:lierdaSPIRecvData�����ڶ�ȡSPI����
 * @����:SPI_BUS bus:������SPI����
 * 		uint8* cmd_buff������buffer������ĳЩ����Ҫ���豸ʹ��ʱ��NULL����Ӧ��"cmd_len"Ҳ��0
 * 		uint16 cmd_len�������
 * 		uint8* data_buff��д�������
 * 		uint16 data_len��д������ݳ���
 * 		SPI_CALLBACK callback���ص�����
 * 		bool ignore_rx_while_tx��������ʱ���Ƿ���Խ��ա�һ����TRUE
 * @����ֵ:���ɹ�������SPI_RET_OK
 * 		 ��ʧ�ܣ�����SPI_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
SPI_RET lierdaSPIRecvData(SPI_BUS bus, uint8* cmd_buff, uint16 cmd_len, uint8* data_buff, uint16 data_len, SPI_CALLBACK callback, bool ignore_rx_while_tx);

#endif /* SRC_LIB_LIERDASPI_PUBLIC_LIERDASPI_H_ */

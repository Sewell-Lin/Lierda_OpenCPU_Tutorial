/*
 * lierdaCloudConected.h
 *
 *  Created on: 2019��3��11��
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDALIB_PUBLIC_LIERDACLOUDCONNECTED_H_
#define SRC_LIB_LIERDALIB_PUBLIC_LIERDACLOUDCONNECTED_H_


#include "lierda_app_main.h"

#define AT_MLWULDATAEX_STRING_LEN 40

typedef enum
{
	CLOUD_RET_OK 				= 0,
	CLOUD_RET_PARAM_INVALID		= 1,
	CLOUD_RET_MEMORY_ERROR		= 4,
	CLOUD_RET_PROGRESS_ERROR    = 6,
	CLOUD_RET_ERROR				= 22
}CLOUD_RET;

typedef enum
{
    MSG_NON_NORAI = 0x0000,
    MSG_NON_WITHRAI = 0x0001,
    MSG_NON_WITH_SENDBACKRAI = 0x0010,
    MSG_CON_NORAI = 0x0100,
    MSG_CON_WITHRAI = 0x0101
}MSG_MODE;


/******************************************************************************
 * @������:lierdaSendMsgToPlatform��������IoTƽ̨����CON��NON����
 * @����:uint8 *data����Ҫ���͵�����
 * 		uint16 data_len�����ݳ���
 * 		MSG_MODE mode��0x0000: Send NON message;0x0001: Send Non message and carry RELEASE RAI;0x0010: Send NON message and carry RELEASE_AFTER_REPLY RAI.x0100: Send CON message; 0x0101: Send CON message and carry RELEASE_AFTER_REPLY RAI
 * 		uint8 seq_num��0~255������ATָ���ֲ�һ����0
 * 		uint8 isHEX:0��ʾ�����Ϊ�ַ�����1��ʾ������hex
 * @����ֵ:���ɹ�������CLOUD_RET_OK
 * 		 ��ʧ�ܣ�������Ӧ����ԭ��CLOUD_RET
 * @��Ҫ�޸ļ�¼:190311��Def��������
******************************************************************************/
CLOUD_RET lierdaSendMsgToPlatform(uint8 *data, uint16 data_len, MSG_MODE mode, uint8 seq_num,uint8 isHEX);


#endif /* SRC_LIB_LIERDALIB_PUBLIC_LIERDACLOUDCONNECTED_H_ */

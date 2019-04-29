
#ifndef SRC_LIB_LIERDAMODULESTATUS_LIERDA_MODULE_STATUS_H_
#define SRC_LIB_LIERDAMODULESTATUS_LIERDA_MODULE_STATUS_H_

#include "neulfw.h"

#define AT_MAX_STRING_LEN  15
#define AT_PLUS_MAX_STRING_LEN  48

extern char SocketNum[7];

typedef struct
{
	char   charCGATT[AT_MAX_STRING_LEN];
	char   charCSCON[AT_MAX_STRING_LEN];
	char   charCEREG[AT_MAX_STRING_LEN];
	char   charCPSMS[AT_MAX_STRING_LEN];
	char   charNPSMR[AT_MAX_STRING_LEN];
	char   charNMSTATUS[AT_PLUS_MAX_STRING_LEN];
	char   charFOTASTATUS[AT_PLUS_MAX_STRING_LEN];
	char   charSockNum[AT_PLUS_MAX_STRING_LEN];
}lierdaModStatus;



typedef enum
{
	FOTA_NON=0,//��FOTA״̬
	FOTA_DOWNLOADING,//FOTA������
	FOTA_DOWNLOAD_FAILED,//FOTA����ʧ��
	FOTA_DOWNLOADED,//FOTA���ؽ���
	FOTA_UPDATING,//FOTA������
	FOTA_UPDATE_SUCCESS,//FOTA�����ɹ�
	FOTA_UPDATE_FAILED,//FOTA����ʧ��
	FOTA_UPDATE_OVER,//FOTA��������
}lierda_fotaSta;

typedef enum{
	LierdaFota_DataEnable,
	LierdaFota_DataDisable,
}lierdaFota;

extern lierdaModStatus  module_status;

/******************************************************************************
* @������ �����¼�����
* @����	param : �ղ���
* @����ֵ  ��
******************************************************************************/
void lierda_module_status_read(void);


/******************************************************************************
* @������ FOTA״̬��ѯ
* @����	param : �ղ���
* @����ֵ  FOTA״̬��ö�ٱ���
******************************************************************************/
lierda_fotaSta lierda_FotaStatus(void);


/******************************************************************************
* @������    �����ж�FOTA�������ܲ�����ҵ��,���鷢����ǰ���ô˺���
* @����	param : �ղ���
* @����ֵ  LierdaFota_DataEnable����������������ҵ��  LierdaFota_DataDisable�������Է�������ҵ��
******************************************************************************/
lierdaFota lierda_FotaEnableData(void);
#endif



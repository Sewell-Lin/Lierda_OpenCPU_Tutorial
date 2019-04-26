/*
 * LierdaTCPtest.c
 *
 *  Created on: 2019��4��23��
 *      Author: Def_Lin
 */

#include "LierdaTCPtest.h"
#include "lierda_app_main.h"

char userCMDbuff[100] = {0};

/******************************************************************************
 * @������	lierdaTCPcreateSocket
 * @����    ʹ������AT�ӿڴ���TCPsocket
 * @����    ��
 * @����ֵ  ATָ��ؽ��
 ******************************************************************************/
static char *lierdaTCPcreateSocket( void )
{
	char *ret = NULL;

	ret = lierdaATCall("AT+NSOCR=STREAM,6,31001,1", 3000);  //����TCP socket

	socketID = ret[2];

	return ret;
}

/******************************************************************************
 * @������	lierdaTCPconnect
 * @����    ʹ������AT�ӿ�����Ŀ��IP�Ͷ˿�
 * @����    ��
 * @����ֵ  ATָ��ؽ��
 ******************************************************************************/
static char *lierdaTCPconnect( void )
{
	char *ret = NULL;

	memcpy(userCMDbuff, "AT+NSOCO=", 9);

	userCMDbuff[9] = socketID;

	memcpy(userCMDbuff + 10, ",54.222.172.6,31001", 19);

	ret = lierdaATCall(userCMDbuff, 3000);  //����TCP������

	lierdaLog("DBG_INFO:cmd:%s \r\nresult:%s", userCMDbuff,ret);

	memset(userCMDbuff,0,sizeof(100));

	return ret;
}

/******************************************************************************
 * @������	lierdaTCPsendData
 * @����    ����TCP����
 * @����    ��
 * @����ֵ  ��
 ******************************************************************************/
static void lierdaTCPsendData( void )
{
	char *ret = NULL;

	memcpy(userCMDbuff, "AT+NSOSD=", 9);

	userCMDbuff[9] = socketID;

	memcpy(userCMDbuff + 10, ",5,1212121212", 13);

	ret = lierdaATCall(userCMDbuff, 3000);  //��������

	lierdaLog("DBG_INFO:cmd:%s \r\nresult:%s", userCMDbuff,ret);

}

/******************************************************************************
 * @������	lierdaTCPsendTest
 * @����    ʹ��TCP��ƽ̨ͨ��
 * @����    ��
 * @����ֵ  ��
 ******************************************************************************/
void lierdaTCPsendTest( void )
{

	uint8 count = 0;

	for (count = 0; count < 7; count++)
	{
		lierda_module_status_read();  //��ȡ��ǰ��ƽ̨��ע��״̬

		lierdaLog("Current network status is %s", module_status.charCGATT);

		if (strstr(module_status.charCGATT, "CGATT:1") != NULL) //����ƽ̨�Ѿ�ע��ɹ���������
		{
			lierdaLog("Current network status is %s", module_status.charCGATT);

			if (strstr(lierdaTCPcreateSocket(), "OK"))
			{
				if (strstr(lierdaTCPconnect(), "OK"))
				{
					lierdaTCPsendData();

					break;

				}
			}

		}
		else
		{
			lierdaLog("Current network status is %s", module_status.charCGATT);

			osDelay(3000);
		}

	}

	if (count >= 7)
	{
		lierdaLog("The network is poor!");
	}

}



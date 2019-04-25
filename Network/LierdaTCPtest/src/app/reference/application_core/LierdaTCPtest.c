/*
 * LierdaTCPtest.c
 *
 *  Created on: 2019��4��23��
 *      Author: Def_Lin
 */

#include "LierdaTCPtest.h"
#include "lierda_app_main.h"
#include "lierda_module_status.h"
#include "lierdaNNMIData.h"


osThreadAttr_t test_task_attr = { "lierda_test_task"/*��������*/, 0, NULL, 0, NULL,
		(512) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * test_task_handle = NULL;

uint8 socketID;
char tcp_UDPcmd_buff[100]={0};
char udpcmd_buff[20]="AT+NSORF=";//ATָ���ȡ����

static char *lierdaTCPcreateSocket( void )
{
	char *ret = NULL;

	ret = lierdaATCall("AT+NSOCR=STREAM,6,31001,1", 3000);  //����TCP socket

	socketID = ret[2];

	return ret;
}

static char *lierdaTCPconnect( void )
{
	char *ret = NULL;

	memcpy(tcp_UDPcmd_buff, "AT+NSOCO=", 9);

	tcp_UDPcmd_buff[9] = socketID;

	memcpy(tcp_UDPcmd_buff + 10, ",54.222.172.6,31001", 19);

	ret = lierdaATCall(tcp_UDPcmd_buff, 3000);  //����TCP������

	lierdaLog("DBG_INFO:cmd:%s \r\nresult:%s", tcp_UDPcmd_buff,ret);

	memset(tcp_UDPcmd_buff,0,sizeof(100));

	return ret;
}

static void lierdaTCPsendData( void )
{
	char *ret = NULL;

	memcpy(tcp_UDPcmd_buff, "AT+NSOSD=", 9);

	tcp_UDPcmd_buff[9] = socketID;

	memcpy(tcp_UDPcmd_buff + 10, ",5,1212121212", 13);

	ret = lierdaATCall(tcp_UDPcmd_buff, 3000);  //��������

	lierdaLog("DBG_INFO:cmd:%s \r\nresult:%s", tcp_UDPcmd_buff,ret);

}

static void lierdaTCPsendTest( void )
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


static void lierda_test_task(void *param)
{
	UNUSED(param);

	char *udpData_addr=NULL;

	osDelay(3000);

	lierdaTCPsendTest();

	for(;;)
	{
		lierdaSocketAcquireSemaphore();

		lierdaLog("DBG_INFO:�յ�TCP/UDP����");

		udpcmd_buff[9] = socketID;

		memcpy(udpcmd_buff + 10, ",512", 4);

		lierdaLog("DBG_INFO:cmd:%s", udpcmd_buff);

		udpData_addr = lierdaATCall(udpcmd_buff, 3000);  //��ȡ����

		lierdaLog("DBG_INFO:result:%s", udpData_addr);  //��ӡUDP/TCP���е�����

		osDelay(1);

	}

}

void lierda_test_main(void)
{
	test_task_handle = osThreadNew(lierda_test_task, NULL, &test_task_attr); //������������

	if (test_task_handle == NULL)
	{
		lierdaLog("lierda_test_task���񴴽�ʧ��");
	}
}

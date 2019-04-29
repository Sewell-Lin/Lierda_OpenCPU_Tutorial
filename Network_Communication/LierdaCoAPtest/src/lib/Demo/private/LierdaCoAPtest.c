/*
 * LierdaCoAPtest.c
 *
 *  Created on: 2019��4��23��
 *      Author: Def_Lin
 */
#include "lierda_app_main.h"
#include "LierdaCoAPtest.h"
#include "lierda_module_status.h"
#include "stdio.h"

/******************************************************************************
 * @������	lierdaATCalldemo
 * @����    ��������AT�ӿڷ���ATָ��
 * @����    ��
 * @����ֵ  ��
 ******************************************************************************/
static uint8 lierdaATCalldemo(char* cmd, char* result, uint16 timeOut, uint16 num)
{
	uint16 i;
	char *at_cgpaddr_ret = NULL;

	for (i = 0; i < num; i++)
	{
		at_cgpaddr_ret = lierdaATCall(cmd, timeOut);  //����ATָ��

		lierdaLog("DBG_INFO:cmd:%s\r\nresult:%s",cmd,at_cgpaddr_ret);

		if (strstr(at_cgpaddr_ret, result) != NULL)
		{
			return 1;
		}
		else
		{
			osDelay(1000);
		}
	}

	return 0;
}

/******************************************************************************
 * @������	sendCoAPdata
 * @����    ����CoAP����
 * @����    ��
 * @����ֵ  ��
 ******************************************************************************/
void sendCoAPdata(void)
{
	uint8 count = 0;

	for( count = 0;count < 7;count ++ )
	{
		lierda_module_status_read();//��ȡ��ǰ��ƽ̨��ע��״̬

		if(strstr(module_status.charNMSTATUS,"MO_DATA_ENABLED") != NULL)//����ƽ̨�Ѿ�ע��ɹ���������
		{
			lierdaLog("Current network status is %s",module_status.charNMSTATUS);

			lierdaATCalldemo("AT+NMGS=10,A9A1A2A3A4A5A6A7A8A9", "OK",3000, 5);

			break;
		}
		else
		{
			lierdaLog("Current network status is %s",module_status.charNMSTATUS);

			osDelay(3000);
		}

	}

	if( count >= 7 )
	{

		lierdaLog("The network is poor!");

	}


}


/*
 * LierdaCoAPtest.c
 *
 *  Created on: 2019��4��23��
 *      Author: Def_Lin
 */
#include "lierda_app_main.h"
#include "LierdaCoAPtest.h"
#include "lierda_module_status.h"
#include "lierdaNNMIData.h"
#include "stdio.h"

osThreadAttr_t test_task_attr = { "lierda_test_task"/*��������*/, 0, NULL, 0, NULL,
		(512) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * test_task_handle = NULL;

char *at_cgpaddr_ret = NULL;
uint8 nnmi_buff[128];//����buff
uint16 nnmi_buff_len;//�������ݽ��ճ���

void TitlePrint( void );


static uint8 lierdaATCalldemo(char* cmd, char* result, uint16 timeOut, uint16 num)
{
	uint16 i;

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

	return 0;  //����ʧ������
}

static void sendCoAPdata(void)
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

void TitlePrint( void )
{

	lierdaLog("******************************************************************************");
	lierdaLog("                       NB86 EVK����������----CoAP�����շ�                                                                                \r\n");
	lierdaLog(" ������Ƽ�����<www.lierda.com>");
	lierdaLog(" LSD Science&Technology Co.,Ltd");
	lierdaLog(" �������ຼ����һ��·1326��������Ƽ�԰");
	lierdaLog(" ����������������<http://bbs.lierda.com>");
	lierdaLog("******************************************************************************\r\n");

}


static void lierda_test_task(void *param)
{
	UNUSED(param);
	uint8 i = 0;

	osDelay(500);

	TitlePrint();

	osDelay(5000);

	sendCoAPdata();//���Ͳ�������

	lierdaNNMIDataInit();//NNMI�������ݽ��ճ�ʼ��

	for(;;)
	{
		lierdaNNMIDataReceived(nnmi_buff, &nnmi_buff_len, 0xFFFFFFFF); //NNMI�������ݽ���

		if (nnmi_buff_len > 0)
		{
			lierdaLog("�������� :");

			for (i = 0; i < nnmi_buff_len; i++)
			{
				lierdaLog("%x", nnmi_buff[i]);
			}

			memset(nnmi_buff, 0, nnmi_buff_len);

			nnmi_buff_len = 0;
		}
		osDelay(2000);
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

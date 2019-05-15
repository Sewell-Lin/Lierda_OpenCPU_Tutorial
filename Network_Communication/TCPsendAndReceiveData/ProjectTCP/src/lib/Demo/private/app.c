/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;

char readCMDbuff[20] = "AT+NSORF=";//ATָ���ȡ����


/******************************************************************************
* @������ ϵͳ��Ϣ��ӡ
* @����	 *name : ������
* @����ֵ  ��
******************************************************************************/
static void TitlePrint( char *name)
{

 lierdaLog("******************************************************************************");
 lierdaLog("                       NB86 EVK����������----%s                                    \r\n",name);
 lierdaLog(" ������Ƽ�����<www.lierda.com>");
 lierdaLog(" LSD Science&Technology Co.,Ltd");
 lierdaLog(" �������ຼ����һ��·1326��������Ƽ�԰");
 lierdaLog(" ����������������<http://bbs.lierda.com>");
 lierdaLog("******************************************************************************\r\n");
}


/******************************************************************************
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);
	char *ret = NULL;

	osDelay(500);

	TitlePrint("TCP�����շ�");

	osDelay(3000);

	lierdaTCPsendTest();

	for(;;)
	{
		lierdaSocketAcquireSemaphore();

		lierdaLog("DBG_INFO:�յ�TCP/UDP����");

		readCMDbuff[9] = socketID;

		memcpy(readCMDbuff + 10, ",512", 4);

		lierdaLog("DBG_INFO:cmd:%s", readCMDbuff);

		ret = lierdaATCall(readCMDbuff, 3000);  //��ȡ����

		lierdaLog("DBG_INFO:result:%s", ret);  //��ӡUDP/TCP���е�����

		osDelay(1);

	}
}

/******************************************************************************
* @������ �����û��߳�
* @����	param : �ղ���
* @����ֵ  ��
******************************************************************************/
void lierda_App_main(void)
{
	App_task_handle = osThreadNew(lierda_App_task, NULL, &App_task_attr); //������������
	if (App_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task���񴴽�ʧ��");
	}

}

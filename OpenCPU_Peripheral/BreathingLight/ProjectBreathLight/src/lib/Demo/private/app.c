/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;
osTimerId_t LierdaTimer_handle=NULL;


/******************************************************************************
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);uint8 count=0;
	osDelay(500);//�ȴ�ģ���ʼ�����
	lierdaLog("LED Demo");
	Lierda_Led_Init();
	LEDx_StateSet(LED10|LED11|LED12,LED_OFF);
	osTimerStart(LierdaTimer_handle,700);//����һ��700ms��ʱ��
	for (;;)
	{
		switch (count)
		{
		case 0:
			LED10_ON;
			LED12_OFF;
			break;
		case 1:
			LED10_OFF;
			LED11_ON;
			break;
		case 2:
			LED11_OFF;
			LED12_ON;
			break;
		}
		count++;
		if (count == 3)
			count = 0;
		osThreadSuspend(App_task_handle); //��������
	}
}
void Lierda_SoftTimerCallback(void *param)
{
	UNUSED(param);
	osThreadResume(App_task_handle); //700ms���˻ָ�����
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
	LierdaTimer_handle=osTimerNew (Lierda_SoftTimerCallback, osTimerPeriodic, NULL, NULL);
	if (LierdaTimer_handle == NULL)
	{
		lierdaLog("	LierdaTimer_handle��ʱ������ʧ��");
	}
}

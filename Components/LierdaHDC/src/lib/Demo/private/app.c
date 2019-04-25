/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;

/******************************************************************************
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);int16 Temper=0,Humidity=0;
	osDelay(500);//�ȴ�ģ���ʼ�����
	lierdaLog("��ʪ��HDC1000 Demo");
	I2C_init();//I2c���߳�ʼ��
	if(HDC1000_Init())  //HDC1000��ʼ��
		lierdaLog("HDC1000 Init Success");
	else
		lierdaLog("HDC1000 Init Fail");
	for (;;)
	{
		HDC1000_UpdateInfo(&Temper,&Humidity);  //��ʪ�Ȳɼ�
		lierdaLog("Temper:%d  Humidity:%d",Temper/100,Humidity);  //��ʪ��ͨ��AT�ڴ�ӡ
		osDelay(5000);//ÿ5��ɼ�һ���¶�ʪ��
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

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
	UNUSED(param);int16 X=0,Y=0,Z=0;
	osDelay(500);//�ȴ�ģ���ʼ�����
	lierdaLog("���ᴫ����LIS3DH Demo");
	I2c_Init();//I2c���߳�ʼ��
	if(LIS3DH_init())  //HDC1000��ʼ��
		lierdaLog("LIS3DH Init Success");
	else
		lierdaLog("LIS3DH Init Fail");
	for (;;)
	{
		LIS3DHUpdateInfo(&X,&Y,&Z);  //�������ݲɼ�
		lierdaLog("X:%d  Y:%d  Z:%d",X,Y,Z);  //��������ͨ��AT�ڴ�ӡ
		osDelay(5000);//ÿ5��ɼ�һ����������
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

/*
 * LierdaDACtest.c
 *
 *  Created on: 2019��4��23��
 *      Author: Def_Lin
 */
#include "LierdaDACtest.h"
#include "lierda_app_main.h"

osThreadAttr_t test_task_attr = { "lierda_test_task"/*��������*/, 0, NULL, 0, NULL,
		(512) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * test_task_handle = NULL;

static void Lierda_DAC_Init(void)
{
	lierdaDACInit(); //DAC��ʼ��

	lierdaDACSetRange(3);//����DAC�����ѹ��Χ

	lierdaDACConnect(LIERDA_AIO1);//���ڽ���DAC����AIO����
}

static void lierda_test_task(void *param)
{
	UNUSED(param);

	Lierda_DAC_Init();

	osDelay(3000);

	for(;;)
	{
		if(LIERDA_DAC_OK==lierdaDACWriteRaw(1023))//�����ѹ��AIO����
		{
			lierdaLog("DBG_INFO:AIO��ѹ����ɹ�");

			return ;
		}
		else
		{
			lierdaLog("DBG_INFO:AIO��ѹ���ʧ��");

			return ;
		}

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

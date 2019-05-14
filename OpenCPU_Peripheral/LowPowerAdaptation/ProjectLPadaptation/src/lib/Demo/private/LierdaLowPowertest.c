/*
 * LierdaLowPowertest.c
 *
 *  Created on: 2019��4��23��
 *      Author: Def_Lin
 */

#include "LierdaLowPowertest.h"
#include "lierda_app_main.h"

uint8 TestKeyFlag = 2;

/******************************************************************************
 * @������	createMsgQueue ������Ϣ����
 * @����	��
 * @����ֵ  ��
 ******************************************************************************/
void createMsgQueue( void )
{
	msg_QueueId = osMessageQueueNew(2, 1, NULL); //��������

	if (msg_QueueId == NULL)
	{
		lierdaLog("create msg_QueueId failed.");
	}
}

/******************************************************************************
 * @������	TestKeyCallback �����жϻص�����
 * @����	PIN �ж�����
 * @����ֵ  ��
 ******************************************************************************/
static void TestKeyCallback(PIN pin)
{
	if (0==lierdaGPIORead(pin))
	{
		osDelay(10);  //����
		if (lierdaGPIORead(pin)==0)  //GPIO��ȡ����
		{
			while(lierdaGPIORead(pin)==0);

			osMessageQueuePut(msg_QueueId, &TestKeyFlag, 0,osNoWait);//���з�����Ϣ
		}
	}
}


/******************************************************************************
 * @������	TestKeyInit ��ʼ�����԰���
 * @����	PIN �ж�����,GPIO_DIRECTION ����ģʽ
 * @����ֵ  ��
 ******************************************************************************/
void TestKeyInit(PIN key_pin, GPIO_DIRECTION mode)
{
	lierdaGPIOClaim(key_pin, mode);  //GPIO����

	lierdaGPIORegisterCallback(key_pin, GPIO_INTERRUPT_LOW,TestKeyCallback);//���õ͵�ƽ���������ж�
}




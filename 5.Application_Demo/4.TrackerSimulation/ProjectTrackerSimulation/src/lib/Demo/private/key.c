/******************************************************************************
 * @����	��������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "key.h"


/******************************************************************************
 * @������	�����жϻص�����
 * @����	    PIN �ж�����
 * @����ֵ           ��
 ******************************************************************************/
void sos_key_callback(PIN pin)
{
	uint8 temp=key_data;
	if (0==lierdaGPIORead(pin))
	{
		osDelay(10);  //����
		if (lierdaGPIORead(pin)==0)  //GPIO��ȡ����
		{
			while(lierdaGPIORead(pin)==0);
			QueueSendDataFun(&temp);//���з�����Ϣ
		}
	}
}

void Key_Open(void)
{
	Lierda_KEY_Init(KEY2, GPIO_DIRECTION_INPUT); //������ʼ��
}

void Key_Close(void)
{
	Lierda_KEY_Init(KEY2, GPIO_DIRECTION_INPUT); //������ʼ��
	lierdaGPIORelease(KEY2);
}
/******************************************************************************
 * @������	GPIO�������жϳ�ʼ��
 * @����	key_pin:��ʼ����GPIO����
 * @����                 mode�����ŵĹ���ģʽ�����/����
 * @����ֵ  ��
 ******************************************************************************/
void Lierda_KEY_Init(PIN key_pin, GPIO_DIRECTION mode)
{
	lierdaGPIOInit();
	lierdaGPIOClaim(key_pin, mode);  //GPIO����
	lierdaGPIORegisterCallback(key_pin, GPIO_INTERRUPT_LOW,sos_key_callback);//�����жϳ�ʼ��
}
/******************************************************************************
 * @������	GPIO��ȡ����
 * @����	key_pin:��ȡ����
 * @����ֵ   1���ߵ�ƽ     0���͵�ƽ
 ******************************************************************************/
uint8 Lierda_KEY_Read(PIN key_pin)
{
	if (lierdaGPIORead(key_pin))
	{
		osDelay(10);  //����
		if (lierdaGPIORead(key_pin))  //GPIO��ȡ����
			return 1;
		else
			return 0;
	}
	else
		return 0;
}





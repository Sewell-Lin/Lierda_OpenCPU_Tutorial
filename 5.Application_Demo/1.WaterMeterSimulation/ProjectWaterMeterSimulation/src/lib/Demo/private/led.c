/******************************************************************************
 * @����	LED��غ���
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "led.h"

static void PowerOnSta(void);
static void NetConnectSta(void);
static void DeviceRegSta(void);
static void RegCompleteSta(void);
/******************************************************************************
* @������	LED��ʼ��
* @����	        ��
* @����ֵ       ��
******************************************************************************/
void Lierda_Led_Init(void)
{
	lierdaGPIOInit();
	lierdaGPIOClaim(LED_10,GPIO_DIRECTION_OUTPUT);  //LED_10 GPIO����
	lierdaGPIOClaim(LED_11,GPIO_DIRECTION_OUTPUT);  //LED_11 GPIO����
	lierdaGPIOClaim(LED_12,GPIO_DIRECTION_OUTPUT);  //LED_12 GPIO����
}
uint8 GetLEDState(PIN led_pin)
{
	bool PinState;
	uint8 ledState;

	PinState = lierdaGPIORead(led_pin);
	if(PinState)
		ledState = 0;	//��
	else
		ledState = 1;	//��

	return ledState;
}
void SendDataled(void)
{
	LED11_ON;
	osDelay(300);
	LED11_OFF;
}
void ReceiveDataled(void)
{
	LED12_ON;
	osDelay(300);
	LED12_OFF;
}
static void PowerOnSta(void)
{
	LED10_OFF;
	LED11_OFF;
	LED12_OFF;
}
static void NetConnectSta(void)
{
	LED10_ON;
	osDelay(300);
	LED10_OFF;
	osDelay(100);
}
static void DeviceRegSta(void)
{
	LED10_ON;
	osDelay(700);
	LED10_OFF;
	osDelay(300);
}
static void RegCompleteSta(void)
{
	LED10_OFF;
	Lierda_SysValue.RegCompLedflag=1;
}
/******************************************************************************
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
******************************************************************************/
void lierda_LedSta_task(void *param)
{
	UNUSED(param);uint8 count=0;
	osDelay(500);//�ȴ�ģ���ʼ�����
	Lierda_Led_Init();//LED�Ƴ�ʼ��
	for (;;)
	{
		switch(Lierda_SysValue.DeviceSta)
		{
			case Power_ON:
				PowerOnSta();//����״̬
				break;
			case ConnectNet:
				NetConnectSta();//��������״̬
				break;
			case Device_Reg:
				DeviceRegSta();//�豸ע��״̬
				break;
			case Reg_Complete:
				if(Lierda_SysValue.RegCompLedflag==0)
					RegCompleteSta();//ע�����״̬
				break;
			default:; break;
		}
		count++;
		if(count==100)
		{
			count=0;
			lierda_ReadSensor();//1s����һ��������Ϣ
		}
		osDelay(10);
	}
}

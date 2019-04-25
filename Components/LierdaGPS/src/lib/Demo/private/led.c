/******************************************************************************
 * @����	LED��غ���
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "led.h"


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
/**
  * ��������: ���ð���LED�Ƶ�״̬
  * �������: LEDx:����x������Ϊ(1,2,3)����ѡ���Ӧ��LED��
  * ���������state:����LED�Ƶ����״̬��
  *             ��ѡֵ��LED_OFF��LED����
  *                     LED_ON�� LED������
  *                     LED_TOGGLE����תLED
  * �� �� ֵ: ��
  * ˵    �����ú���ʹ�����Ʊ�׼�⺯���ı�̷�������������׼�⺯�����˼�롣
  */
/******************************************************************************
* @������	���ð���LED�Ƶ�״̬
* @����	    LEDx:����x������Ϊ(10,11,12)����ѡ���Ӧ��LED��
* @����		state:����LED�Ƶ����״̬�� ��ѡֵ��LED_OFF��LED���� LED_ON�� LED������LED_TOGGLE����תLED
* @����ֵ       ��
******************************************************************************/
void LEDx_StateSet(uint8 LEDx,LEDState_TypeDef state)
{

  /* �ж����õ�LED��״̬���������ΪLED���� */
  if(state==LED_OFF)
  {
    if(LEDx & LED10)
    	LED10_OFF;/* LED10�� */

    if(LEDx & LED11)
    	LED11_OFF;/* LED11�� */

    if(LEDx & LED12)
    	LED12_OFF;/* LED12�� */
  }
  else if(state==LED_ON) /* ����LED��Ϊ�� */
  {
    if(LEDx & LED10)
    	LED10_ON;/* LED10�� */

    if(LEDx & LED11)
    	LED11_ON;/* LED11�� */

    if(LEDx & LED12)
    	LED12_ON;/* LED12�� */
  }
  else
  {
    if(LEDx & LED10)
      LED10_TOGGLE;/* �������������ת */

    if(LEDx & LED11)
      LED11_TOGGLE;/* �������������ת */

    if(LEDx & LED12)
      LED12_TOGGLE;/* �������������ת */
  }
}

/******************************************************************************
 * @����	LED��غ���
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "led.h"
#include "pwm.h"
#include "lierda_app_main.h"
#include "cmsis_os2.h"
#include "core.h"
#include "stdio.h"

static bool test_pwm_callback_triggered = false;

/******************************************************************************
* @������	LED��ʼ��
* @����	        ��
* @����ֵ       ��
******************************************************************************/
void Lierda_Led_Init(void)
{
	lierdaGPIOInit();
//	lierdaGPIOClaim(LED_10,GPIO_DIRECTION_OUTPUT);  //LED_10 GPIO����
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

static void pwmcallback(PWM_NUMBER pwm)
{
	UNUSED(pwm);
	test_pwm_callback_triggered = true;

	LED10_ON;

	pwm_stop(pwm);
	pwm_close(pwm);

}


void setPWM( void )
{
	PIN pin = PIN_25;
	PWM_NUMBER pwm_num = PWM_NUMBER_0;

	pwm_init();

	if (true == pwm_open(pwm_num, pin)) {
	PWM_BASE_CONFIGURATION pwm_cfg;
	PWM_CYCLE_DATA pwm_cyc_data;// U can also choose PWM_US_DATA or PWM_MS_DATA
//	uint16 duty_cycle;

	//Support output several group PWM waves by setting length. 1 means only have one kind of configuration
	pwm_cfg.length = 1;
	//determine the cycles numbers of PWM
	pwm_cfg.cycles = 200;
	//repeat or Not, if using interrupt callback, make sure false.
	pwm_cfg.repeat = false;
	pwm_register_interrupt(pwm_num, pwmcallback);
	test_pwm_callback_triggered = false;
	//period cycles determine the freq.
	pwm_cyc_data.period_cycles = 50;
	// Duty cycle (parts per 1000)
	pwm_cyc_data.duty_cycle = 500;

	pwm_cycle_start(pwm_num, pwm_cfg, &pwm_cyc_data);

//	while(!test_pwm_callback_triggered);
	}

}



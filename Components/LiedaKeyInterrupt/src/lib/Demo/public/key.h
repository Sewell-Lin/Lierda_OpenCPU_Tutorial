/******************************************************************************
 * @����	����ͷ�ļ�
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_KEY_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_KEY_H_
#include "lierdaGPIO.h"
#include "neulfw.h"
#include "lierda_app_main.h"
#include "cmsis_os2.h"
#include "led.h"


#define KEY2  PIN_12//����0����
void Lierda_KEY_Init(void);
uint8  Lierda_KEY_Read(PIN key_pin);



#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_KEY_H_ */

/******************************************************************************
 * @����	����ͷ�ļ�
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_KEY_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_KEY_H_

#include "lierdaGPIO.h"
#include "cmsis_os2.h"
#include "neulfw.h"
#include "lierda_app_main.h"
#include "app.h"

#define KEY2  PIN_12//����0����
void Lierda_KEY_Init(PIN key_pin,GPIO_DIRECTION mode);
uint8  Lierda_KEY_Read(PIN key_pin);
void sos_key_callback(PIN pin);
void Key_Close(void);
void Key_Open(void);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_KEY_H_ */

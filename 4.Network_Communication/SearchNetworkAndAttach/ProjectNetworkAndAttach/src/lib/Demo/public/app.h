/******************************************************************************
 * @����	�û�����ͷ�ļ�
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_
//include
#include "neulfw.h"
#include "cmsis_os2.h"
#include "string.h"
#include <assert.h>
#include "lierda_app_main.h"
#include "NetConnect.h"
#include "lierda_module_status.h"
#include "lierda_network_dealwith.h"
#include "lierdaCloudConnected.h"


void lierda_App_main(void);
void lierda_App_task(void *param);


#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_ */

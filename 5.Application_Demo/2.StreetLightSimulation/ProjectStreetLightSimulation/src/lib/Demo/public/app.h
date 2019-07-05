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
#include "led.h"
#include "key.h"
#include "lierda_HDC1000.h"
#include "lierda_OPT3001DN.h"
#include "lierda_app_main.h"
#include "ServerProtocol.h"
#include "Lierda_NNMI.h"
#include "Lierda_Hdgps.h"

#define TIMEDREPORT 1
#define IMEI_LEN			15
#define IMSI_LEN			15
#define ICCID_LEN			20
#define SENDCYCLE			30

typedef enum
{
	Power_ON=1,
	ConnectNet,
	Device_Reg,
	Reg_Complete,
}SysSta;
enum datatype{
	Timer_data=1,
	key_data,
	Stachange_data,
};
struct SysGPS_INFO{

			uint8 		Position;
			uint32		longitude;
			uint32		latitude;

};

typedef struct
{
	uint8 StreetLightSta;//·��״̬
	uint32 Illuminance;//����ǿ��
	uint32 SendDataNum;//�������ݰ�����
	uint32 AckDataNum;//Ӧ�����ݰ�����
	uint8 RegCompLedflag;//ע�����LED�����־
	SysSta DeviceSta;//�豸״̬
	char Module_IMEI  [IMEI_LEN+1];
	char Module_IMSI  [IMSI_LEN+1];
	char Module_ICCID [ICCID_LEN+1];
	struct SysGPS_INFO gpsinfo;
}SysValue;

extern SysValue Lierda_SysValue;

//
void TimerControlFun(uint8 timerid,uint8 control,uint32 timer);//��ʱ�����ƺ���
void QueueSendDataFun(uint8 *msg);//���з��ͺ���
void lierda_App_main(void);
void lierda_App_task(void *param);
void Lierda_SoftTimerCallback(void *param);
void lierda_ReadSensor(void);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_ */

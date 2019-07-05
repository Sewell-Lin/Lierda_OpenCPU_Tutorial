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
#include "lierda_app_main.h"
#include "ServerProtocol.h"
#include "Lierda_NNMI.h"
#include "lierdaKVStorage.h"
#include "Lierda_Hdgps.h"
#include "lierda_gps.h"


#define KVID                1


#define TIMEDREPORT            1
#define TIMECOOLLECGPS         2
#define TIMESEARCHGPS          3


#define IMEI_LEN			15
#define IMSI_LEN			15
#define ICCID_LEN			20


#define REPORTCYCLE			60  //�ϱ�����120S
#define COOLLCYCLE		    10	//GPS��������
#define MAXSEARTIME		    10	//�������ʱ��
#define SEARHOLDTIME	    20	//���Ǳ���ʱ��

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
	OpenGPS,
	CloseGPS,

};

enum DeviceMode{
	StandardMode=0,
	TrackerMode,
};

struct SysKvSave{
	enum DeviceMode DeviceMode;//�豸ģʽ
	uint32 CollCycle;//��������
	uint32 ReportCycle;//�ϱ�����
	uint32 MaxSearchTimer;//�������ʱ��
	uint32 GpsHoldTimer;//����ʱ��
} __attribute__((packed));


struct SysGPS_INFO{
			uint8 		SerialNum;//���
			uint8 		SignalQuality;//0X01��Ч   0x00��Ч
			uint32		longitude;//����
			uint32		latitude;//ά��
			uint8 		Position;//��λ
			uint8		UtcTime[3];//UTCʱ��
			uint8		NowTime[3];//��ǰʱ��
} __attribute__((packed));

typedef struct
{
	uint8 GpsHoldFlag;//gps���ֱ�־λ
	uint8 GpsDataNum;//gps�������ݸ���
	uint8 GpsDataNumFullFlag;//gps������������־λ
	uint8 GpsDataGetFlag;//gps���ݻ�ȡ��־λ
	uint8 GpsPositSuc;//GPS��λ�ɹ���־λ
	enum DeviceMode SysMode;//ϵͳģʽ
	uint32 GpsHoldTimer;//����ʱ��
	uint32 CollCycle;//��������
	uint32 ReportCycle;//�ϱ�����
	uint32 MaxSearchTimer;//�������ʱ��
	uint32 SendDataNum;//�������ݰ�����
	uint32 AckDataNum;//Ӧ�����ݰ�����
	uint8 RegCompLedflag;//ע�����LED�����־
	SysSta DeviceSta;//�豸״̬
	struct SysGPS_INFO gpsInfo;
	char Module_IMEI  [IMEI_LEN+1];
	char Module_IMSI  [IMSI_LEN+1];
	char Module_ICCID [ICCID_LEN+1];
}SysValue;


extern struct SysKvSave syskvsave;
extern SysValue Lierda_SysValue;

//
void TimerControlFun(uint8 timerid,uint8 control,uint32 timer);//��ʱ�����ƺ���
void QueueSendDataFun(uint8 *msg);//���з��ͺ���
void lierda_App_main(void);
void lierda_App_task(void *param);
void Lierda_SoftTimerCallback(void *param);
void DeviceParameterSave(void);
void Deviceswitch(void);
#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_ */

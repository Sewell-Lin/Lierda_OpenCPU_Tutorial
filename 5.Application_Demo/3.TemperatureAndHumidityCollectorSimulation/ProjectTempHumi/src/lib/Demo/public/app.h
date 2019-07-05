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

#define KVID                1


#define TIMEDREPORT         1
#define TIMETEMPDWARNING        2
#define TIMEHUMIDWARNING        3


#define IMEI_LEN			15
#define IMSI_LEN			15
#define ICCID_LEN			20

#define HIGHTTEMPW          0X01
#define LOWTEMPW            0X01<<1
#define HIGHTHUMIW          0X01<<2
#define LOWHUMIW            0X01<<3
#define LOWPOWREW           0X01<<4

#define REPORTCYCLE			300  //�ϱ�����300S
#define HIGHTTEMPTHRE		30	//���±�����ֵ30��
#define LOWTTEMPTHRE		10	//���±�����ֵ10��
#define TEMPDELYWARN		1	//�¶���ʱ����1min
#define TEMPCORRECT		    0	//�¶�����ֵ0
#define HIGHTHUMITHRE		80 //��ʪ������ֵ80%
#define LOWTHUMITHRE		20	//��ʪ������ֵ20%
#define HUMIDELYWARN		1	//ʪ����ʱ����1min
#define BATTERYTHRES		20	//��ر�����ֵ20%

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
	TempWarning_data,
	HumiWarning_data,
};
struct SysGPS_INFO{

			uint8 		Position;
			uint32		longitude;
			uint32		latitude;

};

typedef struct
{
	uint16 Temperature;//�¶�
	uint8 humidity;//ʪ��
	uint8 tempwarningflag;//�¶ȱ�����־λ��Ϣ
	uint8 humiwarningfalg;//ʪ�ȱ�����Ϣ��־λ
	uint8 oldtempwarning;//�ϴ��¶ȱ�����Ϣ
	uint8 oldhumiwarning;//�ϴ�ʪ�ȶȱ�����Ϣ
	uint8 warning;//������Ϣ
	uint32 ReportCycle;//�ϱ�����
	uint16 HightTempThreshold;//���±�����ֵ
	uint16 LowTempThreshold;//���±�����ֵ
	uint8  TempDelayWarn;//�¶���ʱ����
	uint16 TempCorrect;//�¶�����ֵ
	uint8  HightHumiThreshold;//��ʪ������ֵ
	uint8  LowHumiThreshold;//��ʪ������ֵ
	uint8  HumiDelayWarn;//ʪ����ʱ����
	uint8  BatteryThreshold;//��ر�����ֵ
	uint32 SendDataNum;//�������ݰ�����
	uint32 AckDataNum;//Ӧ�����ݰ�����
	uint8 RegCompLedflag;//ע�����LED�����־
	SysSta DeviceSta;//�豸״̬
	char Module_IMEI  [IMEI_LEN+1];
	char Module_IMSI  [IMSI_LEN+1];
	char Module_ICCID [ICCID_LEN+1];
}SysValue;
typedef struct
{
	uint32 ReportCycle;//�ϱ�����
	uint16 HightTempThreshold;//���±�����ֵ
	uint16 LowTempThreshold;//���±�����ֵ
	uint8  TempDelayWarn;//�¶���ʱ����
	uint16 TempCorrect;//�¶�����ֵ
	uint8  HightHumiThreshold;//��ʪ������ֵ
	uint8  LowHumiThreshold;//��ʪ������ֵ
	uint8  HumiDelayWarn;//ʪ����ʱ����
	uint8  BatteryThreshold;//��ر�����ֵ
} __attribute__((packed)) kvTempHumi;


extern kvTempHumi LierdatempHumiKv;
extern SysValue Lierda_SysValue;

//
void TimerControlFun(uint8 timerid,uint8 control,uint32 timer);//��ʱ�����ƺ���
void QueueSendDataFun(uint8 *msg);//���з��ͺ���
void lierda_App_main(void);
void lierda_App_task(void *param);
void Lierda_SoftTimerCallback(void *param);
void lierda_ReadSensor(void);
void DeviceParametersave(void);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_ */

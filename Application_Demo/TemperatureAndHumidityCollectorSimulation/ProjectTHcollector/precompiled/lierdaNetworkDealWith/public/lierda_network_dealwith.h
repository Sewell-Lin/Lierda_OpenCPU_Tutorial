/*
 * lierda_network_dealwith.h
 *
 *  Created on: 2019��4��12��
 *      Author:
 */
#ifndef _LIERDA_NETWORK_DEALWITH_H_
#define _LIERDA_NETWORK_DEALWITH_H_

#include "neulfw.h"

#define IMEI_LEN			15
#define IMSI_LEN			15
#define ICCID_LEN			20

//�˽ṹ��Ϊϵͳ�õ���һЩȫ�ֱ�����Ϊ��ͳһ����ŵ�һ���ṹ���ڣ������������������鶼�ŵ�����
typedef struct NET_AppSystem1{

	uint8 DiscreteCGATT_State;
	//�ϵ��ʼ���Ͷ�������ģ�������ϢIMEI, IMSI, ICCID
	char Module_IMEI  [IMEI_LEN+1];
	char Module_IMSI  [IMSI_LEN+1];
	char Module_ICCID [ICCID_LEN+1];

	char RandomSeed[9];		 // ������ɢ������ʱ���ӵ�����   IMEI��8λ
	uint16 DiscreteFactor;   // ��ɢ������ʱ���� ��λ��s
	uint8 CGATT_Status;      // ģ���Ƿ���������?  1Ϊ�����ϣ�0Ϊδ����
	uint8  NetCyclicNumber;  // ����ѭ������

}NET_AppSystem;

extern NET_AppSystem  AppSysTem;

// ��ö������Ϊ��ʼ�����ò���ʱ���صĴ�������
typedef enum
{
	NET_PARA_OK = 0x00,
	NET_FIRST_PARA_ERROR = 0x01,
	NET_SECOND_PARA_ERROR = 0x02,
	NET_EDRX_ERROR = 0x03,
	NET_PSM_ERROR = 0x04,
	NET_CYCLIC_NUMBER_ERROR = 0x05,
	NET_QUERY_CGATT_TIME_ERROR = 0x06,
	NET_NCDP_VALUE_ERROR = 0x07,
}NET_PARA_RET;

//�˽ṹ������Ҫ���浽KV���Ĳ�������
struct NET_Local_Para{
	uint8  net_para_flag;
	uint8  first_disperse_factor;  // ��һ����ɢ�������� (>=1)
	uint8  second_disperse_factor; // �ڶ�����ɢ�������� (>=1)
	uint8  edrx_mode;              // 1ΪPSMģʽ��0�෴
	uint8  psm_mode;               // 1ΪeDRXģʽ��0�෴
	uint8  net_cyclic_number;      // �ظ�ִ�������Ĵ���
	uint8  query_cgatt_time;       // ��λ min, ÿ����������ʱ�䣬ѭ����ѯCGATTʱ��
    char   ncdp_value[25];         // NCDP������IP,port
}__attribute__((packed));

struct NUESTATS{
	int16 	Rsrp;   // �з���
	int16 	Snr;    // �з���
	uint32	Cell_ID;
	uint8 	Coverage_level;
	uint16   PCI;
}__attribute__((packed));

extern struct NUESTATS ModuleState;
/********************************************************
 *����: lierda_net_local_config_init
 *���: None
 *����: None
 *����ֵ:
 *����: ��ʼ�����ò���
 ********************************************************/
extern NET_PARA_RET lierda_net_local_config_init(struct NET_Local_Para *p_local_para);

/********************************************************
 *����: lierda_network_dealwith_task_enable
 *���: None
 *����: None
 *����ֵ:
 *����: ����������NB����ע�������߳�
 ********************************************************/
extern void lierda_network_dealwith_task_enable(void);

/********************************************************
 *����: lierda_IOT_connect_state
 *���: None
 *����: None
 *����ֵ: 1:������IOTƽ̨, 0:δ����
 *����: NBģ���Ƿ����IOTƽ̨
 ********************************************************/
extern uint8 lierda_IOT_connect_state(void);

/********************************************************
 *����: lierda_CGATT_state
 *���: None
 *����: None
 *����ֵ: 1:����������, 0:δ����
 *����: NBģ���Ƿ���������
 ********************************************************/
extern uint8 lierda_CGATT_state(void);

#endif /* _LIERDA_NETWORK_DEALWITH_H_ */


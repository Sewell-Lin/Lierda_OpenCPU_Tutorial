/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"
#include "lierda_network_dealwith.h"
#include "lierdaNNMIData.h"
#include "lierdaCloudConnected.h"
#include "stdio.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;

osThreadAttr_t server_task_attr = { "lierda_server_task"/*��������*/, 0, NULL, 0, NULL,
		(512) /*�����ջ��С*/, 12/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * server_task_handle = NULL;


int16 Temper=0,Humidity=0;

static void local_para_init(void)
{
	NET_PARA_RET  cause;
  	struct NET_Local_Para  net_local_pa =
  	{
  	   1,
       8, //��һ����ɢ�������� (>=1)
  	   30, //�ڶ�����ɢ�������� (>=1)
	   0,
	   0,
	   3,
       2,
	   {"180.101.147.115,5683"},
  	};

  	cause = lierda_net_local_config_init(&net_local_pa);
  	if (cause != 0)
  	{
  		lierdaLog("lierda_net_local_config_init,fail,%d\r\n",cause);
  	}
}

static void TitlePrint( char *name);
/******************************************************************************
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);


	osDelay(500);//�ȴ�ģ���ʼ�����
	TitlePrint("��ʪ��HDC1000����");
	I2C_init();//I2c���߳�ʼ��
	if(HDC1000_Init())  //HDC1000��ʼ��
		lierdaLog("HDC1000 Init Success");
	else
		lierdaLog("HDC1000 Init Fail");

	local_para_init();

	lierda_network_dealwith_task_enable();

	for (;;)
	{
		HDC1000_UpdateInfo(&Temper,&Humidity);  //��ʪ�Ȳɼ�
		lierdaLog("Temper:%d  Humidity:%d",Temper/100,Humidity);  //��ʪ��ͨ��AT�ڴ�ӡ
		osDelay(5000);//ÿ5��ɼ�һ���¶�ʪ��
	}
}

void lierda_server_task(void *param)
{
	UNUSED(param);

	uint8 recvBuffer[128] = {0};//��������
	uint16 recvBufferLenth;//�������ݽ��ճ���
	CLOUD_RET ret = CLOUD_RET_OK;
	uint8 sendBuffer[100] = {0};

	lierdaNNMIDataInit();

	for(;;)
	{
		lierdaNNMIDataReceived(recvBuffer, &recvBufferLenth, 0xFFFFFFFF);

		if(recvBuffer[0] == 0xff && recvBuffer[1] == 0xaa)
		{
			memset(sendBuffer,0,sizeof(100));

			sprintf((char *)sendBuffer,"FFAAD0D0%d%d",Temper/100,Humidity);


			ret = lierdaSendMsgToPlatform(sendBuffer, strlen((const char *)sendBuffer), MSG_NON_WITH_SENDBACKRAI, 0,0);

			if(ret == 0)
			{
				lierdaLog("update info is ok");
			}
			else
			{
				lierdaLog("update info is failed");
			}


		}
	}

}




/******************************************************************************
* @������ �����û��߳�
* @����	param : �ղ���
* @����ֵ  ��
******************************************************************************/
void lierda_App_main(void)
{
	App_task_handle = osThreadNew(lierda_App_task, NULL, &App_task_attr); //������������
	if (App_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task���񴴽�ʧ��");
	}

	server_task_handle = osThreadNew(lierda_server_task, NULL, &server_task_attr); //������������
		if (App_task_handle == NULL)
		{
			lierdaLog("	lierda_App_task���񴴽�ʧ��");
		}
}

/******************************************************************************
* @������ ϵͳ��Ϣ��ӡ
* @����	 *name : ������
* @����ֵ  ��
******************************************************************************/
static void TitlePrint( char *name)
{

 lierdaLog("******************************************************************************");
 lierdaLog("                       NB86 EVK����������----%s                                    \r\n",name);
 lierdaLog(" ������Ƽ�����<www.lierda.com>");
 lierdaLog(" LSD Science&Technology Co.,Ltd");
 lierdaLog(" �������ຼ����һ��·1326��������Ƽ�԰");
 lierdaLog(" ����������������<http://bbs.lierda.com>");
 lierdaLog("******************************************************************************\r\n");
}

/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;

osThreadAttr_t Key_task_attr = { "lierda_Key_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * Key_task_handle = NULL;
osThreadAttr_t NNMI_task_attr = { "lierda_NNMI_task"/*��������*/, 0, NULL, 0, NULL,
		(128) /*�����ջ��С*/, 12/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * NNMI_task_handle = NULL;
osTimerId_t LierdaTimer_handle=NULL;
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
	TitlePrint("������������");
	NetConnect_Init();//�������ӳ�ʼ��
	for (;;)
	{
		lierda_module_status_read();//�����¼�״̬
		if(strstr(module_status.charCEREG,"+CEREG:1"))//�鿴���������Ƿ�����
		{
			if(strstr(module_status.charNMSTATUS,"MO_DATA_ENABLED"))
			{
				lierdaLog("IoTƽ̨���ӳɹ�");
				if(lierda_FotaEnableData()==LierdaFota_DataEnable)
				{
					lierdaLog("��FOTA�¼����������Է�����");
					lierdaSendMsgToPlatform((uint8 *)"123456789", 9,MSG_NON_NORAI, 0,1);//��IoTƽ̨������
				}
				else
					lierdaLog("FOTA�У������Է�����");
			}
			else
				lierdaLog("IoTƽ̨����ʧ�ܣ������豸�Ƿ�ע��");
		}
		else
			lierdaLog("����Ͽ��������豸����");
		osDelay(5000);//5�����һ���¼�״̬
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

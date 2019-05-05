/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"


osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;

extern uint8 TestKeyFlag;

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



/******************************************************************************
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);

	uint8 temp = 0;
	int16 LIS3DH_X = 0,LIS3DH_Y = 0,LIS3DH_Z = 0;

	osDelay(500);

	TitlePrint("�͹��Ĳ���");

	createMsgQueue();

	lierdaLog("waiting init complete.");

	osDelay(3000);

	TestKeyInit(PIN_12,GPIO_DIRECTION_INPUT);

	I2c_Init();

	LIS3DH_init();

	lierdaLog("press k2 button to get LIS3DH data.");

	for (;;)
	{
		if (osMessageQueueGet(msg_QueueId, &temp, NULL, 0xffffffff) == osOK)//�ȴ���Ϣ���У�����������״̬ʱ����͹���ģʽ
		{
			if(temp == TestKeyFlag)
			{

				LIS3DHUpdateInfo(&LIS3DH_X, &LIS3DH_Y, &LIS3DH_Z);  //�������ݻ�ȡ

				lierdaLog("X��:%d,Y��:%d,Z��:%d", LIS3DH_X, LIS3DH_Y, LIS3DH_Z);  //�������ݴ�ӡ

			}

		}
		osDelay(500);
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

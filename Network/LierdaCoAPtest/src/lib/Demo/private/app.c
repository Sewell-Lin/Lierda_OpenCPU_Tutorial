/******************************************************************************
 * @����	�û�������
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "app.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*��������*/, 0, NULL, 0, NULL,
		(256) /*�����ջ��С*/, 11/*�������ȼ�*/, 0, 0 };//�������Խṹ��
uint32 * App_task_handle = NULL;

/******************************************************************************
* @������	app�����߳�
* @����	    param : �ղ�������Ч
* @����ֵ  ��
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);
	uint8 i = 0;

	osDelay(5000);

	sendCoAPdata();//���Ͳ�������

	lierdaNNMIDataInit();//NNMI�������ݽ��ճ�ʼ��

	for(;;)
	{
		lierdaNNMIDataReceived(nnmi_buff, &nnmi_buff_len, 0xFFFFFFFF); //NNMI�������ݽ���

		if (nnmi_buff_len > 0)
		{
			lierdaLog("�������� :");

			for (i = 0; i < nnmi_buff_len; i++)
			{
				lierdaLog("%x", nnmi_buff[i]);
			}

			memset(nnmi_buff, 0, nnmi_buff_len);

			nnmi_buff_len = 0;
		}
		osDelay(2000);
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

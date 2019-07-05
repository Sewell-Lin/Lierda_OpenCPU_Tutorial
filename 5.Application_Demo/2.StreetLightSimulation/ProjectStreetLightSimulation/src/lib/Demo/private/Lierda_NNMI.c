/******************************************************************************
* @����	NNMI�������ݴ����ļ�
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "irmalloc.h"
#include "Lierda_NNMI.h"
#include "string.h"
#include "stdio.h"
#include "stdarg.h"
#include "lierdaNNMIData.h"
#include "cmsis_os2.h"
#include "lierda_app_main.h"
#include "app.h"
#include "app_at_send_data.h"

uint8 nnmi_buff[NNMI_BUFFSIZE];
uint16 nnmi_datalen;


void lierda_MMNI_task(void *unused)
{
	UNUSED(unused);uint16 len=0;
	osDelay(500);
	lierdaNNMIDataInit();//����������ճ�ʼ��
	memset(nnmi_buff,0,NNMI_BUFFSIZE);
	nnmi_datalen=0;
	for(;;)
	{
		lierdaNNMIDataReceived(nnmi_buff,&nnmi_datalen,0xFFFFFFFF);//���ݽ���
		if(nnmi_datalen>0)
		{
			lierdaLog_NNMI("\r\n");
			lierdaLog_NNMI("len:%d	nnmi_buff:",nnmi_datalen);
			for(len=0;len<nnmi_datalen;len++)
			{
				lierdaLog_NNMI("%02x",nnmi_buff[len]);
			}
			lierdaLog_NNMI("\r\n");
			if(Lierda_SysValue.DeviceSta==Device_Reg)
			{
				RegMsgProtocolAnalysis(nnmi_buff);//ע���������ݽ���
			}
			else if(Lierda_SysValue.DeviceSta==Reg_Complete)
			{
				lierda_RegMsgRecv(nnmi_buff);//�����������ݽ���
			}
			ReceiveDataled();//�յ���������
		}

		memset(nnmi_buff,0,NNMI_BUFFSIZE);
		nnmi_datalen=0;
		osDelay(10);
	}
}

/******************************************************************************
 * @������:lierdaLog
 * @����:ͬ�⺯��"printf"�÷���û���Զ����ӻس�����
 * @����ֵ:ִ�гɹ�����0�����ɹ�����-1
 * @��Ҫ�޸ļ�¼:180830��Def���ĺ�����
******************************************************************************/
int lierdaLog_NNMI(const char *pcFormat, ...)
{
    int iRet = 0;
    char *pcBuff, *pcTemp;
    int iSize = 512;
    va_list list;
    pcBuff = (char*)irzalloc(iSize);
    if(pcBuff == NULL)
    {
        return -1;
    }

    while(1)
    {
        va_start(list,pcFormat);
        iRet = vsnprintf(pcBuff,iSize,pcFormat,list);
        va_end(list);
        if(iRet > -1 && iRet < iSize)
        {
            break;
        }
        else
        {
            //iSize*=2;
            //if((pcTemp=realloc(pcBuff,iSize))==NULL)
            {
                iRet = -1;
                break;
            }
            //else
            {
                pcBuff=pcTemp;
            }

        }
    }
    app_at_send_at_rsp_string(pcBuff,true,AT_FLAG_LOGABLE);
    irfree(pcBuff);
    return iRet;
}


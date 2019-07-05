/*
 * ServerProtocol.c
 *
 *  Created on: 2019��5��21��
 *      Author: Administrator
 */
#include "ServerProtocol.h"
struct RegProtocolFrame1 RegProtocolFrame;
uint8  Server_SendBuff[SERVER_BUFF_MAXLEN];
struct NOtifyFormat1 SendDataNOtify;

static struct RegProtocolFrame1* RegMsgFilling(void);
static struct NOtifyFormat1* SendDataFilling(void);
static void WATER_DataFilling(uint8 *FillingBuff);
static void lierda_RegMsgSend(void);
static void Lierda_Server_Protocol_Analysis(uint8 * databuff);


static struct RegProtocolFrame1* RegMsgFilling(void)
{
	uint16 dataLen = 0;

	RegProtocolFrame.PackHead = PACK_HEAD;

	RegProtocolFrame.CmdWord = SERVER_CMD_REG;

	RegProtocolFrame.Pritocol_Ver = PRITOCOL_VERSION;

	dataLen = sizeof(struct RegProtocolFrame1) -1;	//��������У��λ
	//��Ϊ������ΪС��ģʽ��Э��Ҫ��Ϊ���ģʽ ���԰�һЩ���ݸߵ�λ������һ��
	RegProtocolFrame.PackDataLen = (dataLen << 8);

	RegProtocolFrame.RegData.IMEI_Len = IMEI_LEN;
	strncpy(RegProtocolFrame.RegData.ModuleIMEI, Lierda_SysValue.Module_IMEI, IMEI_LEN);

	RegProtocolFrame.RegData.IMSI_Len = IMSI_LEN;
	strncpy(RegProtocolFrame.RegData.ModuleIMSI, Lierda_SysValue.Module_IMSI, IMSI_LEN);

	RegProtocolFrame.RegData.ICCID_Len = ICCID_LEN;
	strncpy(RegProtocolFrame.RegData.ModuleICCID, Lierda_SysValue.Module_ICCID, ICCID_LEN);

	//��ͷ������У��ͼ���
	RegProtocolFrame.Crc = DataAccumulateSumCRC(&RegProtocolFrame.CmdWord, dataLen-2);

	return &RegProtocolFrame;
}
uint8 DataAccumulateSumCRC(void *DataBuff, uint16 DataLen)
{
	uint16 crc=0;
	uint16 i;
	uint8 *Ptr = (uint8*)DataBuff;

    for(i=0; i < DataLen; i++)
    {
    	crc += *Ptr++;
    }
	return (uint8)(crc&0xff);  // ȡ��λ�ֽ�
}

static void lierda_RegMsgSend(void)
{
	struct RegProtocolFrame1  *RegProtocol=NULL;

	RegProtocol = RegMsgFilling();
	if(RegProtocol!=NULL)
	{
		 memcpy(Server_SendBuff,(uint8 *)RegProtocol,sizeof(struct RegProtocolFrame1));
		lierdaSendMsg(Server_SendBuff, sizeof(struct RegProtocolFrame1));
	}
}

void lierdaSendMsg(uint8* databuff,uint16 datalen)
{
	uint16 len=0;
	lierdaLog_NNMI("\r\n\r\n");
	lierdaLog_NNMI("Len:%d	databuff:\r\n",datalen);
	for(len=0;len<datalen;len++)
	{
		lierdaLog_NNMI("%02x",databuff[len]);
	}
	lierdaLog_NNMI("\r\n\r\n");
	 lierdaSendMsgToPlatform(databuff, datalen, MSG_NON_NORAI,0,1);
	 SendDataled();
	 Lierda_SysValue.SendDataNum++;
	 //������������
}
void Lierda_ServerReg(void)
{
	Lierda_SysValue.DeviceSta=Device_Reg;
	do
	{

		lierda_module_status_read();//�¼�״̬����
		if(strstr(module_status.charNMSTATUS,"MO_DATA_ENABLED")==NULL)
		{
			lierdaLog("OC ƽ̨δע��");
			osDelay(1000);
		}
	}while(strstr(module_status.charNMSTATUS,"MO_DATA_ENABLED")==NULL);
	lierdaLog("OC ƽ̨ע��ɹ�");
	lierda_RegMsgSend();//����ע����Ϣ
}

void RegMsgProtocolAnalysis(uint8 *ProtocolData)
{
	struct RegProtocoRSPFrame1 *RegProtocoRSP=NULL;
	RegProtocoRSP = (struct RegProtocoRSPFrame1 *)ProtocolData;
	if(RegProtocoRSP->PackHead == PACK_HEAD)
	{
		if(RegProtocoRSP->CmdWord == SERVER_CMD_REG_RSP)
		{
			if(RegProtocoRSP->Pritocol_Ver == PRITOCOL_VERSION)
			{
				if(strncmp(Lierda_SysValue.Module_IMEI, RegProtocoRSP->RegRSPData.ModuleIMEI, IMEI_LEN)==0)
				{
					if(RegProtocoRSP->RegRSPData.RegVlaue == 0)
					{
						LED10_OFF;
						lierdaLog("Reg Success\r\n");
						Lierda_SysValue.DeviceSta=Reg_Complete;
						 Lierda_SysValue.AckDataNum++;
						 Lierda_ServerSendData();
					}
					else
					{
						lierdaLog("Reg fail ErrorCode=0x%x\r\n",RegProtocoRSP->RegRSPData.RegVlaue);
					}
				}
			}
		}
	}
}

void Lierda_ServerSendData(void)
{
	struct NOtifyFormat1 *NOtifyFormat=NULL;
	uint16 PackLen=0;
	memset(Server_SendBuff,0,SERVER_BUFF_MAXLEN);
	NOtifyFormat=SendDataFilling();//���ݰ����
	memcpy(Server_SendBuff,NOtifyFormat,sizeof(struct NOtifyFormat1));
	WATER_DataFilling(Server_SendBuff+sizeof(struct NOtifyFormat1));//ˮ���������
	PackLen=sizeof(struct NOtifyFormat1)+sizeof(struct Water_Pack);
	Server_SendBuff[PackLen] = DataAccumulateSumCRC(Server_SendBuff+2, PackLen-2);
	PackLen = PackLen+1;
	lierdaSendMsg(Server_SendBuff, PackLen);//���ݷ���
}

static void WATER_DataFilling(uint8 *FillingBuff)
{
	struct Water_Pack water_pack={0};struct time LierdaTime={0};
	//uint16 HumiditySensor=0;

	Lierda_SysValue.WaterCnt++;
	cclktimeget(&LierdaTime);//ʱ���ȡ
	//lierdaLog("date:%02d/%02d/%02d %02d:%02d:%02d",LierdaTime.time_year,LierdaTime.time_mon,LierdaTime.time_day,LierdaTime.time_hour,LierdaTime.time_min,LierdaTime.time_sec);
	sprintf(water_pack.AcquisitionTime,"%04d%02d%02d%c%02d%02d%02d%c",LierdaTime.time_year+2000,LierdaTime.time_mon,LierdaTime.time_day,'T',LierdaTime.time_hour,LierdaTime.time_min,LierdaTime.time_sec,'Z');
	sprintf(water_pack.Timestamp,"%04d%02d%02d%c%02d%02d%02d%c",LierdaTime.time_year+2000,LierdaTime.time_mon,LierdaTime.time_day,'T',LierdaTime.time_hour,LierdaTime.time_min,LierdaTime.time_sec,'Z');
	//lierdaLog("date1:%s",water_pack.AcquisitionTime);
	water_pack.Scenes = SCENES_WATER;//����

	water_pack.BillingReading = BigtoLittle32(0xB7+Lierda_SysValue.WaterCnt);

	water_pack.CurrReading = BigtoLittle32(0xA5 + Lierda_SysValue.WaterCnt);

	lierdaLog("WaterTemper:%d ",Lierda_SysValue.TemperSensor);
	water_pack.InternalTemper = BigtoLittle16(Lierda_SysValue.TemperSensor);

	water_pack.Day_CumulativeFlow = BigtoLittle32(0x3A + Lierda_SysValue.WaterCnt);

	water_pack.Day_CumulativeReverseFlow = BigtoLittle32(0x2F + Lierda_SysValue.WaterCnt);

	water_pack.Day_MaxFlow = BigtoLittle32(0x011D);

	water_pack.IntervalFlow = BigtoLittle16(0x9C);

	water_pack.WaterPressure = BigtoLittle16(0x0E);
	lierdaLog("WaterTemper:%d ",Lierda_SysValue.TemperSensor);
	water_pack.WaterTemper = BigtoLittle16(Lierda_SysValue.TemperSensor - 0xFF);

	water_pack.AcousticVibration = BigtoLittle16(0x1A);

	water_pack.battery = BATTER;

	water_pack.BatteryThreshold = BATTER_THRESHOLD;

	if(GetLEDState(LED_10))
		Lierda_SysValue.WaterSwitchSta=1;
	else
		Lierda_SysValue.WaterSwitchSta=0;
	water_pack.ValveState = Lierda_SysValue.WaterSwitchSta;

	water_pack.GpsInfo.Position=Lierda_SysValue.gpsinfo.Position;

	water_pack.GpsInfo.latitude=BigtoLittle32(Lierda_SysValue.gpsinfo.latitude);

	water_pack.GpsInfo.longitude=BigtoLittle32(Lierda_SysValue.gpsinfo.longitude);
	if(HA_GPSData.Valid_status!='A')
		lierdaLog("GPS δ��λ�ɹ���ʹ��ģ������");
	else
		lierdaLog("GPS ��λ�ɹ�");
	lierdaLog("Position:%#x latitude:%#x longitude:%#x ",Lierda_SysValue.gpsinfo.Position,Lierda_SysValue.gpsinfo.latitude,Lierda_SysValue.gpsinfo.longitude);
	memcpy(FillingBuff, &water_pack, sizeof(struct Water_Pack));

	lierdaLog("WATER data Filling\r\n");
}

static struct NOtifyFormat1* SendDataFilling(void)
{
	uint16 dataLen = 0;uint64 current_time=0;NueStats ModuleState = {0};
	//�̶���ͷ
	SendDataNOtify.PackHead = PACK_HEAD;		//��Ϊ������ΪС��ģʽ��Э��Ҫ��Ϊ���ģʽ ���԰�һЩ���ݸߵ�λ������һ��
	//������
	SendDataNOtify.CmdWord = TIMIN_NOTIFY;
	//Э��汾
	SendDataNOtify.Pritocol_Ver = PRITOCOL_VERSION;

	dataLen = sizeof(struct NOtifyFormat1)+SIMULATE_WATER_LEN;
	//������ݳ���
	SendDataNOtify.FillingDataLen = BigtoLittle16(SIMULATE_WATER_LEN);

	SendDataNOtify.PackDataLen = BigtoLittle16(dataLen);
	//IMEI
	SendDataNOtify.IMEI_Len = IMEI_LEN;
	strncpy(SendDataNOtify.ModuleIMEI, Lierda_SysValue.Module_IMEI, IMEI_LEN);
	//�ϱ�����
	SendDataNOtify.NotifyCycle = BigtoLittle32(SENDCYCLE);
	//���͵���Ϣ�����
	SendDataNOtify.Send_PackNum = BigtoLittle32(Lierda_SysValue.AckDataNum);
	//���ͳɹ�����
	SendDataNOtify.ACK_PackNum =	BigtoLittle32(Lierda_SysValue.SendDataNum);

	//utcʱ���
	current_time = get_current_time();//UTCʱ���ȡ
	SendDataNOtify.Timestamp = BigtoLittle64(current_time);

	//ģ������״̬
	GetNUESTATS_DelaWith(&ModuleState);
	SendDataNOtify.Rsrp = BigtoLittle16(ModuleState.Rsrp);
	SendDataNOtify.Snr = BigtoLittle16(ModuleState.Snr);
	SendDataNOtify.Coverage_level = ModuleState.Coverage_level;
	SendDataNOtify.Rsrq = BigtoLittle16(ModuleState.Rsrq);
	SendDataNOtify.Cell_ID = BigtoLittle32(ModuleState.Cell_ID);

	//����ģʽ
	SendDataNOtify.Power_mode = DRX_MODE;
	//�ϴ��ط�����
	SendDataNOtify.ResendNum = 0;
	//��־λ
	SendDataNOtify.flag = 0;
	return &SendDataNOtify;
}


void GetNUESTATS_DelaWith(NueStats *ModuleState)
{
	char *recvbuff=NULL;
	char *Ptr=NULL;

	recvbuff = lierdaATCall(LIERDA_NUESTATS,3000);
	if(recvbuff != NULL)
	{
		Ptr = strstr(recvbuff, SIGNAL_POWR);
		if(Ptr!=NULL)
		{
			ModuleState->Rsrp = atoi(Ptr+strlen(SIGNAL_POWR));
			lierdaLog("Rsrp=%d\r\n", ModuleState->Rsrp);
		}

		Ptr = NULL;
		Ptr = strstr(recvbuff, SNR);
		if(Ptr!=NULL)
		{
			ModuleState->Snr = atoi(Ptr+strlen(SNR));
			lierdaLog("Snr=%d\r\n", ModuleState->Snr);
		}

		Ptr = NULL;
		Ptr = strstr(recvbuff, ECL);
		if(Ptr!=NULL)
		{
			ModuleState->Coverage_level = atoi(Ptr+strlen(ECL));
			lierdaLog("Coverage_level=%d\r\n", ModuleState->Coverage_level);
		}

		Ptr = NULL;
		Ptr = strstr(recvbuff, RSRQ);
		if(Ptr!=NULL)
		{
			ModuleState->Rsrq = atoi(Ptr+strlen(RSRQ));
			lierdaLog("Rsrq=%d\r\n", ModuleState->Rsrq);
		}

		Ptr = NULL;
		Ptr = strstr(recvbuff, CELL_ID);
		if(Ptr!=NULL)
		{
			ModuleState->Cell_ID = atoi(Ptr+strlen(CELL_ID));
			lierdaLog("Cell_ID=%d\r\n", ModuleState->Cell_ID);
		}
	}
}
static void Lierda_Server_Protocol_Analysis(uint8 * databuff)
{
	uint8 temp=Stachange_data;

	if((databuff[32]==0xc1)&&(databuff[33]==0x4))
	{
		lierdaLog("cmd %x %x\r\n", databuff[32],databuff[33]);
		if(databuff[39]==1)
		{
			lierdaLog("�򿪷���");
			LED10_ON;
		}
		else
		{
			lierdaLog("�رշ���");
			LED10_OFF;
		}
		QueueSendDataFun(&temp);
	}

}

void lierda_RegMsgRecv(uint8* databuff)
{
	 Lierda_Server_Protocol_Analysis(databuff);
}

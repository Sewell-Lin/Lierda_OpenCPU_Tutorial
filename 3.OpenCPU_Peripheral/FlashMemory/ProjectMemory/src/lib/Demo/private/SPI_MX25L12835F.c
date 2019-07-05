/******************************************************************************
 * @����	SPI���Ժ���   MX25L12835F�Ķ�д����
 * @���	Lierda NB-IoT �������Ŷ�@2018
******************************************************************************/
#include "SPI_MX25L12835F.h"

SPI_InitTypeDef SPI_MX25L12835F;

/************************************************
�������� �� MX25L12835F_spiInit
��    �� �� SPI��ʼ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void MX25L12835F_spiInit(void)
{
#if USESOFTSPI
	SPI_MX25L12835F.DataSize=8;
	SPI_MX25L12835F.Mode=0;
	SPI_MX25L12835F.LierdaSPI_CS=SPI_CS;
	SPI_MX25L12835F.LierdaSPI_SCK=SPI_SCK;
	SPI_MX25L12835F.LierdaSPI_MISO=SPI_MISO;
	SPI_MX25L12835F.LierdaSPI_MOSI=SPI_MOSI;

	if (lierdaSPISoftInit(&SPI_MX25L12835F) == LierdaSPI_RET_OK)
		lierdaLog("SPI  Init  OK");
	else
		lierdaLog("SPI  Init  ERROR");
#else
	SPI_CONFIGURATION lierdaSPIconfig;
	SPI_PIN lierdaSPIpin;
	lierdaSPIconfig.data_size = 8;
	lierdaSPIconfig.clk_mode = SPI_CLK_MODE3;
	lierdaSPIconfig.clk_div = 0x02;
	lierdaSPIpin.interface = SPI_INTERFACE_SINGLE_UNIDIR;
	lierdaSPIpin.clk_pin = SPI_SCK;
	lierdaSPIpin.csb_pin = SPI_CS;
	lierdaSPIpin.miso_pin = SPI_MISO;
	lierdaSPIpin.mosi_pin = SPI_MOSI;
	if (lierdaSPIInit(lierdaSPIconfig, lierdaSPIpin) == SPI_RET_OK)
		lierdaLog("SPI  Init  OK");
	else
		lierdaLog("SPI  Init  ERROR");
#endif
}

/************************************************
�������� �� SFLASH_ReadID
��    �� �� ��ȡоƬID SFLASH��ID
��    �� �� ��
�� �� ֵ �� ID --- 32λID��
*************************************************/
uint32 SFLASH_ReadID(void)
{
 uint32 Temp = 0;
 uint8 idbuff[4]={0};uint8 cmd_JedecDeviceID=W25X_JedecDeviceID;
#if USESOFTSPI
  SPI_CS_ENABLE();                                 //ʹ������

  lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_JedecDeviceID);   //����һ���ֽ����� ���豸ID��ָ��

  idbuff[0]= lierdaSPIReadByte(&SPI_MX25L12835F);//��һ���ֽ�����

  idbuff[1]= lierdaSPIReadByte(&SPI_MX25L12835F);//��һ���ֽ�����

  idbuff[2]= lierdaSPIReadByte(&SPI_MX25L12835F);//��һ���ֽ�����
   SPI_CS_DISABLE();  //ʧ������
#else
   lierdaSPIRecvData(0,&cmd_JedecDeviceID,1,idbuff, 3,NULL,true);//false true
#endif
   Temp = (idbuff[0] << 16) | (idbuff[1] << 8) | idbuff[2];
  return Temp;
}
uint8 Tx_Buffer[]="lierda ���SPI ����";
uint8 Rx_Buffer[BufferSize];
/******************************************************************************
* @������	SPI����
* @����	        ��
* @����ֵ        ��
******************************************************************************/
void Lierda_SPITest(void)
 {
	uint32 ID;
	ID = SFLASH_ReadID();

	if (ID == 0xc22018)
	{
		lierdaLog("SFLASH_ReadID��\r\n%#x\r\nBufferSize=%d", ID,BufferSize);
		SPI_FLASH_SectorErase(FLASH_SectorToErase);
		/* �����ͻ�����������д��flash�� */
		SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
		lierdaLog("д�������Ϊ��\r\n\r\n%s", Tx_Buffer);
		/* ���ո�д������ݶ������ŵ����ջ������� */
		SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		lierdaLog("����������Ϊ�� \r\n\r\n%s", Rx_Buffer);
	}
	else
		lierdaLog("��FLASH  SFLASH_ReadID=%#x", ID);
}


/**
  * ��������: ʹ�ܴ���Flashд����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void SPI_FLASH_WriteEnable(void)
{
	uint8 cmd_WriteEnable=W25X_WriteEnable;
#if USESOFTSPI
  /* ѡ����FLASH: CS�͵�ƽ */
	SPI_CS_ENABLE();

  /* �������дʹ�� */
lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_WriteEnable);

  /* ���ô���Flash��CS�ߵ�ƽ */
  SPI_CS_DISABLE();
#else
  lierdaSPISendData(0, &cmd_WriteEnable,1, NULL, 0, NULL);
#endif
}
/**
  * ��������: �ȴ�����д�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����Polls the status of the Write In Progress (WIP) flag in the
  *           FLASH's status  register  and  loop  until write  opertaion
  *           has completed.
  */
void SPI_FLASH_WaitForWriteEnd(void)
{
  uint8 FLASH_Status = 0;uint8 cmd_ReadStatusReg=W25X_ReadStatusReg;
#if USESOFTSPI
  /* Select the FLASH: Chip Select low */
  SPI_CS_ENABLE();

  /* Send "Read Status Register" instruction */
  lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_ReadStatusReg);

  /* Loop as long as the memory is busy with a write cycle */
  do
  {
    /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status =lierdaSPIReadByte(&SPI_MX25L12835F);
  }
  while ((FLASH_Status & WIP_Flag) == 1); /* Write in progress */

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_DISABLE();
#else
  do
  {
	  lierdaSPIRecvData(0,&cmd_ReadStatusReg,1,&FLASH_Status, 1,NULL,true);
  }
  while ((FLASH_Status & WIP_Flag) == 1); /* Write in progress */

#endif
}
/**
  * ��������: ��������
  * �������: SectorAddr��������������ַ��Ҫ��Ϊ4096����
  * �� �� ֵ: ��
  * ˵    ��������Flash��С�������СΪ4KB(4096�ֽ�)����һ��������С��Ҫ���������
  *           Ϊ4096��������������FlashоƬд������֮ǰҪ���Ȳ����ռ䡣
  */
void SPI_FLASH_SectorErase(uint32 SectorAddr)
{
	uint8 setaddr[4]={0};uint8 cmd_SectorErase=W25X_SectorErase;
	setaddr[0]=(SectorAddr & 0xFF0000)>>16;
	setaddr[1]=(SectorAddr & 0xFF00)>>8;
	setaddr[2]=SectorAddr & 0xFF;
  /* ����FLASHдʹ������ */
  SPI_FLASH_WriteEnable();
  SPI_FLASH_WaitForWriteEnd();
#if USESOFTSPI
  /* �������� */
  /* ѡ����FLASH: CS�͵�ƽ */
   SPI_CS_ENABLE();
  /* ������������ָ��*/
   lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_SectorErase);

  /*���Ͳ���������ַ�ĸ�λ*/
   lierdaSPIWriteByte(&SPI_MX25L12835F,setaddr[0]);

  /* ���Ͳ���������ַ����λ */
   lierdaSPIWriteByte(&SPI_MX25L12835F,setaddr[1]);

  /* ���Ͳ���������ַ�ĵ�λ */
   lierdaSPIWriteByte(&SPI_MX25L12835F,setaddr[2]);

  /* ���ô���FLASH: CS �ߵ�ƽ */
   SPI_CS_DISABLE();
#else
   lierdaSPISendData(0, &cmd_SectorErase,1, setaddr, 3, NULL);
#endif
  /* �ȴ��������*/
  SPI_FLASH_WaitForWriteEnd();
}
/**
  * ��������: ������FLASH��ҳд�����ݣ����ñ�����д������ǰ��Ҫ�Ȳ�������
  * �������: pBuffer����д�����ݵ�ָ��
  *           WriteAddr��д���ַ
  *           NumByteToWrite��д�����ݳ��ȣ�����С�ڵ���SPI_FLASH_PerWritePageSize
  * �� �� ֵ: ��
  * ˵    ��������Flashÿҳ��СΪ256���ֽ�
  */

void SPI_FLASH_PageWrite(uint8* pBuffer, uint32 WriteAddr, uint16 NumByteToWrite)
{
	uint8 writaddr[5]={0};uint8 cmd_PageProgram=W25X_PageProgram;
	writaddr[0]=cmd_PageProgram;
	writaddr[1]=(WriteAddr & 0xFF0000)>>16;
	writaddr[2]=(WriteAddr & 0xFF00)>>8;
	writaddr[3]=WriteAddr & 0xFF;
  /* ����FLASHдʹ������ */
  SPI_FLASH_WriteEnable();
#if USESOFTSPI
   /* Ѱ�Ҵ���FLASH: CS�͵�ƽ */
  SPI_CS_ENABLE();
  /* д��дָ��*/
  lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_PageProgram);
  /*����д��ַ�ĸ�λ*/
  lierdaSPIWriteByte(&SPI_MX25L12835F,writaddr[1]);

  /*����д��ַ����λ*/
  lierdaSPIWriteByte(&SPI_MX25L12835F,writaddr[2]);

  /*����д��ַ�ĵ�λ*/
  lierdaSPIWriteByte(&SPI_MX25L12835F,writaddr[3]);


  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
  {
     NumByteToWrite = SPI_FLASH_PerWritePageSize;
     //printf("Err: SPI_FLASH_PageWrite too large!\n");
  }

  /* д������*/
  while (NumByteToWrite--)
  {
     /* ���͵�ǰҪд����ֽ����� */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,*pBuffer);
     /* ָ����һ�ֽ����� */
    pBuffer++;
  }

  /* ���ô���FLASH: CS �ߵ�ƽ */
  SPI_CS_DISABLE();
#else
  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
   {
      NumByteToWrite = SPI_FLASH_PerWritePageSize;
   }
   lierdaSPISendData(0, writaddr,4, pBuffer, NumByteToWrite, NULL);
#endif
  /* �ȴ�д�����*/
  SPI_FLASH_WaitForWriteEnd();
}
/**
  * ��������: ������FLASHд�����ݣ����ñ�����д������ǰ��Ҫ�Ȳ�������
  * �������: pBuffer����д�����ݵ�ָ��
  *           WriteAddr��д���ַ
  *           NumByteToWrite��д�����ݳ���
  * �� �� ֵ: ��
  * ˵    �����ú���������������д�����ݳ���
  */
void SPI_FLASH_BufferWrite(uint8* pBuffer, uint32 WriteAddr, uint16 NumByteToWrite)
{
  uint8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % SPI_FLASH_PageSize;
  count = SPI_FLASH_PageSize - Addr;
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

  if (Addr == 0) /* ����ַ�� SPI_FLASH_PageSize ����  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /* ����ַ�� SPI_FLASH_PageSize ������ */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      {
        temp = NumOfSingle - count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/**
  * ��������: �Ӵ���Flash��ȡ����
  * �������: pBuffer����Ŷ�ȡ�����ݵ�ָ��
  *           ReadAddr����ȡ����Ŀ���ַ
  *           NumByteToRead����ȡ���ݳ���
  * �� �� ֵ: ��
  * ˵    �����ú����������������ȡ���ݳ���
  */
void SPI_FLASH_BufferRead(uint8* pBuffer, uint32 ReadAddr, uint16 NumByteToRead)
{
	uint8 READADDE[5]={0};uint8 cmd_ReadData=W25X_ReadData;
	READADDE[0]=cmd_ReadData;
	READADDE[1]=(ReadAddr & 0xFF0000)>>16;
	READADDE[2]=(ReadAddr & 0xFF00)>>8;
	READADDE[3]=ReadAddr & 0xFF;
#if USESOFTSPI
  /* ѡ����FLASH: CS�͵�ƽ */
	 SPI_CS_ENABLE();

  /* ���� �� ָ�� */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,cmd_ReadData);


  /* ���� �� ��ַ��λ */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,READADDE[1]);

  /* ���� �� ��ַ��λ */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,READADDE[2]);

  /* ���� �� ��ַ��λ */
	  lierdaSPIWriteByte(&SPI_MX25L12835F,READADDE[3]);

  while (NumByteToRead--) /* ��ȡ���� */
  {
     /* ��ȡһ���ֽ�*/
    *pBuffer = lierdaSPIReadByte(&SPI_MX25L12835F);
    /* ָ����һ���ֽڻ����� */
    pBuffer++;
  }

  /* ���ô���FLASH: CS �ߵ�ƽ */
  SPI_CS_DISABLE();
#else
  lierdaSPIRecvData(0,READADDE,4,pBuffer, NumByteToRead,NULL,true);//true false
#endif
}



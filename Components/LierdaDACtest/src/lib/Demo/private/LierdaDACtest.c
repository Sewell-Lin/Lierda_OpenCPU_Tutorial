/*
 * LierdaDACtest.c
 *
 *  Created on: 2019��4��23��
 *      Author: Def_Lin
 */
#include "LierdaDACtest.h"

/******************************************************************************
 * @������	Lierda_DAC_Init
 * @����    ����DAC�����ѹ
 * @����    ��
 * @����ֵ  ��
 ******************************************************************************/
void Lierda_DAC_Init(void)
{
	lierdaDACInit(); //DAC��ʼ��

	lierdaDACSetRange(3);//����DAC�����ѹ��Χ

	lierdaDACConnect(LIERDA_AIO1);//���ڽ���DAC����AIO����
}



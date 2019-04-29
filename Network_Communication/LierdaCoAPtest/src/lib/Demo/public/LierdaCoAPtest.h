/*
 * LierdaCoAPtest.h
 *
 *  Created on: 2019��4��23��
 *      Author: Def_Lin
 */

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_LIERDACOAPTEST_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_LIERDACOAPTEST_H_

#include "cmsis_os2.h"
#include "neulfw.h"
#include "app_at_log.h"
#include "string.h"
#include <assert.h>
#include "lierdaNNMIData.h"

uint8 nnmi_buff[128];//����buff
uint16 nnmi_buff_len;//�������ݽ��ճ���

void sendCoAPdata(void);


#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_LIERDACOAPTEST_H_ */

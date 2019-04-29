/*
 * lierdaKVStorage.h
 *
 *  Created on: 2018��10��26��
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDAKVSTORAGE_PUBLIC_LIERDAKVSTORAGE_H_
#define SRC_LIB_LIERDAKVSTORAGE_PUBLIC_LIERDAKVSTORAGE_H_


#include "neul_kv_storage.h"
#include "neul_kv_storage_types.h"
#include "irmalloc.h"
#if defined USE_CMSIS_OS
#include "cmsis_os2.h"
#endif
#include <assert.h>
#include <string.h>
#include "core.h"

#if (CORE == SECURITY)
#include "non_os.h"
#include "kv_storage_caches.h"
#include "neul_sec_kv_storage.h"
#else
#include "rpc_auto_generated.h"
#include "rpc_interface.h"
#endif // (CORE == SECURITY)

typedef enum
{
	LIERDA_RET_OK = 0,
	LIERDA_RET_ERROR,

} LIERDA_RET;

typedef uint16 lierda_kv_key;

/******************************************************************************
 * @������:lierdaKVSet�������趨kvֵ
 * @����:neul_kv_key key��д���kvӳ��ID����Χ��0��26880��
 * 		uint8 *kvalue��Ҫд���ֵ
 * 		kvalue_length��д�����ֵ����
 * @����ֵ:���ɹ�������NEUL_RET_OK��0��
 * 		 ��ʧ�ܣ�����NEUL_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
extern LIERDA_RET lierdaKVSet(lierda_kv_key key, const uint8 *kvalue, uint16 kvalue_length);


/******************************************************************************
 * @������:lierdaKVGet�����ڻ�ȡkvֵ
 * @����:neul_kv_key key����ȡ��kvӳ��ID����Χ��0��26880��
 * 		uint16 kvalue_max_length��kv��ID����
 * 		kvalue_length����ȡ����ֵ����
 * 		uint8 *kvalue����ȡ����ֵ
 * @����ֵ:���ɹ�������NEUL_RET_OK��0��
 * 		��ʧ�ܣ�����NEUL_RET_ERROR
 * @��Ҫ�޸ļ�¼:180830��Def��������
******************************************************************************/
extern LIERDA_RET lierdaKVGet(lierda_kv_key key, uint16 kvalue_max_length, uint16 *kvalue_length, uint8 *kvalue);

#endif /* SRC_LIB_LIERDAKVSTORAGE_PUBLIC_LIERDAKVSTORAGE_H_ */

/**
* @file         
* @brief		        hudi common interface
* @par Copyright(c): 	Hichip Semiconductor (c) 2023
*/

#ifndef __HUDI_COM_H__
#define __HUDI_COM_H__

typedef void *hudi_handle;

typedef enum
{
    HUDI_LL_FATAL = 0,
    HUDI_LL_ERROR,
    HUDI_LL_WARNING,
    HUDI_LL_NOTICE,
    HUDI_LL_INFO,
    HUDI_LL_DEBUG,
    HUDI_LL_SPEW,
    HUDI_LL_FLOOD,
} hudi_log_level;

#ifdef __cplusplus
extern "C" {
#endif

void hudi_log_level_set(hudi_log_level level);

#ifdef __cplusplus
}
#endif

#endif

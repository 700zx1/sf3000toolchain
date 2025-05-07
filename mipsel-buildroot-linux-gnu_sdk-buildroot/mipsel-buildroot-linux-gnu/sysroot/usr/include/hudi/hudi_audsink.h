/**
* @file
* @brief                hudi audio sink driver interface.
* @par Copyright(c):    Hichip Semiconductor (c) 2024
*/

#ifndef __HUDI_AUDSINK_H__
#define __HUDI_AUDSINK_H__

#include "hudi_com.h"
#include "hudi_avsync.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HUDI_AUDSINK_TYPE_I2SO      (1UL << (0))
#define HUDI_AUDSINK_TYPE_PCMO      (1UL << (1))
#define HUDI_AUDSINK_TYPE_SPO       (1UL << (2))
#define HUDI_AUDSINK_TYPE_DDP_SPO   (1UL << (3))

#ifdef __cplusplus
}
#endif

#endif

/**
* @file
* @brief                hudi audio decoder interface.
* @par Copyright(c):    Hichip Semiconductor (c) 2024
*/

#ifndef __HUDI_ADEC_H__
#define __HUDI_ADEC_H__

#include "hudi_com.h"
#include "hudi_avsync.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    HUDI_ADEC_CODEC_PCM_S16LE = 1,
    HUDI_ADEC_CODEC_PCM_S16BE,
    HUDI_ADEC_CODEC_PCM_U16LE,
    HUDI_ADEC_CODEC_PCM_U16BE,
    HUDI_ADEC_CODEC_PCM_S8,
    HUDI_ADEC_CODEC_PCM_U8,
    HUDI_ADEC_CODEC_MP2,
    HUDI_ADEC_CODEC_MP3,
    HUDI_ADEC_CODEC_AAC,
    HUDI_ADEC_CODEC_AC3,
    HUDI_ADEC_CODEC_DTS,
    HUDI_ADEC_CODEC_ALAC,
    HUDI_ADEC_CODEC_FLAC,
} hudi_adec_codec_e;

typedef struct
{
    hudi_adec_codec_e codec_type;
    hudi_avsync_type_e sync_mode;
    unsigned int codec_tag;
    unsigned int bit_rate;
    unsigned int sample_rate;
    unsigned int block_align;
    unsigned int audsink;
    unsigned char bitdepth;
    unsigned char channels;
    int flush_thres;
    int kshm_size;
} hudi_adec_config_t;

typedef struct
{
    unsigned char *buf;
    int len;
    unsigned long long pts;
} hudi_adec_pkt_t;

typedef int (*hudi_adec_cb)(hudi_handle handle, unsigned int event, void *arg, void *user_data);

/**
* @brief       Open an hudi audio decoder module instance
* @param[out]  handle  Output the handle of the instance
* @param[in]   config  Decode parameters
* @param[in]   func    Event notifier callback function
* @retval      0       Success
* @retval      other   Error
*/
int hudi_adec_open(hudi_handle *handle, hudi_adec_config_t *config);

/**
* @brief       Close an hudi audio decoder module instance
* @param[in]   handle  Handle of the instance to be closed
* @retval      0       Success
* @retval      other   Error
*/
int hudi_adec_close(hudi_handle handle);

/**
* @brief       Start audio decoding
* @param[in]   handle  Handle of the instance
* @retval      0       Success
* @retval      other   Error
*/
int hudi_adec_start(hudi_handle handle);

/**
* @brief       Pause audio decoding
* @param[in]   handle  Handle of the instance
* @retval      0       Success
* @retval      other   Error
*/
int hudi_adec_pause(hudi_handle handle);

/**
* @brief       Feed frame packet into audio decoder
* @param[in]   handle  Handle of the instance
* @param[in]   pkt     Audio packet parameters
* @retval      0       Success
* @retval      other   Error
*/
int hudi_adec_feed(hudi_handle handle, hudi_adec_pkt_t *pkt);

#ifdef __cplusplus
}
#endif

#endif

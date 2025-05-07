/**
* @file
* @brief                hudi sound driver interface.
* @par Copyright(c):    Hichip Semiconductor (c) 2024
*/

#ifndef __HUDI_SND_H__
#define __HUDI_SND_H__

#include "hudi_com.h"
#include "hudi_avsync.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    HUDI_SND_CODEC_PCM_S16LE = 1,
    HUDI_SND_CODEC_PCM_S16BE,
    HUDI_SND_CODEC_PCM_U16LE,
    HUDI_SND_CODEC_PCM_U16BE,
    HUDI_SND_CODEC_PCM_S8,
    HUDI_SND_CODEC_PCM_U8,
    HUDI_SND_CODEC_AC3,
    HUDI_SND_CODEC_DTS,
} hudi_snd_codec_e;

typedef enum
{
    HUDI_SND_PCM_FORMAT_S8 = 1,
    HUDI_SND_PCM_FORMAT_U8,
    HUDI_SND_PCM_FORMAT_S16_LE,
    HUDI_SND_PCM_FORMAT_S16_BE,
    HUDI_SND_PCM_FORMAT_U16_LE,
    HUDI_SND_PCM_FORMAT_U16_BE,
    HUDI_SND_PCM_FORMAT_S24_LE,
    HUDI_SND_PCM_FORMAT_S24_BE,
    HUDI_SND_PCM_FORMAT_U24_LE,
    HUDI_SND_PCM_FORMAT_U24_BE,
    HUDI_SND_PCM_FORMAT_S32_LE,
    HUDI_SND_PCM_FORMAT_S32_BE,
    HUDI_SND_PCM_FORMAT_U32_LE,
    HUDI_SND_PCM_FORMAT_U32_BE,
    HUDI_SND_PCM_FORMAT_RAW,
} hudi_snd_pcm_format_e;

typedef enum
{
    HUDI_SND_PCM_ACCESS_INTERLEAVED = 0,
    HUDI_SND_PCM_ACCESS_NONINTERLEAVED,
} hudi_snd_pcm_access_e;

typedef enum
{
    HUDI_SND_PCM_SOURCE_AUDPAD = 0,
    HUDI_SND_PCM_SOURCE_HDMIRX,
    HUDI_SND_SPO_SOURCE_I2SODMA,
    HUDI_SND_SPO_SOURCE_SPODMA,
    HUDI_SND_SPO_SOURCE_HDMIRX,
} hudi_snd_pcm_source_e;

typedef enum
{
    HUDI_SND_PCM_DEST_DMA = 0,
    HUDI_SND_PCM_DEST_BYPASS,
} hudi_snd_pcm_dest_e;

typedef struct
{
    hudi_snd_pcm_access_e access;
    hudi_snd_codec_e codec_type;
    hudi_snd_pcm_format_e pcm_format;
    hudi_avsync_type_e sync_mode;
    unsigned int rate;
    unsigned int period_size;
    unsigned int periods;
    unsigned int audio_flush_thres;
    unsigned int use_spo_dma;
    unsigned short start_threshold;
    unsigned short spo_iec_pc;
    unsigned short no_preamble;
    unsigned char align;
    unsigned char channels;
    unsigned char bitdepth;
    int slave_mode;
} hudi_snd_config_t;

typedef struct
{
    unsigned char *buf;
    int len;
    unsigned long long pts;
} hudi_snd_pkt_t;

typedef int (*hudi_snd_cb)(hudi_handle handle, unsigned int event, void *arg, void *user_data);

/**
* @brief       Open an hudi sound module instance
* @param[out]  handle  Output the handle of the instance
* @param[in]   audsink Audio sink
* @param[in]   func    Event notifier callback function
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_open(hudi_handle *handle, unsigned int audsink);

/**
* @brief       Close an hudi sound module instance
* @param[in]   handle  Handle of the instance to be closed
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_close(hudi_handle handle);

/**
* @brief       Start sound
* @param[in]   handle  Handle of the instance
* @param[in]   config  Sound configuration
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_start(hudi_handle handle, hudi_snd_config_t *config);

/**
* @brief       Close an hudi sound module instance
* @param[in]   handle  Handle of the instance to be closed
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_stop(hudi_handle handle);

/**
* @brief       Pause sound
* @param[in]   handle  Handle of the instance
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_pause(hudi_handle handle);

/**
* @brief       Resume sound
* @param[in]   handle  Handle of the instance
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_resume(hudi_handle handle);

/**
* @brief       Feed frame packet into sound
* @param[in]   handle  Handle of the instance
* @param[in]   pkt     Audio packet parameters
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_feed(hudi_handle handle, hudi_snd_pkt_t *pkt);

/**
* @brief       Flush the sound buffer
* @param[in]   handle  Handle of the instance
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_flush(hudi_handle handle);

/**
* @brief       Get the volume
* @param[in]   handle  Handle of the instance
* @param[out]  volume  Out data pointer
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_volume_get(hudi_handle handle, unsigned char *volume);

/**
* @brief       Set the volume
* @param[in]   handle  Handle of the instance
* @param[in]   volume  Volume value
* @retval      0       Success
* @retval      other   Error
*/
int hudi_snd_volume_set(hudi_handle handle, unsigned char volume);

#ifdef __cplusplus
}
#endif

#endif

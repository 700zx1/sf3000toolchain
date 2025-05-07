/**
* @file
* @brief                hudi video decoder interface.
* @par Copyright(c):    Hichip Semiconductor (c) 2024
*/

#ifndef __HUDI_VDEC_H__
#define __HUDI_VDEC_H__

#include "hudi_com.h"
#include "hudi_avsync.h"
#include "hudi_display.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    HUDI_VDEC_CODEC_H264 = 1,
    HUDI_VDEC_CODEC_MPEG1,
    HUDI_VDEC_CODEC_MPEG2,
    HUDI_VDEC_CODEC_MJPEG,
    HUDI_VDEC_CODEC_VP8,
} hudi_vdec_codec_e;

typedef enum
{
    HUDI_VDEC_ROTATE_0,
    HUDI_VDEC_ROTATE_90,
    HUDI_VDEC_ROTATE_180,
    HUDI_VDEC_ROTATE_270,
} hudi_vdec_rotate_e;

typedef enum
{
    HUDI_VDEC_MIRROR_NONE,
    HUDI_VDEC_MIRROR_HORIZONTAL,
    HUDI_VDEC_MIRROR_VERTICAL,
} hudi_vdec_mirror_e;

typedef enum
{
    HUDI_VDEC_PBP_OFF,
    HUDI_VDEC_PBP_2P_ON,
} hudi_vdec_pbp_e;

typedef enum
{
    HUDI_VDEC_EVT_FIRST_FRAME_DECODED = 0,
    HUDI_VDEC_EVT_FIRST_FRAME_SHOWED,
    HUDI_VDEC_EVT_FRAME_DECODED,
    HUDI_VDEC_EVT_MAX = 32,
} hudi_vdec_event_e;

typedef struct
{
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} hudi_vdec_rect_t;

typedef struct
{
    hudi_vdec_codec_e codec_type;
    hudi_avsync_type_e sync_mode;
    unsigned int width;
    unsigned int height;
    unsigned int aspect_x;
    unsigned int aspect_y;
    unsigned int frame_rate;
    unsigned int quick_mode;
    unsigned int kshm_size;
    unsigned int mosaic_mode;
    unsigned char rotate_enable;
    unsigned int preview;
    hudi_vdec_rect_t src_rect;
    hudi_vdec_rect_t dst_rect;
    int buffering_start;
    int buffering_end;
    hudi_vdec_pbp_e pbp_mode;
    hudi_display_type_e dis_type;
    hudi_display_layer_e dis_layer;
} hudi_vdec_config_t;

typedef struct
{
    unsigned char *buf;
    int len;
    unsigned int last_slice;
    unsigned long long pts;
    hudi_vdec_rotate_e rotate;
    hudi_vdec_mirror_e mirror;
} hudi_vdec_pkt_t;

typedef struct
{
    unsigned int width;
    unsigned int height;
    unsigned int first_pic_showed;
    unsigned int frames_decoded;
    unsigned int frames_displayed;
    unsigned int buf_size;
    unsigned int buf_used;
} hudi_vdec_stat_t;

typedef int (*hudi_vdec_cb)(hudi_handle handle, unsigned int event, void *arg, void *user_data);

/**
* @brief       Open a hudi video decoder module instance
* @param[out]  handle  Output the handle of the instance
* @param[in]   config  Decode parameters
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_open(hudi_handle *handle, hudi_vdec_config_t *config);

/**
* @brief       Close a hudi video decoder module instance
* @param[in]   handle  Handle of the instance to be closed
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_close(hudi_handle handle, int frame_backup);

/**
* @brief       Start video decoding
* @param[in]   handle  Handle of the instance
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_start(hudi_handle handle);

/**
* @brief       Pause video decoding
* @param[in]   handle  Handle of the instance
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_pause(hudi_handle handle);

/**
* @brief       Feed frame packet into video decoder
* @param[in]   handle  Handle of the instance
* @param[in]   pkt     Video packet parameters
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_feed(hudi_handle handle, hudi_vdec_pkt_t *pkt);

/**
* @brief       Register and start events polling
* @param[in]   handle  Handle of the instance
* @param[in]   func    Callback function
* @param[in]   events  Events bitmap
* @param[in]   user_data    User data pointer
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_event_register(hudi_handle handle, hudi_vdec_cb func,
                             hudi_vdec_event_e event, void *user_data);

/**
* @brief       Unregister events
* @param[in]   handle  Handle of the instance
* @param[in]   events  Events bitmap
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_event_unregister(hudi_handle handle, hudi_vdec_event_e event);

/**
* @brief       Get the decoder status
* @param[in]   handle  Handle of the instance
* @param[out]  stat    Status information of decoder
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_stat_get(hudi_handle handle, hudi_vdec_stat_t *stat);

/**
* @brief       Get the video play time
* @param[in]   handle  Handle of the instance
* @param[out]  pts     PTS of video playing
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_pts_get(hudi_handle handle, long long *pts);

/**
* @brief       Set the frame rate
* @param[in]   handle  Handle of the instance
* @param[in]   fps     Frame rate to be set, e.g. 60fps - fps = 60 * 1000
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_fps_set(hudi_handle handle, unsigned int fps);

/**
* @brief       Get the buffering level
* @param[in]   handle  Handle of the instance
* @param[out]  percent Percentage of buffering
* @retval      0       Success
* @retval      other   Error
*/
int hudi_vdec_waterline_get(hudi_handle handle, unsigned int *percent);

#ifdef __cplusplus
}
#endif

#endif

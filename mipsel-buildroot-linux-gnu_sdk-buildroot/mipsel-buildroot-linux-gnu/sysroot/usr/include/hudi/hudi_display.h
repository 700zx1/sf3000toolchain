/**
* @file
* @brief                hudi display engine interface.
* @par Copyright(c):    Hichip Semiconductor (c) 2024
*/

#ifndef __HUDI_DISPLAY_H__
#define __HUDI_DISPLAY_H__

#include "hudi_com.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    HUDI_DISPLAY_DEV_2K = 0,
    HUDI_DISPLAY_DEV_4K,
} hudi_display_dev_e;

typedef enum
{
    HUDI_DISPLAY_TYPE_SD = 0,
    HUDI_DISPLAY_TYPE_HD,
    HUDI_DISPLAY_TYPE_UHD,
} hudi_display_type_e;

typedef enum
{
    HUDI_DISPLAY_LAYER_MAIN = 0x01,
    HUDI_DISPLAY_LAYER_AUXP = 0x10,
    HUDI_DISPLAY_LAYER_GMAS,
    HUDI_DISPLAY_LAYER_GMAF,
} hudi_display_layer_e;

typedef enum
{
    HUDI_DISPLAY_TV_4_3 = 0,
    HUDI_DISPLAY_TV_16_9,
    HUDI_DISPLAY_TV_AUTO,
} hudi_display_tv_mode_e;

typedef enum
{
    HUDI_DISPLAY_MODE_PANSCAN = 0,
    HUDI_DISPLAY_MODE_PANSCAN_NOLINEAR,
    HUDI_DISPLAY_MODE_LETTERBOX,
    HUDI_DISPLAY_MODE_PILLBOX,
    HUDI_DISPLAY_MODE_VERTICALCUT,
    HUDI_DISPLAY_MODE_NORMAL_SCALE,
    HUDI_DISPLAY_MODE_LETTERBOX149,
    HUDI_DISPLAY_MODE_AFDZOOM,
    HUDI_DISPLAY_MODE_PANSCAN43ON169,
    HUDI_DISPLAY_MODE_COMBINED_SCALE,
    HUDI_DISPLAY_MODE_VERTICALCUT_149,
    HUDI_DISPLAY_MODE_POINT2POINT,
} hudi_display_dis_mode_e;

typedef enum
{
    HUDI_DISPLAY_SCALE_ACTIVE_IMMEDIATELY = 0,
    HUDI_DISPLAY_SCALE_ACTIVE_NEXTFRAME,
} hudi_display_scale_active_e;

typedef enum
{
    HUDI_DISPLAY_EVT_VBLANK = 0,
    HUDI_DISPLAY_EVT_MIRACAST_VSRCEEN,
    HUDI_DISPLAY_EVT_DE_TYPE_CHANGE,
    HUDI_DISPLAY_EVT_MAX = 32,
} hudi_display_event_e;

typedef struct
{
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} hudi_display_rect_t;

typedef struct
{
    hudi_display_type_e dis_type;
    hudi_display_tv_mode_e tv_mode;
    hudi_display_dis_mode_e dis_mode;
    hudi_display_scale_active_e active_mode;
} hudi_display_aspect_t;

typedef struct
{
    hudi_display_type_e dis_type;
    hudi_display_layer_e layer;
    hudi_display_rect_t src_rect;
    hudi_display_rect_t dst_rect;
    hudi_display_scale_active_e active_mode;
} hudi_display_zoom_t;

typedef int (*hudi_display_cb)(hudi_handle handle, unsigned int event, void *arg, void *user_data);

/**
* @brief       Open a hudi display engine module instance
* @param[out]  handle  Output the handle of the instance
* @retval      0       Success
* @retval      other   Error
*/
int hudi_display_open(hudi_handle *handle);

/**
* @brief       Close a hudi display engine module instance
* @param[in]   handle  Handle of the instance to be closed
* @retval      0       Success
* @retval      other   Error
*/
int hudi_display_close(hudi_handle handle);

/**
* @brief       Set display aspect mode
* @param[in]   handle  Handle of the instance
* @param[in]   aspect_args  Aspect arguments
* @retval      0       Success
* @retval      other   Error
*/
int hudi_display_aspect_set(hudi_handle handle, hudi_display_aspect_t *aspect_args);

/**
* @brief       Set display zoom
* @param[in]   handle  Handle of the instance
* @param[in]   zoom_args  Zoom arguments
* @retval      0       Success
* @retval      other   Error
*/
int hudi_display_zoom_set(hudi_handle handle, hudi_display_zoom_t *zoom_args);

/**
* @brief       Backup main picture of display
* @param[in]   handle  Handle of the instance
* @param[in]   dis_type Display type
* @retval      0       Success
* @retval      other   Error
*/
int hudi_display_pic_backup(hudi_handle handle, hudi_display_type_e dis_type);

/**
* @brief       Free backup main picture
* @param[in]   handle  Handle of the instance
* @param[in]   dis_type Display type
* @retval      0       Success
* @retval      other   Error
*/
int hudi_display_pic_free(hudi_handle handle, hudi_display_type_e dis_type);

/**
* @brief       Register and start events polling
* @param[in]   handle  Handle of the instance
* @param[in]   func    Callback function
* @param[in]   events  Events bitmap
* @param[in]   user_data    User data pointer
* @retval      0       Success
* @retval      other   Error
*/
int hudi_display_event_register(hudi_handle handle, hudi_display_cb func,
                                hudi_display_event_e event, void *user_data);

/**
* @brief       Unregister events
* @param[in]   handle  Handle of the instance
* @param[in]   events  Events bitmap
* @retval      0       Success
* @retval      other   Error
*/
int hudi_display_event_unregister(hudi_handle handle, hudi_display_event_e event);

#ifdef __cplusplus
}
#endif

#endif

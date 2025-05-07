#ifndef __HCCAST_UM_H__
#define __HCCAST_UM_H__

typedef enum
{
    HCCAST_IUM_EVT_DEVICE_ADD = 1,
    HCCAST_IUM_EVT_DEVICE_REMOVE,
    HCCAST_IUM_EVT_MIRROR_START,
    HCCAST_IUM_EVT_MIRROR_STOP,
    HCCAST_IUM_EVT_SAVE_PAIR_DATA,          //param1: buf; param2: length
    HCCAST_IUM_EVT_GET_PAIR_DATA,           //param1: buf; param2: length
    HCCAST_IUM_EVT_NEED_USR_TRUST,
    HCCAST_IUM_EVT_USR_TRUST_DEVICE,
    HCCAST_IUM_EVT_CREATE_CONN_FAILED,
    HCCAST_IUM_EVT_CANNOT_GET_AV_DATA,
    HCCAST_IUM_EVT_UPG_DOWNLOAD_PROGRESS,   //param1: data len; param2: file len
    HCCAST_IUM_EVT_GET_UPGRADE_DATA,        //param1: hccast_ium_upg_bo_t
    HCCAST_IUM_EVT_SAVE_UUID,
    HCCAST_IUM_EVT_GET_FLIP_MODE,
    HCCAST_IUM_EVT_CERT_INVALID,
    HCCAST_IUM_EVT_SET_ROTATE,
    HCCAST_IUM_EVT_FAKE_LIB,
    HCCAST_IUM_EVT_NO_DATA,
    HCCAST_IUM_EVT_SET_DIS_ZOOM_INFO,
    HCCAST_IUM_EVT_GET_UPGRADE_BUF,
    HCCAST_IUM_EVT_COPYRIGHT_PROTECTION,
    HCCAST_IUM_EVT_SET_DIS_ASPECT,
    HCCAST_IUM_EVT_GET_ROTATION_INFO,
    HCCAST_IUM_EVT_AUDIO_NO_DATA,
    HCCAST_IUM_EVT_GET_PREVIEW_INFO,
} hccast_ium_evt_e;

typedef enum
{
    HCCAST_AUM_EVT_DEVICE_ADD = 1,
    HCCAST_AUM_EVT_DEVICE_REMOVE,
    HCCAST_AUM_EVT_MIRROR_START,
    HCCAST_AUM_EVT_MIRROR_STOP,
    HCCAST_AUM_EVT_IGNORE_NEW_DEVICE,
    HCCAST_AUM_EVT_SERVER_MSG,
    HCCAST_AUM_EVT_UPG_DOWNLOAD_PROGRESS,
    HCCAST_AUM_EVT_GET_UPGRADE_DATA,
    HCCAST_AUM_EVT_SET_SCREEN_ROTATE,
    HCCAST_AUM_EVT_SET_AUTO_ROTATE,
    HCCAST_AUM_EVT_SET_FULL_SCREEN,
    HCCAST_AUM_EVT_GET_FLIP_MODE,
    HCCAST_AUM_EVT_SET_DIS_ZOOM_INFO,
    HCCAST_AUM_EVT_GET_UPGRADE_BUF,
    HCCAST_AUM_EVT_SET_DIS_ASPECT,
    HCCAST_AUM_EVT_GET_ROTATION_INFO,
    HCCAST_AUM_EVT_CERT_INVALID,
    HCCAST_AUM_EVT_GET_PREVIEW_INFO,
} hccast_aum_evt_e;

typedef enum
{
    HCCAST_UM_CMD_SET_IUM_RESOLUTION = 1,
    HCCAST_UM_CMD_SET_AUM_RESOLUTION = 100, /* hccast_aum_res_e */
    HCCAST_UM_CMD_SET_AUM_VENDOR,
    HCCAST_UM_CMD_SET_AUM_MODEL,
} hccast_um_cmd_e;

typedef enum
{
    HCCAST_AUM_RES_AUTO = 0,
    HCCAST_AUM_RES_1080P60,
    HCCAST_AUM_RES_720P60,
    HCCAST_AUM_RES_480P60,
} hccast_aum_res_e;

typedef enum
{
    HCCAST_UM_SCREEN_ROTATE_0 = 0,
    HCCAST_UM_SCREEN_ROTATE_270,
    HCCAST_UM_SCREEN_ROTATE_90,
    HCCAST_UM_SCREEN_ROTATE_180,
} hccast_um_rotate_e;

typedef enum
{
    HCCAST_UM_DEV_IUM = 1,
    HCCAST_UM_DEV_IUM_UAC,
    HCCAST_UM_DEV_WCID_UAC,
} hccast_um_dev_type_e;

typedef struct
{
    unsigned char *buf;
    unsigned int len;
    unsigned int crc;
    unsigned char crc_chk_ok;
} hccast_ium_upg_bo_t;

typedef struct
{
    unsigned char *buf;
    unsigned int len;
} hccast_ium_upg_bi_t;

typedef struct
{
    unsigned int rotate_mode;  /* hccast_um_rotate_e */
    unsigned int video_width;
    unsigned int video_height;
} hccast_ium_screen_mode_t;

typedef struct
{
    unsigned char *buf;
    unsigned int len;
} hccast_aum_upg_bo_t;

typedef struct
{
    unsigned char *buf;
    unsigned int len;
} hccast_aum_upg_bi_t;

typedef struct
{
    char product_id[32];
    char fw_url[256];
    char apk_url[256];
    char aoa_desc[48];
    unsigned int fw_version;
} hccast_aum_param_t;

typedef struct
{
    unsigned int mode;  // 0 - Horizontal; 1 - Vertical
    unsigned int video_width;
    unsigned int video_height;
    unsigned int screen_width;
    unsigned int screen_height;
} hccast_aum_screen_mode_t;

typedef struct
{
    hccast_um_rotate_e screen_rotate_en;
    unsigned int screen_rotate_auto;
    unsigned int full_screen_en;
} hccast_um_param_t;

typedef struct
{
    unsigned short x;       //!< Horizontal start point.
    unsigned short y;       //!< Vertical start point.
    unsigned short w;       //!< Horizontal size.
    unsigned short h;       //!< Vertical size.
} hccast_um_av_area_t;

typedef struct
{
    hccast_um_av_area_t src_rect;
    hccast_um_av_area_t dst_rect;
} hccast_um_zoom_info_t;

typedef struct
{
    int rotate_angle;
    int flip_mode;
} hccast_um_rotate_info_t;

typedef struct
{
    hccast_um_av_area_t src_rect;
    hccast_um_av_area_t dst_rect;
    int preview_en;
} hccast_um_preview_info_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*hccast_um_cb)(int, void *, void *);

int hccast_um_init(void);
int hccast_um_deinit(void);
int hccast_um_param_set(hccast_um_param_t *param);
int hccast_um_param_get(hccast_um_param_t *param);
int hccast_um_reset_video(void);
int hccast_um_es_dump_start(char *folder);
int hccast_um_es_dump_stop(void);

int hccast_ium_init(hccast_um_cb event_cb);
int hccast_ium_start(char *uuid, hccast_um_cb event_cb);
int hccast_ium_stop(void);
int hccast_ium_stop_mirroring();
int hccast_ium_set_upg_buf(unsigned char *buf, unsigned int len);
int hccast_ium_set_frm_buf(unsigned char *buf, unsigned int len);
int hccast_ium_set_audio_onoff(int on);
int hccast_ium_slave_start(unsigned char usb_port, const char *udc_name, hccast_um_dev_type_e type);
int hccast_ium_slave_stop(unsigned char usb_port);
int hccast_ium_set_resolution(int width, int height);
int hccast_ium_set_demo_mode(int enable);

int hccast_aum_init(hccast_um_cb event_cb);
int hccast_aum_start(hccast_aum_param_t *param, hccast_um_cb event_cb);
int hccast_aum_stop(void);
int hccast_aum_stop_mirroring(void);
int hccast_aum_set_upg_buf(unsigned char *buf, unsigned int len);
int hccast_aum_set_frm_buf(unsigned char *buf, unsigned int len);
int hccast_aum_set_resolution(hccast_aum_res_e res);
int hccast_aum_slave_start(unsigned char usb_port, const char *udc_name, hccast_um_dev_type_e type);
int hccast_aum_slave_stop(unsigned char usb_port);

// DEPRECATED. DO NOT USE THIS API PLEASE.
int hccast_um_ioctl(int cmd, void *param1, void *param2);

#ifdef __cplusplus
}
#endif

#endif

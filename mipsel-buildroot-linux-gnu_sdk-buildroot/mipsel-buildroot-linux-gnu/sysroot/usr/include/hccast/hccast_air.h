#ifndef __HCCAST_AIR_SERVICE_H__
#define __HCCAST_AIR_SERVICE_H__

typedef enum
{
    HCCAST_AIR_NONE,
    HCCAST_AIR_GET_SERVICE_NAME,
    HCCAST_AIR_GET_NETWORK_DEVICE,
    HCCAST_AIR_GET_MIRROR_RESOLUTION,
    HCCAST_AIR_GET_MIRROR_FRAME,
    HCCAST_AIR_GET_MIRROR_MODE,
    HCCAST_AIR_CHECK_4K_MODE,
    HCCAST_AIR_GET_NETWORK_STATUS,
    HCCAST_AIR_MIRROR_START,
    HCCAST_AIR_MIRROR_STOP,
    HCCAST_AIR_AUDIO_START,
    HCCAST_AIR_AUDIO_STOP,
    HCCAST_AIR_INVALID_CERT,
    HCCAST_AIR_BAD_NETWORK,
    HCCAST_AIR_HOSTAP_MODE_SKIP_URL,
    HCCAST_AIR_GET_MIRROR_ROTATION,
    HCCAST_AIR_GET_MIRROR_VSCREEN_AUTO_ROTATION,
    HCCAST_AIR_GET_FLIP_MODE,
    HCCAST_AIR_FAKE_LIB,
    HCCAST_AIR_URL_ENABLE_SET_DEFAULT_VOL,
    HCCAST_AIR_GET_MIRROR_FULL_VSCREEN,
    HCCAST_AIR_SET_AUDIO_VOL,
    HCCAST_AIR_GET_AIRP2P_PIN,
    HCCAST_AIR_GET_MIRROR_QUICK_MODE_NUM,
    HCCAST_AIR_GET_MIRROR_ROTATION_INFO,
    HCCAST_AIR_GET_ABDISCONNECT_STOP_PLAY_EN,
    HCCAST_AIR_GET_PREVIEW_INFO,	
    HCCAST_AIR_MAX,
} hccast_air_event_e;

typedef enum
{
    HCCAST_AIR_RES_1080P30,
    HCCAST_AIR_RES_1080P60,
    HCCAST_AIR_RES_720P30,
    HCCAST_AIR_RES_720P60,
} hccast_air_res_e;

typedef enum
{
    HCCAST_AIR_CMD_SET_RESOLUTION = 1,
} hccast_air_cmd_e;

typedef enum
{
    HCCAST_AIR_SCREEN_ROTATE_0,
    HCCAST_AIR_SCREEN_ROTATE_270,
    HCCAST_AIR_SCREEN_ROTATE_90,
    HCCAST_AIR_SCREEN_ROTATE_180,
} hccast_air_rotate_type_e;

typedef struct
{
    int video_width;
    int video_height;
}hccast_air_mirror_t;

typedef struct
{
    int rotate_angle;
    int flip_mode;
}hccast_air_rotation_t;

typedef struct
{
    unsigned short x;		//!< Horizontal start point.
    unsigned short y;		//!< Vertical start point.
    unsigned short w;		//!< Horizontal size.
    unsigned short h;		//!< Vertical size.
} hccast_air_av_area_t;

typedef struct
{
    hccast_air_av_area_t src_rect;
    hccast_air_av_area_t dst_rect;
    int preview_en;
} hccast_air_preview_info_t;

typedef int (*hccast_air_event_callback) (hccast_air_event_e event_type, void* in, void* out);

#ifdef __cplusplus
extern "C" {
#endif

int hccast_air_service_init(hccast_air_event_callback aircast_cb);
int hccast_air_service_start(void);
int hccast_air_service_stop(void);
int hccast_air_ap_mirror_stat(void);
int hccast_air_ap_audio_stat(void);
void hccast_air_mdnssd_start(void);
void hccast_air_mdnssd_stop(void);
void hccast_air_mediaplayer_2_aircast_event(int type, void *param);
int hccast_air_ap_get_mirror_frame_num(void);
int hccast_air_service_is_start(void);
void hccast_air_set_resolution(int width, int height, int frame_num);
int hccast_air_es_dump_start(char *folder);
int hccast_air_es_dump_stop(void);  
int hccast_air_stop_playing(void);
int hccast_air_p2p_start(char *intf_name, int chan_num);
int hccast_air_get_connect_status(void);

// DEPRECATED. DO NOT USE THIS API PLEASE.
int hccast_air_ioctl(int cmd, void *arg);

#ifdef __cplusplus
}
#endif

#endif

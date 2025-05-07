#ifndef __HCCAST_DIAL_SERVICE_H__
#define __HCCAST_DIAL_SERVICE_H__

#define DIAL_DEVICE_STR_LEN     (64)
#define DIAL_SERVICE_NAME_LEN   (64)
#define DIAL_UPNP_PORT          (49595)
#define DIAL_BIND_IFNAME        ("wlan0")

typedef enum 
{
    HCCAST_DIAL_NONE = 0,
    HCCAST_DIAL_GET_SVR_NAME,
    HCCAST_DIAL_CONN_CONNECTING = 0x10,
    HCCAST_DIAL_CONN_CONNECTED,
    HCCAST_DIAL_CONN_CONNECTED_FAILED,
    HCCAST_DIAL_CONN_DISCONNECTED,
    HCCAST_DIAL_CONN_DISCONNECTED_ALL,
    HCCAST_DIAL_CTRL_INVALID_CERT = 0x100,
    HCCAST_DIAL_CTRL_GET_VOL,
    HCCAST_DIAL_USER_OP           = 0x200,
    HCCAST_DIAL_USER_ADD_VIDEO,
    HCCAST_DIAL_USER_DEL_VIDEO,
    HCCAST_DIAL_USER_ADD_PLAYLIST,
    HCCAST_DIAL_USER_DEL_PLAYLIST,
    HCCAST_DIAL_MAX   = 0xFFFFFFFF,
} hccast_dial_event_e;

typedef struct _dial_device_st_
{
    char device_name[DIAL_DEVICE_STR_LEN];
    char device_id[DIAL_DEVICE_STR_LEN];
    char *userAvatarUri;
    char *userName;
    unsigned int res[4];
} hccast_dial_device_conn_st;

typedef int (*hccast_dial_event_callback)(hccast_dial_event_e event, void *in, void *out);

#ifdef __cplusplus
extern "C" {
#endif

int hccast_dial_service_init(hccast_dial_event_callback func);
int hccast_dial_service_uninit(void);
int hccast_dial_service_start(void);
int hccast_dial_service_stop(void);
int hccast_dial_service_is_started(void);
int hccast_dial_set_video_quality(unsigned char quality);

#ifdef __cplusplus
}
#endif

#endif

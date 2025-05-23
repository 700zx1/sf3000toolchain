#ifndef __HCCAST_DLNA_SERVICE_H__
#define __HCCAST_DLNA_SERVICE_H__

#define DLNA_SERVICE_NAME_LEN (64)
#define DLNA_UPNP_PORT (49595)
#define DLNA_BIND_IFNAME ("wlan0")

typedef enum
{
    HCCAST_DLNA_NONE = 0,
    HCCAST_DLNA_GET_DEVICE_NAME,
    HCCAST_DLNA_GET_HOSTAP_STATE,
    HCCAST_DLNA_HOSTAP_MODE_SKIP_URL,
    HCCAST_DLNA_GET_SAVE_AUDIO_VOL,
    HCCAST_DLNA_INVALID_CERT,
    HCCAST_DLNA_GET_DEVICE_PARAM,
    HCCAST_DLNA_MAX,
} hccast_dlna_event_e;

typedef struct
{
    struct output_module *output;   // media output cb, required
    const char *ifname;             // upnp/dlna svr listen ifname, default "wlan0", option
    const char *svrname;            // upnp/dlna svr name, required
    int svrport;                    // upnp/dlna svr listen port, default 49494, option
} hccast_dlna_param;

typedef int (*hccast_dlna_event_callback)(hccast_dlna_event_e event, void* in, void* out);

#ifdef __cplusplus
extern "C" {
#endif

int hccast_dlna_service_init(hccast_dlna_event_callback func);
int hccast_dlna_service_uninit(void);
int hccast_dlna_service_start(void);
int hccast_dlna_service_stop(void);
int hccast_dlna_service_is_start(void);


#ifdef __cplusplus
}
#endif

#endif

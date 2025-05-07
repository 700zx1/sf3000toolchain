#ifndef _DIAL_API_H
#define _DIAL_API_H

//#include <stdint.h>

typedef enum
{
    DIAL_RET_NO_ERROR = 0,
    DIAL_RET_MEM,
    DIAL_RET_PARAMS_ERROR,
    DIAL_RET_USER_ABORT_HANDLE,

    DIAL_RET_LIBCURL_ERROR = 10,
    DIAL_RET_LIBCURL_CONNECT_FAILED,
    DIAL_RET_LIBCURL_TIMEOUT,
    DIAL_RET_LIBCURL_DOWNLOAD_FAILED,

    DIAL_RET_HANDLE_ERROR = 100,
    DIAL_RET_HANDLE_WAITING,

    DIAL_RET_NET_ERROR,
    DIAL_RET_RESPONES_ERRORS = 400,
} dial_ret_e;

typedef struct
{
    int media_type; // 0: audio; 1: video
    char *url;
    char *title;
} dial_media_info_t;

typedef enum
{
    DIALR_OK = 0,
    DIALR_ERR = 0,
    DIALR_PARAM_ERR,
    DIALR_CB_NOT_SET,
    DIALR_PLAY_FAILED,
    DIALR_UNSUPPORTED,
    DIALR_UNDEFINED,
} dialr_code_e;

typedef enum
{
    DIAL_EVENT_NONE     = 0,
    DIAL_EVENT_UI       = 0x100,
    DIAL_EVENT_NOTIFY   = 0x200,
    DIAL_EVENT_CTRL     = 0x300,
    DIAL_EVENT_PARSER   = 0x400,
} dial_event_type;

typedef enum
{
    DIAL_EVENT_CTRL_SET_WATCH_ID,
    DIAL_EVENT_CTRL_GET_URL,
    DIAL_EVENT_CTRL_SET_VOL,
    DIAL_EVENT_CTRL_GET_VOL,
    DIAL_EVENT_CTRL_GET_POS,
    DIAL_EVENT_CTRL_GET_DUR,
    DIAL_EVENT_CTRL_GET_STAT,
    DIAL_EVENT_CTRL_SEEK,
    DIAL_EVENT_CTRL_STOP,
    DIAL_EVENT_CTRL_PLAY,
    DIAL_EVENT_CTRL_PAUSE,
    DIAL_EVENT_CTRL_UNSUPPORTED,
    DIAL_EVENT_CTRL_INVALID_CERT,
} dial_event_ctrl_act;

typedef enum
{
    DIAL_STATUS_EXIT_LOOP = 0,
    DIAL_STATUS_PLAYING,
    DIAL_STATUS_PAUSED,
    DIAL_STATUS_LOADING,
    DIAL_STATUS_STOPPED,
    DIAL_STATUS_LOOP,
} dial_play_stat_e;

typedef enum
{
    DIAL_EVENT_CONN_CONNECTING,
    DIAL_EVENT_CONN_CONNECTED,
    DIAL_EVENT_CONN_CONNECTED_FAILED,
    DIAL_EVENT_CONN_DISCONNECTING,
    DIAL_EVENT_CONN_DISCONNECTED,
    DIAL_EVENT_CONN_DISCONNECTED_FAILED,
    DIAL_EVENT_CONN_DISCONNECTED_ALL,
    DIAL_EVENT_CONN_UNSUPPORTED,
    DIAL_EVENT_USER_ADD_VIDEO,
    DIAL_EVENT_USER_DEL_VIDEO,
    DIAL_EVENT_USER_ADD_PLAYLIST,
    DIAL_EVENT_USER_DEL_PLAYLIST,
} dial_event_ui_act;

typedef struct
{
    dial_event_type type;
    int act;
    void *in;
    void *out;
} dial_event_t;

typedef struct
{
    char stat;
    char res[3];
    char *app;
    char *user;
    char *userAvatarUri;
    char *name;
    char *type;
    char *id;
} dial_device_t;

typedef int (*dial_fn_event)(dial_event_t *event, ...);

struct dial_svr_param
{
    const char *ifname;     // upnp/dlna svr listen ifname, default "wlan0", option
    const char *svrname;    // upnp/dlna svr name, required
    int svrport;            // upnp/dlna svr listen port, default 49494, option
    dial_fn_event event_cb; // upnp/dlna svr event callback, option
};

#define DIAL_DEVICE_STR_LEN 64

typedef struct
{
    char device_name[DIAL_DEVICE_STR_LEN];
    char device_id[DIAL_DEVICE_STR_LEN];
    char *userAvatarUri;
    char *userName;
    unsigned int res[4];
} dial_device_conn_st;

/****************************************************************************************************/

int dial_service_init(dial_fn_event func);

/**
 * > Set the log level for the DLNA library
 *
 * @param level The log level to set.  This is a bitmask of the following values:
 *
 * @return The return value is the log level.
 */
int dial_set_log_level(int level);

/**
 * > Get the log level for the DLNA library
 *
 * @return The return value is the log level.
 */
int dial_get_log_level(void);

/**
 * It initializes the UPnP device and starts the UPnP server
 *
 * @param param the parameter structure of the DLNA server
 *
 * @return The return value is the result of the function.
 */
int dial_service_start(struct dial_svr_param *param);

/**
 * It stops the DLNA server
 */
int dial_service_stop(void);

/**
 * It get the dlna lib build version string
 *
 * @return The return value is build version string.
 */
char *dial_get_version();

#endif

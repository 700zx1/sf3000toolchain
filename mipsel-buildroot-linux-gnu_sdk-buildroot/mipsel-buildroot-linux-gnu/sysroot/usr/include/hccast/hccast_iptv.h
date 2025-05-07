#ifndef __HCCAST_IPTV__
#define __HCCAST_IPTV__

#include <stdbool.h>
#include <time.h>
#include "hccast_list.h"

#define HCCAST_IPTV_APP_YT      (0)
#define HCCAST_IPTV_APP_YP      (1)
#define HCCAST_IPTV_APP_MAX     (10)

#define HCCAST_IPTV_THUMB_MAX   (5)

#define BIT(nr) (1UL << (nr))

// iptv events
typedef enum
{
    HCCAST_IPTV_PAGE_CURR,
    HCCAST_IPTV_PAGE_PREV,
    HCCAST_IPTV_PAGE_NEXT,
} hccast_iptv_page_direction;

typedef enum
{
    HCCAST_IPTV_EVT_TIMEOUT,                    //action timeout
    HCCAST_IPTV_EVT_NETWORK_ERR,                //network error
    HCCAST_IPTV_EVT_NOT_SUPPORT,                //not support action
    HCCAST_IPTV_EVT_CATEGORY_FETCH_ERR = 1,    //cannot fetch category
    HCCAST_IPTV_EVT_CATEGORY_FETCH_OK,         //fetch category success
    HCCAST_IPTV_EVT_CATEGORY_OPEN_ERR,          //cannot open category
    HCCAST_IPTV_EVT_CATEGORY_OPEN_OK,           //open category success
    HCCAST_IPTV_EVT_VIDEO_NOT_EXIST,            //no video link detected
    HCCAST_IPTV_EVT_VIDEO_FETCH_OK,            //get video link done
    HCCAST_IPTV_EVT_VIDEO_FETCH_ERR,           //cannot get the video link
    HCCAST_IPTV_EVT_NEXT_PAGE_ERR,              //cannot goto next page
    HCCAST_IPTV_EVT_NEXT_PAGE_OK,               //goto next page done
    HCCAST_IPTV_EVT_NO_PAGES,
    HCCAST_IPTV_EVT_SEARCH_ERR,
    HCCAST_IPTV_EVT_SEARCH_OK,
    HCCAST_IPTV_EVT_INVALID_CERT,
} hccast_iptv_evt_e;

typedef enum
{
    HCCAST_IPTV_RET_NO_ERROR = 0,
    HCCAST_IPTV_RET_STREAM_LIMIT,
    HCCAST_IPTV_RET_STREAM_CIPHER,
    HCCAST_IPTV_RET_MEM,
    HCCAST_IPTV_RET_PARAMS_ERROR,
    HCCAST_IPTV_RET_USER_ABORT_HANDLE,

    HCCAST_IPTV_RET_LIBCURL_ERROR = 10,
    HCCAST_IPTV_RET_LIBCURL_CONNECT_FAILED,
    HCCAST_IPTV_RET_LIBCURL_TIMEOUT,
    HCCAST_IPTV_RET_LIBCURL_DOWNLOAD_FAILED,

    HCCAST_IPTV_RET_DECODE_ERROR = 100,
    HCCAST_IPTV_RET_JSON_PARSE_ERROR,
    HCCAST_IPTV_RET_PCRE_COMPILE_ERROR,
    HCCAST_IPTV_RET_PCRE_EXEC_ERROR,
    HCCAST_IPTV_RET_PCRE_NOMATCH,
    HCCAST_IPTV_RET_DECRYPT_PARAM_ERROR,

    HCCAST_IPTV_RET_HANDLE_ERROR = 200,
    HCCAST_IPTV_RET_HANDLE_WAITING,

    HCCAST_IPTV_RET_NET_ERROR,
    HCCAST_IPTV_RET_RESPONES_ERRORS = 400,
} hccast_iptv_ret_e;

typedef enum
{
    HCCAST_IPTV_VIDEO_NONE      = 0,
    HCCAST_IPTV_VIDEO_144P      = BIT(0),
    HCCAST_IPTV_VIDEO_240P      = BIT(1),
    HCCAST_IPTV_VIDEO_360P      = BIT(2),
    HCCAST_IPTV_VIDEO_480P      = BIT(3),
    HCCAST_IPTV_VIDEO_720P      = BIT(4),
    HCCAST_IPTV_VIDEO_1080P     = BIT(5),
    HCCAST_IPTV_VIDEO_1440P     = BIT(6),   // unsupported
    HCCAST_IPTV_VIDEO_2160P     = BIT(7),   // unsupported

    HCCAST_IPTV_VIDEO_720P60    = BIT(16),
    HCCAST_IPTV_VIDEO_1080P60   = BIT(17),  // unsupported
    HCCAST_IPTV_VIDEO_1440P60   = BIT(18),  // unsupported
    HCCAST_IPTV_VIDEO_2160P60   = BIT(19),  // unsupported
} hccast_iptv_video_quality_e;

typedef enum
{
    HCCAST_IPTV_CODECS_NONE     = 0,
    HCCAST_IPTV_CODECS_AVC      = BIT(0),
    HCCAST_IPTV_CODECS_VP9      = BIT(1),   // unsupported
    HCCAST_IPTV_CODECS_AV1      = BIT(2),   // unsupported
    HCCAST_IPTV_CODECS_MPEG4    = BIT(3),   // mp4a.40.2: means audio codecs AAC LC (Low Complexity)
    HCCAST_IPTV_CODECS_OPUS     = BIT(4),
} hccast_iptv_video_mimeType_e;

typedef enum 
{
	MIME_OPTION_NONE            = 0,
	MIME_OPTION_IS_VIDEO        = BIT(0),
	MIME_OPTION_IS_AUDIO        = BIT(1),
	MIME_OPTION_IS_DASH         = BIT(2),
	MIME_OPTION_IS_HLS          = BIT(3),
} mime_option_e;

typedef enum
{
    HCCAST_IPTV_SEARCH_TYPE_VIDEO        = BIT(0),
    HCCAST_IPTV_SEARCH_TYPE_CHANNEL      = BIT(1),
    HCCAST_IPTV_SEARCH_TYPE_PLAYLIST     = BIT(2),

    HCCAST_IPTV_SEARCH_ORDER_DATE        = BIT(5),
    HCCAST_IPTV_SEARCH_ORDER_RATING      = BIT(6),
    HCCAST_IPTV_SEARCH_ORDER_RELEVANCE   = BIT(7),
    HCCAST_IPTV_SEARCH_ORDER_TITLE       = BIT(8),
    HCCAST_IPTV_SEARCH_ORDER_VIDEOCOUNT  = BIT(9),
    HCCAST_IPTV_SEARCH_ORDER_VIEWCOUNT   = BIT(10),

    HCCAST_IPTV_VIDEO_OPTION_MAX         = 0xFFFFFFFF,
} hccast_iptv_search_option_e;

typedef struct
{
    char region[8];                     // region code, i18n string
    char part[128];                     // part, string. warning: Only modify it if you understand what you are doing
    char chart[128];                    // chart, string. warning: Only modify it if you understand what you are doing
    char api_key[64];                   // api key, string. warning: Only modify it if you understand what you are doing
    char page_max[16];                  // max page number, string
    unsigned char timeout;              // api timeout
    bool cate_fetch_net;                // fetch category from network
    char log_level;                     // log level
    unsigned int quality_option;        // supported quality option
    unsigned int down_buf_size;         // download buffer size
    unsigned short link_lifetime;       // link lifetime
    char service_addr[128];             // service address
    char service_token[128];            // service token
} hccast_iptv_app_config_st;

typedef struct
{
    char cate_id[16];                       // category id
    char cate_name[32];                     // category name
    char cate_etag[32];                     // category etag
} hccast_iptv_cate_node_st;

typedef struct
{
    list_t list;
    int cate_num;
} hccast_iptv_cate_st;

typedef struct
{
    char channel_id[16];                    // category id
    char channel_name[32];                  // category name
    char channel_etag[32];                  // category etag
} hccast_iptv_channel_node_st;

typedef struct
{
    list_t list;
    int channel_num;
} hccast_iptv_channel_st;

typedef struct
{
    char quality[16];                       // quality label
    char *url;                              // url
} hccast_iptv_thumb_node_st;

typedef struct
{
    char id[32];                            // video id
    char quality[16];                       // quality label
    char quality_label[16];                 // quality label
    unsigned quality_option;                // quality option items
    int  itag;                              // video tags (represents format and quality)
    unsigned bitrate;                       // bitrate (formate)
    unsigned avg_bitrate;                   // average bitrate (hls)
    char *mimeType;                         // mime info
    char *projectionType;                   // reserve
    char *url;                              // url
    unsigned mime_option;                   // mime option
    unsigned short width;                   // video width
    unsigned short height;                  // video height
    unsigned short fps;                     // video fps
    unsigned short res;                     // reserved
    unsigned contentLength;                 // content length
} hccast_iptv_links_node_st;

typedef struct
{
    list_t list;
    char id[32];
    unsigned quality_option;
    void *extra_info;
    time_t last_modify;
} hccast_iptv_links_st;

typedef struct
{
    char id[32];                            // video id
    char ch_id[32];                         // channel id
    char cate_id[16];                       // category id
    char lang[8];                           // audio default lang
    char *title;                            // video title
    char *ch_title;                         // channel title
    char *descr;                            // video description
    char *tags;                             // video tags (unused)
    char url_parse;                         // video parses flag
    char type;                              // video type (0: vod, 1: live)
    char res[2];                            // reserved
    char *duration;                         // contentDetails PT1h2M3S
    char *dimension;                        // contentDetails "2d"
    char *definition;                       // contentDetails "HD"
    char res1[4];
    unsigned long viewCount;                // statistics
    unsigned long likeCount;                // statistics
    unsigned long favoriteCount;            // statistics
    unsigned long commentCount;             // statistics
    hccast_iptv_thumb_node_st thumb[HCCAST_IPTV_THUMB_MAX];
    hccast_iptv_links_st *links;
} hccast_iptv_info_node_st;

typedef struct
{
    list_t list;
    char cate_id[8];                        // cate id
    char res[8];                            // reserved
    char *key_word;                         // key_word
    int  info_num;                          // video info per page
    int  info_total_num;                    // video info total num
    char next_page_token[12];               // next page token
    char prev_page_token[12];               // prev page token
} hccast_iptv_info_list_st;

typedef struct
{
    char cate_id[8];                        // [input]  category id
    char *video_id;                         // [input]  video id
    char type;                              // [input]  0: category, 1: video, 2: trend
    char res[3];                            // [input]  category
    char page_token[12];                    // [input]  page token
    unsigned option;                        // [input]  option
    hccast_iptv_info_list_st *list_node;    // [output] category detail info
} hccast_iptv_cate_req_st;

typedef struct
{
    char channel_id[16];                    // [input]  category total num
    char page_token[12];                    // [input]  page token
    unsigned option;                        // [input]  option
    hccast_iptv_info_list_st *list_node;    // [output] category detail info
} hccast_iptv_channel_req_st;

typedef struct
{
    char *key_word;                         // [input]  key word
    char page_token[12];                    // [input]  page token
    char relevance_language[12];            // [input]  reserve
    unsigned option;                        // [input]  option
    hccast_iptv_info_list_st *list_node;    // [output] search list detail info
} hccast_iptv_search_req_st;

typedef struct
{
    char id[32];                            // [input]  video id
    unsigned option;                        // [output] supported quality option
    unsigned cur_option;                    // [output] current url quality option
    char url[3072];                         // [output] url for best quality option
    hccast_iptv_info_node_st *extra_info;
} hccast_iptv_info_req_st;

typedef struct
{
    unsigned cur_option;                    // [input]  current url quality option
    char url[3072];                         // [output] url for current select quality option
    unsigned rate;
} hccast_iptv_links_req_st;

typedef void (*hccast_iptv_notifier)(hccast_iptv_evt_e evt, void *arg);

typedef struct
{
    unsigned int initialized;
    char app_title[16];
    int (*init)(const hccast_iptv_app_config_st *config, hccast_iptv_notifier notifier);
    int (*deinit)(void);
    int (*conf_get)(hccast_iptv_app_config_st *conf);
    int (*conf_set)(const hccast_iptv_app_config_st *conf);
    int (*cate_get)(hccast_iptv_cate_st **cate_out);
    int (*cate_fetch)(hccast_iptv_cate_req_st *req, hccast_iptv_info_list_st **list_out);
    int (*channel_get)(hccast_iptv_channel_st **channel_out);
    int (*channel_fetch)(hccast_iptv_channel_req_st *req, hccast_iptv_info_list_st **list_out);
    int (*search_fetch)(hccast_iptv_search_req_st *req, hccast_iptv_info_list_st **list_out);
    int (*page_get)(hccast_iptv_page_direction direction, hccast_iptv_info_list_st **list_out);
    int (*link_fetch)(hccast_iptv_info_req_st *req, hccast_iptv_links_st **links);
    int (*link_switch)(hccast_iptv_links_req_st *req, hccast_iptv_links_st **links);
    int (*handle_abort)(void);
    int (*handle_flush)(void);
} hccast_iptv_app_instance_st;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The function `hccast_iptv_app_register` registers an IPTV application instance with a given ID.
 *
 * @param app_id The `app_id` parameter is an integer representing the ID of the IPTV application being
 * registered.
 * @param inst The `inst` parameter is a pointer to an instance of a structure type
 * `hccast_iptv_app_instance_st`.
 *
 * @return 0
 *
 * @note It is called by plugin, users don't need to care. implement by plugin.
 */
int hccast_iptv_app_register(int app_id, hccast_iptv_app_instance_st *inst);

/**
 * The function hccast_iptv_attach_yt registers a yt application instance with specific function
 * pointers for initialization, deinitialization, configuration, category fetching, searching, page
 * retrieval, link fetching, and error handling.
 *
 * @return The function `hccast_iptv_attach_yt` is returning the value `HCCAST_IPTV_RET_NO_ERROR`.
 *
 * @note It is called by hccast itself, Users don't need to care. implement by plugin.
 */
int hccast_iptv_attach_yt(void);

/**
 * The function `hccast_iptv_service_init` initializes all IPTV services by locking a mutex, checking if
 * the service is already initialized, and initializing it if not.
 *
 * @return an integer value of 0.
 *
 * @note call only once at system initialized stage.
 */
int hccast_iptv_service_init(void);

/**
 * The function `hccast_iptv_service_app_init` initializes an IPTV service application interface.
 *
 * @param app_id The `app_id` parameter is an integer value representing the ID of the IPTV service
 * application that is being initialized.
 *
 * @return The function `hccast_iptv_service_app_init` is returning 0.
 *
 * @note app service dependent interface, Must be called before app function calling.
 */
int hccast_iptv_service_app_init(int app_id);

/**
 * The function `hccast_iptv_app_open` returns a pointer to the `g_iptv_inst` array element
 * corresponding to the given `app_id` if it is within bounds and initialized.
 *
 * @param app_id The `app_id` parameter is an integer value representing the ID of the IPTV application
 * that you want to open.
 *
 * @return A pointer to the `g_iptv_inst` structure at index `app_id` is being returned.
 *
 * @note It should be called after hccast_iptv_service_app_init calls
 */
void *hccast_iptv_app_open(int app_id);

/**
 * This function retrieves the configuration settings for an IPTV application instance.
 *
 * @param inst A pointer to an instance of the IPTV application.
 * @param conf conf is a pointer to a structure of type hccast_iptv_app_config_st, which is used to
 * store the configuration settings for an IPTV application. The function hccast_iptv_config_get()
 * retrieves the configuration settings from the application instance pointed to by inst and stores
 * them in
 *
 * @return the result of calling the `conf_get` function of the `app_inst` object with the `conf`
 * parameter passed as an argument. The return type of the `conf_get` function is not specified in the
 * code snippet, so it is unclear what is being returned. However, the function signature suggests that
 * it should return an integer value.
 */
int hccast_iptv_config_get(void *inst, hccast_iptv_app_config_st *config);

/**
 * This function sets the configuration for an IPTV application instance.
 *
 * @param inst A pointer to an instance of the hccast_iptv_app_instance_st struct, which represents an
 * instance of an IPTV application.
 * @param conf A pointer to a structure of type hccast_iptv_app_config_st, which contains the
 * configuration settings for an IPTV application.
 *
 * @return the result of calling the `conf_set` function of the `app_inst` object with the `conf`
 * parameter passed to the function. The return type of the `conf_set` function is not specified in the
 * code snippet, so it is unclear what is being returned by the `hccast_iptv_config_set` function.
 * However, the function signature suggests that it
 */
int hccast_iptv_config_set(void *inst, const hccast_iptv_app_config_st *config);

/**
 * The function `hccast_iptv_app_init` initializes an IPTV application instance with a given
 * configuration and notifier.
 *
 * @param inst The `inst` parameter is a void pointer that points to an instance of the
 * `hccast_iptv_app_instance_st` structure.
 * @param config The `config` parameter in the `hccast_iptv_app_init` function is of type
 * `hccast_iptv_app_config_st *`, which is a pointer to a structure of type
 * `hccast_iptv_app_config_st`. This structure likely contains configuration settings or
 * @param notifier The `notifier` parameter in the `hccast_iptv_app_init` function is of type
 * `hccast_iptv_notifier`. It is a function pointer that points to a function responsible for notifying
 * events related to the IPTV application.
 *
 * @return the result of calling the `init` function of the `app_inst` instance with the provided
 * `config` and `notifier` parameters.
 */
int hccast_iptv_app_init(void *inst, const hccast_iptv_app_config_st *config, hccast_iptv_notifier notifier);

/**
 * The function `hccast_iptv_app_deinit` deinitialize an IPTV application instance.
 *
 * @param inst The `inst` parameter is a void pointer that points to an instance of the
 * `hccast_iptv_app_instance_st` structure.
 *
 * @return the result of calling the `deinit` function stored in the `app_inst` structure.
 */
int hccast_iptv_app_deinit(void *inst);

/**
 * The function retrieves IPTV categories from an initialized app instance.
 *
 * @param inst A void pointer to an instance of the hccast_iptv_app_instance_st struct, which contains
 * information about the IPTV application instance.
 * @param cate A pointer to a pointer of hccast_iptv_category_node_st, which is a struct representing a
 * node in a linked list of IPTV categories. This function is used to retrieve the current category
 * node from the IPTV app instance.
 *
 * @return an integer value. If the function execution is successful, it will return 0. If there is an
 * error, it will return -1.
 */
hccast_iptv_ret_e hccast_iptv_cate_get(void *inst, hccast_iptv_cate_st **cate);

/**
 * This function fetches IPTV categories and returns a list of nodes.
 *
 * @param inst A void pointer to an instance of the hccast_iptv_app_instance_st struct, which contains
 * information about the IPTV application instance.
 * @param req hccast_iptv_cate_req_st is a structure that contains the request parameters for fetching
 * IPTV categories. The exact contents of this structure are not shown in the code snippet provided.
 * @param list_out A pointer to a pointer of hccast_iptv_info_list_st, which is the output parameter
 * that will contain the fetched IPTV category list.
 *
 * @return an integer value. The specific value depends on the execution of the function. If the
 * function executes successfully, it will return a value of 0 or a positive integer. If there is an
 * error, it will return a negative integer.
 */
hccast_iptv_ret_e hccast_iptv_cate_fetch(void *inst, hccast_iptv_cate_req_st *req, hccast_iptv_info_list_st **list_out);

/**
 * This function searches for IPTV channels and returns a list of nodes.
 *
 * @param inst A void pointer to an instance of the hccast_iptv_app_instance_st struct, which contains
 * information about the application instance.
 * @param req req is a pointer to a structure of type hccast_iptv_search_req_st, which contains the
 * search request parameters.
 * @param list_out list_out is a pointer to a pointer of hccast_iptv_info_list_st, which is an output
 * parameter. The function hccast_iptv_search will populate this parameter with a linked list of search
 * results.
 *
 * @return a value of type hccast_iptv_ret_e, which is likely an enumerated type representing different
 * return codes or error states. The specific value being returned depends on the execution of the
 * function and the values of the input parameters.
 */
hccast_iptv_ret_e hccast_iptv_search_fetch(void *inst, hccast_iptv_search_req_st *req, hccast_iptv_info_list_st **list_out);

/**
 * This function handles abort events for an IPTV application instance.
 *
 * @param inst The "inst" parameter is a void pointer to an instance of a structure or object. In this
 * case, it is being cast to a pointer of type "hccast_iptv_app_instance_st" using a typecast.
 *
 * @return the value returned by the `app_inst->handle_abort()` function, which is of type
 * `hccast_iptv_ret_e`.
 */
hccast_iptv_ret_e hccast_iptv_handle_abort(void *inst);

/**
 * This function handles flush all cache (include video list, video links etc.) for an IPTV application instance.
 *
 * @param inst The "inst" parameter is a void pointer to an instance of a structure or object. In this
 * case, it is being cast to a pointer of type "hccast_iptv_app_instance_st" using a typecast.
 *
 * @return the value returned by the `app_inst->handle_flush()` function, which is of type
 * `hccast_iptv_ret_e`.
 */
hccast_iptv_ret_e hccast_iptv_handle_flush(void *inst);

/**
 * This function retrieves a list of IPTV pages in the direction (only supported video list. no include video search).
 *
 * @param inst A void pointer to an instance of the hccast_iptv_app_instance_st struct, which contains
 * information about the IPTV application instance.
 * @param direction an enum type variable of hccast_iptv_page_direction, which specifies the direction
 * of the page to be retrieved. It can have one of the following values:
 * @param list_out A pointer to a pointer of hccast_iptv_info_list_st, which will be used to return the
 * list of IPTV pages.
 *
 * @return an integer value, which could be either a success code or an error code. The specific
 * meaning of the return value depends on the implementation of the function and the context in which
 * it is called.
 */
hccast_iptv_ret_e hccast_iptv_page_get(void *inst, hccast_iptv_page_direction direction, hccast_iptv_info_list_st **list_out);

/**
 * This function fetches IPTV links based on a request and returns an error code.
 *
 * @param inst A void pointer to an instance of the hccast_iptv_app_instance_st struct, which contains
 * information about the application instance.
 * @param req A pointer to a structure containing information about the IPTV channel or program being
 * requested, such as the channel or program ID, start time, and duration.
 * @param links The "links" parameter is a double pointer to a structure of type
 * "hccast_iptv_links_node_st". This parameter is used to return the fetched IPTV links to the calling
 * function. The function "hccast_iptv_link_fetch" will allocate memory for the "h
 *
 * @return a value of type hccast_iptv_ret_e, which is likely an enumerated type representing different
 * error codes or success statuses. The specific value being returned depends on the execution of the
 * function and the values of the input parameters.
 */
hccast_iptv_ret_e hccast_iptv_link_fetch(void *inst, hccast_iptv_info_req_st *req, hccast_iptv_links_st **links);

/**
 * This function switches IPTV links based on a request and returns a status code.
 *
 * @param inst A void pointer to an instance of the hccast_iptv_app_instance_st struct, which contains
 * information about the application instance.
 * @param req A pointer to a structure containing information about the requested links.
 * @param links A pointer to a pointer of hccast_iptv_links_st, which is a struct that contains
 * information about IPTV links. The function hccast_iptv_link_switch will modify the value of this
 * pointer to point to a linked list of hccast_iptv_links_node
 *
 * @return a value of type hccast_iptv_ret_e, which is likely an enumerated type representing different
 * error codes or success statuses. The specific value being returned depends on the execution of the
 * function and the values of the input parameters.
 */
hccast_iptv_ret_e hccast_iptv_link_switch(void *inst, hccast_iptv_links_req_st *req, hccast_iptv_links_st **links);

#ifdef __cplusplus
}
#endif

#endif
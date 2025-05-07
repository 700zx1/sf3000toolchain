#ifndef __HCUAPI_VINDVP_H_
#define __HCUAPI_VINDVP_H_

#include <hcuapi/iocbase.h>
#include <hcuapi/kshm.h>
#include <hcuapi/tvtype.h>
#include <hcuapi/dis.h>
#include <hcuapi/viddec.h>

typedef enum VINDVP_VIDEO_DATA_PATH {
	VINDVP_VIDEO_TO_DE,
	VINDVP_VIDEO_TO_DE_ROTATE,
	VINDVP_VIDEO_TO_KSHM,
	VINDVP_VIDEO_TO_DE_AND_KSHM,
	VINDVP_VIDEO_TO_DE_ROTATE_AND_KSHM,
} vindvp_video_data_path_e;

typedef enum VINDVP_COMBINED_MODE {
	VINDVP_COMBINED_MODE_DISABLE,
	VINDVP_COMBINED_MODE_4_REGION,
} vindvp_combined_mode_e;

typedef enum VINDVP_COMBINED_CAPTURE_MODE {
	VINDVP_COMBINED_CAPTRUE_ORIGINAL,
	VINDVP_COMBINED_CAPTRUE_COMBINED,
} vindvp_combined_capture_mode_e;

typedef enum VINDVP_BG_COLOR {
	VINDVP_BG_COLOR_BLACK,
	VINDVP_BG_COLOR_BLUE,
} vindvp_bg_color_e;

typedef enum VINDVP_STOP_MODE {
	VINDVP_BLACK_SRCREEN_ANYWAY, //<! black screen anyway
	VINDVP_KEEP_LASTFRAME_ANYWAY, //<! keep last frame anyway
	VINDVP_KEEP_LASTFRAME_IF_NO_SIGNAL, //<! keep last frame screen when no signal stop
	VINDVP_KEEP_LASTFRAME_IF_HAS_SIGNAL, //<! keep last frame screen when have signal stop
} vindvp_stop_mode_e;

typedef struct vindvp_video_info {
	int width;
	int height;
	int frame_rate;
	int b_progressive;
} vindvp_video_info_t;

typedef enum VINDVP_YUV_BUF_CAPTURE_FORMAT {
	CAPTURE_FORMAT_YUV, //<! format:every pixel is 4 BYTE:VUY+0xFF
	CAPTURE_FORMAT_Y_ONLY, //<! capture y only

} vindvp_yuv_buf_capture_format_e;

typedef enum VINDVP_TO_KSHM_SCALE_MODE {
    VIN_DVP_TO_KSHM_SCALE_BY_FACTOR ,//<! scale by ratio:1/1,1/2,1/4,1/8
    VIN_DVP_TO_KSHM_SCALE_BY_SIZE ,  //<! scale by size
} vindvp_to_kshm_scale_mode_e;

typedef struct vindvp_to_kshm_setting {
	bool rotate_enable;                          //<! rotate enable
	bool scale_enable;                           //<! scale enable
	enum ROTATE_TYPE rotate_mode;                //<! enum ROTATE_TYPE
	enum MIRROR_TYPE mirror_mode;                //<! enum mirror_mode
	enum VINDVP_TO_KSHM_SCALE_MODE scale_mode;   //<! scale by factor or by size
	enum VIDDEC_SCALE_FACTOR scale_factor;       //<! scale by factor
	int scaled_width;                            //<! scaled width
	int scaled_height;                           //<! scaled height
	bool snapshot_enable;                        //<! 0:to khsm :video mode 1:to khsm :still piture mode mode
} vindvp_to_kshm_setting_t;

typedef struct vindvp_to_display_info {
	enum DIS_TYPE dis_type;
	enum DIS_LAYER dis_layer;
} vindvp_to_display_info_t;

#define VINDVP_START				_IO (VINDVP_IOCBASE,  0)
#define VINDVP_STOP				_IO (VINDVP_IOCBASE,  1)
#define VINDVP_ENABLE				_IO (VINDVP_IOCBASE,  2)
#define VINDVP_DISABLE				_IO (VINDVP_IOCBASE,  3)
#define VINDVP_SET_VIDEO_DATA_PATH		_IO (VINDVP_IOCBASE,  4)
#define VINDVP_VIDEO_KSHM_ACCESS		_IOR(VINDVP_IOCBASE,  5, struct kshm_info)
#define VINDVP_SET_VIDEO_ROTATE_MODE		_IO (VINDVP_IOCBASE,  6)
#define VINDVP_SET_COMBINED_MODE		_IO (VINDVP_IOCBASE,  7)
#define VINDVP_SET_COMBINED_REGION_FREEZE	_IOW(VINDVP_IOCBASE,  8, struct combine_region_freeze_cfg)
#define VINDVP_CAPTURE_ONE_PICTURE		_IO (VINDVP_IOCBASE,  9) //<! param: vindvp_combined_capture_mode_e
#define VINDVP_SET_EXT_DEV_INPUT_PORT_NUM	_IO (VINDVP_IOCBASE, 10)
#define VINDVP_SET_DISPLAY_LAYRER		_IO (VINDVP_IOCBASE, 11) //<! param: dis_layer_e in dis.h
#define VINDVP_NOTIFY_CONNECT			_IO (VINDVP_IOCBASE, 12)
#define VINDVP_NOTIFY_DISCONNECT		_IO (VINDVP_IOCBASE, 13)
#define VINDVP_SET_BG_COLOR			_IO (VINDVP_IOCBASE, 14) //<! param: enum VINDVP_BG_COLOR
#define VINDVP_SET_VIDEO_STOP_MODE		_IO (VINDVP_IOCBASE, 15) //<! param: enum VINDVP_STOP_MODE
#define VINDVP_SET_VIDEO_MIRROR_MODE		_IO (VINDVP_IOCBASE, 16) //<! param: enum MIRROR_TYPE, but for MIRROR_TYPE_UPDOWN, please using VINDVP_SET_VIDEO_ROTATE_MODE + MIRROR_TYPE_LEFTRIGHT
#define VINDVP_GET_VIDEO_INFO			_IOR(VINDVP_IOCBASE, 17, struct vindvp_video_info)
#define VINDVP_SET_YUV_BUF_CAPTURE_FORMAT	_IO (VINDVP_IOCBASE, 18) //<! param: enum VINDVP_YUV_BUF_CAPTURE_FORMAT
#define VINDVP_SET_YUV_BUF_CAPTURE_ROTATE_MODE	_IO (VINDVP_IOCBASE, 19) //<! param: enum ROTATE_TYPE
#define VINDVP_SET_TO_KSHM_SETTING		_IOW(VINDVP_IOCBASE, 20, struct vindvp_to_kshm_setting)
#define VINDVP_SET_EXT_DEV          		_IO (VINDVP_IOCBASE, 21) //<! param: external dev index, e.g 0/1/etc; this is for multiple external devices use scenario
#define VINDVP_SET_DISPLAY_INFO			_IOW(VINDVP_IOCBASE, 22, struct vindvp_to_display_info)
#define VINDVP_SET_DISPLAY_RECT			_IOW(VINDVP_IOCBASE, 23, struct vdec_dis_rect)

#endif /* __HCUAPI_TVDEC_H_ */

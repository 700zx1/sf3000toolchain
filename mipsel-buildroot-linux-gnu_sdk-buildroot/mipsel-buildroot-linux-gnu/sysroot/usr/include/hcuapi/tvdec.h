#ifndef __HCUAPI_TVDEC_H_
#define __HCUAPI_TVDEC_H_

#include <hcuapi/iocbase.h>
#include <hcuapi/kshm.h>
#include <hcuapi/tvtype.h>
#include <hcuapi/viddec.h>
#include <hcuapi/dis.h>

typedef enum TVDEC_TRAINING_STATUS {
	TVDEC_TRAINING_STATUS_SUCCESS,
	TVDEC_TRAINING_STATUS_FAIL,
} tvdec_training_status_e;

typedef enum TVDEC_VIDEO_DATA_PATH {
	TVDEC_VIDEO_TO_DE,
	TVDEC_VIDEO_TO_DE_ROTATE,
	TVDEC_VIDEO_TO_KSHM,
	TVDEC_VIDEO_TO_DE_AND_KSHM,
	TVDEC_VIDEO_TO_DE_ROTATE_AND_KSHM,
} tvdec_video_data_path_e;

typedef struct tvdec_video_info {
	tvtype_e tv_sys;
	int width;
	int height;
	int frame_rate;
	int b_progressive;
} tvdec_video_info_t;

typedef struct tvdec_training_result {
    tvdec_training_status_e status;
    uint8_t dc_offset_val;
} tvdec_training_result_t;

typedef struct tvdec_display_info {
	enum DIS_TYPE dis_type;
	enum DIS_LAYER dis_layer;
} tvdec_display_info_t;

#define TVDEC_START			_IO (TVDEC_IOCBASE, 0)
#define TVDEC_STOP			_IO (TVDEC_IOCBASE, 1)
#define TVDEC_SET_VIDEO_DATA_PATH	_IO (TVDEC_IOCBASE, 2)
#define TVDEC_VIDEO_KSHM_ACCESS		_IOR(TVDEC_IOCBASE, 3, struct kshm_info)
#define TVDEC_SET_VIDEO_ROTATE_MODE	_IO (TVDEC_IOCBASE, 4)
#define TVDEC_SET_VIDEO_MIRROR_MODE	_IO (TVDEC_IOCBASE, 5)
#define TVDEC_NOTIFY_CONNECT		_IO (TVDEC_IOCBASE, 6)
#define TVDEC_NOTIFY_DISCONNECT		_IO (TVDEC_IOCBASE, 7)
#define TVDEC_GET_VIDEO_INFO		_IOR(TVDEC_IOCBASE, 8, struct tvdec_video_info)
#define TVDEC_SET_VIDEO_STOP_MODE	_IO (TVDEC_IOCBASE, 9) //<! param: Keep last frame: 1, Black screen: 0
#define TVDEC_SET_TRAINING_START	_IO (TVDEC_IOCBASE, 10)
#define TVDEC_NOTIFY_TRAINING_FINISH	_IO (TVDEC_IOCBASE, 11)
#define TVDEC_GET_TRAINING_RESULT	_IOR(TVDEC_IOCBASE, 12, struct tvdec_training_result)
#define TVDEC_SET_DC_OFFSET		_IO (TVDEC_IOCBASE, 13) //<! param: 0x1-0xFE
#define TVDEC_SET_BRIGHTNESS		_IO (TVDEC_IOCBASE, 14) //<! param: 0-100
#define TVDEC_SET_DISPLAY_INFO		_IOW(TVDEC_IOCBASE, 15, struct tvdec_display_info)
#define TVDEC_SET_DISPLAY_RECT		_IOW(TVDEC_IOCBASE, 16, struct vdec_dis_rect)

#endif /* __HCUAPI_TVDEC_H_ */

#ifndef __HCUAPI_HDMI_CEC_H_
#define __HCUAPI_HDMI_CEC_H_

#include <hcuapi/iocbase.h>

#define HDMI_CEC_MAX_LEN 16
typedef struct hdmi_cec_info {
	unsigned char data[HDMI_CEC_MAX_LEN];
	unsigned data_len;
} hdmi_cec_info_t;

#define HDMI_CEC_SET_ONOFF			_IO  (HDMI_CEC_BASE,  1)			//<! param: 1: ON, 0: Off
#define HDMI_CEC_GET_ONOFF			_IOR (HDMI_CEC_BASE, 2, unsigned int)
#define HDMI_CEC_SEND_CMD			_IOW (HDMI_CEC_BASE, 3, struct hdmi_cec_info)
#define HDMI_CEC_GET_CMD			_IOR (HDMI_CEC_BASE, 4, struct hdmi_cec_info)
#define HDMI_CEC_SET_LOGIC_ADDR			_IO  (HDMI_CEC_BASE, 5)
#define HDMI_CEC_GET_LOGIC_ADDR			_IOR (HDMI_CEC_BASE, 6, unsigned int)
#define HDMI_CEC_SET_PHYSICAL_ADDR		_IO  (HDMI_CEC_BASE, 7)
#define HDMI_CEC_GET_PHYSICAL_ADDR		_IOR (HDMI_CEC_BASE, 8, unsigned int)

#endif /* __HCUAPI_HDMI_CEC_H_ */

#ifndef _HCUAPI_HDMI_SWITCH_MS9601_H_
#define _HCUAPI_HDMI_SWITCH_MS9601_H_

#include <hcuapi/iocbase.h>

typedef enum MS9601_PORT_IDX {
	MS9601_PORT_0 = 0,
	MS9601_PORT_1,
	MS9601_PORT_2,
	MS9601_PORT_MAX
} ms9601_idx_e;

#define MS9601A_SET_CH_SEL		_IO (HDMI_SWITCH_MS9601_IOCBASE, 0x01)	//<! param: enum MS9601_PORT_IDX
#define MS9601A_SET_CH_AUTO		_IO (HDMI_SWITCH_MS9601_IOCBASE, 0x02)	//<! param: none, Set channel auto detect

#endif	// _HCUAPI_HDMI_SWITCH_MS9601_H_


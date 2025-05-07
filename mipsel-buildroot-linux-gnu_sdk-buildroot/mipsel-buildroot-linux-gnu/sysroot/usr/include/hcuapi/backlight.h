#ifndef _HCUAPI_BACKLIGHT_H_
#define _HCUAPI_BACKLIGHT_H_

#include <hcuapi/iocbase.h>

#define BACKLIGHT_GET_INFO			_IOR (BACKLIGHT_IOCBASE, 1, struct backlight_info)
#define BACKLIGHT_SET_INFO			_IOW (BACKLIGHT_IOCBASE, 2, struct backlight_info)
#define BACKLIGHT_START				_IO (BACKLIGHT_IOCBASE, 3)
#define BACKLIGHT_STOP				_IO (BACKLIGHT_IOCBASE, 4)

#define BACKLIGHT_LEVEL_SIZE			(40)

struct backlight_info {
	unsigned int levels[BACKLIGHT_LEVEL_SIZE];
	unsigned int levels_count;
	unsigned int pwm_frequency;
	unsigned int pwm_polarity;
	unsigned int default_brightness_level;
	unsigned int brightness_value;
};

#endif

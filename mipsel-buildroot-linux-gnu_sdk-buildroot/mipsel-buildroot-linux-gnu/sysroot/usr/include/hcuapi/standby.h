#ifndef _HCUAPI_STANDBY_H_
#define _HCUAPI_STANDBY_H_

#include <hcuapi/iocbase.h>
#include <hcuapi/pinpad.h>
#ifndef __KERNEL__
#include <stdint.h>
#endif

#define STANDBY_SET_WAKEUP_BY_IR		_IOW(STANDBY_IOCBASE, 0, struct standby_ir_setting)
#define STANDBY_SET_WAKEUP_BY_GPIO		_IOW(STANDBY_IOCBASE, 1, struct standby_gpio_setting)
#define STANDBY_SET_WAKEUP_BY_SARADC		_IOW(STANDBY_IOCBASE, 2, struct standby_saradc_setting)
#define STANDBY_ENTER				_IO (STANDBY_IOCBASE, 3)
#define STANDBY_SET_PWROFF_DDR			_IOW(STANDBY_IOCBASE, 4, struct standby_pwroff_ddr_setting)
#define STANDBY_LOCKER_REQUEST			_IOW(STANDBY_IOCBASE, 5, struct standby_locker)
#define STANDBY_LOCKER_RELEASE			_IOW(STANDBY_IOCBASE, 6, struct standby_locker)
#define STANDBY_GET_BOOTUP_MODE			_IOR(STANDBY_IOCBASE, 7, enum standby_bootup_mode)
#define STANDBY_SET_WAKEUP_TIME			_IO (STANDBY_IOCBASE, 8)
#define STANDBY_GET_BOOTUP_SLOT			_IOR(STANDBY_IOCBASE, 9, unsigned long)
#define STANDBY_SET_BOOTUP_SLOT			_IO (STANDBY_IOCBASE, 9)
#define STANDBY_DDR_SCAN			_IO (STANDBY_IOCBASE, 10)

#define STANDBY_FLAG_COLD_BOOT 0xa5
#define STANDBY_FLAG_WARM_BOOT 0x5a

typedef enum standby_bootup_mode {
	STANDBY_BOOTUP_COLD_BOOT,
	STANDBY_BOOTUP_WARM_BOOT,
} standby_bootup_mode_e;

#define STANDBY_BOOTUP_SLOT_UNDEF		(0)
#define STANDBY_BOOTUP_SLOT_NR_UNDEF		(0)
#define STANDBY_BOOTUP_SLOT_NR_PRIMARY		(1)
#define STANDBY_BOOTUP_SLOT_NR_SECONDARY	(2)
#define STANDBY_BOOTUP_SLOT_NR(slot)		((slot) & 0xfUL)
#define STANDBY_BOOTUP_SLOT_FEATURE_UNDEF	(0)
#define STANDBY_BOOTUP_SLOT_FEATURE_LOGO_ON	(1)
#define STANDBY_BOOTUP_SLOT_FEATURE_LOGO_OFF	(2)
#define STANDBY_BOOTUP_SLOT_FEATURE_OSDLOGO_ON	(3)
#define STANDBY_BOOTUP_SLOT_FEATURE_OSDLOGO_OFF	(4)
#define STANDBY_BOOTUP_SLOT_FEATURE(slot)	(((slot) >> 4) & 0xfUL)
#define STANDBY_BOOTUP_SLOT(nr, feature)	(((nr) & 0xfUL) | (((feature) & 0xfUL) << 4))

struct standby_locker {
	char name[64];
};

struct standby_gpio_setting {
	pinpad_e pin;
	int polarity;
};

struct standby_ir_setting {
	int num_of_scancode;
	uint32_t scancode[16];
};

struct standby_saradc_setting {
	int channel;
	int min;
	int max;
};

struct standby_pwroff_ddr_setting {
	pinpad_e pin;
	int polarity;
};

#endif

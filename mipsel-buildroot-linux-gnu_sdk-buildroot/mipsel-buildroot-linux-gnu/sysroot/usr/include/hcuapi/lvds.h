#ifndef __UAPI_LVDS_H_H
#define __UAPI_LVDS_H_H

#include <hcuapi/iocbase.h>
#include <hcuapi/pinpad.h>

#define LVDS_SET_CHANNEL_MODE		_IO (LVDS_IOCBASE, 1)
#define LVDS_SET_MAP_MODE		_IO (LVDS_IOCBASE, 2)
#define LVDS_SET_CH0_SRC_SEL		_IO (LVDS_IOCBASE, 3)
#define LVDS_SET_CH1_SRC_SEL		_IO (LVDS_IOCBASE, 4)
#define LVDS_SET_CH0_INVERT_CLK_SEL	_IO (LVDS_IOCBASE, 5)
#define LVDS_SET_CH1_INVERT_CLK_SEL	_IO (LVDS_IOCBASE, 6)
#define LVDS_SET_CH0_CLK_GATE		_IO (LVDS_IOCBASE, 7)
#define LVDS_SET_CH1_CLK_GATE		_IO (LVDS_IOCBASE, 8)
#define LVDS_SET_HSYNC_POLARITY		_IO (LVDS_IOCBASE, 9)
#define LVDS_SET_VSYNC_POLARITY		_IO (LVDS_IOCBASE, 10)
#define LVDS_SET_EVEN_ODD_ADJUST_MODE	_IO (LVDS_IOCBASE, 11)
#define LVDS_SET_EVEN_ODD_INIT_VALUE	_IO (LVDS_IOCBASE, 12)
#define LVDS_SET_SRC_SEL		_IO (LVDS_IOCBASE, 13)
#define LVDS_SET_RESET			_IO (LVDS_IOCBASE, 14)
#define LVDS_SET_POWER_TRIGGER		_IO (LVDS_IOCBASE, 15)
#define LVDS_SET_GPIO_OUT		_IOW (LVDS_IOCBASE, 16, struct lvds_set_gpio)
#define LVDS_SET_GPIO_BACKLIGHT		_IO (LVDS_IOCBASE, 17)		//!< param: value: 0 1
#define LVDS_SET_PWM_BACKLIGHT		_IO (LVDS_IOCBASE, 18)		//!< param: Duty cycle: 0~100
#define LVDS_SET_PWM_VCOM		_IO (LVDS_IOCBASE, 19)		//!< param: Duty cycle: 0~100
#define LVDS_SET_GPIO_POWER		_IO (LVDS_IOCBASE, 20)		//!< param: value: 0 1
#define LVDS_SET_TRIGGER_EN		_IO (LVDS_IOCBASE, 21)
#define LVDS_GET_CHANNEL_MODE		_IOR (LVDS_IOCBASE, 22, enum LVDS_CHANNEL_MODE)	//get lvds channel mode
#define LVDS_GET_CHANNEL_INFO		_IOR (LVDS_IOCBASE, 23, struct lvds_info)	//get lvds channel info
#define LVDS_SET_CHANNEL_INFO		_IOW (LVDS_IOCBASE, 24, struct lvds_info)	//set lvds channel info

struct lvds_set_gpio {
	unsigned int padctl;
	unsigned char value;
};

typedef enum LVDS_CHANNEL_MODE {
	LVDS_CHANNEL_MODE_SINGLE_IN_SINGLE_OUT,
	LVDS_CHANNEL_MODE_SINGLE_IN_DUAL_OUT,
} lvds_channel_mode_e;

typedef enum LVDS_VIDEO_SRC_SEL {
	LVDS_VIDEO_SRC_SEL_FXDE,
	LVDS_VIDEO_SRC_SEL_4KDE,
	LVDS_VIDEO_SRC_SEL_HDMI_RX,
} lvds_video_src_sel_e;

typedef enum LVDS_RGB_SRC_SEL {
	LVDS_RGB_SRC_SEL_FXDE,
	LVDS_RGB_SRC_SEL_4KDE,
	LVDS_RGB_SRC_SEL_HDMI_RX,
	LVDS_RGB_SRC_SEL_FXDE_,
	LVDS_RGB_SRC_SEL_FXDE_LOW_TO_HIGH,
	LVDS_RGB_SRC_SEL_DE4K_LOW_TO_HIGH,
	LVDS_RGB_SRC_SEL_HDMI_RX_LOW_TO_HIGH,
	LVDS_RGB_SRC_SEL_PQ_LOW_TO_HIGH,
} lvds_rgb_src;

typedef enum LVDS_CHANNEL_SEL {
	LVDS_CHANNEL_SEL_RGB888,
	LVDS_CHANNEL_SEL_RGB666,
	LVDS_CHANNEL_SEL_RGB565,
	LVDS_CHANNEL_SEL_I2SO,
	LVDS_CHANNEL_SEL_LVDS_GPIO1,
	LVDS_CHANNEL_SEL_LVDS,
} lvds_channel_sel_e;

typedef enum LVDS_RGB_SRC_SHOW {
	LVDS_RGB_SRC_SHOW_R,
	LVDS_RGB_SRC_SHOW_G,
	LVDS_RGB_SRC_SHOW_B,
} lvds_rgb_src_show_e;

typedef enum LVDS_LLD_PHY_DRIVE_STRENGTH {
	LVDS_LLD_PHY_DRIVE_STRENGTH_WEAKEST,
	LVDS_LLD_PHY_DRIVE_STRENGTH_NORMAL,
	LVDS_LLD_PHY_DRIVE_STRENGTH_STRONGEST,
} lvds_drive_strength_e;

typedef enum LVDS_TTL_DRIVE_STRENGTH {
	LVDS_TTL_DRIVE_STRENGTH_WEAKEST,
	LVDS_TTL_DRIVE_STRENGTH_NORMAL,
	LVDS_TTL_DRIVE_STRENGTH_ENHANCE,
	LVDS_TTL_DRIVE_STRENGTH_STRONGEST,
} lvds_ttl_drive_strength_e;

typedef struct lvds_configure {
	unsigned int channel_mode;
	unsigned int map_mode;
	unsigned int ch0_src_sel;
	unsigned int ch1_src_sel;
	unsigned int ch0_invert_clk_sel;
	unsigned int ch1_invert_clk_sel;
	unsigned int ch0_clk_gate;
	unsigned int ch1_clk_gate;
	unsigned int hsync_polarity;
	unsigned int vsync_polarity;
	unsigned int even_odd_adjust_mode;
	unsigned int even_odd_init_value;
	unsigned int chx_swap_ctrl;
	lvds_drive_strength_e drive_strength;
	lvds_video_src_sel_e src_sel;
} lvds_configure_t;

typedef struct ttl_configure {
	uint32_t rgb_clk_inv;
	lvds_rgb_src src_sel;
	lvds_rgb_src_show_e rgb_src_sel[3];
	lvds_ttl_drive_strength_e drive_strength;
} ttl_configure_t;

typedef struct lvds_info {
	lvds_channel_sel_e channel_type[2];
	lvds_configure_t lvds_cfg;
	ttl_configure_t ttl_cfg;
} lvds_info_t;

#endif

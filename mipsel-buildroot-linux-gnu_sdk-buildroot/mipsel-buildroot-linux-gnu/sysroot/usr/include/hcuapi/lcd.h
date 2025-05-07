#ifndef _HCUAPI_LCD_H_
#define _HCUAPI_LCD_H_

#include <hcuapi/iocbase.h>

#define LCD_INIT					_IO  (LCD_IOCBASE, 1)
#define LCD_GET_INIT_STATUS				_IOR (LCD_IOCBASE, 2, enum LCD_INIT_STATUS)
#define LCD_SEND_INIT_SEQUENCE				_IO  (LCD_IOCBASE, 3)	//<! the init sequence is set in DTS
#define LCD_SET_INIT_SEQUENCE				_IOW (LCD_IOCBASE, 4, struct hc_lcd_init_sequence)	//!< Change init sequence
#define LCD_SET_ROTATE					_IO  (LCD_IOCBASE, 5)	//!< param: lcd_rotate_type_e
#define LCD_SEND_DATA					_IOW (LCD_IOCBASE, 5, struct hc_lcd_write)
#define LCD_SEND_CMDS					_IOW (LCD_IOCBASE, 7, struct hc_lcd_write)
#define LCD_READ_DATA					_IOWR(LCD_IOCBASE, 8, struct hc_lcd_read)
#define LCD_SET_ONOFF					_IO  (LCD_IOCBASE, 9)	//!< param: On: 1, Off: 0
#define LCD_SET_PWM_VCOM				_IO  (LCD_IOCBASE, 10)	//!< param: Duty cycle: 0~100
#define LCD_GET_PWM_VCOM				_IOR (LCD_IOCBASE, 10, int)
#define LCD_SET_POWER_GPIO				_IO  (LCD_IOCBASE, 11)  //!< param: 0 or 1 as Power-GPIO value
#define LCD_SET_RESET_GPIO				_IO  (LCD_IOCBASE, 12)  //!< param: 0 or 1 as Reset-GPIO value
#define LCD_GET_MODE_INFO				_IOR (LCD_IOCBASE, 13, struct hc_lcd_mode_info)
#define LCD_SET_MODE_INFO				_IOW (LCD_IOCBASE, 13, struct hc_lcd_mode_info)

#define LCD_MAX_DATA_SIZE				32
#define LCD_MAX_COMMAND_SIZE				32
#define LCD_MAX_RECEIVED_SIZE				32
#define LCD_MAX_PACKET_SIZE 				4032

typedef enum LCD_ROTATE_TYPE {
	LCD_ROTATE_0 = 0,
	LCD_ROTATE_180,
	LCD_H_MIRROR,
	LCD_V_MIRROR,
} lcd_rotate_type_e;

typedef enum LCD_INIT_STATUS {
	LCD_NOT_INITED,
	LCD_IS_INITED,
} lcd_init_status_e;

typedef enum LCD_INIT_SEQUENCE_FLAG {
	LCD_INIT_SEQUENCE_DEFAULT = 0x0,
	LCD_INIT_SEQUENCE_SPI = 0x01,
	LCD_INIT_SEQUENCE_I2C = 0x02,
} lcd_init_sequence_flag_e;

struct hc_lcd_write {
	unsigned int count;
	unsigned int packet[LCD_MAX_DATA_SIZE];
};

struct hc_lcd_read {
	unsigned int command_size;
	unsigned int command_data[LCD_MAX_COMMAND_SIZE];
	unsigned int received_size;
	unsigned int received_data[LCD_MAX_RECEIVED_SIZE];
};

struct hc_lcd_spi_info {
	unsigned int mosi;
	unsigned int miso;
	unsigned int sck;
	unsigned int cs;
	unsigned int mode;
	unsigned int bit;
	unsigned int orcmds;
	unsigned int ordata;
};

struct hc_lcd_i2c_info {
	unsigned int sda;
	unsigned int scl;
	unsigned int addr;
	unsigned int orcmds;
	unsigned int ordata;
};

struct hc_lcd_pinpad_info {
	unsigned int power;
	unsigned int reset;
	unsigned int stbyb;
	unsigned int pinpad0;
	unsigned int pinpad1;
};

struct hc_lcd_init_sequence {
	unsigned int count;
	unsigned char packet[LCD_MAX_PACKET_SIZE];
	int flag;
};

struct hc_lcd_mode_info {
	int mode;
	struct hc_lcd_spi_info spi;
	struct hc_lcd_i2c_info i2c;
	struct hc_lcd_pinpad_info pinpad;
};

#endif

/**
 * @file
 * @brief                hudi cec module interface.
 * @par Copyright(c):    Hichip Semiconductor (c) 2024
 */
#ifndef _HUDI_CEC_API_H_
#define _HUDI_CEC_API_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hudi_com.h"

/**
 * Maximum size of a data packet
 */
#define HUDI_CEC_MAX_DATA_PACKET_SIZE (16 * 4)

#ifdef __cplusplus
extern "C"
{
#endif

/************************************************************************************************************
 * CEC Key Code for Remote Control Pass Through (RCP Feature)
 ************************************************************************************************************/
typedef enum
{
    HUDI_CEC_USER_CONTROL_CODE_SELECT        = 0x00,
    HUDI_CEC_USER_CONTROL_CODE_UP            = 0x01,
    HUDI_CEC_USER_CONTROL_CODE_DOWN          = 0x02,
    HUDI_CEC_USER_CONTROL_CODE_LEFT          = 0x03,
    HUDI_CEC_USER_CONTROL_CODE_RIGHT         = 0x04,
    HUDI_CEC_USER_CONTROL_CODE_RIGHT_UP      = 0x05,
    HUDI_CEC_USER_CONTROL_CODE_RIGHT_DOWN    = 0x06,
    HUDI_CEC_USER_CONTROL_CODE_LEFT_UP       = 0x07,
    HUDI_CEC_USER_CONTROL_CODE_LEFT_DOWN     = 0x08,
    HUDI_CEC_USER_CONTROL_CODE_ROOT_MENU     = 0x09,
    HUDI_CEC_USER_CONTROL_CODE_SETUP_MENU    = 0x0A,
    HUDI_CEC_USER_CONTROL_CODE_CONTENTS_MENU = 0x0B,
    HUDI_CEC_USER_CONTROL_CODE_FAVORITE_MENU = 0x0C,
    HUDI_CEC_USER_CONTROL_CODE_EXIT          = 0x0D,
    // reserved: 0x0E, 0x0F
    HUDI_CEC_USER_CONTROL_CODE_TOP_MENU = 0x10,
    HUDI_CEC_USER_CONTROL_CODE_DVD_MENU = 0x11,
    // reserved: 0x12 ... 0x1C
    HUDI_CEC_USER_CONTROL_CODE_NUMBER_ENTRY_MODE   = 0x1D,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER11            = 0x1E,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER12            = 0x1F,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER0             = 0x20,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER1             = 0x21,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER2             = 0x22,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER3             = 0x23,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER4             = 0x24,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER5             = 0x25,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER6             = 0x26,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER7             = 0x27,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER8             = 0x28,
    HUDI_CEC_USER_CONTROL_CODE_NUMBER9             = 0x29,
    HUDI_CEC_USER_CONTROL_CODE_DOT                 = 0x2A,
    HUDI_CEC_USER_CONTROL_CODE_ENTER               = 0x2B,
    HUDI_CEC_USER_CONTROL_CODE_CLEAR               = 0x2C,
    HUDI_CEC_USER_CONTROL_CODE_NEXT_FAVORITE       = 0x2F,
    HUDI_CEC_USER_CONTROL_CODE_CHANNEL_UP          = 0x30,
    HUDI_CEC_USER_CONTROL_CODE_CHANNEL_DOWN        = 0x31,
    HUDI_CEC_USER_CONTROL_CODE_PREVIOUS_CHANNEL    = 0x32,
    HUDI_CEC_USER_CONTROL_CODE_SOUND_SELECT        = 0x33,
    HUDI_CEC_USER_CONTROL_CODE_INPUT_SELECT        = 0x34,
    HUDI_CEC_USER_CONTROL_CODE_DISPLAY_INFORMATION = 0x35,
    HUDI_CEC_USER_CONTROL_CODE_HELP                = 0x36,
    HUDI_CEC_USER_CONTROL_CODE_PAGE_UP             = 0x37,
    HUDI_CEC_USER_CONTROL_CODE_PAGE_DOWN           = 0x38,
    // reserved: 0x39 ... 0x3F
    HUDI_CEC_USER_CONTROL_CODE_POWER        = 0x40,
    HUDI_CEC_USER_CONTROL_CODE_VOLUME_UP    = 0x41,
    HUDI_CEC_USER_CONTROL_CODE_VOLUME_DOWN  = 0x42,
    HUDI_CEC_USER_CONTROL_CODE_MUTE         = 0x43,
    HUDI_CEC_USER_CONTROL_CODE_PLAY         = 0x44,
    HUDI_CEC_USER_CONTROL_CODE_STOP         = 0x45,
    HUDI_CEC_USER_CONTROL_CODE_PAUSE        = 0x46,
    HUDI_CEC_USER_CONTROL_CODE_RECORD       = 0x47,
    HUDI_CEC_USER_CONTROL_CODE_REWIND       = 0x48,
    HUDI_CEC_USER_CONTROL_CODE_FAST_FORWARD = 0x49,
    HUDI_CEC_USER_CONTROL_CODE_EJECT        = 0x4A,
    HUDI_CEC_USER_CONTROL_CODE_FORWARD      = 0x4B,
    HUDI_CEC_USER_CONTROL_CODE_BACKWARD     = 0x4C,
    HUDI_CEC_USER_CONTROL_CODE_STOP_RECORD  = 0x4D,
    HUDI_CEC_USER_CONTROL_CODE_PAUSE_RECORD = 0x4E,
    // reserved: 0x4F
    HUDI_CEC_USER_CONTROL_CODE_ANGLE                     = 0x50,
    HUDI_CEC_USER_CONTROL_CODE_SUB_PICTURE               = 0x51,
    HUDI_CEC_USER_CONTROL_CODE_VIDEO_ON_DEMAND           = 0x52,
    HUDI_CEC_USER_CONTROL_CODE_ELECTRONIC_PROGRAM_GUIDE  = 0x53,
    HUDI_CEC_USER_CONTROL_CODE_TIMER_PROGRAMMING         = 0x54,
    HUDI_CEC_USER_CONTROL_CODE_INITIAL_CONFIGURATION     = 0x55,
    HUDI_CEC_USER_CONTROL_CODE_SELECT_BROADCAST_TYPE     = 0x56,
    HUDI_CEC_USER_CONTROL_CODE_SELECT_SOUND_PRESENTATION = 0x57,
    // reserved: 0x58 ... 0x5F
    HUDI_CEC_USER_CONTROL_CODE_PLAY_FUNCTION               = 0x60,
    HUDI_CEC_USER_CONTROL_CODE_PAUSE_PLAY_FUNCTION         = 0x61,
    HUDI_CEC_USER_CONTROL_CODE_RECORD_FUNCTION             = 0x62,
    HUDI_CEC_USER_CONTROL_CODE_PAUSE_RECORD_FUNCTION       = 0x63,
    HUDI_CEC_USER_CONTROL_CODE_STOP_FUNCTION               = 0x64,
    HUDI_CEC_USER_CONTROL_CODE_MUTE_FUNCTION               = 0x65,
    HUDI_CEC_USER_CONTROL_CODE_RESTORE_VOLUME_FUNCTION     = 0x66,
    HUDI_CEC_USER_CONTROL_CODE_TUNE_FUNCTION               = 0x67,
    HUDI_CEC_USER_CONTROL_CODE_SELECT_MEDIA_FUNCTION       = 0x68,
    HUDI_CEC_USER_CONTROL_CODE_SELECT_AV_INPUT_FUNCTION    = 0x69,
    HUDI_CEC_USER_CONTROL_CODE_SELECT_AUDIO_INPUT_FUNCTION = 0x6A,
    HUDI_CEC_USER_CONTROL_CODE_POWER_TOGGLE_FUNCTION       = 0x6B,
    HUDI_CEC_USER_CONTROL_CODE_POWER_OFF_FUNCTION          = 0x6C,
    HUDI_CEC_USER_CONTROL_CODE_POWER_ON_FUNCTION           = 0x6D,
    // reserved: 0x6E ... 0x70
    HUDI_CEC_USER_CONTROL_CODE_F1_BLUE   = 0x71,
    HUDI_CEC_USER_CONTROL_CODE_F2_RED    = 0X72,
    HUDI_CEC_USER_CONTROL_CODE_F3_GREEN  = 0x73,
    HUDI_CEC_USER_CONTROL_CODE_F4_YELLOW = 0x74,
    HUDI_CEC_USER_CONTROL_CODE_F5        = 0x75,
    HUDI_CEC_USER_CONTROL_CODE_DATA      = 0x76,
    // reserved: 0x77 ... 0xFF
    HUDI_CEC_USER_CONTROL_CODE_AN_RETURN        = 0x91,  // return (Samsung)
    HUDI_CEC_USER_CONTROL_CODE_AN_CHANNELS_LIST = 0x96,  // channels list (Samsung)
    HUDI_CEC_USER_CONTROL_CODE_MAX              = 0x96,
    HUDI_CEC_USER_CONTROL_CODE_UNKNOWN          = 0xFF
} hudi_cec_key_code_e;

typedef enum
{
    HUDI_CEC_DEVICE_UNKNOWN          = -1,  // not a valid logical address
    HUDI_CEC_DEVICE_TV               = 0,
    HUDI_CEC_DEVICE_RECORDINGDEVICE1 = 1,
    HUDI_CEC_DEVICE_RECORDINGDEVICE2 = 2,
    HUDI_CEC_DEVICE_TUNER1           = 3,
    HUDI_CEC_DEVICE_PLAYBACKDEVICE1  = 4,
    HUDI_CEC_DEVICE_AUDIOSYSTEM      = 5,
    HUDI_CEC_DEVICE_TUNER2           = 6,
    HUDI_CEC_DEVICE_TUNER3           = 7,
    HUDI_CEC_DEVICE_PLAYBACKDEVICE2  = 8,
    HUDI_CEC_DEVICE_RECORDINGDEVICE3 = 9,
    HUDI_CEC_DEVICE_TUNER4           = 10,
    HUDI_CEC_DEVICE_PLAYBACKDEVICE3  = 11,
    HUDI_CEC_DEVICE_RESERVED1        = 12,
    HUDI_CEC_DEVICE_RESERVED2        = 13,
    HUDI_CEC_DEVICE_FREEUSE          = 14,
    HUDI_CEC_DEVICE_UNREGISTERED     = 15,
    HUDI_CEC_DEVICE_BROADCAST        = 15
} hudi_cec_la_e;

typedef enum
{
    HUDI_CEC_DEVICE_TYPE_TV               = 0,
    HUDI_CEC_DEVICE_TYPE_RECORDING_DEVICE = 1,
    HUDI_CEC_DEVICE_TYPE_RESERVED         = 2,
    HUDI_CEC_DEVICE_TYPE_TUNER            = 3,
    HUDI_CEC_DEVICE_TYPE_PLAYBACK_DEVICE  = 4,
    HUDI_CEC_DEVICE_TYPE_AUDIO_SYSTEM     = 5
} hudi_cec_dev_type_e;

typedef enum
{
    HUDI_CEC_POWER_STATUS_ON                          = 0x00,
    HUDI_CEC_POWER_STATUS_STANDBY                     = 0x01,
    HUDI_CEC_POWER_STATUS_IN_TRANSITION_STANDBY_TO_ON = 0x02,
    HUDI_CEC_POWER_STATUS_IN_TRANSITION_ON_TO_STANDBY = 0x03,
    HUDI_CEC_POWER_STATUS_UNKNOWN                     = 0x99
} hudi_cec_power_status_e;

typedef enum
{
    // One Touch Play
    HUDI_CEC_OPCODE_ACTIVE_SOURCE = 0x82,
    HUDI_CEC_OPCODE_IMAGE_VIEW_ON = 0x04,
    HUDI_CEC_OPCODE_TEXT_VIEW_ON  = 0x0D,

    // Routing Control Feature
    HUDI_CEC_OPCODE_INACTIVE_SOURCE       = 0x9D,
    HUDI_CEC_OPCODE_REQUEST_ACTIVE_SOURCE = 0x85,
    HUDI_CEC_OPCODE_ROUTING_CHANGE        = 0x80,
    HUDI_CEC_OPCODE_ROUTING_INFORMATION   = 0x81,
    HUDI_CEC_OPCODE_SET_STREAM_PATH       = 0x86,

    // Standby Feature
    HUDI_CEC_OPCODE_SYSTEM_STANDBY = 0x36,

    // One Touch Record
    HUDI_CEC_OPCODE_RECORD_OFF       = 0x0B,
    HUDI_CEC_OPCODE_RECORD_ON        = 0x09,
    HUDI_CEC_OPCODE_RECORD_STATUS    = 0x0A,
    HUDI_CEC_OPCODE_RECORD_TV_SCREEN = 0x0F,

    // Timer Programming
    HUDI_CEC_OPCODE_CLEAR_ANALOG_TIMER      = 0x33,
    HUDI_CEC_OPCODE_CLEAR_DIGITAL_TIMER     = 0x99,
    HUDI_CEC_OPCODE_CLEAR_EXTERNAL_TIMER    = 0xA1,
    HUDI_CEC_OPCODE_SET_ANALOG_TIMER        = 0x34,
    HUDI_CEC_OPCODE_SET_DIGITAL_TIMER       = 0x97,
    HUDI_CEC_OPCODE_SET_EXTERNAL_TIMER      = 0xA2,
    HUDI_CEC_OPCODE_SET_TIMER_PROGRAM_TITLE = 0x67,
    HUDI_CEC_OPCODE_TIMER_CLEARED_STATUS    = 0x43,
    HUDI_CEC_OPCODE_TIMER_STATUS            = 0x35,

    // System Information
    HUDI_CEC_OPCODE_CEC_VERSION          = 0x9E,
    HUDI_CEC_OPCODE_GET_CEC_VERSION      = 0x9F,
    HUDI_CEC_OPCODE_GIVE_PHYSICAL_ADDR   = 0x83,
    HUDI_CEC_OPCODE_GET_MENU_LANGUAGE    = 0x91,
    HUDI_CEC_OPCODE_REPORT_PHYSICAL_ADDR = 0x84,
    HUDI_CEC_OPCODE_SET_MENU_LANGUAGE    = 0x32,

    // Deck Control
    HUDI_CEC_OPCODE_DECK_CONTROL     = 0x42,
    HUDI_CEC_OPCODE_DECK_STATUS      = 0x1B,
    HUDI_CEC_OPCODE_GIVE_DECK_STATUS = 0x1A,
    HUDI_CEC_OPCODE_PLAY             = 0x41,

    HUDI_CEC_OPCODE_SELECT_ANALOG_SERVICE  = 0x92,
    HUDI_CEC_OPCODE_SELECT_DIGITAL_SERVICE = 0x93,

    // Vendor Specific Commands
    HUDI_CEC_OPCODE_DEVICE_VENDOR_ID          = 0x87,
    HUDI_CEC_OPCODE_GIVE_DEVICE_VENDOR_ID     = 0x8C,
    HUDI_CEC_OPCODE_VENDOR_COMMAND            = 0x89,
    HUDI_CEC_OPCODE_VENDOR_COMMAND_WITH_ID    = 0xA0,
    HUDI_CEC_OPCODE_VENDOR_REOMTE_BUTTON_DOWN = 0x8A,
    HUDI_CEC_OPCODE_VENDOR_REOMTE_BUTTON_UP   = 0x8B,

    // OSD Status Display
    HUDI_CEC_OPCODE_SET_OSD_STRING = 0x64,

    // Device OSD Transfer
    HUDI_CEC_OPCODE_GIVE_OSD_NAME = 0x46,
    HUDI_CEC_OPCODE_SET_OSD_NAME  = 0x47,

    // Device Menu Control
    OPCODE_MENU_REQUEST = 0x8D,
    OPCODE_MENU_STATUS  = 0x8E,

    // Remote Control Passthrough
    HUDI_CEC_OPCODE_USER_CTRL_PRESSED  = 0x44,
    HUDI_CEC_OPCODE_USER_CTRL_RELEASED = 0x45,

    // Power STATUS
    HUDI_CEC_OPCODE_GIVE_POWER_STATUS   = 0x8F,
    HUDI_CEC_OPCODE_REPORT_POWER_STATUS = 0x90,

    // General Protocol Message
    HUDI_CEC_OPCODE_FEATURE_ABORT = 0x00,
    HUDI_CEC_OPCODE_ABORT         = 0xFF,

    // System Audio Control
    HUDI_CEC_OPCODE_GIVE_AUDIO_STATUS              = 0x71,
    HUDI_CEC_OPCODE_GIVE_SYSTEM_AUDIO_MODE_STATUS  = 0x7D,
    HUDI_CEC_OPCODE_REPORT_AUDIO_STATUS            = 0x7A,
    HUDI_CEC_OPCODE_REPORT_SHORT_AUDIO_DESCRIPTOR  = 0xA3,  // CEC V1.4 New MSG
    HUDI_CEC_OPCODE_REQUEST_SHORT_AUDIO_DESCRIPTOR = 0xA4,  // CEC V1.4 New MSG
    HUDI_CEC_OPCODE_SET_SYSTEM_AUDIO_MODE          = 0x72,
    HUDI_CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST      = 0x70,
    HUDI_CEC_OPCODE_SYSTEM_AUDIO_MODE_STATUS       = 0x7E,

    // Audio Rate Control
    HUDI_CEC_OPCODE_SET_AUDIO_RATE = 0x9A,

    // Audio Return Channel Control (CEC V1.4 New MSG)
    HUDI_CEC_OPCODE_INITIATE_ARC            = 0xC0,
    HUDI_CEC_OPCODE_REPORT_ARC_INITIATED    = 0xC1,
    HUDI_CEC_OPCODE_REPORT_ARC_TERMINATED   = 0xC2,
    HUDI_CEC_OPCODE_REQUEST_ARC_INITIATION  = 0xC3,
    HUDI_CEC_OPCODE_REQUEST_ARC_TERMINATION = 0xC4,
    HUDI_CEC_OPCODE_TERMINAE_ARC            = 0xC5,

    // Capability Discovery and Control Feature (CEC V1.4 New MSG)
    HUDI_CEC_OPCODE_CDC_MESSAGE = 0xF8,
} hudi_cec_opcode_e;

typedef enum
{
    HUDI_CEC_CB_KEY_PRESS,
    HUDI_CEC_CB_COMMAND,
    HUDI_CEC_CB_ALERT,
    HUDI_CEC_CB_CONFIGURATION,
    HUDI_CEC_CB_MENU_STATE,
    HUDI_CEC_CB_SOURCE_ACTIVATED,
} hudi_cec_cb_type_e;

typedef enum
{
    HUDI_CEC_MENU_STATE_ACTIVATED   = 0,
    HUDI_CEC_MENU_STATE_DEACTIVATED = 1,
    HUDI_CEC_MENU_STATE_UNINITED,
} hudi_cec_menu_state_e;

typedef enum
{
    HUDI_CEC_MSGID_ACTION_NONE = 0,
    HUDI_CEC_MSGID_ACTION_CREATE,
    HUDI_CEC_MSGID_ACTION_REUSE,
} hudi_cec_msgid_action_e;

typedef struct
{
    uint8_t data[HUDI_CEC_MAX_DATA_PACKET_SIZE]; /**< the actual data */
    uint8_t size;                                /**< the size of the data */
} hudi_cec_datapacket_t;

typedef struct
{
    hudi_cec_la_e initiator;          /**< the logical address of the initiator of
                                               this message */
    hudi_cec_la_e destination;        /**< the logical address of the destination
                                               of this message */
    hudi_cec_opcode_e     opcode;     /**< the opcode of this message */
    hudi_cec_datapacket_t parameters; /**< the parameters attached to this message */
    uint8_t               reserved[10];
} hudi_cec_cmd_t;

typedef struct
{
    hudi_cec_la_e primary;       /**< the primary logical address to use */
    int           addresses[16]; /**< the list of addresses */
} hudi_cec_logical_addresses_t;

typedef struct
{
    hudi_cec_la_e logical_address; /**< (read-only) the current logical
                                            addresses. added in 1.5.3 */
    int                     msg_id;
    hudi_cec_msgid_action_e msgid_action; /**< impliy the usage of msg_id */
    const char *            dev_path;
    uint8_t                 reserved[100];
} hudi_cec_config_t;

/**
 * @brief       Open a hudi cec module instance
 * @param[out]  handle  Output the handle of the instance
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_open(hudi_handle *handle, const hudi_cec_config_t *config);

/**
 * @brief       Close a hudi cec module instance
 * @param[in]   handle  Handle of the instance
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_close(hudi_handle handle);

/**
 * @brief       Open the hdmi devices that connected and switch to the
 *              active source automatically.
 * @param[in]   handle  Handle of the instance
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_one_touch_play(hudi_handle handle);

/**
 * @brief       Standby the hdmi devices that connected automatically.
 * @param[in]   handle  Handle of the instance
 * @param[in]   la      the logical address of the device
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_standby_device(hudi_handle handle, const hudi_cec_la_e la);

/**
 * @brief       Poweron the hdmi devices that connected.
 * @param[in]   handle  Handle of the instance
 * @param[in]   la      the logical address of the device
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_poweron_device(hudi_handle handle, const hudi_cec_la_e la);

/**
 * @brief       Scan the hdmi devices that connected.
 * @param[in]   handle  Handle of the instance
 * @param[out]  laes    the logical addresses of the devices connected
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_scan_devices(hudi_handle handle, hudi_cec_logical_addresses_t *laes);

/**
 * @brief       Get the hdmi active devices that connected.
 * @param[in]   handle      Handle of the instance
 * @param[in]   timewaitms  time wait
 * @param[out]  laes        the logical addresses of the active devices
 * @retval      0           Success
 * @retval      other       Error
 */
int hudi_cec_get_active_devices(hudi_handle handle, hudi_cec_logical_addresses_t *laes, const uint32_t timewaitms);

/**
 * @brief       volup the hdmi active devices that connected.
 * @param[in]   handle  Handle of the instance
 * @param[in]   la      the logical address of the device
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_audio_volup(hudi_handle handle, const hudi_cec_la_e la);

/**
 * @brief       voldown the hdmi active devices that connected.
 * @param[in]   handle  Handle of the instance
 * @param[in]   la      the logical address of the device
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_audio_voldown(hudi_handle handle, const hudi_cec_la_e la);

/**
 * @brief       toggle mute the hdmi active devices that connected.
 * @param[in]   handle  Handle of the instance
 * @param[in]   la      the logical address of the device
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_audio_toggle_mute(hudi_handle handle, const hudi_cec_la_e la);

/**
 * @brief       get the msg_id for communication
 * @param[in]   handle  Handle of the instance
 * @param[out]  msg_id  the msg_id to communicate with caller
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_get_msgid(hudi_handle handle, int *msg_id);

/**
 * @brief       receive message from hudi cec
 * @param[in]   handle  Handle of the instance
 * @param[in]   nowait  receive message in blocking mode or not
 * @param[out]  cmd     the received message
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_msg_receive(hudi_handle handle, hudi_cec_cmd_t *cmd, const bool nowait);

/**
 * @brief       send a key code through key press.
 * @param[in]   handle  Handle of the instance
 * @param[in]   la      the logical address of the device
 * @param[in]   key     the key code
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_key_press_through(hudi_handle handle, const hudi_cec_la_e la, const hudi_cec_key_code_e key);

/**
 * @brief       get device's power status.
 * @param[in]   handle      Handle of the instance
 * @param[in]   la          the logical address of the device
 * @param[in]   timeoutms   time out
 * @param[out]  status      the status of the device
 * @retval      0           Success
 * @retval      other       Error
 */
int hudi_cec_get_device_power_status(hudi_handle handle, const hudi_cec_la_e la, hudi_cec_power_status_e *status, const int32_t timeoutms);

/**
 * @brief       get a device's active status.
 * @param[in]   handle  Handle of the instance
 * @param[in]   la      the logical address of the device
 * @retval      true    this is active
 * @retval      other   this is not active
 */
bool hudi_cec_is_active_source(hudi_handle handle, const hudi_cec_la_e la);

/**
 * @brief       get device's vendor id.
 * @param[in]   handle      Handle of the instance
 * @param[in]   la          the logical address of the device
 * @param[in]   timeoutms   time out
 * @param[out]  vendorid    the vendor id of the device
 * @retval      0           Success
 * @retval      other       Error
 */
int hudi_cec_get_device_vendor_id(hudi_handle handle, const hudi_cec_la_e la, uint32_t *vendorid, const int32_t timeoutms);

/**
 * @brief       send a special command for special device.
 * @param[in]   handle  Handle of the instance
 * @param[in]   la      the logical address of the device
 * @param[in]   opcode  the opcode
 * @param[in]   params  the parameters of the opcode
 * @retval      0       Success
 * @retval      other   Error
 */
int hudi_cec_send_special_command(hudi_handle handle, const hudi_cec_la_e la, const uint8_t opcode, const hudi_cec_datapacket_t *params);

#ifdef __cplusplus
}
#endif

#endif

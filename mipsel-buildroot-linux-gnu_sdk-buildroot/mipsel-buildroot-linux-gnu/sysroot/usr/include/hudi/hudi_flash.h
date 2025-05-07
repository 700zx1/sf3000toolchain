/**
* @file
* @brief                hudi flash operation interface.
* @par Copyright(c):    Hichip Semiconductor (c) 2024
*/

#ifndef __HUDI_FLASH_H__
#define __HUDI_FLASH_H__

#include "hudi_com.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    HUDI_FLASH_TYPE_NOR = 1,
    HUDI_FLASH_TYPE_NAND,
} hudi_flash_type_e;

typedef enum
{
    HUDI_FLASH_OTP_REG1 = 1,
    HUDI_FLASH_OTP_REG2,
    HUDI_FLASH_OTP_REG3,
} hudi_flash_otp_reg_e;

/**
* @brief       Open a hudi flash module instance
* @param[out]  handle  output the handle of the instance
* @param[in]   type    flash type
* @retval      0       Success
* @retval      other   Error
*/
int hudi_flash_open(hudi_handle *handle, hudi_flash_type_e type);

/**
* @brief       Close a hudi flash module instance
* @param[in]   handle  Handle of the instance to be closed
* @retval      0       Success
* @retval      other   Error
*/
int hudi_flash_close(hudi_handle handle);

/**
* @brief       Read OTP data from flash
* @param[in]   handle  Handle of the instance
* @param[in]   bank    Security register number to be read
* @param[in]   offset  Offset to be read
* @param[in]   data    Buffer to be store the read data, should not be null
* @param[in]   len     Data length to be read
* @retval      0       Success
* @retval      other   Error
*/
int hudi_flash_otp_read(hudi_handle handle, hudi_flash_otp_reg_e bank,
                        unsigned int offset, unsigned char *data, unsigned int len);

/**
* @brief       Write data to flash OTP
* @param[in]   handle  Handle of the instance
* @param[in]   bank    Index of the security register to be written
* @param[in]   offset  Offset to be written
* @param[in]   data    Data to be written, should not be null
* @param[in]   len     Data length to be written
* @retval      0       Success
* @retval      other   Error
* @note        Write operatioin will cause the whole register be ereased, \n
*              suggest to backup the register data before write
*/
int hudi_flash_otp_write(hudi_handle handle, hudi_flash_otp_reg_e bank,
                         unsigned int offset, unsigned char *data, unsigned int len);

/**
* @brief       Read the UID of the flash
* @param[in]   handle  Handle of the instance
* @param[in]   uid     Buffer to be store the UID data, should not be less than 16B
* @param[out]  len     Bytes of uid
* @retval      0       Success
* @retval      other   Error
* @note        Always read 16 bytes
*/
int hudi_flash_uid_read(hudi_handle handle, unsigned char *uid, unsigned int *len);

/**
* @brief       Lock the write protection of specific security register
* @param[in]   handle  Handle of the instance
* @param[in]   bank    Security register number to be lock
* @retval      0       Success
* @retval      other   Error
* @note        null
*/
int hudi_flash_otp_lock(hudi_handle handle, hudi_flash_otp_reg_e bank);

#ifdef __cplusplus
}
#endif

#endif

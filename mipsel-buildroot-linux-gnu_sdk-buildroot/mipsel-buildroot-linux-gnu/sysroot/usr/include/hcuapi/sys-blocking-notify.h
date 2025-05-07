#ifndef _HCUAPI_SYS_BLOCKING_NOTIFY_H_
#define _HCUAPI_SYS_BLOCKING_NOTIFY_H_

#if defined(__HCRTOS__)

#include <hcuapi/iocbase.h>

#define DISK_NAME_LEN 32

struct removable_notify_info {
	char devname[DISK_NAME_LEN];
};

struct hidg_func_descriptor;
struct usb_hid_dev_info {
	char devname[DISK_NAME_LEN];
	struct hidg_func_descriptor *report;
};

/*
 * <XX>_DEV_NOTIFY_CONNECT : the notification before enumeration
 * <XX>_NOTIFY_CONNECT     : the notification after enumeration
 */
#define USB_MSC_NOTIFY_CONNECT		_IOR(USBDEVFS_IOCBASE, 100, struct removable_notify_info)	//!< devname contains device path. e.g: "sda1, sda2, sdb1, ..."
#define USB_MSC_NOTIFY_DISCONNECT	_IOR(USBDEVFS_IOCBASE, 101, struct removable_notify_info)	//!< devname contains device path. e.g: "sda1, sda2, sdb1, ..."

#define USB_MSC_NOTIFY_MOUNT		_IOR(USBDEVFS_IOCBASE, 102, struct removable_notify_info)	//!< devname contains device path. e.g: "sda1, sda2, sdb1, ..."
#define USB_MSC_NOTIFY_UMOUNT		_IOR(USBDEVFS_IOCBASE, 103, struct removable_notify_info)	//!< devname contains device path. e.g: "sda1, sda2, sdb1, ..."

#define SDMMC_NOTIFY_CONNECT		_IOR(SDMMC_IOCBASE, 100, struct removable_notify_info)		//!< devname contains device path. e.g: "mmcblk0, mmcblk0p1, mmcblk0p2, ..."
#define SDMMC_NOTIFY_DISCONNECT		_IOR(SDMMC_IOCBASE, 101, struct removable_notify_info)		//!< devname contains device path. e.g: "mmcblk0, mmcblk0p1, mmcblk0p2"

#define SDMMC_NOTIFY_MOUNT		_IOR(SDMMC_IOCBASE, 102, struct removable_notify_info)		//!< devname contains device path. e.g: "mmcblk0, mmcblk0p1, mmcblk0p2, ..."
#define SDMMC_NOTIFY_UMOUNT		_IOR(SDMMC_IOCBASE, 103, struct removable_notify_info)		//!< devname contains device path. e.g: "mmcblk0, mmcblk0p1, mmcblk0p2, ..."

#define USB_DEV_NOTIFY_CONNECT		_IOR(USBDEVFS_IOCBASE, 104, struct removable_notify_info)	//!< devname contains vendor & product id: "v%04Xp%04X", eg: "v0BDApF179"
#define USB_DEV_NOTIFY_DISCONNECT	_IOR(USBDEVFS_IOCBASE, 105, struct removable_notify_info)	//!< devname contains vendor & product id: "v%04Xp%04X", eg: "v0BDApF179"

#define USB_MSC_NOTIFY_MOUNT_FAIL	_IOR(USBDEVFS_IOCBASE, 106, struct removable_notify_info)	//!< devname contains device path. e.g: "sda1, mmcblk0p2, ..."
#define USB_MSC_NOTIFY_UMOUNT_FAIL	_IOR(USBDEVFS_IOCBASE, 107, struct removable_notify_info)	//!< devname contains device path. e.g: "sda1, mmcblk0p2, ..."

#define USB_HID_KBD_NOTIFY_CONNECT	_IOR(USBDEVFS_IOCBASE, 108, struct usb_hid_dev_info)		//!< 1.keyboard ID and vendor & product id: "v%04Xp%04X",  eg: "1-v0BDApF179"
													//!< 2.report descriptor
#define USB_HID_KBD_NOTIFY_DISCONNECT	_IOR(USBDEVFS_IOCBASE, 109, struct usb_hid_dev_info)		//!< 1.keyboard ID and vendor & product id: "v%04Xp%04X",  eg: "1-v0BDApF179"
													//!< 2.report descriptor

#define USB_HID_MOUSE_NOTIFY_CONNECT	_IOR(USBDEVFS_IOCBASE, 110, struct usb_hid_dev_info)		//!< 1.mouse ID and vendor & product id: "v%04Xp%04X",  eg: "1-v0BDApF179"
													//!< 2.report descriptor
#define USB_HID_MOUSE_NOTIFY_DISCONNECT	_IOR(USBDEVFS_IOCBASE, 111, struct usb_hid_dev_info)		//!< 1.mouse ID and vendor & product id: "v%04Xp%04X",  eg: "1-v0BDApF179"
													//!< 2.report descriptor

#define SDIO_DEV_NOTIFY_CONNECT		_IOR(USBDEVFS_IOCBASE, 112, struct removable_notify_info)	//!< devname contains vendor & product id: "v%04Xp%04X", eg: "v0BDApF179"
#define SDIO_DEV_NOTIFY_DISCONNECT	_IOR(USBDEVFS_IOCBASE, 113, struct removable_notify_info)	//!< devname contains vendor & product id: "v%04Xp%04X", eg: "v0BDApF179"

#define USB_GADGET_NOTIFY_CONNECT	_IOR(USBDEVFS_IOCBASE, 114, struct removable_notify_info)	//!< contains usb port: "musb-hdrc.0.auto" or "musb-hdrc.1.auto"
#define USB_GADGET_NOTIFY_DISCONNECT	_IOR(USBDEVFS_IOCBASE, 115, struct removable_notify_info)	//!< contains usb port: "musb-hdrc.0.auto" or "musb-hdrc.1.auto"

#define USB_MSC_DEV_NOTIFY_CONNECT	_IOR(USBDEVFS_IOCBASE, 116, NULL)
#define USB_MSC_DEV_NOTIFY_DISCONNECT	_IOR(USBDEVFS_IOCBASE, 117, NULL)

#endif

#endif /* _HCUAPI_USBMSC_H_ */

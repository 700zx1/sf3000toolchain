/**
 * @file fbdev.h
 *
 */

#ifndef FBDEV_H
#define FBDEV_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef LV_DRV_NO_CONF
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_drv_conf.h"
#else
#include "../lv_drv_conf.h"
#endif
#endif

#if USE_FBDEV || USE_BSD_FBDEV

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "hc-porting/lv_hc_2dge.h"

/*********************
 *      DEFINES
 *********************/
//32byte align, cache must be 32 bytes align also.
#define HC_MEM_ALIGN_MASK (0x1F)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void fbdev_init(void);
void fbdev_exit(void);
void fbdev_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p);
void fbdev_get_sizes(uint32_t *width, uint32_t *height);
/**
 * Set the X and Y offset in the variable framebuffer info.
 * @param xoffset horizontal offset
 * @param yoffset vertical offset
 */
void fbdev_set_offset(uint32_t xoffset, uint32_t yoffset);

void  *fbdev_virt_to_phy(void *virt_addr);
void *fbdev_static_malloc_virt(int size);
bool fbdev_check_addr(uint32_t virt_addr, uint32_t size);
void  *fbdev_virt_to_phy(void *virt_addr);
void fbdev_wait_cb(struct _lv_disp_drv_t * disp_drv);
void fbdev_set_rotate(int rotate, int hor_flip, int ver_flip);
uint32_t fbdev_get_buffer_size(void);
void fbdev_get_fb_buf(uint8_t **buf1, uint8_t **buf2);
void fbdev_hor_scr_rotate(int rotate, int hor_flip, int ver_flip, int xoff, int yoff);

#ifdef __linux__
void lv_fb_hotplug_support_set(bool enable);
#endif

/**********************
 *      MACROS
 **********************/

#endif  /*USE_FBDEV*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*FBDEV_H*/

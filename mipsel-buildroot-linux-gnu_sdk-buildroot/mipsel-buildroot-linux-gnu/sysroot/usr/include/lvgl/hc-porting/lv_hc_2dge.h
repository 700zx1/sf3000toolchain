/**
 * @file lv_gpu_hichip.h
 *
 */

#ifndef LV_GPU_HICHIP_H
#define LV_GPU_HICHIP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "lvgl/src/misc/lv_color.h"
#include "lvgl/src/hal/lv_hal_disp.h"
#include "lvgl/src/draw/sw/lv_draw_sw.h"
#include <hcge/ge_api.h>
#ifdef __HCRTOS__
#include <assert.h>

#include <cpu_func.h>
#undef cacheflush
//#define cacheflush(a,b,c)  do{printf("a:%p\n", a);assert(((uint32_t)(a)&(~(1<<5))) != 0);flush_cache(a, b);cache_invalidate(a,b);}while(0)
#define cacheflush(a,b,c)  do{flush_cache(a, b);cache_invalidate(a,b);}while(0)
//#define cacheflush(a,b,c)  do{}while(0)
#endif

#if LV_USE_GPU_HICHIP

/*********************
 *      DEFINES
 *********************/

struct lv_blit {
	lv_color_t *dst_buf;
	const lv_area_t *dst_area;
	lv_coord_t dst_stride;
	HCGESurfacePixelFormat dst_fmt;
	const lv_color_t *src_buf;
	const lv_area_t *src_area;
	lv_coord_t src_stride;
	HCGESurfacePixelFormat src_fmt;
	lv_opa_t opa;
	const lv_area_t *crop;
	double angle;
	lv_point_t *pivot;
	bool v_flip;
	bool h_flip;
	bool stretch;
	//src cover dst
	bool cover;
};

typedef lv_draw_sw_ctx_t lv_draw_hc_ctx_t;
struct _lv_disp_drv_t;

int lv_draw_hc_init(void);
void lv_draw_hc_ctx_init(struct _lv_disp_drv_t * drv, lv_draw_ctx_t * draw_ctx);
void lv_draw_hc_ctx_deinit(struct _lv_disp_drv_t * drv, lv_draw_ctx_t * draw_ctx);
void lv_draw_hc_blend(lv_draw_ctx_t * draw_ctx, const lv_draw_sw_blend_dsc_t * dsc);
void lv_draw_hc_buffer_copy(lv_draw_ctx_t * draw_ctx,
                            void * dest_buf, lv_coord_t dest_stride, const lv_area_t * dest_area,
                            void * src_buf, lv_coord_t src_stride, const lv_area_t * src_area);
void lv_draw_hc_wait_cb(lv_draw_ctx_t * draw_ctx);

bool lv_ge_blit(struct lv_blit *blit, bool f_cache);
void lv_ge_lock(void);
void lv_ge_unlock(void);
void lv_ge_memset(void *dst, uint8_t val, size_t len);

extern hcge_context *hcge_ctx;

/**********************
 *      MACROS
 **********************/

#endif  /*LV_USE_GPU_HICHIP*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_GPU_HICHIP_H*/

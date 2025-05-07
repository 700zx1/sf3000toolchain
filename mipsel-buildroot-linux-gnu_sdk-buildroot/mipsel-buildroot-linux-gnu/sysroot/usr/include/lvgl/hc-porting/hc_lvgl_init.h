#ifndef _H_HC_LVGL_INIT_H
#define _H_HC_LVGL_INIT_H

uint32_t custom_tick_get(void);
int hc_lvgl_init(void);
uint32_t hc_cpu_usage_get(void);
typedef int (*hc_lvgl_loop_cb)(void *data);
//wait_time in millisecone
int hc_lvgl_loop(int wait_time, hc_lvgl_loop_cb cb, void *data);
#endif

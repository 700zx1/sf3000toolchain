#ifndef __HCPLAYER_MANAGER_H_
#define __HCPLAYER_MANAGER_H_

#include "ffplayer.h"

void *hcplayer_multi_create (HCPlayerInitArgs *audio_initargs, HCPlayerInitArgs *video_initargs);
void hcplayer_multi_destroy(void *hdl);

int hcplayer_multi_seek(void *hdl, int64_t time_ms);
int hcplayer_multi_play(void *hdl);
int hcplayer_multi_pause(void *hdl);
int hcplayer_multi_duration(void *hdl);
int hcplayer_multi_position(void *hdl);

/* other functions should get the vplayer or aplayer, such as rotate.*/
void *hcplayer_multi_get_vplayer(void *hdl);//get the player handle of video uri
void *hcplayer_multi_get_aplayer(void *hdl);//get the player handle of audio uri

#endif /* __HCPLAYER_MANAGER_H_ */
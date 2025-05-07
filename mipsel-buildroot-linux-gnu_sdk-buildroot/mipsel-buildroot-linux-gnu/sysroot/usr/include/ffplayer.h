#ifndef __HCPLAYER_H_
#define __HCPLAYER_H_

#include <hcuapi/viddec.h>
#include <libavcodec/avcodec.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if __x86_64__
#define LONG_INT_FORMAT "%ld"
#else
#define LONG_INT_FORMAT "%lld"
#endif

#define configPLAYER_QUEUE_LENGTH (256)

#ifndef __ASSEMBLER__
#define BIT(nr)				(1UL << (nr))
#else
#define BIT(nr)				(1 << (nr))
#endif

/* audio_device_t */
#define AUDDEV_DEFAULT  0
#define AUDDEV_I2SO		BIT(0)
#define AUDDEV_PCMO		BIT(1)
#define AUDDEV_SPO		BIT(2)
#define AUDDEV_DDP_SPO	BIT(3)
typedef unsigned long AudioOutDev;

typedef enum
{
	HCPLAYER_NULL,
	HCPLAYER_READY,
	HCPLAYER_PAUSED,
	HCPLAYER_PLAYING,
}HCPlayerState;

typedef enum
{
	/* HCPLAYER_FREERUN: av free run;
	 * HCPLAYER_VIDEO_MASTER: video update stc, audio sync to stc.
	 * HCPLAYER_AUDIO_MASTER: audio update stc, video sync to stc,
	 * HCPLAYER_SYNC_STC:set stc when write first audio & video, audio & video both sync to stc.
	 * HCPLAYER_SYNC_STC_SLAVE:audio & video both sync to stc.
	 */
	HCPLAYER_FREERUN,
	HCPLAYER_VIDEO_MASTER,
	HCPLAYER_AUDIO_MASTER,
	HCPLAYER_SYNC_STC,
	HCPLAYER_SYNC_STC_SLAVE,
}HCPlayerSyncType;

typedef enum{
	LOG_PANIC,//0
	LOG_FATAL,//1
	LOG_ERROR,//2
	LOG_WARNING,//3
	LOG_INFO,//4
	LOG_VERBOSE,//5
	LOG_DEBUG,//6
	LOG_TRACE,//7
}HCPlayerLogLevel;

typedef enum
{
	HCPLAYER_CALLBACK_SUBTITLE_ON,
	HCPLAYER_CALLBACK_SUBTITLE_OFF,
	HCPLAYER_CALLBACK_NONE,
} HCPlayerCallbackType;

typedef enum
{
	/* state change msgs */
	HCPLAYER_MSG_STATE_PLAYING = 1,
	HCPLAYER_MSG_STATE_PAUSED,

	/* the infos of the stream, for example, curtime, duration, mediainfo, filesize, and so on,
	 * only can be get after this msg emited
	 */
	HCPLAYER_MSG_STATE_READY,
	/* the val of the msg is the buffering percent */
	HCPLAYER_MSG_BUFFERING,

	/* end of stream msgs */
	HCPLAYER_MSG_STATE_EOS,

	/* reach the end of stream when rate != 1 & rate > 0 */
	HCPLAYER_MSG_STATE_TRICK_EOS,
	/* reach the begining of the stream when rate < 0,
	 * can call resume to play from the begining(normal way), or call stop to end the play
	 */
	HCPLAYER_MSG_STATE_TRICK_BOS,

	HCPLAYER_MSG_READ_TIMEOUT,

	/* err/warning msgs */
	/* Error: ffmpeg open err */
	HCPLAYER_MSG_OPEN_FILE_FAILED,
	/* Error: ffmpeg read/container err */
	HCPLAYER_MSG_UNSUPPORT_FORMAT,

	/* Warning: open viddec err, the val of the msg is the index of the video track, the player will switch to next video track if have*/
	HCPLAYER_MSG_UNSUPPORT_VIDEO_TYPE,
	/* Error: viddec dec err during decode */
	HCPLAYER_MSG_VIDEO_DECODE_ERR,
	/* Warning: There is no video track or all video tracks are unsupport */
	HCPLAYER_MSG_UNSUPPORT_ALL_VIDEO,

	/* Warning: open auddec err, the val of the msg is the index of the audio track, the player will switch to next video track if have*/
	HCPLAYER_MSG_UNSUPPORT_AUDIO_TYPE,
	/* Error: auddec dec err during decode */
	HCPLAYER_MSG_AUDIO_DECODE_ERR,
	/* Warning: There is no audio track or all audio tracks are unsupport */
	HCPLAYER_MSG_UNSUPPORT_ALL_AUDIO,

	/* Warning: */
	HCPLAYER_MSG_UNSUPPORT_SUBTITLE_TYPE,
	/* Error: */
	HCPLAYER_MSG_SUBTITLE_DECODE_ERR,
	/* Warning: */
	HCPLAYER_MSG_UNSUPPORT_ALL_SUBTITLE,

	/* Warning: the file is not entire, the duration of the index table is different of the real duration */
	HCPLAYER_MSG_WARNING_INVALID_FILE_END,

	/* Error: undefined err happend */
	HCPLAYER_MSG_ERR_UNDEFINED,

	/* other msgs */
	HCPLAYER_MSG_FIRST_VIDEO_FRAME_DECODED,
	HCPLAYER_MSG_FIRST_VIDEO_FRAME_SHOWED,
	HCPLAYER_MSG_FIRST_VIDEO_FRAME_TRANSCODED,
	HCPLAYER_MSG_HTTP_FORBIDDEN,

	HCPLAYER_MSG_UNDEFINED,
} HCPlayerMsgType;

typedef void (* HCPlayerCallback) (HCPlayerCallbackType type,
	void *user_data, void *val);

typedef int (* FillIoBuffer)(void * opaque, uint8_t *buf, int bufsize);
typedef int64_t (*FillIoSeek)(void *opaque, int64_t offset, int whence);

typedef struct HCPlayerMsg
{
	long type;
	void *user_data;
	int val;
	void *player_data;
}HCPlayerMsg;

enum HCSubtitleType {
    HC_SUBTITLE_NONE,

    HC_SUBTITLE_BITMAP,                ///< A bitmap, pict will be set

    /**
     * Plain text, the text field must be set by the decoder and is
     * authoritative. ass and pict fields may contain approximations.
     */
    HC_SUBTITLE_TEXT,

    /**
     * Formatted text, the ass field must be set by the decoder and is
     * authoritative. pict and text fields may contain approximations.
     */
    HC_SUBTITLE_ASS,
};

typedef struct HCSubtitleRect {
    int x;         ///< top left corner  of pict, undefined when pict is not set
    int y;         ///< top left corner  of pict, undefined when pict is not set
    int w;         ///< width            of pict, undefined when pict is not set
    int h;         ///< height           of pict, undefined when pict is not set
    int nb_colors; ///< number of colors in pict, undefined when pict is not set

    /**
     * data+linesize for the bitmap of this subtitle.
     * Can be set for text/ass as well once they are rendered.
     */
    uint8_t *data[4];
    int linesize[4];

    enum HCSubtitleType type;

    char *text;                     ///< 0 terminated plain UTF-8 text

    /**
     * 0 terminated ASS/SSA compatible event line.
     * The presentation of this is unaffected by the other values in this
     * struct.
     */
    char *ass;

    int flags;
} HCSubtitleRect;

typedef struct HCSubtitle {
    uint16_t format; /* 0 = graphics */
    uint32_t start_display_time; /* relative to packet pts, in ms */
    uint32_t end_display_time; /* relative to packet pts, in ms */
    unsigned num_rects;
    HCSubtitleRect **rects;
    int64_t pts;    ///< Same as packet pts, in AV_TIME_BASE
} HCSubtitle;

typedef enum HCAlphaBlendMode {
	/* for pictures which have alpha value.
	 * ALPHA_BLEND_UNIFORM: black background.
	 * ALPHA_BLEND_UNIFORM_WHITE: white background.
	 * ALPHA_BLEND_CHECKERBOARD: checkerboard background.
	 */
	ALPHA_BLEND_NONE   = 0,
	ALPHA_BLEND_UNIFORM,
	ALPHA_BLEND_UNIFORM_WHITE,
	ALPHA_BLEND_CHECKERBOARD,
	ALPHA_BLEND_NB,
} HCAlphaBlendMode;

struct hcplayer_transcode_config {
	bool b_enable;
	bool b_show;
	bool b_scale;
	bool b_capture_one;
	int16_t dst_w;
	int16_t dst_h;
	enum AVVideoRenderMode transcode_mode;
	enum IMG_TRANSCODE_FORMAT transcode_format;
};

typedef struct HCPlayerTranscodeArgs
{
	char *url; //!< input param, file path
	uint8_t *out; //!< output param, out jpg/bgra buf
	int out_size; //!< output param, size of jpg/bgra buf
	int render_width; //!< input param, expected width
	int render_height; //!< input param, expected height
	double start_time; //!< input param, only for video, select which time to capture the picture.
	int out_width; //!< output param, width of output picture
	int out_height; //!< output param, height of output picture
	enum AVVideoRenderMode transcode_mode; //!< input param, see detail info in avcodec.h
	enum IMG_TRANSCODE_FORMAT transcode_format; //!< input param, output jpg or bgra.
	int (*interrupt_cb)(void *); //!< input param, return 1 to break current transcode.
	void *opaque; //!< input param, interrupt_cb's arg
}HCPlayerTranscodeArgs;

typedef struct HCPlayerInitArgs
{
	/* play a file from local path or from network uri */
	char *uri;
	/* play data from memory */
	FillIoBuffer readdata_callback;
	void *readdata_opaque;
	//FillIoBuffer writedata_callback;
	FillIoSeek seekdata_callback;
	HCPlayerCallback callback;//block msg, only used by subtitle yet
	int msg_id;//non block msg, if do not need receive msg, please set to -1 in linux or set to 0 in rtos;

	HCPlayerSyncType sync_type;
	/* show B/P frame if the first frame is not I frame, drop frames if delay happended */
	bool quick_mode;
	/* quick mode drop threshold, unit: frame; default 3(if qm_drop_thresh was not set) */
	int qm_drop_thresh;
	/* in audio master mode, if i2so dma's audio data time > audio_flush_thres(unit:ms; default 0 means not work), we drop current frame*/
	int audio_flush_thres;

	/* do not close video pe when stop viddec */
	bool do_not_closevp;
	bool fillblack;//not work now.

	/* play from appointed time,
	 * if start_time >= 1, unit is milliseconds.
	 * if 0 < start_time < 1, unit is percent of total duration.
	 */
	double start_time;

	struct hcplayer_transcode_config transcode_config;

	/* enable both video rotate&mirror, it will alloc more memory during init. */
	bool rotate_enable;
	rotate_type_e rotate_type;
	mirror_type_e mirror_type;

	/* for picture play */
	img_dis_mode_e img_dis_mode;
	image_effect_t img_effect;
	bool bg_disable;
	/* emit eos wait for img_hold_time after get eos; if it is not set, emit eos immediately after get eos, unit ms */
	int img_dis_hold_time;
	/* used in gif play, interval between each frame, unit ms */
	int gif_dis_interval;
	HCAlphaBlendMode img_alpha_mode;
	/* a video file in the tag of the stream, for example:play an id3 tag's picture */
	int play_attached_file;

	/*
	 * set the buffering calc start & end of the av buffer. default 500ms ~ 3000ms
	 * buffering percent = 100 if bufffered_time > buffering_end
	 * buffering percent = 0 if bufffered_time < buffering_start
	 * buffering percent = (bufffered_time - buffering_start) * 100 / (buffering_end - buffering_start);
	 * @buffering_start: the buffering start threshhold. unit ms
	 * @buffering_end: the buffering end threshhold. unit ms
	 * @buffering_enable: 0, buffering is disable. 1, buffering is enable
	 */
	int buffering_start;
	int buffering_end;
	bool buffering_enable;

	/*
	 * enable preview
	 */
	struct av_area src_area;
	struct av_area dst_area;
	bool preview_enable;

	void *user_data;

	/* for ac3 */
	int bypass;

	/* for httpsrc */
	int read_timeout;
	int connect_timeout;
	char *user_agent;

	bool disable_audio;
	bool disable_video;
	AudioOutDev snd_devs;

	char *decryption_key;
	bool disable_nonencrypt;

	/* audio and video use independented urls*/
	bool independent_url;

	int ext_subtitle_stream_num;
	char **ext_sub_uris;
	AVDictionary *sub_opts;
	bool abort_subtitle;

	bool enable_audsink;
	bool play_both;

	bool enable_audio_thread;
	int audio_thread_buffer_size;//default: 1 * 1024 * 1024
	int dma_buffer_time;
	int mix_priority;
	bool mix_maximum_weight;

	bool force_use_ffmpeg_dec;
	int slave_mode;
	bool is_cycleplay;
}HCPlayerInitArgs;

typedef struct HCPlayerAudioInfo
{
	int index;//the nth in audio stream list
	int codec_id;//enum AVCodecID
	char lang_code[5];//audio language

	int channels ;
	int sample_rate;
	int depth;

	int block_align;
	int64_t bit_rate;//the bitrate of current audio track
}HCPlayerAudioInfo;

typedef struct HCPlayerVideoInfo
{
	int index;//the nth in video stream list
	int codec_id;//enum AVCodecID
	char lang_code[5];//video language
	int width;
	int height;
	float frame_rate;
	int64_t bit_rate;//the bitrate of current video track
}HCPlayerVideoInfo;

typedef struct HCPlayerSubtitleInfo
{
	int index;//the nth in subtitle stream list
	int codec_id;//enum AVCodecID
	char lang_code[5];//subtitle language
}HCPlayerSubtitleInfo;

typedef struct HCPlayerMediaInfo
{
	char *artist;//only used in id3-mp3
	char *album;//only used in id3-mp3
	char *title;//only used in id3-mp3
	char *TYER;//only used in id3-mp3, the publish time of the mp3
	void *mjpg;//only used in id3-mp3, the attach jpg of the mp3
	int mjpg_size;//only used in id3-mp3, the size of attached jpg

	char *datetime;//only used in exif-jpg, photo time
	char *orientation;//only used in exif-jpg, photo orientation
	char *gpslatitude;//only used in exif-jpg, photo location
	char *make;//only used in exif-jpg, photographer.

	int64_t bit_rate;
}HCPlayerMediaInfo;

/* ---------------------- basic handles ---------------------*/

/* if init is not called, default log level is LOG_WARNING */
int hcplayer_init (HCPlayerLogLevel log_level);

/* free all resource of hcplayer */
void hcplayer_deinit (void);

/* create a handle of player
 * return: the handle of the player.
 * init_args: set url/syncmode/callback/... to create the player
*/
void *hcplayer_create (HCPlayerInitArgs *init_args);

/**
 * Stop and destroy player
 * @player: a handle created by hcplayer_create
 * @bclosevp: true, close vp(video display); false, keep vp on after player stopped.
 * @bfillblack: true, fill black to video display layer; false, keep last video frame.
 */
void hcplayer_stop2 (void *player, bool closevp, bool fillblack);

/* default call hcplayer_stop2 (player, 1, 0) */
void hcplayer_stop (void *player);

/**
 * change player status to play,
 * if not called, the player will goto pause status after create.
 * @player: a handle created by hcplayer_create
 */
void hcplayer_play (void *player);

/**
 * change player status to play
 * this api run in block mode, api will return after play end.
 * @player: a handle created by hcplayer_create
 */
void hcplayer_play2 (void *player);

/**
 * change player status to play,
 * if not called, the player will goto pause status after create.
 * @player: a handle created by hcplayer_create
 */
void hcplayer_pause (void *player);

/* pause av, but do not change status */
void hcplayer_pause2 (void *player);

/**
 * resume to normal play(rate = 1) status
 * if the player is in pause or fast-play(rate != 1).
 * @player: a handle created by hcplayer_create
 */
void hcplayer_resume (void *player);

/* resume av which paused by hcplayer_pause2 */
void hcplayer_resume2 (void *player);

/**
 * seek to the target time and start play.
 * if player is in pause status,
 * the seek will let the player change to play status.
 * @player: a handle created by hcplayer_create
 * @time_ms: seek time, unit is ms.
 * @return: 0 if successed.
 */
int hcplayer_seek (void *player, int64_t time_ms);

/**
 * get total duration of the stream.
 * @player: a handle created by hcplayer_create
 * @return: seek time, unit is ms.
 */
int64_t hcplayer_get_duration (void *player);

/**
 * get current play timestamp.
 * @player: a handle created by hcplayer_create
 * return: current time, unit is ms.
 */
int64_t hcplayer_get_position (void *player);

/**
 * get the number fo audio tracks in current stream.
 * @player: a handle created by hcplayer_create
 * return: number fo audio tracks.
 */
int hcplayer_get_audio_streams_count (void *player);

/**
 * get the info of nth audio track in current stream,
 * @player: a handle created by hcplayer_create
 * @index: nth(0 ~
(hcplayer_get_audio_streams_count -1)).
 * @audio_info(out): audio info
 * @return: 0 succeess.
 */
int hcplayer_get_nth_audio_stream_info (void *player, int index, HCPlayerAudioInfo *audio_info);

/**
 * get the number fo video tracks in current stream.
 * @player: a handle created by hcplayer_create
 * return: number fo video tracks.
 */
int hcplayer_get_video_streams_count (void *player);

/**
 * get the info of nth video track in current stream,
 * @player: a handle created by hcplayer_create
 * @index: nth(0 ~
(hcplayer_get_video_streams_count -1)).
 * @video_info(out): video info
 * @return: 0 succeess.
 */
int hcplayer_get_nth_video_stream_info (void *player, int index, HCPlayerVideoInfo *video_info);

int hcplayer_get_subtitle_streams_count (void *player);
int hcplayer_get_nth_subtitle_stream_info (void *player, int index, HCPlayerSubtitleInfo *subtitle_info);

/**
 * get the info of current actived audio track,
 * @player: a handle created by hcplayer_create
 * @video_info(out): audio info
 * @return: 0 succeess.
 */
int hcplayer_get_cur_audio_stream_info (void *player, HCPlayerAudioInfo *audio_info);

/**
 * get the info of current actived video track,
 * @player: a handle created by hcplayer_create
 * @video_info(out): video info
 * @return: 0 succeess.
 */
int hcplayer_get_cur_video_stream_info (void *player, HCPlayerVideoInfo *video_info);

/**
 * get the info of current actived subtitle track,
 * @player: a handle created by hcplayer_create
 * @video_info(out): subtitle info
 * @return: 0 succeess.
 */
int hcplayer_get_cur_subtitle_stream_info (void *player, HCPlayerSubtitleInfo *subtitle_info);

/**
 * get media informations of current audio/video/subtile.
 * @player: a handle created by hcplayer_create
 * @media_info(out): infos in eixf/idv3/idv2 ....
 * @return: 0 succeess.
 */
int hcplayer_get_media_info (void *player, HCPlayerMediaInfo *media_info);
/**
 * get file size.
 * @player: a handle created by hcplayer_create
 * @return: file size.
 */
int64_t hcplayer_get_filesize (void *player);

/********************* special handles ***********************/
/**
 * change audio track.
 * @player: a handle created by hcplayer_create.
 * @index: nth(0 ~
(hcplayer_get_audio_streams_count -1)).
 * @return: 0 succeess.
 */
int hcplayer_change_audio_track (void *player, int index);

/**
 * change video track.
 * @player: a handle created by hcplayer_create.
 * @index: nth(0 ~
(hcplayer_get_video_streams_count -1)).
 * @return: 0 succeess.
 */
int hcplayer_change_video_track (void *player, int index);

/**
 * change subtitle track.
 * @player: a handle created by hcplayer_create.
 * @index: nth(0 ~
(hcplayer_get_subtitle_streams_count -1)).
 * @return: 0 succeess.
 */
int hcplayer_change_subtitle_track (void *player, int index);

/**
 * change play rate.
 * @player: a handle created by hcplayer_create.
 * @rate: play rate(-32 <= rate <= 32 && rate != 0).
 * @return: 0 succeess.
 */
int hcplayer_set_speed_rate (void *player, float rate);

/**
 * this function will be effective when called early than hcplayer_play.
 * can set one or more snd out put. AUDDEV_I2SO | AUDDEV_SPO | AUDDEV_PCM
 * if this function is not called, AUDDEV_I2SO will be used as default
 * @player: a handle created by hcplayer_create.
 * @snd_devs: AUDDEV_I2SO | AUDDEV_SPO | AUDDEV_PCM.
 * @return: 0 succeess.
 */
int hcplayer_set_audio_output_dev (void *player, AudioOutDev snd_devs);

/**
 * this fucntion can set the src rect and dst rect of the display of video.
 * @player: a handle created by hcplayer_create.
 * @rect: a point to the display rect.
 */
int hcplayer_set_display_rect (void *player, struct vdec_dis_rect *rect);

/**
 * those fucntions can set the rotate/mirror of video,
 * the function will not work if the rotate_enable flag is not set when hcplayer_create.
 * @player: a handle created by hcplayer_create.
 * @rotate_type: rotate/mirror mode.
 * @return: 0 succeess. -1 failed.
 */
int hcplayer_change_rotate_type(void *player, rotate_type_e rotate_type);
int hcplayer_change_mirror_type(void *player, mirror_type_e mirror_type);
int hcplayer_change_rotate_mirror_type(void *player,
	rotate_type_e rotate_type, mirror_type_e mirror_type);

int hcplayer_read_transcoded_picture(void *player, void *buf, int len);

/**
 * 本函数能将图片缩放并裁剪到指定尺寸后，并转码成jpeg格式输出。
 * @url: 原始图片的路径
 * @out: 输出图片的地址， 此内存由本函数内部malloc，需要在使用完后由应用来free。
 * @out_size: 输出图片的大小。
 * @dst_width: 用户期望的图片宽度。
 * @dst_height: 用户期望的图片高度。
 * @start_time: 转视频时，设置截图时间点。设置范围((float)0 ~ (float)1)，表示文件的0~100%位置.
 * @out_width: 输出图片的宽度
 * @out_height: 输出图片的高度
 * @transcode_mode: 转码模式, 0:长宽等比例缩到指定长宽之内。1：等比例缩放后，裁剪到输出长宽≈指定长宽
 * @interrupt_cb: 用户注册的callback函数，返回非0时强制中断transcode。
 * @opaque: callback函数的入参
 */
int hcplayer_pic_transcode(char *url, uint8_t **out, int *out_size,
	int dst_width, int dst_height, double start_time,
	int *out_width, int *out_height, enum AVVideoRenderMode transcode_mode,
	int (*interrupt_cb)(void *), void *opaque);

int hcplayer_pic_transcode2(HCPlayerTranscodeArgs *transcode_args);

int hcplayer_get_buffering_percent(void *hdl);

/**
 * change printf dbg level.
 * @HCPlayerLogLevel: 0~7.
 */
void hcplayer_change_log_level (HCPlayerLogLevel level);

//register event callback
int hcplayer_active_event (void *player, uint32_t type);
//int hcplayer_inactive_event (void *player, int event_id);

void ffplayer_debug(void);
void *get_last_ffplayer(void);

int hcplayer_get_bypass_mode(void *player);

#ifdef __cplusplus
}
#endif

#endif /* __HCPLAYER_H_ */

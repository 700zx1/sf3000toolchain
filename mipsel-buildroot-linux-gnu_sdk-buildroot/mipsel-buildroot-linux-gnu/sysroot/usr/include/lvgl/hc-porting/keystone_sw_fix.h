#pragma once
#include "lv_area.h"

// KAF: Keystone Artifact Fix

enum {
    KAF_KNOB_NONE = 0,
    KAF_KNOB_ALWAYS_CHOP_EDGE_DEAD_ZONE = 1u << 0,
};

enum kaf_status_t {
    KAF_STATUS_NO_ERR,
    KAF_STATUS_FRAME_ACTIVE,
    KAF_STATUS_FRAME_INACTIVE,
    KAF_STATUS_INVALID_TRANSFORM,
    KAF_STATUS_FRAME_FAIL_TO_START,
    KAF_STATUS_FRAME_IN_FRAME,
};

enum {
    KAF_EDGE_LEFT = 1u << 0,
    KAF_EDGE_RIGHT = 1u << 1,
};

struct kaf_ctx_t;

struct kaf_ctx_t *kaf_get_ctx(void);

void kaf_init(struct kaf_ctx_t *ctx, int width, int height, unsigned knob);
void kaf_free(struct kaf_ctx_t *ctx);
void kaf_reset(struct kaf_ctx_t *ctx);

/// @brief switch KAF to in-frame state
/// @return KAF_STATUS_FRAME_ACTIVE, or KAF_STATUS_FRAME_INACTIVE, or KAF_STATUS_FRAME_IN_FRAME
enum kaf_status_t kaf_start_frame(struct kaf_ctx_t *ctx);

/// @brief switch KAF off in-frame state
void kaf_end_frame(struct kaf_ctx_t *ctx);

int kaf_is_active(struct kaf_ctx_t *ctx);

/// @brief catch edge pixels, regardless if KAF is active or not
enum kaf_status_t kaf_catch_edge(struct kaf_ctx_t *ctx,
		int rotate, int h_flip, int v_flip,
		const lv_area_t *area, const void *src, int src_stride);

/// @return flag to indicate if left or right should be updated
int kaf_fix(struct kaf_ctx_t *ctx);

/// @brief get left edge buffer
/// @param width width of the left edge buffer
/// @param height height of the left edge buffer
void *kaf_get_left_edge(struct kaf_ctx_t *ctx, int *width, int *height);

/// @brief get right edge buffer
/// @param width width of the right edge buffer
/// @param height height of the right edge buffer
void *kaf_get_right_edge(struct kaf_ctx_t *ctx, int *width, int *height);

/// @brief chop edge from rotated/flipped area
/// @param area The area before rotation and flipping
/// @param [out] chopped The edge chopped area. nothing is chopped if KAF is inactive.
void kaf_chop_edge(struct kaf_ctx_t *ctx, const lv_area_t *area,
                   int rotate, int h_flip, int v_flip, lv_area_t *chopped);

struct pq_settings;
/// @brief set PQ parameter so KAF can fix edge with gamma correction
/// @param pq the PQ parameter to set. NULL to invalidate gamma correction.
void kaf_set_pq_param(const struct pq_settings *pq);

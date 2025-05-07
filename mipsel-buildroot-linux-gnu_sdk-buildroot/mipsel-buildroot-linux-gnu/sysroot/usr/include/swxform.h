#pragma once

#include <stdbool.h>
#include "tile.h"

enum {
    GEO_XF_INVALID  = 0x1,
    GEO_XF_FLIP_H   = 0x2,
    GEO_XF_FLIP_V   = 0x4,
    GEO_XF_SWAP_XY  = 0x8,
};

unsigned translate_geo_xform(int rotate_clockwise, bool flip_h, bool flip_v);

struct swxf_cfg_t {
    unsigned geo_xform;
    const struct tile_t *src_tile;
    const struct tile_t *dst_tile;
    // TODO maybe filter mode
    int test_mode;
};

void scale(struct swxf_cfg_t *cfg,
    unsigned stride_tile, unsigned width, unsigned height, const uint8_t *luma,
    unsigned out_stride_tile, unsigned out_width, unsigned out_height, uint8_t *out_luma);

void scale_uv(struct swxf_cfg_t *cfg,
    unsigned stride_tile, unsigned width, unsigned height, const uint8_t *src,
    unsigned out_strid_tile, unsigned out_width, unsigned out_height, uint8_t *out);

void bilinear_tile_to_raster(const struct tile_t *tile,
    unsigned src_x, unsigned src_y,
    unsigned src_width, unsigned src_height, unsigned src_stride, const uint8_t *src,
    unsigned dst_width, unsigned dst_height, unsigned dst_stride, uint8_t *dst);

void bilinear_tile_uv_to_raster(const struct tile_t *tile,
    unsigned src_x, unsigned src_y,
    unsigned src_width, unsigned src_height, unsigned src_stride, const uint8_t *src,
    unsigned dst_width, unsigned dst_height, unsigned dst_stride, uint8_t *out);

void bilinear_raster_to_raster(
        unsigned src_x, unsigned src_y,
        unsigned src_width, unsigned src_height, unsigned src_stride, const uint8_t *src,
        unsigned dst_width, unsigned dst_height, unsigned dst_stride, uint8_t *dst);

void bilinear_raster_uv_to_raster(
        unsigned src_x, unsigned src_y,
        unsigned src_width, unsigned src_height, unsigned src_stride, const uint8_t *src,
        unsigned dst_width, unsigned dst_height, unsigned dst_stride, uint8_t *out);

void bilinear_planar_raster_uv_to_raster(
        unsigned src_x, unsigned src_y,
        unsigned src_width, unsigned src_height, unsigned src_stride,
        const uint8_t *src_u, const uint8_t *src_v,
        unsigned dst_width, unsigned dst_height, unsigned dst_stride, uint8_t *out);

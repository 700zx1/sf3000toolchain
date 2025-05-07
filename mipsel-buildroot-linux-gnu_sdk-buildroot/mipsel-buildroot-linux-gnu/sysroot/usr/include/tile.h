#pragma once

#include <stdint.h>

#ifdef __GNUC__
#define TILE_INLINE inline __attribute__((always_inline))
#else
#define TILE_INLINE inline
#endif

#define TILE_WIDTH(WIDTH_LOG2) (1 << (WIDTH_LOG2))
#define TILE_DX_MASK(WIDTH_LOG2) ((1 << (WIDTH_LOG2)) - 1)

#define TILE_HEIGHT(HEIGHT_LOG2) (1 << (HEIGHT_LOG2))
#define TILE_DY_MASK(HEIGHT_LOG2) ((1 << (HEIGHT_LOG2)) - 1)

#define TILE_SIZE_LOG2(WIDTH_LOG2, HEIGHT_LOG2) ((WIDTH_LOG2) + (HEIGHT_LOG2))
#define TILE_SIZE(WIDTH_LOG2, HEIGHT_LOG2) (1 << TILE_SIZE_LOG2(WIDTH_LOG2, HEIGHT_LOG2))


/// @brief Align value to alignment (given as log2(alignment))
static TILE_INLINE
unsigned align_log2(unsigned x, unsigned alignment_log2) {
    const unsigned mask = (1 << alignment_log2) - 1;
    return (x + mask) & ~mask;
}

/// @brief Align value to denominator and divide
static TILE_INLINE
unsigned align_div_log2(unsigned x, unsigned den_log2) {
    const unsigned mask = (1 << den_log2) - 1;
    return (x >> den_log2) + ((x & mask) != 0);
}

/// @brief Divide value and return the quotient and remainder
static TILE_INLINE
void div_log2(unsigned x, unsigned den_log2, unsigned *quot, unsigned *rem) {
    *quot = x >> den_log2;
    *rem = x & ((1u << den_log2) - 1);
}

/// @brief Get remainder
static TILE_INLINE
unsigned rem_log2(unsigned x, unsigned den_log2) {
    return x & ((1u << den_log2) - 1);
}


////////////////////////////////////////////////////////////////////////////////
// tiled 16x32
////////////////////////////////////////////////////////////////////////////////
#define T16X32_WIDTH_LOG2   4
#define T16X32_HEIGHT_LOG2  5

/*  swizzle rows within tile: 4 rows per group, inside the group
        line 0 -> 0 (storage row 0)
        line 1 \/ 2 (storage row 1)
        line 2 /\ 1 (storage row 2)
        line 3 -> 3 (storage row 3)
 */
static TILE_INLINE
int t16x32_swizzle(int dy) {
    return (dy & ~3) | ((dy & 1) << 1) | ((dy & 2) >> 1);
    // unsigned bits = dy & 3;
    // return (bits == 0 || bits == 3) ? dy : dy ^ 3;
}


////////////////////////////////////////////////////////////////////////////////
// tiled 32x16
////////////////////////////////////////////////////////////////////////////////
#define T32X16_WIDTH_LOG2   5
#define T32X16_HEIGHT_LOG2  4


struct tile_t {
    uint8_t type;
    uint8_t width_log2;
    uint8_t height_log2;
};

enum tile_type_e {
    TILE_32X16,
    TILE_16X32,
};

enum yuv_type_e
{
    YUV_420 ,
    YUV_422 ,
};
struct tile_t *tile_obj(enum tile_type_e);

/// @brief Evaluate tile offset from tile-x and tile-y
static TILE_INLINE
unsigned tile_offset(const struct tile_t *tile,
                     unsigned stride, unsigned tx, unsigned ty) {
    const int sh = TILE_SIZE_LOG2(tile->width_log2, tile->height_log2);
    return (stride * ty + tx) << sh;
}

/// @brief Evaluate intra-tile offset from dx and dy
static TILE_INLINE
unsigned tile_intra_offset(const struct tile_t *tile, unsigned dx, unsigned dy) {
    if (tile->type == TILE_16X32) {
        return (t16x32_swizzle(dy) << tile->width_log2) + dx;
    } else {
        return (dy << tile->width_log2) + dx;
    }
}

/// @brief Evaluate plane sample offset from x and y
static TILE_INLINE
unsigned tile_sample_offset(const struct tile_t *tile,
                            unsigned stride, unsigned x, unsigned y) {
    unsigned tx, ty, dx, dy;
    div_log2(x, tile->width_log2, &tx, &dx);
    div_log2(y, tile->height_log2, &ty, &dy);
    return tile_offset(tile, stride, tx, ty) + tile_intra_offset(tile, dx, dy);
}

/// @brief Evaluate plane sample offset from x and y
static TILE_INLINE
unsigned tile_sample_offset_uv(const struct tile_t *tile,
                               unsigned stride, unsigned x, unsigned y) {
    unsigned tx, ty, dx, dy;
    div_log2(x << 1, tile->width_log2, &tx, &dx);
    div_log2(y, tile->height_log2, &ty, &dy);
    return tile_offset(tile, stride, tx, ty) + tile_intra_offset(tile, dx, dy);
}

/// @brief Evaluate plane offset delta for (x + 1)
static TILE_INLINE
unsigned tile_offset_delta(const struct tile_t *tile, unsigned x) {
    const unsigned dx = rem_log2(x, tile->width_log2);
    const unsigned max_dx = (1u << tile->width_log2) - 1;
    if (dx < max_dx) {
        return 1;
    } else {
        return TILE_SIZE(tile->width_log2, tile->height_log2) - max_dx;
    }
}

/// @brief Evaluate UV plane offset delta for (x + 1)
static TILE_INLINE
unsigned tile_offset_delta_uv(const struct tile_t *tile, unsigned x) {
    const unsigned dx = rem_log2(x << 1, tile->width_log2);
    const unsigned max_dx = (1u << tile->width_log2) - 2;
    if (dx < max_dx) {
        return 2;
    } else {
        return TILE_SIZE(tile->width_log2, tile->height_log2) - max_dx;
    }
}

/// @brief Evaluate plane offset for x and (x + 1)
static TILE_INLINE
void tile_sample_offset_x(const struct tile_t *tile, unsigned x,
                          unsigned *offset_x, unsigned *offset_x_plus_1) {
    unsigned tx, dx;
    div_log2(x, tile->width_log2, &tx, &dx);
    const unsigned sz_log2 = tile->width_log2 + tile->height_log2;
    const unsigned offset = (tx << sz_log2) + dx;
    const unsigned max_dx = (1u << tile->width_log2) - 1;
    const unsigned delta = dx == max_dx ? (1u << sz_log2) - max_dx : 1;
    *offset_x = offset;
    *offset_x_plus_1 = offset + delta;
}

/// @brief Evaluate plane offset for y and (y + 1)
static TILE_INLINE
void tile_sample_offset_y(const struct tile_t *tile, unsigned stride, unsigned y,
                          unsigned *offset_y, unsigned *offset_y_plus_1) {
    unsigned ty, dy;
    div_log2(y, tile->height_log2, &ty, &dy);
    const unsigned sz_log2 = tile->width_log2 + tile->height_log2;
    const unsigned t_offset = (ty * stride) << sz_log2;
    *offset_y = t_offset + tile_intra_offset(tile, 0, dy);
    const unsigned max_dy = (1u << tile->height_log2) - 1;
    if (dy < max_dy) {
        *offset_y_plus_1 = t_offset + tile_intra_offset(tile, 0, dy + 1);
    } else {
        *offset_y_plus_1 = t_offset + (stride << sz_log2);
    }
}

/// @brief Evaluate UV plane offset for x and (x + 1)
static TILE_INLINE
void tile_sample_offset_x_uv(const struct tile_t *tile, unsigned x,
                             unsigned *offset_x, unsigned *offset_x_plus_1) {
    unsigned tx, dx;
    div_log2(x << 1, tile->width_log2, &tx, &dx);
    const unsigned sz_log2 = tile->width_log2 + tile->height_log2;
    const unsigned offset = (tx << sz_log2) + dx;
    const unsigned max_dx = (1u << tile->width_log2) - 2;
    const unsigned delta = dx == max_dx ? (1u << sz_log2) - max_dx : 2;
    *offset_x = offset;
    *offset_x_plus_1 = offset + delta;
}

uint8_t *tile_extract_line(const struct tile_t *tile,
        unsigned stride, const uint8_t *tiled_src,
        unsigned x, unsigned y, unsigned width, uint8_t *out);

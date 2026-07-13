/*
 * ANM06 data structures for TH10 sprite/animation format.
 * 64-byte packed headers with linked-list sprite traversal.
 */
#pragma once
#include <cstdint>
#include <vector>

namespace th10 {

#pragma pack(push, 1)
struct AnmSprite06 {
    uint32_t sprite_count;
    uint8_t  pad_04[24];
    uint32_t name_offset;
    int32_t  x;
    int32_t  y;
    uint8_t  pad_28[8];
    uint32_t texture_offset;
    uint16_t has_data;
    uint8_t  pad_36[2];
    uint32_t next_offset;
    uint8_t  pad_3C[4];
};
#pragma pack(pop)
static_assert(sizeof(AnmSprite06) == 64, "AnmSprite06 must be 64 bytes");

struct AnmTextureEntry {
    uint32_t offset;
    uint32_t size;
};

#pragma pack(push, 1)
struct AnmSpriteEntry {
    int32_t  frame_index;  // frame number within sequence
    float    x, y;          // pixel position within texture atlas
    float    w, h;          // pixel width and height
};
#pragma pack(pop)
static_assert(sizeof(AnmSpriteEntry) == 20, "AnmSpriteEntry must be 20 bytes");

struct AnmFrameUV {
    float    u0, v0;
    float    u1, v1;
    uint32_t id;
};

struct AnmTexture {
    int  gl_texture_id = 0;
    int  width  = 0;
    int  height = 0;
    std::vector<AnmFrameUV> frames;
};

} // namespace th10

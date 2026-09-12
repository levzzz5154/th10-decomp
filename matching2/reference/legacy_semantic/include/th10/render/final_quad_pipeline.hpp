#pragma once

// Sprite quad submission (retail 0x00442670).
//
// Retail builds every sprite into one shared four-vertex buffer at
// 0x004978C0 and then calls 0x00442670 to finish it: the manager's screen
// offset, the optional pixel snap, the sprite's texture coordinates, the
// viewport cull, the texture change, the modulation colour and finally the
// render-state sync (0x004425A0) and the staging append (0x00442FE0).

// One vertex of the shared quad buffer. Retail's stride is 0x1C bytes and
// the corner order 0x004978C0/DC/F8/914 is
// {left,top} {right,top} {left,bottom} {right,bottom}.
struct QuadSubmitVertex {
    float x;             // +0x00
    float y;             // +0x04
    float z;             // +0x08
    float rhw;           // +0x0C
    unsigned int color;  // +0x10
    float u;             // +0x14
    float v;             // +0x18
};

// The sprite descriptor the VM points at through vm+0x394.
struct QuadSubmitSprite {
    unsigned int texture;  // +0x04, the value handed to SetTexture
    float u0;              // +0x20
    float v0;              // +0x24
    float u1;              // +0x28
    float v1;              // +0x2C
};

// The animation VM fields 0x00442670 reads.
struct QuadSubmitVm {
    float uv_scroll_x;               // vm+0x54
    float uv_scroll_y;               // vm+0x58
    unsigned int flags;              // vm+0x35C, bit 15 picks the colour
    unsigned int color_primary;      // vm+0x2FC
    unsigned int color_secondary;    // vm+0x300
    const QuadSubmitSprite* sprite;  // vm+0x394
};

// The animation manager fields 0x00442670 reads or updates.
struct QuadSubmitManager {
    float offset_x;               // manager+0x5C
    float offset_y;               // manager+0x60
    unsigned int cached_texture;  // manager+0x3ADA64
    unsigned char textured;       // manager+0x3ADA6A
    int fade_enabled;             // manager+0x73245C
    unsigned char fade[4];        // manager+0x732458..0x73245B: b, g, r, a
    // The cull rectangle is the active viewport, read as four unsigned
    // words from dword_491FAC+0xCC, +0xD0, +0xD4 and +0xD8 - the same
    // D3DVIEWPORT9 that render-target selection hands to SetViewport
    // through the device vtable +0xBC.
    unsigned int clip_x;
    unsigned int clip_y;
    unsigned int clip_width;
    unsigned int clip_height;
};

struct QuadSubmitEnv {
    void (*flush)(void);                                 // 0x00442F50
    void (*set_texture)(unsigned int texture);           // device vtable +0x104
    void (*sync_render_state)(unsigned int vm_flags);    // 0x004425A0
    void (*append)(const QuadSubmitVertex vertices[4]);  // 0x00442FE0
};

// Finish and stage one sprite quad. `mode` is retail's third argument:
// bit 0 arms the pixel snap and bit 1 suppresses the colour override.
// Always returns 0, like retail.
int Quad_SubmitFinal(QuadSubmitVertex quad[4], const QuadSubmitVm* vm,
                     QuadSubmitManager* manager, const QuadSubmitEnv* env,
                     unsigned int mode);

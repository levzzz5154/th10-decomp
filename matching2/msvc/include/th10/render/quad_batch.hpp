#ifndef TH10_QUAD_BATCH_HPP
#define TH10_QUAD_BATCH_HPP
struct RenderEntity;
struct TexturedVertex { float x, y, z, rhw; unsigned int color; float u, v; };
struct SprtCtrlBatchView {
    unsigned char unknown_00000000[0x54];
    int state_changes;
    int draw_calls;
    float origin_x;
    float origin_y;
    unsigned char unknown3[0x3ADA60 - 0x64];
    unsigned int cached_color;
    void* cached_texture;
    unsigned char cached_blend, cached_unknown_69, cached_format, cached_unknown_6b;
    unsigned char cached_unknown_6c, cached_unknown_6d, cached_filter, cached_unknown_6f;
    unsigned char unknown5[0x3ADAC8 - 0x3ADA70];
    int quad_count;
    unsigned char unknown6[0x72DACC - 0x3ADACC];
    TexturedVertex* cursor;
    void* batch_start;
    unsigned char unknown7[0x732458 - 0x72DAD4];
    unsigned char fade_blue, fade_green, fade_red, fade_alpha;
    int fade_enabled;

    __declspec(noinline) int AppendQuad(const TexturedVertex* vertices);
    __declspec(noinline) int SubmitSpriteQuad(const RenderEntity* entity, unsigned int mode);
    __declspec(noinline) int SubmitSpriteQuadMirrored(const RenderEntity* entity, unsigned int mode);
    __declspec(noinline) int DrawQuad(const RenderEntity* entity, const TexturedVertex* vertices);
    __declspec(noinline) int DrawFan(const RenderEntity* entity, const void* vertices, unsigned int count);
    __declspec(noinline) int DrawSolidStrip(const RenderEntity* entity, const void* vertices, unsigned int count);
    __declspec(noinline) int DrawSolidFan(const RenderEntity* entity, const void* vertices, unsigned int count);
    __declspec(noinline) int Flush();
    __declspec(noinline) void SyncRenderState(const RenderEntity* entity);
    __declspec(noinline) int DrawStrip(const RenderEntity* entity, const void* vertices, unsigned int count);
    // 0x00448620: republishes the first render stage and draws animation
    // bucket 3; see src/core/sprtlib/animation_manager_draw_stage0_bucket3.cpp.
    __declspec(noinline) int RenderStage0Bucket3();
    // 0x00448770, 0x004487C0 and 0x00448810: the scheduler tasks that
    // republish the second render stage and then draw one animation bucket
    // (0x0F, 0x10 and 0x13); see src/core/sprtlib/animation_manager_draw_stage1_bucket0f.cpp.
    __declspec(noinline) int RenderStage1Bucket0F();
    __declspec(noinline) int RenderStage1Bucket10();
    __declspec(noinline) int RenderStage1Bucket13();
    // 0x00448740: the scheduler task that clears the shake offsets and the
    // stored sprite origin and then renders render-slot 14.
    __declspec(noinline) int ResetOriginAndRenderSlot14();
    // 0x004485F0, 0x00448610 and 0x004486A0..0x00448730: scheduler tasks that
    // draw one animation bucket; see src/core/sprtlib/animation_bucket_tasks.cpp.
    __declspec(noinline) int DrawBucket0();
    __declspec(noinline) int DrawBucket2();
    __declspec(noinline) int DrawBucket4();
    __declspec(noinline) int DrawBucket5();
    __declspec(noinline) int DrawBucket6();
    __declspec(noinline) int DrawBucket7();
    __declspec(noinline) int DrawBucket8();
    __declspec(noinline) int DrawBucket9();
    __declspec(noinline) int DrawBucket10();
    __declspec(noinline) int DrawBucket11();
    __declspec(noinline) int DrawBucket12();
    __declspec(noinline) int DrawBucket13();
    // 0x00448980: walks one animation bucket's entity list and draws every node
    // in it; see src/core/sprtlib/animation_manager_render_bucket.cpp.
    __declspec(noinline) int RenderBucket(int index);
};

struct RenderTexture {
    int reserved;
    void* texture;
    unsigned char reserved_008[0x20 - 0x08];
    float u0, v0, u1, v1;
};
struct RenderVec3 { float x, y, z; };
struct RenderEntity {
    unsigned char reserved_000[0x24];
    RenderVec3 rotation;                   // 0x24, radians around X/Y/Z
    unsigned char reserved_030[0x3C - 0x30];
    float scale_x;                         // 0x3C
    float scale_y;                         // 0x40
    unsigned char reserved_044[0x4C - 0x44];
    float sprite_width;                    // 0x4C
    float sprite_height;                   // 0x50
    float uv_scroll_x;
    float uv_scroll_y;
    unsigned char reserved_05C[0x2FC - 0x5C];
    unsigned int color;
    unsigned int color_secondary;
    unsigned char reserved_304[0x30C - 0x304];
    unsigned int strip_count;
    unsigned char reserved_310[0x334 - 0x310];
    RenderVec3 base_position;              // 0x334
    RenderVec3 position;                   // 0x340
    RenderVec3 render_offset;              // 0x34C
    const void* strip_vertices;
    unsigned int flags;
    unsigned char reserved_360[0x394 - 0x360];
    RenderTexture* texture;

    // 0x00443F80: project the entity's billboard quad and submit it as a
    // plain sprite when the projection succeeds; see
    // src/core/sprtfunc/entity_submit_projected.cpp.
    __declspec(noinline) int SubmitProjectedQuad(SprtCtrlBatchView* manager);
    // 0x00445880: draw the strip vertices as a 33-point fan; see
    // src/core/sprtfunc/render_entity_draw_fan.cpp.
    __declspec(noinline) int DrawFan33();
};
// The shared sprite quad both submit pipelines finish and append.
extern "C" TexturedVertex g_quad_vertices[4];
// The half-pixel the two submit pipelines pull their snapped edges back by.
// Retail kept one .rdata copy per pipeline instead of the shared 0.5f pool.
extern "C" float data_00470e8;
extern "C" float data_00470ec;
// The render target whose D3D viewport bounds the sprite quad.
struct RenderTargetViewport {
    unsigned char reserved[0xCC];
    unsigned int x, y, width, height;
    float min_z, max_z;
};
extern "C" RenderTargetViewport* g_render_stage_active;
// 0x004423C0: one saturated colour channel product, scaled by 1/128.
__declspec(noinline) unsigned int AnimationColor_MultiplyChannel(unsigned char value, unsigned char scale);
struct ScreenRect { float left, top, right, bottom; };
__declspec(noinline) int __stdcall DrawSolidQuad(const ScreenRect*, unsigned int);
extern "C" SprtCtrlBatchView* g_sprt_ctrl;
struct RenderDevice {
    void** vtable;
    long Stage(unsigned int stage, unsigned int state, unsigned int value) {
        typedef long (__stdcall *Call)(void*, unsigned int, unsigned int, unsigned int);
        return ((Call)vtable[0x10C / 4])(this, stage, state, value);
    }
    long Sampler(unsigned int stage, unsigned int state, unsigned int value) {
        typedef long (__stdcall *Call)(void*, unsigned int, unsigned int, unsigned int);
        return ((Call)vtable[0x114 / 4])(this, stage, state, value);
    }
    long Texture(unsigned int stage, void* texture) {
        typedef long (__stdcall *Call)(void*, unsigned int, void*);
        return ((Call)vtable[0x104 / 4])(this, stage, texture);
    }
    long State(unsigned int state, unsigned int value) {
        typedef long (__stdcall *Call)(void*, unsigned int, unsigned int);
        return ((Call)vtable[0xE4 / 4])(this, state, value);
    }
    long Format(unsigned int format) {
        typedef long (__stdcall *Call)(void*, unsigned int);
        return ((Call)vtable[0x164 / 4])(this, format);
    }
    long Draw(unsigned int type, unsigned int count, const void* vertices, unsigned int stride) {
        typedef long (__stdcall *Call)(void*, unsigned int, unsigned int, const void*, unsigned int);
        return ((Call)vtable[0x14C / 4])(this, type, count, vertices, stride);
    }
    long Clear(unsigned int count, const void* rects, unsigned int flags,
               unsigned int color, float depth, unsigned int stencil) {
        typedef long (__stdcall *Call)(void*, unsigned int, const void*, unsigned int, unsigned int, float, unsigned int);
        return ((Call)vtable[0xAC / 4])(this, count, rects, flags, color, depth, stencil);
    }
    long Present(const void* source, const void* dest, void* window, const void* dirty) {
        typedef long (__stdcall *Call)(void*, const void*, const void*, void*, const void*);
        return ((Call)vtable[0x44 / 4])(this, source, dest, window, dirty);
    }
    long Reset(void* parameters) {
        typedef long (__stdcall *Call)(void*, void*);
        return ((Call)vtable[0x40 / 4])(this, parameters);
    }
    long Viewport(const void* viewport) {
        typedef long (__stdcall *Call)(void*, const void*);
        return ((Call)vtable[0xBC / 4])(this, viewport);
    }
};
extern "C" RenderDevice* g_d3d_device;
struct DeviceViewport { unsigned int x, y, width, height; float min_z, max_z; };
extern "C" DeviceViewport g_device_viewport;
extern "C" char g_present_parameters[];
__declspec(noinline) int __stdcall ClearAndPresentTwice(unsigned int color);
struct SolidPosition {
    float x, y, z;
    SolidPosition(float px, float py, float pz) : x(px), y(py), z(pz) {}
    SolidPosition() {}
};
struct SolidVertex {
    SolidPosition position;
    float rhw;
    unsigned int color;
};
__declspec(noinline) int __stdcall DrawGradientQuad(const ScreenRect*, unsigned int, unsigned int, unsigned int, unsigned int);
#endif

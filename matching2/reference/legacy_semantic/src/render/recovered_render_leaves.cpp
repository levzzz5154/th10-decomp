#include "th10/render/recovered_render_leaves.hpp"

#include <cstring>

namespace th10 {
namespace render_leaves {
namespace {

// The recovery chain owns the vertex staging in its readable (host) form.
// Retail keeps the three fields scattered across the 32-bit manager
// (quad count at +0x3ADAC8, write cursor at +0x72DACC, batch start at
// +0x72DAD0); those dword slots cannot hold host pointers - the cursor
// and batch-start slots are only four bytes apart - so the scattered
// offsets are the 32-bit MSVC overlays' territory and the host-form
// struct below is the recovery side's staging.
QuadVertexStaging g_staging = {0, 0, 0};
QuadVertexStaging* g_bound_staging = &g_staging;
void (*g_bound_flush)(void) = 0;
int g_draw_calls = 0;

extern "C" unsigned long dword_491C10;   // animation manager
extern "C" unsigned long dword_491C30;   // IDirect3DDevice9

typedef unsigned long (__stdcall* SetTextureStageStateFn)(
    void* device, unsigned int stage, unsigned int type,
    unsigned int value);
typedef unsigned long (__stdcall* SetFvFFn)(void* device,
                                            unsigned int fvf);
typedef unsigned long (__stdcall* DrawPrimitiveUpFn)(
    void* device, unsigned int primitive_type, unsigned int primitive_count,
    const void* vertices, unsigned int vertex_stride);

// The retail D3D calls go through the device's vtable: `mov eax, dword_491C30;
// mov ecx, [eax]; ... call dword ptr [ecx+10Ch]` - the method slot is
// vtable[offset/4], with the device as the first argument.
void DeviceSetTextureStageState(unsigned int stage, unsigned int type,
                                unsigned int value) {
    void* device = (void*)dword_491C30;
    if (device == 0) return;
    SetTextureStageStateFn fn =
        (SetTextureStageStateFn)(*(void***)device)[0x10C / 4];
    fn(device, stage, type, value);
}

void DeviceSetFvF(unsigned int fvf) {
    void* device = (void*)dword_491C30;
    if (device == 0) return;
    SetFvFFn fn = (SetFvFFn)(*(void***)device)[0x164 / 4];
    fn(device, fvf);
}

void DeviceDrawPrimitiveUp(unsigned int primitive_type,
                           unsigned int primitive_count,
                           const QuadRenderVertex* vertices,
                           unsigned int vertex_stride) {
    void* device = (void*)dword_491C30;
    if (device == 0) return;
    DrawPrimitiveUpFn fn = (DrawPrimitiveUpFn)(*(void***)device)[0x14C / 4];
    fn(device, primitive_type, primitive_count, vertices, vertex_stride);
}

QuadVertexStaging ReadStaging() {
    return *g_bound_staging;
}

void WriteStaging(const QuadVertexStaging& staging) {
    *g_bound_staging = staging;
}

// Retail sub_443080 reads the three-term origin as the sum of the position
// triples at +0x334 / +0x340 / +0x34C (per-axis).
void ReadOrigin(const AnmDrawVm* vm, float origin[3]) {
    const unsigned char* p = (const unsigned char*)vm;
    for (int axis = 0; axis < 3; ++axis) {
        origin[axis] = *(const float*)(p + 0x334 + 4 * axis) +
                       *(const float*)(p + 0x340 + 4 * axis) +
                       *(const float*)(p + 0x34C + 4 * axis);
    }
}

// Retail 0x00442670 selects vm+0x2FC over vm+0x300 on bit 15 of the flag
// word at +0x35C.
unsigned int ReadVmColor(const AnmDrawVm* vm) {
    const unsigned char* p = (const unsigned char*)vm;
    const unsigned int flags = *(const unsigned int*)(p + 0x35C);
    return (flags & 0x8000u) != 0 ? *(const unsigned int*)(p + 0x300)
                                  : *(const unsigned int*)(p + 0x2FC);
}

float RoundCenterEdge(float edge, float /*extent*/) {
    // Retail floors the centred near-edge (`floor(... - w*0.5)`).
    return std::floor(edge);
}

void AppendCorners(const AnchoredQuadVertex vertices[4], unsigned int color) {
    QuadVertexStaging staging = ReadStaging();
    QuadRenderVertex words[4];
    for (int i = 0; i < 4; ++i) {
        unsigned int* w = words[i].words;
        std::memcpy(&w[0], &vertices[i].x, sizeof(unsigned int));
        std::memcpy(&w[1], &vertices[i].y, sizeof(unsigned int));
        std::memcpy(&w[2], &vertices[i].z, sizeof(unsigned int));
        std::memcpy(&w[3], &vertices[i].w, sizeof(unsigned int));
        w[4] = color;
        w[5] = 0;  // u: the sprite UV decode is the render platform's
        w[6] = 0;  // v: (the host supplies texture coordinates)
    }
    AnimationManager_AppendQuadVertices(&staging, words);
    WriteStaging(staging);
}

// The render_quad callback has no context parameter (retail's colour lands
// in the shared quad buffer); a static slot carries the current colour
// between the builder and the staging writer.
unsigned int g_current_quad_color = 0xFFFFFFFFu;

void RenderQuadAppend(const AnchoredQuadVertex vertices[4], int /*mode*/) {
    AppendCorners(vertices, g_current_quad_color);
}

int DrawStandard(void* context) {
    const AnmDrawVm* vm = static_cast<const AnmDrawVm*>(context);
    // The AnmDrawVm struct is the cleaned host form; the retail offsets are
    // scale +0x3C/+0x40, size +0x4C/+0x50 and the flag word +0x35C.
    const unsigned char* p = (const unsigned char*)vm;
    float origin[3];
    ReadOrigin(vm, origin);
    AnchoredQuadSource source;
    std::memset(&source, 0, sizeof(source));
    source.base_x = origin[0];
    source.base_y = origin[1];
    source.base_z = origin[2];
    source.scale_x = *(const float*)(p + 0x3C);
    source.scale_y = *(const float*)(p + 0x40);
    source.width = *(const float*)(p + 0x4C);
    source.height = *(const float*)(p + 0x50);
    const unsigned int flags = *(const unsigned int*)(p + 0x35C);
    source.anchor_x = (flags >> 0x12) & 3u;
    source.anchor_y = (flags >> 0x12) & 3u;
    const unsigned int color = ReadVmColor(vm);
    g_current_quad_color = color;
    AnchoredQuadEnv env;
    env.round_center_edge = RoundCenterEdge;
    env.render_quad = RenderQuadAppend;
    Quad_BuildAndRenderAnchored(&source, &env);
    return 0;
}

int DrawUnrotated(void* context) { return DrawStandard(context); }

int DrawMode7(void* context, AnmDrawVm* vm) {
    (void)context;
    return DrawStandard(vm);
}

int DrawCornerQuad(void* context, int /*layer*/) {
    const AnmDrawVm* vm = static_cast<const AnmDrawVm*>(context);
    AnchoredQuadVertex corners[4];
    std::memset(corners, 0, sizeof(corners));
    AppendCorners(corners, ReadVmColor(vm));
    return 0;
}

}  // namespace

QuadBatchEnv DefaultQuadBatchEnv() {
    QuadBatchEnv env;
    env.set_texture_stage_state = DeviceSetTextureStageState;
    env.set_fvf = DeviceSetFvF;
    env.draw_primitive_up = DeviceDrawPrimitiveUp;
    return env;
}

void BindSharedQuadStaging(QuadVertexStaging* staging,
                           void (*flush)(void)) {
    g_bound_staging = staging != 0 ? staging : &g_staging;
    g_bound_flush = staging != 0 ? flush : 0;
}

void FlushQuadBatch() {
    if (g_bound_flush != 0) {
        g_bound_flush();
        return;
    }
    QuadVertexStaging staging = ReadStaging();
    if (staging.quad_count == 0) return;
    static const QuadBatchEnv env = DefaultQuadBatchEnv();
    AnimationManager_FlushQuadBatch(&staging, &g_draw_calls, &env);
    WriteStaging(staging);
}

// Test-visible handle to the recovery-side staging (the host-form
// counterpart of the retail manager's scattered 32-bit fields).
QuadVertexStaging* Staging() { return g_bound_staging; }

void AppendQuadColored(const float corners[4][2], unsigned int color) {
    AnchoredQuadVertex vertices[4];
    for (int i = 0; i < 4; ++i) {
        vertices[i].x = corners[i][0];
        vertices[i].y = corners[i][1];
        vertices[i].z = 0.0f;
        vertices[i].w = 1.0f;
    }
    AppendCorners(vertices, color);
}

AnmDrawEnv DefaultAnmDrawEnv() {
    AnmDrawEnv env;
    env.draw_standard = DrawStandard;
    env.draw_unrotated = DrawUnrotated;
    env.draw_corner_quad = DrawCornerQuad;
    env.draw_mode4 = DrawStandard;
    env.draw_mode5 = DrawStandard;
    env.draw_mode6 = DrawStandard;
    env.draw_mode7 = DrawMode7;
    env.draw_mode8 = DrawStandard;
    env.draw_mode9 = DrawStandard;
    return env;
}

}  // namespace render_leaves
}  // namespace th10

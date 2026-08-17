#pragma once

// Readable host form of the retail normal ANM sprite quad.
struct AnmSpriteQuadVertex {
    float x;
    float y;
    float z;
    float rhw;
    unsigned int color;
    float u;
    float v;
};

struct AnmSpriteQuadInput {
    float center_x;
    float center_y;
    float center_z;
    float width;
    float height;
    float rotation;
    unsigned int flags;
    unsigned int primary_color;
    unsigned int secondary_color;
    float u0;
    float v0;
    float u1;
    float v1;
    float uv_scroll_x;
    float uv_scroll_y;
};

unsigned int AnmSprite_SelectedColor(const AnmSpriteQuadInput* input);
void AnmSprite_BuildQuad(const AnmSpriteQuadInput* input,
                         AnmSpriteQuadVertex output[4]);
void AnmSprite_ExpandTriangleList(const AnmSpriteQuadVertex quad[4],
                                  AnmSpriteQuadVertex output[6]);

struct AnmSpriteProjectionContext {
    const float* view;
    const float* projection;
    const float* viewport; // x, y, width, height
    float reference_point[3];
};

// Build the projected billboard used by retail ANM mode 4. Returns nonzero
// when the center is outside the active depth range or projection is unavailable.
int AnmSprite_BuildProjectedBillboard(
    const AnmSpriteQuadInput* input,
    const AnmSpriteProjectionContext* projection,
    AnmSpriteQuadVertex output[4]);

// Rebuild and persist the raw AnimationObject world matrix used by retail ANM
// mode 5, then project its anchor-dependent 256x256 quad.
int AnmSprite_BuildProjectedWorldQuad(
    unsigned char* object, const AnmSpriteQuadInput* input,
    const AnmSpriteProjectionContext* projection,
    AnmSpriteQuadVertex output[4], float output_world[16]);

// Retail mode 7 transforms four 0x14-byte probe records through the published
// world matrix and fades each projected corner's RGB by camera distance.
int AnmSprite_ApplyProjectedDistanceColors(
    AnmSpriteQuadVertex quad[4], const unsigned char* probes,
    const float world[16], unsigned int base_color, const float camera[3],
    float near_distance, float far_distance, unsigned int far_color);

struct AnmSpriteRenderBackend {
    void* context;
    void (*submit)(void* context, void* manager, unsigned int texture,
                   const AnmSpriteQuadInput* input,
                   const AnmSpriteQuadVertex quad[4],
                   unsigned int submit_mode);
    const AnmSpriteProjectionContext* (*projection)(void* context);
    int (*draw_transformed)(void* context, void* manager,
                            unsigned char* object);
    int (*draw_strip)(void* context, void* manager,
                      unsigned char* object);
    int (*draw_ring)(void* context, void* manager,
                     unsigned char* object);
};

// The standalone binds its manager-owned batch here. Other PE32 consumers may
// leave it unbound and use the direct D3D9 fallback in AnimationObject_Render.
void AnmSpriteRenderer_BindBackend(const AnmSpriteRenderBackend* backend);
const AnmSpriteRenderBackend* AnmSpriteRenderer_GetBackend();

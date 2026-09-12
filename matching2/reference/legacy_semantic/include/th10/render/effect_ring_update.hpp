#pragma once

// 32-segment textured ripple ring per-frame update (retail 0x00445620).
// ---------------------------------------------------------------------------
// 0x00445620 - 32-segment ripple ring update (update callback stored at
// owner+0x398 by the constructor 0x004452F0; the float block is 0x4B0 bytes)
// ---------------------------------------------------------------------------

struct EffectRingVertex {
	float x, y, z, w;     // w stays 1.0 from the constructor
	unsigned int diffuse; // D3DCOLOR
	float u, v;
};

struct EffectRingState {
	EffectRingVertex vertices[33]; // [0] center, [1..31] rim, [32] closing dup
	float pad_231;                  // float index 231 (unused)
	float radius[33];               // float index 232; entries 0..30 used
	float radial_speed[32];         // float index 265; entries 0..30 used
	float uv_scroll_speed;          // float index 297 (applied to u and v)
	float uv_scroll_speed_alt;      // float index 298 (used by the draw path)
	float pad_299;                  // float index 299 (unused)
};

struct EffectRingOwner {
	unsigned int diffuse;     // +0x2FC
	float base_position[3];   // +0x334
	float offset_position[3]; // +0x340
	EffectRingState* ring;  // +0x358 (malloc'd 0x4B0 bytes by 0x004452F0)
};

int EffectRing_Update(EffectRingOwner* owner);

struct EffectRingDrawEnv {
    void* context;
    void (*flush)(void* context);
    void (*sync_state)(void* context);
    void (*bind_texture)(void* context);
    void (*draw_fan)(void* context, int primitive_count,
                     const EffectRingVertex* vertices, int stride);
};

// Retail 0x00445880 -> 0x004450E0: submit all 33 ring vertices as a
// 31-primitive triangle fan after synchronizing ANM state and texture.
int EffectRing_Draw(const EffectRingOwner* owner,
                    const EffectRingDrawEnv* env);

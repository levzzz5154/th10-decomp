#pragma once
// Game-state animation/overlay renderer (retail 0x00415800, 768 bytes).
struct OverlayRect { float left,top,right,bottom; };
struct OverlayGaugeSegment { float value; unsigned color; };
struct GameStateOverlay {
    void* primary[10]; void* secondary[10]; void* tertiary[9];
    void* quaternary[4]; void* quinary[7];
    unsigned char overlay_alpha; float overlay_progress;
    float gauge_value; OverlayGaugeSegment gauge_segments[4];
    void* input_prompt; int stage_index; int prompt_hidden;
    void* late_pair[2];
};
struct GameStateOverlayEnv {
    int overlay_counter; bool input_owner_present; bool input_device_present;
    unsigned input_bits;
    void (*draw_animation)(void* animation);
    void (*draw_rect)(const OverlayRect& rect,unsigned color);
};
int GameStateOverlay_Draw(const GameStateOverlay* state,const GameStateOverlayEnv* env);

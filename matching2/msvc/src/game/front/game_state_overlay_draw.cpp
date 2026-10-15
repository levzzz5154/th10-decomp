// 0x00415800: draw the front animation banks, progress bars and input prompts.
#include "th10/render/quad_batch.hpp"
#include <stddef.h>
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
    SprtCtrlBatchView* manager, RenderEntity* entity);

struct OverlayVm_00415800 {
    RenderEntity entity;
    unsigned char reserved_tail[0x3AC - sizeof(RenderEntity)];
};
struct OverlaySegment_00415800 { float value; unsigned int color; };
struct FrontDrawView {
    unsigned char reserved_0000[0x10];
    OverlayVm_00415800 primary[10];
    OverlayVm_00415800 secondary[10];
    OverlayVm_00415800 tertiary[9];
    OverlayVm_00415800 quaternary[4];
    OverlayVm_00415800 late_pair[2];
    OverlayVm_00415800 quinary[7];
    OverlayVm_00415800 input_prompt;
    unsigned char reserved_9df4[0x9E84 - 0x9DF4];
    float gauge_value;
    unsigned char reserved_9e88[0x9E94 - 0x9E88];
    OverlaySegment_00415800 gauge_segments[4];
    unsigned char reserved_9eb4[4];
    int prompt_hidden;
    unsigned char reserved_9ebc[4];
    int stage_index;
};
typedef char OverlaySecondaryOffset[(offsetof(FrontDrawView, secondary) == 0x24C8) ? 1 : -1];
typedef char OverlayTertiaryOffset[(offsetof(FrontDrawView, tertiary) == 0x4980) ? 1 : -1];
typedef char OverlayGaugeOffset[(offsetof(FrontDrawView, gauge_value) == 0x9E84) ? 1 : -1];
typedef char OverlaySegmentsOffset[(offsetof(FrontDrawView, gauge_segments) == 0x9E94) ? 1 : -1];
struct OverlayInputDevice_00415800 { unsigned char reserved[0x2480]; unsigned int flags; };
struct OverlayInputOwner_00415800 { unsigned char reserved[0x10]; OverlayInputDevice_00415800* device; };
extern "C" {
    extern int g_player_power_display;
    extern OverlayInputOwner_00415800* g_enemy_ctrl;
}
#pragma code_seg(".text$001soverlay")
extern "C" __declspec(noinline) int __stdcall GameStateOverlay_Draw_00415800(FrontDrawView* state) {
    ScreenRect rect;
    OverlayVm_00415800* cursor = state->secondary;
    int count = 10;
    do {
        asm_FUN_004451c0_004451c0(g_sprt_ctrl, &cursor[-10].entity);
        asm_FUN_004451c0_004451c0(g_sprt_ctrl, &cursor->entity);
        ++cursor;
    } while (--count);
    cursor = state->tertiary;
    count = 9;
    do {
        asm_FUN_004451c0_004451c0(g_sprt_ctrl, &cursor->entity);
        ++cursor;
    } while (--count);
    cursor = state->quaternary;
    count = 4;
    do {
        asm_FUN_004451c0_004451c0(g_sprt_ctrl, &cursor->entity);
        ++cursor;
    } while (--count);
    cursor = state->quinary;
    count = 7;
    do {
        asm_FUN_004451c0_004451c0(g_sprt_ctrl, &cursor->entity);
        ++cursor;
    } while (--count);
    if (g_player_power_display) {
        rect.left = 51.0f;
        rect.top = 461.0f;
        rect.right = static_cast<float>(g_player_power_display);
        rect.right *= 0.2923077f;
        rect.bottom = 463.0f;
        rect.right += 51.0f;
        DrawSolidQuad(&rect, static_cast<unsigned int>(((const unsigned char*)&state->quinary[0].entity.color)[3]) << 24);
        rect.left = 50.0f;
        rect.top = 460.0f;
        rect.right -= 1.0f;
        rect.bottom = 462.0f;
        DrawSolidQuad(&rect, (static_cast<unsigned int>(((const unsigned char*)&state->quinary[0].entity.color)[3]) << 24) | 0xFFFFFFu);
    }
    if (state->gauge_value > 0.0f) {
        rect.left = 41.0f;
        rect.top = 23.0f;
        rect.right = state->gauge_value * 342.0f + 41.0f;
        rect.bottom = 25.0f;
        DrawSolidQuad(&rect, 0xFF000000u);
        rect.left = 40.0f;
        rect.top = 22.0f;
        rect.right -= 1.0f;
        rect.bottom = 24.0f;
        DrawSolidQuad(&rect, 0xFFFFFFFFu);
        OverlaySegment_00415800* segment = state->gauge_segments;
        count = 4;
        do {
            if (segment->value != 0.0f) {
                const float value = segment->value < state->gauge_value ? segment->value : state->gauge_value;
                rect.left = 40.0f;
                rect.top = 22.0f;
                rect.right = value * 342.0f + 40.0f;
                rect.bottom = 24.0f;
                DrawSolidQuad(&rect, segment->color);
            }
            ++segment;
        } while (--count);
    }
    if (g_enemy_ctrl) {
        OverlayInputDevice_00415800* device = g_enemy_ctrl->device;
        if (device && (~(device->flags >> 4) & 1) && (~device->flags & 1))
            asm_FUN_004451c0_004451c0(g_sprt_ctrl, &state->input_prompt.entity);
        if (g_enemy_ctrl && state->stage_index >= 0 && g_enemy_ctrl->device && !state->prompt_hidden) {
            cursor = state->late_pair;
            count = 2;
            do {
                asm_FUN_004451c0_004451c0(g_sprt_ctrl, &cursor->entity);
                ++cursor;
            } while (--count);
        }
    }
    return 1;
}
#pragma code_seg()

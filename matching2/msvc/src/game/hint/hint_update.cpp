// 0x00419650 - per-frame update of the floating text manager.
//
// Drains the current stage's pending-text queue into the ten on-screen text
// sprites, then fades every sprite the player is standing behind so the text
// never hides the player: a quarter of its normal alpha inside the sprite's
// box, ramping back to full over a 32-pixel margin on either axis.
//
// The receiver arrives in EBX and the queue head goes to the drain in EAX;
// both come from the whole-program pass, so this unit is compiled in the
// cluster build_support/layout/ltcg/recovery_mark_text_and_dispatcher_004479d0.json.
#include <math.h>

#include "th10/game/indicator_animation_lookup_00419120.hpp"
#include "th10/game/player.hpp"

extern "C" int recovery_indicator_owner_00474c84;   // current stage tag
extern "C" int g_globals_stage;                       // current stage queue index

#pragma code_seg(".text$00419650_fn")
int HintUpdateView::Update() {
    if (owner_tag != recovery_indicator_owner_00474c84)
        stage_frame = 0;
    queues[g_globals_stage].head->Drain(this, 1);

    float player_x = g_player->position.x + 224.0f;
    float player_y = g_player->position.y + 16.0f;
    for (int i = 0; i < 10; ++i) {
        HintVm* vm = IndicatorHandle_GetInline(handles[i]);
        if (!vm)
            continue;
        if (vm->interrupt_pending)
            continue;
        float dx = fabsf(player_x - positions[i].x);
        float dy = fabsf(player_y - positions[i].y);
        int opacity;
        if (dx < widths[i] * 0.5f && dy < vm->height * vm->scale_y * 0.5f) {
            vm->color.bytes[3] = vm->opacity_byte >> 2;
        } else if (dx < widths[i] * 0.5f + 32.0f && dy < vm->height * vm->scale_y * 0.5f) {
            opacity = vm->opacity;
            vm->color.bytes[3] = opacity
                - (widths[i] * 0.5f + 32.0f - dx) * (opacity * 3 / 4) / 32.0f;
        } else if (dx < widths[i] * 0.5f && dy < vm->height * vm->scale_y * 0.5f + 32.0f) {
            opacity = vm->opacity;
            vm->color.bytes[3] = opacity
                - (vm->height * vm->scale_y * 0.5f + 32.0f - dy) * (opacity * 3 / 4) / 32.0f;
        } else {
            vm->color.bytes[3] = vm->opacity;
        }
    }
    frame++;
    stage_frame++;
    return 1;
}
#pragma code_seg()

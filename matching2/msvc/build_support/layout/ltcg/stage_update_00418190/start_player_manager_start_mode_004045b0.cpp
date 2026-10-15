#define g_sprt_ctrl stage_start_g_sprt_ctrl
#define g_front stage_start_g_front
#define g_globals stage_start_data_00474c40
#define g_ascii_manager stage_start_data_004776e0
#define g_enemy_ctrl stage_start_g_enemy_ctrl
#define g_player stage_start_data_00477834
#define g_replay stage_start_data_00477838
#define g_score stage_start_data_0047783c
#define g_game_speed stage_start_data_00476f78
#define g_stage_flags stage_start_data_00491fc4
#define g_main_state stage_start_data_00491fb8
#define g_sound_manager stage_start_data_00492590
// 0x004045B0: start the background's "active" mode, initialising its timer
// record to defaults while the record's initialised flag is still clear.
//
// Retail: 8B 88 2C 2A 00 00        mov ecx,[eax+0x2A2C]
//         F6 C1 01                 test cl,1
//         75 2B                    jne done
//         33 D2                    xor edx,edx
//         83 C9 01                 or ecx,1
//         89 90 20 2A 00 00        mov [eax+0x2A20],edx
//         C7 80 1C 2A 00 00 C1 BD F0 FF  mov [eax+0x2A1C],0xFFF0BDC1
//         89 90 24 2A 00 00        mov [eax+0x2A24],edx
//         C7 80 28 2A 00 00 78 6F 47 00  mov [eax+0x2A28],0x476F78
//         89 88 2C 2A 00 00        mov [eax+0x2A2C],ecx
//  done:  C7 80 20 2A 00 00 3C 00 00 00  mov [eax+0x2A20],60
//         C7 80 24 2A 00 00 00 00 70 42  mov [eax+0x2A24],60.0f
//         C7 80 1C 2A 00 00 3B 00 00 00  mov [eax+0x2A1C],59
//         83 88 18 2A 00 00 04     or  [eax+0x2A18],4
//         C3                       ret
// The manager pointer arrives in EAX, so the mode switch is compiled as a
// native LTCG cluster.
// The background owns this fade timer at +0x2A1C.

#include "th10/game/background_fade.hpp"

#pragma code_seg(".text$004045b0_fn")
void BackGround::StartMode() {
    if (!(this->timer.flags & 1)) {
        this->timer.current = 0;
        this->timer.previous = 0xFFF0BDC1;
        this->timer.elapsed = 0.0f;
        this->timer.speed = (const float*)0x476F78;
        this->timer.flags |= 1;
    }
    // The flag update is a single read-modify-write of the field: taking the
    // field's address first keeps it from being split into load/or/store.
    unsigned int* flags = &this->flags;
    this->timer.current = 60;
    this->timer.elapsed = 60.0f;
    this->timer.previous = 59;
    *flags |= 4;
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef g_replay
#undef g_score
#undef g_game_speed
#undef g_stage_flags
#undef g_main_state
#undef g_sound_manager

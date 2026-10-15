#define g_sprt_ctrl stage_decay_g_sprt_ctrl
#define g_front stage_decay_g_front
#define data_00474c40 stage_decay_data_00474c40
#define g_ascii_manager stage_decay_data_004776e0
#define g_enemy_ctrl stage_decay_g_enemy_ctrl
#define g_player stage_decay_data_00477834
#define data_00477838 stage_decay_data_00477838
#define data_0047783c stage_decay_data_0047783c
#define data_00476f78 stage_decay_data_00476f78
#define data_00491fc4 stage_decay_data_00491fc4
#define data_00491fb8 stage_decay_data_00491fb8
#define data_00492590 stage_decay_data_00492590
// 0x00418A00..0x00418A40 (65 bytes): ScoreState::DecayGauge
//
// The gauge is raised by SetGauge/AddGauge and then runs down again. Two
// stages do that: while the gauge timer at +0x14 still has frames on it the
// timer is advanced by -1.0f, and once it has run out the gauge itself bleeds
// off by the decay step at +0x10, one step per frame, with the gauge held at
// the 5000 floor the other gauge updates use and the step held at 18.
//
// Retail, in order:
//     8B 48 18        mov ecx,[eax+18h]      ; gauge_timer.current
//     85 C9           test ecx,ecx
//     56              push esi
//     7E 0F           jle decay
//     68 00 00 80 BF  push 0BF800000h        ; -1.0f
//     8D 70 14        lea esi,[eax+14h]      ; &gauge_timer
//     E8 .. .. .. ..  call FrameTimer::Advance
//     5E C3           pop esi / ret
//  decay:
//     8B 48 0C        mov ecx,[eax+0Ch]      ; gauge
//     BE 88 13 00 00  mov esi,5000
//     3B CE           cmp ecx,esi
//     7E 1C           jle done
//     8B 50 10        mov edx,[eax+10h]      ; gauge_decay
//     2B CA           sub ecx,edx
//     83 FA 12        cmp edx,18
//     89 48 0C        mov [eax+0Ch],ecx
//     7D 07           jge skip
//     C7 40 10 12 00 00 00  mov [eax+10h],18
//  skip:
//     39 70 0C        cmp [eax+0Ch],esi
//     7D 03           jge done
//     89 70 0C        mov [eax+0Ch],esi
//  done:
//     5E C3           pop esi / ret
//
// The receiver arrives in EAX and the nested timer in ESI. Neither is a
// register an MSVC convention can express, so this source is compiled in the
// native-LTCG link that also carries FrameTimer::Advance
// (see build_support/layout/ltcg/frame_timer.json): the whole-program pass selects EAX for
// the gauge record and ESI for the timer the advance call is handed.
#include "th10/game/score.hpp"

#pragma code_seg(".text$00418a00_fn")
void ScoreState::DecayGauge() {
    if (gauge_timer.current > 0) {
        gauge_timer.Advance(-1.0f);
        return;
    }
    if (gauge > 5000) {
        gauge -= gauge_decay;
        if (gauge_decay < 18)
            gauge_decay = 18;
        if (gauge < 5000)
            gauge = 5000;
    }
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef data_00474c40
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590

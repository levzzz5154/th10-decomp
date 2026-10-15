// 0x00412FF0..0x0041304D (93 bytes): ScoreState::AdvanceGaugeTimer
//
// Every retail caller pushes the requested frame count and loads EDI with the
// run-score global (0x00474C40) before the call, and the callee returns with
// RET 4, so this arrives in EDI with the count at [ESP+4].
//
// The gauge is raised by SetGauge/AddGauge and then runs down again: while the
// gauge timer at +0x14 still has frames on it DecayGauge advances it by -1.0f
// per frame, and only once it has run out does the gauge itself bleed off. This
// entry adds a hold of `frames` frames to that timer and clamps it to the end of
// its 130-frame animation, lazily registering the timer against the script-time
// frame delta on the first call.
//
// The clamp has to keep the receiver alive across the advance call, and the
// embedded FrameTimer can only reach its Advance (receiver in ESI, measured in
// this same native link) by co-compiling frame_timer.cpp, so this source sits in
// build_support/layout/ltcg/frame_timer.json instead of a cluster of its own.
//
// Retail, in order:
//     83 7F 18 82        cmp dword [edi+18h],130    ; gauge_timer.current
//     7D 51              jge done
//     DB 44 24 04        fild dword [esp+4]
//     56                 push esi
//     51                 push ecx
//     8D 77 14           lea esi,[edi+14h]          ; &gauge_timer
//     D9 1C 24           fstp dword [esp]
//     E8 .. .. .. ..     call FrameTimer::Advance   ; receiver in ESI
//     83 7F 18 82        cmp dword [edi+18h],130
//     7E 36              jle done
//     8B 46 10           mov eax,[esi+0x10]         ; timer.flags
//     A8 01              test al,1
//     75 1B              jne clamp
//     33 C9              xor ecx,ecx
//     83 C8 01           or eax,1
//     89 4E 04           mov [esi+4],ecx
//     C7 06 C1 BD F0 FF  mov dword [esi],0xFFF0BDC1
//     89 4E 08           mov [esi+8],ecx
//     C7 46 0C 78 6F 47 00  mov dword [esi+0xC],0x476F78
//     89 46 10           mov [esi+0x10],eax
//  clamp:
//     C7 46 04 82 00 00 00  mov dword [esi+4],130
//     C7 46 08 00 00 02 43  mov dword [esi+8],130.0f
//     C7 06 81 00 00 00  mov dword [esi],129
//  done: 5E C3            pop esi / ret 4
//
// The two guards address the timer through the receiver (EDI), while the advance
// and the whole clamp block address it through the timer pointer in ESI, so the
// guards keep the member spelling and the block goes through the alias.
#include "th10/game/score.hpp"

extern float g_score_default_speed;  // 0x00476F78, the script-time frame delta

#pragma code_seg(".text$04mreplay")
void ScoreState::AdvanceGaugeTimer(int frames) {
    if (gauge_timer.current < 130) {
        FrameTimer& timer = gauge_timer;
        timer.Advance(float(frames));
        if (gauge_timer.current > 130) {
            if ((timer.flags & 1) == 0) {
                timer.current = 0;
                timer.previous = -999999;
                timer.elapsed = 0.0f;
                timer.speed = &g_score_default_speed;
                timer.flags |= 1;
            }
            timer.current = 130;
            timer.elapsed = 130.0f;
            timer.previous = 129;
        }
    }
}
#pragma code_seg()

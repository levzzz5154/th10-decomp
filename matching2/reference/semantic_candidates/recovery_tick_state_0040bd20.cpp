#include "th10/game/recovery_emitter_state.hpp"

// 0x0040BD20..0x0040BD7C: RecoveryTickState_0040bd20::Tick
//
// The state this runs on is the ending/credits script object constructed at
// 0x0040BA90. At +0x04 it carries the FrameTimer shape shared by the whole
// image: a previous/current integer pair (+0x04/+0x08), an elapsed float
// (+0x0C) and a pointer (+0x10) to the shared game speed. Retail, in order:
//
//     push esi                 ; retail's private receiver is passed to the helper
//     call 0x0040BD80          ; argument to the finished? query, which pops it
//     test eax,eax / je
//     mov eax,1 / ret          ; finished -> report 1
//     mov edx,[esi+8]          ; current
//     mov ecx,[esi+10h]        ; speed
//     mov [esi+4],edx          ; previous = current
//     ...
//     xor eax,eax / ret        ; still running -> 0
//
// This C++ member model keeps the same object layout and calculations but uses
// an ordinary thiscall receiver. UpdateEmitterDecision calls Tick() through
// the same typed object instead of relying on retail's private ESI handoff.
// The timer body at +0x04 advances the frame counter and adds 1.0 to elapsed
// at normal speed; otherwise it converts the accumulated speed to a counter.

extern float g_frame_timer_normal_lower;  // 0x00470B68
extern float g_frame_timer_normal_upper;  // 0x00470B64

extern "C" int __stdcall asm_FUN_0040bd80_0040bd80(void* state);

#pragma code_seg(".text$03tick")
__declspec(noinline) int RecoveryTickState_0040bd20::Tick() {
    if (asm_FUN_0040bd80_0040bd80(this))
        return 1;

    this->previous_004 = this->current_008;
    if (*this->speed_010 > g_frame_timer_normal_lower &&
        *this->speed_010 < g_frame_timer_normal_upper) {
        ++this->current_008;
        this->elapsed_00c += 1.0f;
    } else {
        this->current_008 = int(this->elapsed_00c += *this->speed_010);
    }
    return 0;
}
#pragma code_seg()

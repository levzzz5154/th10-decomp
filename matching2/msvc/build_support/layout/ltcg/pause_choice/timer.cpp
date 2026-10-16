#include "th10/game/pause_choice/state.hpp"
// 0x00405410: store a scheduler value into the record whose address arrives in
// EAX, initialising the record to its defaults while its "initialised" flag is
// still clear.
//
// Retail: 8B 48 10           mov ecx,[eax+0x10]
//         F6 C1 01           test cl,1
//         56                 push esi
//         8B 74 24 08        mov esi,[esp+8]      ; value
//         75 1B              jne done
//         33 D2              xor edx,edx
//         83 C9 01           or ecx,1
//         89 50 04           mov [eax+4],edx
//         C7 00 C1 BD F0 FF  mov [eax],0xFFF0BDC1
//         89 50 08           mov [eax+8],edx
//         C7 40 0C 78 6F 47 00  mov [eax+0xC],0x476F78
//         89 48 10           mov [eax+0x10],ecx
//  done:  DB 44 24 08        fild dword [esp+8]
//         89 70 04           mov [eax+4],esi
//         4E                 dec esi
//         89 30              mov [eax],esi
//         D9 58 08           fstp dword [eax+8]
//         5E                 pop esi
//         C2 04 00           ret 4
// The record pointer arrives in EAX while the value stays on the stack, so the
// complete setter is compiled with its actual pause-update caller.



#pragma code_seg(".text$05timer")
void PlayerSchedulerRecord::SetSchedulerValue(int value) {
    if (!(this->flags_10 & 1)) {
        this->field_04 = 0;
        this->field_00 = 0xFFF0BDC1;
        this->field_08 = 0.0f;
        this->field_0C = 0x476F78;
        this->flags_10 |= 1;
    }
    this->field_04 = value;
    this->field_00 = value - 1;
    this->field_08 = (float)value;
}
#pragma code_seg()

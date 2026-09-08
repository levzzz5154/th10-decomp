#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004052B0..0x004052C3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004052b0() {
    __asm {
    L_004052b0:
        push ecx
    L_004052b1:
        neg eax
    L_004052b3:
        mov dword ptr [esp],eax
    L_004052b6:
        fild dword ptr [esp]
    L_004052b9:
        push ecx
    L_004052ba:
        fstp dword ptr [esp]
    L_004052bd:
        call asm_FrameTimer_Advance_0044bf40
    L_004052c2:
        pop ecx
    L_004052c3:
        ret
    }
}

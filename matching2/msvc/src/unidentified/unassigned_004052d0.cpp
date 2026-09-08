#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004052D0..0x004052DF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004052d0() {
    __asm {
    L_004052d0:
        fild dword ptr [esp+4]
    L_004052d4:
        push ecx
    L_004052d5:
        fstp dword ptr [esp]
    L_004052d8:
        call asm_FrameTimer_Advance_0044bf40
    L_004052dd:
        ret 4
    }
}

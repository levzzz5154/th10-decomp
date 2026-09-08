#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004052A0..0x004052AA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004052a0() {
    __asm {
    L_004052a0:
        push 0BF800000h
    L_004052a5:
        call asm_FrameTimer_Advance_0044bf40
    L_004052aa:
        ret
    }
}

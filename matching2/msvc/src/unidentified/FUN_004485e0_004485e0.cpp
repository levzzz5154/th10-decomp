#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004485E0..0x004485E6: FUN_004485e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004485e0_004485e0() {
    __asm {
    L_004485e0:
        mov eax,ecx
    L_004485e2:
        jmp asm_AnimationManager_UpdateSecondary_00448900
    }
}

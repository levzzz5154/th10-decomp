#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004485D0..0x004485D6: FUN_004485d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004485d0_004485d0() {
    __asm {
    L_004485d0:
        mov eax,ecx
    L_004485d2:
        jmp asm_AnimationManager_UpdatePrimary_00448860
    }
}

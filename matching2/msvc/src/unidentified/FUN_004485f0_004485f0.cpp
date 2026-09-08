#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004485F0..0x004485FB: FUN_004485f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004485f0_004485f0() {
    __asm {
    L_004485f0:
        push edi
    L_004485f1:
        xor eax,eax
    L_004485f3:
        mov edi,ecx
    L_004485f5:
        call asm_AnimationManager_RenderBucket_00448980
    L_004485fa:
        pop edi
    L_004485fb:
        ret
    }
}

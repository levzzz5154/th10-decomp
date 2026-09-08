#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004486F0..0x004486FE: FUN_004486f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004486f0_004486f0() {
    __asm {
    L_004486f0:
        push edi
    L_004486f1:
        mov eax,9
    L_004486f6:
        mov edi,ecx
    L_004486f8:
        call asm_AnimationManager_RenderBucket_00448980
    L_004486fd:
        pop edi
    L_004486fe:
        ret
    }
}

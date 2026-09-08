#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004486A0..0x004486AE: FUN_004486a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004486a0_004486a0() {
    __asm {
    L_004486a0:
        push edi
    L_004486a1:
        mov eax,4
    L_004486a6:
        mov edi,ecx
    L_004486a8:
        call asm_AnimationManager_RenderBucket_00448980
    L_004486ad:
        pop edi
    L_004486ae:
        ret
    }
}

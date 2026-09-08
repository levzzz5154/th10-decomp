#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004486B0..0x004486BE: FUN_004486b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004486b0_004486b0() {
    __asm {
    L_004486b0:
        push edi
    L_004486b1:
        mov eax,5
    L_004486b6:
        mov edi,ecx
    L_004486b8:
        call asm_AnimationManager_RenderBucket_00448980
    L_004486bd:
        pop edi
    L_004486be:
        ret
    }
}

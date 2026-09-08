#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004486E0..0x004486EE: FUN_004486e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004486e0_004486e0() {
    __asm {
    L_004486e0:
        push edi
    L_004486e1:
        mov eax,8
    L_004486e6:
        mov edi,ecx
    L_004486e8:
        call asm_AnimationManager_RenderBucket_00448980
    L_004486ed:
        pop edi
    L_004486ee:
        ret
    }
}

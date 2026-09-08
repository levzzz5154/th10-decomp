#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004486D0..0x004486DE: FUN_004486d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004486d0_004486d0() {
    __asm {
    L_004486d0:
        push edi
    L_004486d1:
        mov eax,7
    L_004486d6:
        mov edi,ecx
    L_004486d8:
        call asm_AnimationManager_RenderBucket_00448980
    L_004486dd:
        pop edi
    L_004486de:
        ret
    }
}

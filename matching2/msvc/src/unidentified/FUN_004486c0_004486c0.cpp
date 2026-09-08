#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004486C0..0x004486CE: FUN_004486c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004486c0_004486c0() {
    __asm {
    L_004486c0:
        push edi
    L_004486c1:
        mov eax,6
    L_004486c6:
        mov edi,ecx
    L_004486c8:
        call asm_AnimationManager_RenderBucket_00448980
    L_004486cd:
        pop edi
    L_004486ce:
        ret
    }
}

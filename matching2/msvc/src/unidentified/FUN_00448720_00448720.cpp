#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448720..0x0044872E: FUN_00448720
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448720_00448720() {
    __asm {
    L_00448720:
        push edi
    L_00448721:
        mov eax,0Ch
    L_00448726:
        mov edi,ecx
    L_00448728:
        call asm_AnimationManager_RenderBucket_00448980
    L_0044872d:
        pop edi
    L_0044872e:
        ret
    }
}

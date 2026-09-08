#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448700..0x0044870E: FUN_00448700
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448700_00448700() {
    __asm {
    L_00448700:
        push edi
    L_00448701:
        mov eax,0Ah
    L_00448706:
        mov edi,ecx
    L_00448708:
        call asm_AnimationManager_RenderBucket_00448980
    L_0044870d:
        pop edi
    L_0044870e:
        ret
    }
}

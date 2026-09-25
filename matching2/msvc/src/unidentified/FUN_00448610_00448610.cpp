#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448610..0x0044861E: FUN_00448610
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448610_00448610() {
    __asm {
    L_00448610:
        push edi
    L_00448611:
        mov eax,2
    L_00448616:
        mov edi,ecx
    L_00448618:
        call asm_AnimationManager_RenderBucket_00448980
    L_0044861d:
        pop edi
    L_0044861e:
        ret
    }
}

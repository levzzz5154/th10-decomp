#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448730..0x0044873E: FUN_00448730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448730_00448730() {
    __asm {
    L_00448730:
        push edi
    L_00448731:
        mov eax,0Dh
    L_00448736:
        mov edi,ecx
    L_00448738:
        call asm_AnimationManager_RenderBucket_00448980
    L_0044873d:
        pop edi
    L_0044873e:
        ret
    }
}

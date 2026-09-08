#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448600..0x0044860E: FUN_00448600
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448600_00448600() {
    __asm {
    L_00448600:
        push edi
    L_00448601:
        mov eax,1
    L_00448606:
        mov edi,ecx
    L_00448608:
        call asm_AnimationManager_RenderBucket_00448980
    L_0044860d:
        pop edi
    L_0044860e:
        ret
    }
}

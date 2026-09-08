#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448710..0x0044871E: FUN_00448710
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448710_00448710() {
    __asm {
    L_00448710:
        push edi
    L_00448711:
        mov eax,0Bh
    L_00448716:
        mov edi,ecx
    L_00448718:
        call asm_AnimationManager_RenderBucket_00448980
    L_0044871d:
        pop edi
    L_0044871e:
        ret
    }
}

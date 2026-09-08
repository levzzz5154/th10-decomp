#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449660..0x0044966E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449660() {
    __asm {
    L_00449660:
        mov ecx,dword ptr [eax]
    L_00449662:
        mov edx,dword ptr [data_00491c10]
    L_00449668:
        push ecx
    L_00449669:
        call asm_AnimationManager_SetTranslatedPosition_00449350
    L_0044966e:
        ret
    }
}

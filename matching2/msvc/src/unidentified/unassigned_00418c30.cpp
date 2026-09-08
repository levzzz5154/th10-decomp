#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418C30..0x00418C39: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418c30() {
    __asm {
    L_00418c30:
        mov edx,esi
    L_00418c32:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00418c37:
        mov eax,esi
    L_00418c39:
        ret
    }
}

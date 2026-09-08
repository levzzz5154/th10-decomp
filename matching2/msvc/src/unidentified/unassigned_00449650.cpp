#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449650..0x0044965E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449650() {
    __asm {
    L_00449650:
        mov ecx,dword ptr [eax]
    L_00449652:
        mov edx,dword ptr [data_00491c10]
    L_00449658:
        push ecx
    L_00449659:
        call asm_AnimationManager_SetPosition_004492f0
    L_0044965e:
        ret
    }
}

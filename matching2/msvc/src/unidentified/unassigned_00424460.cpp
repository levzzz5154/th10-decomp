#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424460..0x0042446E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424460() {
    __asm {
    L_00424460:
        push 0
    L_00424462:
        push 7
    L_00424464:
        mov edx,46E0B8h
    L_00424469:
        call asm_AnimationManager_RegisterResource_0043e460
    L_0042446e:
        ret
    }
}

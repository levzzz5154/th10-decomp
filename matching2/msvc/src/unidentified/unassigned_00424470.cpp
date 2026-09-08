#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424470..0x0042447E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424470() {
    __asm {
    L_00424470:
        push 0
    L_00424472:
        push 6
    L_00424474:
        mov edx,46E0C0h
    L_00424479:
        call asm_AnimationManager_RegisterResource_0043e460
    L_0042447e:
        ret
    }
}

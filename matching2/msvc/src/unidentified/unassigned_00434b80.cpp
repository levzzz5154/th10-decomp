#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434B80..0x00434B8E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00434b80() {
    __asm {
    L_00434b80:
        push 0
    L_00434b82:
        push 8
    L_00434b84:
        mov edx,46ECE8h
    L_00434b89:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00434b8e:
        ret
    }
}

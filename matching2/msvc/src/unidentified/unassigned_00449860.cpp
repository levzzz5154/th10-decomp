#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449860..0x00449869: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449860() {
    __asm {
    L_00449860:
        mov eax,dword ptr [eax]
    L_00449862:
        sub eax,dword ptr [ecx]
    L_00449864:
        neg eax
    L_00449866:
        sbb eax,eax
    L_00449868:
        inc eax
    L_00449869:
        ret
    }
}

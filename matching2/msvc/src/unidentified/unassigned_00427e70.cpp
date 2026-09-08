#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427E70..0x00427E89: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427e70() {
    __asm {
    L_00427e70:
        mov eax,dword ptr [eax+2480h]
    L_00427e76:
        test al,11h
    L_00427e78:
        jne short L_00427e84
    L_00427e7a:
        test eax,0C0000h
    L_00427e7f:
        jne short L_00427e84
    L_00427e81:
        xor eax,eax
    L_00427e83:
        ret
    L_00427e84:
        mov eax,1
    L_00427e89:
        ret
    }
}

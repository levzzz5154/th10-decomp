#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427E50..0x00427E69: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427e50() {
    __asm {
    L_00427e50:
        mov eax,dword ptr [eax+1444h]
    L_00427e56:
        test al,11h
    L_00427e58:
        jne short L_00427e64
    L_00427e5a:
        test eax,0C0000h
    L_00427e5f:
        jne short L_00427e64
    L_00427e61:
        xor eax,eax
    L_00427e63:
        ret
    L_00427e64:
        mov eax,1
    L_00427e69:
        ret
    }
}

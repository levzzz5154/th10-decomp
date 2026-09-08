#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C8A0..0x0042C8B5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042c8a0() {
    __asm {
    L_0042c8a0:
        imul eax,10DFh
    L_0042c8a6:
        add eax,ecx
    L_0042c8a8:
        mov ecx,dword ptr [esp+4]
    L_0042c8ac:
        mov eax,dword ptr [ecx+eax*4+4D0h]
    L_0042c8b3:
        ret 4
    }
}

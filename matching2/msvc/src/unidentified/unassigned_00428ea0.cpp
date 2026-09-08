#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428EA0..0x00428EB7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428ea0() {
    __asm {
    L_00428ea0:
        imul eax,98h
    L_00428ea6:
        lea eax,[eax+edx+32DCh]
    L_00428ead:
        mov edx,dword ptr [ecx]
    L_00428eaf:
        mov dword ptr [eax],edx
    L_00428eb1:
        mov ecx,dword ptr [ecx+4]
    L_00428eb4:
        mov dword ptr [eax+4],ecx
    L_00428eb7:
        ret
    }
}

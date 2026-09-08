#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428EE0..0x00428EF7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428ee0() {
    __asm {
    L_00428ee0:
        imul eax,98h
    L_00428ee6:
        lea eax,[eax+edx+32E4h]
    L_00428eed:
        mov edx,dword ptr [ecx]
    L_00428eef:
        mov dword ptr [eax],edx
    L_00428ef1:
        mov ecx,dword ptr [ecx+4]
    L_00428ef4:
        mov dword ptr [eax+4],ecx
    L_00428ef7:
        ret
    }
}

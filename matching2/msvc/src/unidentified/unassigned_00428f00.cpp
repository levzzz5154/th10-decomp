#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428F00..0x00428F17: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428f00() {
    __asm {
    L_00428f00:
        imul eax,98h
    L_00428f06:
        lea eax,[eax+edx+32ECh]
    L_00428f0d:
        mov edx,dword ptr [ecx]
    L_00428f0f:
        mov dword ptr [eax],edx
    L_00428f11:
        mov ecx,dword ptr [ecx+4]
    L_00428f14:
        mov dword ptr [eax+4],ecx
    L_00428f17:
        ret
    }
}

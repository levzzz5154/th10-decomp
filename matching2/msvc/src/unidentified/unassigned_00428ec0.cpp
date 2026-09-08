#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428EC0..0x00428ED7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428ec0() {
    __asm {
    L_00428ec0:
        imul eax,98h
    L_00428ec6:
        lea eax,[eax+edx+32D4h]
    L_00428ecd:
        mov edx,dword ptr [ecx]
    L_00428ecf:
        mov dword ptr [eax],edx
    L_00428ed1:
        mov ecx,dword ptr [ecx+4]
    L_00428ed4:
        mov dword ptr [eax+4],ecx
    L_00428ed7:
        ret
    }
}

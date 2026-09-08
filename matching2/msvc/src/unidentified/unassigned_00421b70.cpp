#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421B70..0x00421B86: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421b70() {
    __asm {
    L_00421b70:
        mov eax,dword ptr [ecx+40h]
    L_00421b73:
        mov dword ptr [ecx+3Ch],eax
    L_00421b76:
        lea eax,[eax+eax*2]
    L_00421b79:
        shl eax,4
    L_00421b7c:
        add eax,474788h
    L_00421b81:
        mov dword ptr [data_00477848],eax
    L_00421b86:
        ret
    }
}

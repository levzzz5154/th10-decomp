#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409E10..0x00409E1B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00409e10() {
    __asm {
    L_00409e10:
        mov eax,dword ptr [ecx+28h]
    L_00409e13:
        mov edx,dword ptr [ecx+2Ch]
    L_00409e16:
        lea eax,[eax+eax*2]
    L_00409e19:
        add eax,edx
    L_00409e1b:
        ret
    }
}

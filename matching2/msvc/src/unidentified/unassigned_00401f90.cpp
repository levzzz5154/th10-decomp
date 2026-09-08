#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401F90..0x00401F9A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401f90() {
    __asm {
    L_00401f90:
        mov dword ptr [eax],ecx
    L_00401f92:
        xor ecx,ecx
    L_00401f94:
        mov dword ptr [eax+4],ecx
    L_00401f97:
        mov dword ptr [eax+8],ecx
    L_00401f9a:
        ret
    }
}

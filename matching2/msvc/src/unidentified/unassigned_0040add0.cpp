#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040ADD0..0x0040ADF1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040add0() {
    __asm {
    L_0040add0:
        xor ecx,ecx
    L_0040add2:
        mov dword ptr [eax+8Ch],ecx
    L_0040add8:
        mov dword ptr [eax],ecx
    L_0040adda:
        mov dword ptr [eax+0D4h],ecx
    L_0040ade0:
        mov dword ptr [eax+0D0h],1
    L_0040adea:
        mov dword ptr [eax+8],3E7h
    L_0040adf1:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401F40..0x00401F4E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401f40() {
    __asm {
    L_00401f40:
        xor ecx,ecx
    L_00401f42:
        mov dword ptr [eax+4],ecx
    L_00401f45:
        mov dword ptr [eax],0FFF0BDC1h
    L_00401f4b:
        mov dword ptr [eax+8],ecx
    L_00401f4e:
        ret
    }
}

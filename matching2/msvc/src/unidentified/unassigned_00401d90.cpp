#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401D90..0x00401D9E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401d90() {
    __asm {
    L_00401d90:
        xor ecx,ecx
    L_00401d92:
        mov dword ptr [eax+896Ch],ecx
    L_00401d98:
        mov dword ptr [eax+8970h],ecx
    L_00401d9e:
        ret
    }
}

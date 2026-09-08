#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418AF0..0x00418B00: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418af0() {
    __asm {
    L_00418af0:
        lea edx,[ecx+ecx]
    L_00418af3:
        mov ecx,dword ptr [eax+60h]
    L_00418af6:
        xor edx,ecx
    L_00418af8:
        and edx,2
    L_00418afb:
        xor ecx,edx
    L_00418afd:
        mov dword ptr [eax+60h],ecx
    L_00418b00:
        ret
    }
}

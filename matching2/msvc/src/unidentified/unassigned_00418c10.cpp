#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418C10..0x00418C18: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418c10() {
    __asm {
    L_00418c10:
        xor ecx,ecx
    L_00418c12:
        mov dword ptr [eax+48h],ecx
    L_00418c15:
        mov dword ptr [eax+4Ch],ecx
    L_00418c18:
        ret
    }
}

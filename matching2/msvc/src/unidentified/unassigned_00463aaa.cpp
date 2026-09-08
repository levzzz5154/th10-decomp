#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463AAA..0x00463AC9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00463aaa() {
    __asm {
    L_00463aaa:
        push 463A5Ch
    L_00463aaf:
        call dword ptr [data_004661d4]
    L_00463ab5:
        mov dword ptr [data_004776d8],eax
    L_00463aba:
        xor eax,eax
    L_00463abc:
        ret
    L_00463abd:
        push dword ptr [data_004776d8]
    L_00463ac3:
        call dword ptr [data_004661d4]
    L_00463ac9:
        ret
    }
}

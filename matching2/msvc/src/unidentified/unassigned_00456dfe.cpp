#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456DFE..0x00456E02: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00456dfe() {
    __asm {
    L_00456dfe:
        mov esi,dword ptr [ebp-24h]
    L_00456e01:
        xor edi,edi
    }
}

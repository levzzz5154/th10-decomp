#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004576D3..0x004576D7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004576d3() {
    __asm {
    L_004576d3:
        xor edi,edi
    L_004576d5:
        xor esi,esi
    L_004576d7:
        inc esi
    }
}

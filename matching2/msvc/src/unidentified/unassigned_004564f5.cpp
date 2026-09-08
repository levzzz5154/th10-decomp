#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004564F5..0x004564F9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004564f5() {
    __asm {
    L_004564f5:
        xor edi,edi
    L_004564f7:
        mov esi,dword ptr [ebp+8]
    }
}

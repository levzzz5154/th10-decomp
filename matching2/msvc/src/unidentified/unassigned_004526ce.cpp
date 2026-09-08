#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004526CE..0x004526D0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004526ce() {
    __asm {
    L_004526ce:
        mov esi,dword ptr [ebp+8]
    }
}

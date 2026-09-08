#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459F12..0x00459F14: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00459f12() {
    __asm {
    L_00459f12:
        mov ebx,dword ptr [ebp+8]
    }
}

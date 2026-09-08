#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461546..0x00461548: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00461546() {
    __asm {
    L_00461546:
        mov ebx,dword ptr [ebp+8]
    }
}

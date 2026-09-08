#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459CAB..0x00459CAD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00459cab() {
    __asm {
    L_00459cab:
        mov ebx,dword ptr [ebp+8]
    }
}

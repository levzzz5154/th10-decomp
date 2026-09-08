#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CFAC..0x0045CFAE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045cfac() {
    __asm {
    L_0045cfac:
        mov esi,dword ptr [ebp-1Ch]
    }
}

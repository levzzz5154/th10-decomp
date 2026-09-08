#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F7A9..0x0045F7AB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045f7a9() {
    __asm {
    L_0045f7a9:
        mov edi,dword ptr [ebp+8]
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C356..0x0040C357: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c356() {
    __asm {
    L_0040c356:
        mov edi,edi
    }
}

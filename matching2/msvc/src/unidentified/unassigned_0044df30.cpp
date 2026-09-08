#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF30..0x0044DF32: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044df30() {
    __asm {
    L_0044df30:
        add eax,ecx
    L_0044df32:
        ret
    }
}

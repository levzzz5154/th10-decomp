#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FDA6..0x0045FDAE: __flushall
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_flushall_0045fda6() {
    __asm {
    L_0045fda6:
        push 1
    L_0045fda8:
        call asm_flsall_0045fc81
    L_0045fdad:
        pop ecx
    L_0045fdae:
        ret
    }
}

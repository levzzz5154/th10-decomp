#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FDAF..0x0045FDB7: FUN_0045fdaf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045fdaf_0045fdaf() {
    __asm {
    L_0045fdaf:
        push 2
    L_0045fdb1:
        call asm_amsg_exit_0045373d
    L_0045fdb6:
        pop ecx
    L_0045fdb7:
        ret
    }
}

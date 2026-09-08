#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043B830..0x0043B83B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043b830() {
    __asm {
    L_0043b830:
        push 497C30h
    L_0043b835:
        call dword ptr [data_004660fc]
    L_0043b83b:
        ret
    }
}

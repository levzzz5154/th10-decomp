#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453B54..0x00453B5F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00453b54() {
    __asm {
    L_00453b54:
        push dword ptr [esp+4]
    L_00453b58:
        push 0
    L_00453b5a:
        call dword ptr [data_00466180]
    }
}

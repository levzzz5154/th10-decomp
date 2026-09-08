#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004622F6..0x00462300: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004622f6() {
    __asm {
    L_004622f6:
        push dword ptr [esp+4]
    L_004622fa:
        call asm_operator_new_00452493
    L_004622ff:
        pop ecx
    L_00462300:
        ret
    }
}

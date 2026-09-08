#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045653E..0x00456549: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045653e() {
    __asm {
    L_0045653e:
        jmp dword ptr [data_0046619c]
    L_00456544:
        jmp dword ptr [data_00466168]
    }
}

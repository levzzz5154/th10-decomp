#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413770..0x00413777: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413770() {
    __asm {
    L_00413770:
        or dword ptr [eax+9EB4h],20h
    L_00413777:
        ret
    }
}

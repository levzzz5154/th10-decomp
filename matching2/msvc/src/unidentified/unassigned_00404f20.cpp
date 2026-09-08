#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404F20..0x00404F27: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404f20() {
    __asm {
    L_00404f20:
        and dword ptr [eax+35Ch],0FFFFFFFEh
    L_00404f27:
        ret
    }
}

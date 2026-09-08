#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408840..0x00408847: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408840() {
    __asm {
    L_00408840:
        and dword ptr [eax+2A18h],0FFFFFFFEh
    L_00408847:
        ret
    }
}

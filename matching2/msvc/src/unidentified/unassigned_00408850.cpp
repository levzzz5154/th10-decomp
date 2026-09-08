#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408850..0x00408857: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408850() {
    __asm {
    L_00408850:
        or dword ptr [eax+2A18h],1
    L_00408857:
        ret
    }
}

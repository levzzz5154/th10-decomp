#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401CA0..0x00401CA3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401ca0() {
    __asm {
    L_00401ca0:
        fld dword ptr [eax+3Ch]
    L_00401ca3:
        ret
    }
}

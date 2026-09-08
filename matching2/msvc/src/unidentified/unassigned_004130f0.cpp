#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004130F0..0x004130F3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004130f0() {
    __asm {
    L_004130f0:
        fld dword ptr [eax+4]
    L_004130f3:
        ret
    }
}

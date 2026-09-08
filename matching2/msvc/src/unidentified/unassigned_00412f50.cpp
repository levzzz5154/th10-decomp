#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F50..0x00412F54: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412f50() {
    __asm {
    L_00412f50:
        or dword ptr [eax+28h],1
    L_00412f54:
        ret
    }
}

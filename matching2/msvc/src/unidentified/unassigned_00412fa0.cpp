#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412FA0..0x00412FA4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412fa0() {
    __asm {
    L_00412fa0:
        and dword ptr [eax+28h],0FFFFFFFEh
    L_00412fa4:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004020F0..0x004020F4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004020f0() {
    __asm {
    L_004020f0:
        and dword ptr [eax+40h],0FFFFFFFEh
    L_004020f4:
        ret
    }
}

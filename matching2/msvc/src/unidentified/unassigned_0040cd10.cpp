#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CD10..0x0040CD14: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040cd10() {
    __asm {
    L_0040cd10:
        and dword ptr [eax+30h],0FFFFFFFEh
    L_0040cd14:
        ret
    }
}

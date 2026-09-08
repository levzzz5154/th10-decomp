#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C250..0x0044C253: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c250() {
    __asm {
    L_0044c250:
        or dword ptr [eax],2
    L_0044c253:
        ret
    }
}

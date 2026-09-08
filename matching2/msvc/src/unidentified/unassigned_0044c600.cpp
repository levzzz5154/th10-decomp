#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C600..0x0044C603: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c600() {
    __asm {
    L_0044c600:
        dec dword ptr [eax+4]
    L_0044c603:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402220..0x00402227: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402220() {
    __asm {
    L_00402220:
        and dword ptr [eax+80h],0FFFFFFFEh
    L_00402227:
        ret
    }
}

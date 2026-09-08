#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CE90..0x0040CE97: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ce90() {
    __asm {
    L_0040ce90:
        or dword ptr [eax+378Ch],8
    L_0040ce97:
        ret
    }
}

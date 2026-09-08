#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421CA0..0x00421CAC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421ca0() {
    __asm {
    L_00421ca0:
        mov eax,dword ptr [eax+150h]
    L_00421ca6:
        shr eax,5
    L_00421ca9:
        and eax,1
    L_00421cac:
        ret
    }
}

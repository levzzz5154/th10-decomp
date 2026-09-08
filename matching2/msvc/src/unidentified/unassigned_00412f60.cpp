#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F60..0x00412F66: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412f60() {
    __asm {
    L_00412f60:
        mov eax,dword ptr [eax+28h]
    L_00412f63:
        and eax,1
    L_00412f66:
        ret
    }
}

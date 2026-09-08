#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404990..0x00404993: FUN_00404990
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404990_00404990() {
    __asm {
    L_00404990:
        mov eax,dword ptr [eax+44h]
    L_00404993:
        ret
    }
}

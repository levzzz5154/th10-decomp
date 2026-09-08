#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EBBA..0x0045EBCA: __frnd
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_frnd_0045ebba() {
    __asm {
    L_0045ebba:
        push ecx
    L_0045ebbb:
        push ecx
    L_0045ebbc:
        fld qword ptr [esp+0Ch]
    L_0045ebc0:
        frndint
    L_0045ebc2:
        fstp qword ptr [esp]
    L_0045ebc5:
        fld qword ptr [esp]
    L_0045ebc8:
        pop ecx
    L_0045ebc9:
        pop ecx
    L_0045ebca:
        ret
    }
}

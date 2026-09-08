#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CD56..0x0045CD84: FUN_0045cd56
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045cd56_0045cd56() {
    __asm {
    L_0045cd56:
        sub eax,3A4h
    L_0045cd5b:
        je short L_0045cd7f
    L_0045cd5d:
        sub eax,4
    L_0045cd60:
        je short L_0045cd79
    L_0045cd62:
        sub eax,0Dh
    L_0045cd65:
        je short L_0045cd73
    L_0045cd67:
        dec eax
    L_0045cd68:
        je short L_0045cd6d
    L_0045cd6a:
        xor eax,eax
    L_0045cd6c:
        ret
    L_0045cd6d:
        mov eax,404h
    L_0045cd72:
        ret
    L_0045cd73:
        mov eax,412h
    L_0045cd78:
        ret
    L_0045cd79:
        mov eax,804h
    L_0045cd7e:
        ret
    L_0045cd7f:
        mov eax,411h
    L_0045cd84:
        ret
    }
}

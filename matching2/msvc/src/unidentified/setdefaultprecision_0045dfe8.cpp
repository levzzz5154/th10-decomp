#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DFE8..0x0045DFF9: __setdefaultprecision
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_setdefaultprecision_0045dfe8() {
    __asm {
    L_0045dfe8:
        push 30000h
    L_0045dfed:
        push 10000h
    L_0045dff2:
        call asm_controlfp_00461090
    L_0045dff7:
        pop ecx
    L_0045dff8:
        pop ecx
    L_0045dff9:
        ret
    }
}

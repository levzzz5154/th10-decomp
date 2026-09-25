#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045ED70..0x0045ED7A: __statfp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_statfp_0045ed70() {
    __asm {
    L_0045ed70:
        push ecx
    L_0045ed71:
        wait
        fnstsw word ptr [esp]
    L_0045ed75:
        movsx eax,word ptr [esp]
    L_0045ed79:
        pop ecx
    L_0045ed7a:
        ret
    }
}

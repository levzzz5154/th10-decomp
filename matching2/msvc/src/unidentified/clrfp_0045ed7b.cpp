#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045ED7B..0x0045ED86: __clrfp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_clrfp_0045ed7b() {
    __asm {
    L_0045ed7b:
        push ecx
    L_0045ed7c:
        fnstsw word ptr [esp]
    L_0045ed7f:
        fnclex
    L_0045ed81:
        movsx eax,word ptr [esp]
    L_0045ed85:
        pop ecx
    L_0045ed86:
        ret
    }
}

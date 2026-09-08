#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044A130..0x0044A154: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044a130() {
    __asm {
    L_0044a130:
        test ax,ax
    L_0044a133:
        jl short L_0044a152
    L_0044a135:
        movsx eax,ax
    L_0044a138:
        add eax,ecx
    L_0044a13a:
        cmp byte ptr [eax],0
    L_0044a13d:
        jns short L_0044a144
    L_0044a13f:
        movzx ecx,si
    L_0044a142:
        jmp short L_0044a146
    L_0044a144:
        xor ecx,ecx
    L_0044a146:
        or word ptr [edx],cx
    L_0044a149:
        cmp byte ptr [eax],0
    L_0044a14c:
        jns short L_0044a152
    L_0044a14e:
        movzx eax,si
    L_0044a151:
        ret
    L_0044a152:
        xor eax,eax
    L_0044a154:
        ret
    }
}

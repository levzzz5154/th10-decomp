#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C850..0x0042C894: GameProgress_HasAnyPlayRecord
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameProgress_HasAnyPlayRecord_0042c850() {
    __asm {
    L_0042c850:
        mov cl,byte ptr [eax+1D888h]
    L_0042c856:
        test cl,cl
    L_0042c858:
        jne short L_0042c88f
    L_0042c85a:
        mov cl,byte ptr [eax+1D889h]
    L_0042c860:
        test cl,cl
    L_0042c862:
        jne short L_0042c88f
    L_0042c864:
        mov cl,byte ptr [eax+1D88Ah]
    L_0042c86a:
        test cl,cl
    L_0042c86c:
        jne short L_0042c88f
    L_0042c86e:
        mov cl,byte ptr [eax+1D88Bh]
    L_0042c874:
        test cl,cl
    L_0042c876:
        jne short L_0042c88f
    L_0042c878:
        mov cl,byte ptr [eax+1D88Ch]
    L_0042c87e:
        test cl,cl
    L_0042c880:
        jne short L_0042c88f
    L_0042c882:
        mov cl,byte ptr [eax+1D88Dh]
    L_0042c888:
        test cl,cl
    L_0042c88a:
        jne short L_0042c88f
    L_0042c88c:
        xor eax,eax
    L_0042c88e:
        ret
    L_0042c88f:
        mov eax,1
    L_0042c894:
        ret
    }
}


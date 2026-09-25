#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C4F2..0x0045C526: _LcidFromHexString
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_LcidFromHexString_0045c4f2() {
    __asm {
    L_0045c4f2:
        xor eax,eax
    L_0045c4f4:
        jmp short L_0045c520
    L_0045c4f6:
        inc edx
    L_0045c4f7:
        cmp cl,61h
    L_0045c4fa:
        jl short L_0045c506
    L_0045c4fc:
        cmp cl,66h
    L_0045c4ff:
        jg short L_0045c506
    L_0045c501:
        add cl,0D9h
    L_0045c504:
        jmp short L_0045c513
    L_0045c506:
        cmp cl,41h
    L_0045c509:
        jl short L_0045c513
    L_0045c50b:
        cmp cl,46h
    L_0045c50e:
        jg short L_0045c513
    L_0045c510:
        add cl,0F9h
    L_0045c513:
        add eax,0FFFFFFDh
    L_0045c518:
        movsx ecx,cl
    L_0045c51b:
        shl eax,4
    L_0045c51e:
        add eax,ecx
    L_0045c520:
        mov cl,byte ptr [edx]
    L_0045c522:
        test cl,cl
    L_0045c524:
        jne short L_0045c4f6
    L_0045c526:
        ret
    }
}

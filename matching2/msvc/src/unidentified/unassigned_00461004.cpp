#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461004..0x0046105D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00461004() {
    __asm {
    L_00461004:
        mov cl,byte ptr [esp+4]
    L_00461008:
        xor eax,eax
    L_0046100a:
        test cl,1
    L_0046100d:
        je short L_00461012
    L_0046100f:
        push 10h
    L_00461011:
        pop eax
    L_00461012:
        test cl,4
    L_00461015:
        je short L_0046101a
    L_00461017:
        or eax,8
    L_0046101a:
        test cl,8
    L_0046101d:
        je short L_00461022
    L_0046101f:
        or eax,4
    L_00461022:
        test cl,10h
    L_00461025:
        je short L_0046102a
    L_00461027:
        or eax,2
    L_0046102a:
        test cl,20h
    L_0046102d:
        je short L_00461032
    L_0046102f:
        or eax,1
    L_00461032:
        test cl,2
    L_00461035:
        je short L_0046103c
    L_00461037:
        or eax,80000h
    L_0046103c:
        ret
    L_0046103d:
        push ecx
    L_0046103e:
        wait
        fnstsw word ptr [esp]
    L_00461042:
        push dword ptr [esp]
    L_00461045:
        call asm_unassigned_00461004
    L_0046104a:
        pop ecx
    L_0046104b:
        pop ecx
    L_0046104c:
        ret
    L_0046104d:
        push ecx
    L_0046104e:
        fnstsw word ptr [esp]
    L_00461051:
        fnclex
    L_00461053:
        push dword ptr [esp]
    L_00461056:
        call asm_unassigned_00461004
    L_0046105b:
        pop ecx
    L_0046105c:
        pop ecx
    L_0046105d:
        ret
    }
}

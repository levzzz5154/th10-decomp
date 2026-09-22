#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

extern "C" __declspec(naked) void __cdecl asm_unassigned_0046103d() {
    __asm {
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

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C3F1..0x0045C40E: FUN_0045c3f1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045c3f1_0045c3f1() {
    __asm {
    L_0045c3f1:
        xor eax,eax
    L_0045c3f3:
        mov cx,word ptr [esp+4]
    L_0045c3f8:
        cmp cx,word ptr [eax+46BD3Ch]
    L_0045c3ff:
        je short L_0045c40c
    L_0045c401:
        inc eax
    L_0045c402:
        inc eax
    L_0045c403:
        cmp eax,14h
    L_0045c406:
        jb short L_0045c3f3
    L_0045c408:
        xor eax,eax
    L_0045c40a:
        inc eax
    L_0045c40b:
        ret
    L_0045c40c:
        xor eax,eax
    L_0045c40e:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455A90..0x00455ADD: ___lc_lctostr
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_lc_lctostr_00455a90() {
    __asm {
    L_00455a90:
        push esi
    L_00455a91:
        mov esi,dword ptr [esp+0Ch]
    L_00455a95:
        push esi
    L_00455a96:
        push dword ptr [esp+0Ch]
    L_00455a9a:
        call asm_FUN_0045bd80_0045bd80
    L_00455a9f:
        lea eax,[esi+40h]
    L_00455aa2:
        cmp byte ptr [eax],0
    L_00455aa5:
        pop ecx
    L_00455aa6:
        pop ecx
    L_00455aa7:
        je short L_00455abd
    L_00455aa9:
        push eax
    L_00455aaa:
        push 46E1C4h
    L_00455aaf:
        push 2
    L_00455ab1:
        push dword ptr [esp+14h]
    L_00455ab5:
        call asm_strcats_00455990
    L_00455aba:
        add esp,10h
    L_00455abd:
        lea eax,[esi+80h]
    L_00455ac3:
        cmp byte ptr [eax],0
    L_00455ac6:
        pop esi
    L_00455ac7:
        je short L_00455add
    L_00455ac9:
        push eax
    L_00455aca:
        push 46A9ECh
    L_00455acf:
        push 2
    L_00455ad1:
        push dword ptr [esp+10h]
    L_00455ad5:
        call asm_strcats_00455990
    L_00455ada:
        add esp,10h
    L_00455add:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004415C0..0x004415F8: FUN_004415c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004415c0_004415c0() {
    __asm {
    L_004415c0:
        push ebx
    L_004415c1:
        push ebp
    L_004415c2:
        mov ebp,dword ptr [esp+0Ch]
    L_004415c6:
        push esi
    L_004415c7:
        mov ebx,eax
    L_004415c9:
        test ebx,ebx
    L_004415cb:
        push edi
    L_004415cc:
        mov edi,ecx
    L_004415ce:
        mov esi,edx
    L_004415d0:
        je short L_004415f2
    L_004415d2:
        push ebp
    L_004415d3:
        mov eax,edi
    L_004415d5:
        call asm_FUN_00404f30_00404f30
    L_004415da:
        mov ax,word ptr [esi+384h]
    L_004415e1:
        mov word ptr [esi+388h],ax
    L_004415e8:
        inc edi
    L_004415e9:
        add esi,3ACh
    L_004415ef:
        dec ebx
    L_004415f0:
        jne short L_004415d2
    L_004415f2:
        pop edi
    L_004415f3:
        pop esi
    L_004415f4:
        pop ebp
    L_004415f5:
        pop ebx
    L_004415f6:
        ret 4
    }
}

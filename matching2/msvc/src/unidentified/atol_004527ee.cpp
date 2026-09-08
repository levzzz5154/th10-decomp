#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004527EE..0x00452875: _atol
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_atol_004527ee() {
    __asm {
    L_004527ee:
        push esi
    L_004527ef:
        push edi
    L_004527f0:
        call asm_getptd_00456357
    L_004527f5:
        mov edi,dword ptr [eax+64h]
    L_004527f8:
        cmp edi,dword ptr [data_0047320c]
    L_004527fe:
        je short L_00452807
    L_00452800:
        call asm_updatetlocinfo_00455ade
    L_00452805:
        mov edi,eax
    L_00452807:
        mov esi,dword ptr [esp+0Ch]
    L_0045280b:
        cmp dword ptr [edi+28h],1
    L_0045280f:
        movzx eax,byte ptr [esi]
    L_00452812:
        jle short L_00452822
    L_00452814:
        push 8
    L_00452816:
        push eax
    L_00452817:
        push edi
    L_00452818:
        call asm_isctype_mt_00455752
    L_0045281d:
        add esp,0Ch
    L_00452820:
        jmp short L_0045282c
    L_00452822:
        mov ecx,dword ptr [edi+48h]
    L_00452825:
        movzx eax,byte ptr [ecx+eax*2]
    L_00452829:
        and eax,8
    L_0045282c:
        test eax,eax
    L_0045282e:
        je short L_00452833
    L_00452830:
        inc esi
    L_00452831:
        jmp short L_0045280b
    L_00452833:
        movzx ecx,byte ptr [esi]
    L_00452836:
        inc esi
    L_00452837:
        cmp ecx,2Dh
    L_0045283a:
        mov edx,ecx
    L_0045283c:
        je short L_00452843
    L_0045283e:
        cmp ecx,2Bh
    L_00452841:
        jne short L_00452847
    L_00452843:
        movzx ecx,byte ptr [esi]
    L_00452846:
        inc esi
    L_00452847:
        xor eax,eax
    L_00452849:
        cmp ecx,30h
    L_0045284c:
        jl short L_00452858
    L_0045284e:
        cmp ecx,39h
    L_00452851:
        jg short L_00452858
    L_00452853:
        sub ecx,30h
    L_00452856:
        jmp short L_0045285b
    L_00452858:
        or ecx,0FFFFFFFFh
    L_0045285b:
        cmp ecx,0FFFFFFFFh
    L_0045285e:
        je short L_0045286c
    L_00452860:
        lea eax,[eax+eax*4]
    L_00452863:
        lea eax,[ecx+eax*2]
    L_00452866:
        movzx ecx,byte ptr [esi]
    L_00452869:
        inc esi
    L_0045286a:
        jmp short L_00452849
    L_0045286c:
        cmp edx,2Dh
    L_0045286f:
        pop edi
    L_00452870:
        pop esi
    L_00452871:
        jne short L_00452875
    L_00452873:
        neg eax
    L_00452875:
        ret
    }
}

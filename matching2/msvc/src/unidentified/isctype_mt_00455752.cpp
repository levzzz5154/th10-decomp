#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455752..0x004557C8: ___isctype_mt
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_isctype_mt_00455752() {
    __asm {
    L_00455752:
        push ebp
    L_00455753:
        mov ebp,esp
    L_00455755:
        push ecx
    L_00455756:
        mov eax,dword ptr [ebp+0Ch]
    L_00455759:
        lea ecx,[eax+1]
    L_0045575c:
        cmp ecx,100h
    L_00455762:
        mov ecx,dword ptr [ebp+8]
    L_00455765:
        ja short L_00455770
    L_00455767:
        mov ecx,dword ptr [ecx+48h]
    L_0045576a:
        movzx eax,word ptr [ecx+eax*2]
    L_0045576e:
        jmp short L_004557c4
    L_00455770:
        push esi
    L_00455771:
        mov edx,eax
    L_00455773:
        sar edx,8
    L_00455776:
        push edi
    L_00455777:
        mov edi,dword ptr [ecx+48h]
    L_0045577a:
        movzx esi,dl
    L_0045577d:
        test byte ptr [edi+esi*2+1],80h
    L_00455782:
        pop edi
    L_00455783:
        pop esi
    L_00455784:
        je short L_00455795
    L_00455786:
        push 2
    L_00455788:
        mov byte ptr [ebp-3],al
    L_0045578b:
        mov byte ptr [ebp-4],dl
    L_0045578e:
        mov byte ptr [ebp-2],0
    L_00455792:
        pop eax
    L_00455793:
        jmp short L_0045579f
    L_00455795:
        mov byte ptr [ebp-4],al
    L_00455798:
        xor eax,eax
    L_0045579a:
        mov byte ptr [ebp-3],0
    L_0045579e:
        inc eax
    L_0045579f:
        push 1
    L_004557a1:
        push dword ptr [ecx+14h]
    L_004557a4:
        push dword ptr [ecx+4]
    L_004557a7:
        lea ecx,[ebp+0Eh]
    L_004557aa:
        push ecx
    L_004557ab:
        push eax
    L_004557ac:
        lea eax,[ebp-4]
    L_004557af:
        push eax
    L_004557b0:
        push 1
    L_004557b2:
        call asm_crtGetStringTypeA_0045a25d
    L_004557b7:
        add esp,1Ch
    L_004557ba:
        test eax,eax
    L_004557bc:
        jne short L_004557c0
    L_004557be:
        leave
    L_004557bf:
        ret
    L_004557c0:
        movzx eax,word ptr [ebp+0Eh]
    L_004557c4:
        and eax,dword ptr [ebp+10h]
    L_004557c7:
        leave
    L_004557c8:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456674..0x00456714: FUN_00456674
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00456674_00456674() {
    __asm {
    L_00456674:
        push ebp
    L_00456675:
        mov ebp,esp
    L_00456677:
        sub esp,24h
    L_0045667a:
        mov eax,dword ptr [data_00473660]
    L_0045667f:
        push ebx
    L_00456680:
        push esi
    L_00456681:
        mov esi,dword ptr [ebp+8]
    L_00456684:
        push edi
    L_00456685:
        xor edi,edi
    L_00456687:
        push edi
    L_00456688:
        push edi
    L_00456689:
        xor eax,ebp
    L_0045668b:
        push edi
    L_0045668c:
        mov dword ptr [ebp-4],eax
    L_0045668f:
        mov eax,dword ptr [ebp+0Ch]
    L_00456692:
        push edi
    L_00456693:
        push eax
    L_00456694:
        mov dword ptr [ebp-20h],eax
    L_00456697:
        lea eax,[ebp-24h]
    L_0045669a:
        push eax
    L_0045669b:
        lea eax,[ebp-10h]
    L_0045669e:
        push eax
    L_0045669f:
        xor ebx,ebx
    L_004566a1:
        call asm_FUN_0045d746_0045d746
    L_004566a6:
        add esp,1Ch
    L_004566a9:
        test al,4
    L_004566ab:
        mov dword ptr [ebp-14h],eax
    L_004566ae:
        je short L_004566bd
    L_004566b0:
        mov ebx,200h
    L_004566b5:
        mov dword ptr [ebp-1Ch],edi
    L_004566b8:
        mov dword ptr [ebp-18h],edi
    L_004566bb:
        jmp short L_004566ed
    L_004566bd:
        lea eax,[ebp-1Ch]
    L_004566c0:
        push eax
    L_004566c1:
        lea eax,[ebp-10h]
    L_004566c4:
        push eax
    L_004566c5:
        call asm_FID_conflict___ld12tod_0045d5ce
    L_004566ca:
        test byte ptr [ebp-14h],2
    L_004566ce:
        pop ecx
    L_004566cf:
        pop ecx
    L_004566d0:
        jne short L_004566d7
    L_004566d2:
        cmp eax,1
    L_004566d5:
        jne short L_004566dc
    L_004566d7:
        mov ebx,80h
    L_004566dc:
        test byte ptr [ebp-14h],1
    L_004566e0:
        jne short L_004566e7
    L_004566e2:
        cmp eax,2
    L_004566e5:
        jne short L_004566ed
    L_004566e7:
        or ebx,100h
    L_004566ed:
        mov eax,dword ptr [ebp-24h]
    L_004566f0:
        sub eax,dword ptr [ebp-20h]
    L_004566f3:
        mov ecx,dword ptr [ebp-4]
    L_004566f6:
        mov dword ptr [esi+4],eax
    L_004566f9:
        mov eax,dword ptr [ebp-1Ch]
    L_004566fc:
        mov dword ptr [esi+10h],eax
    L_004566ff:
        mov eax,dword ptr [ebp-18h]
    L_00456702:
        mov dword ptr [esi+14h],eax
    L_00456705:
        pop edi
    L_00456706:
        mov dword ptr [esi],ebx
    L_00456708:
        mov eax,esi
    L_0045670a:
        pop esi
    L_0045670b:
        xor ecx,ebp
    L_0045670d:
        pop ebx
    L_0045670e:
        call asm_security_check_cookie_00458ea5
    L_00456713:
        leave
    L_00456714:
        ret
    }
}

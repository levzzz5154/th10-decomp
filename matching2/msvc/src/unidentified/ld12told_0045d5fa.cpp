#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D5FA..0x0045D675: __ld12told
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ld12told_0045d5fa() {
    __asm {
    L_0045d5fa:
        push ebp
    L_0045d5fb:
        mov ebp,esp
    L_0045d5fd:
        sub esp,10h
    L_0045d600:
        mov eax,dword ptr [ebp+8]
    L_0045d603:
        and dword ptr [ebp-4],0
    L_0045d607:
        xor ecx,ecx
    L_0045d609:
        mov cx,word ptr [eax+0Ah]
    L_0045d60d:
        push esi
    L_0045d60e:
        push edi
    L_0045d60f:
        push 40h
    L_0045d611:
        mov esi,ecx
    L_0045d613:
        and ecx,8000h
    L_0045d619:
        mov edi,ecx
    L_0045d61b:
        mov ecx,dword ptr [eax+6]
    L_0045d61e:
        mov dword ptr [ebp-10h],ecx
    L_0045d621:
        mov ecx,dword ptr [eax+2]
    L_0045d624:
        movzx eax,word ptr [eax]
    L_0045d627:
        shl eax,10h
    L_0045d62a:
        mov dword ptr [ebp-8],eax
    L_0045d62d:
        lea eax,[ebp-10h]
    L_0045d630:
        push eax
    L_0045d631:
        and esi,7FFFh
    L_0045d637:
        mov dword ptr [ebp-0Ch],ecx
    L_0045d63a:
        call asm_RoundMan_0045d349
    L_0045d63f:
        test eax,eax
    L_0045d641:
        pop ecx
    L_0045d642:
        pop ecx
    L_0045d643:
        je short L_0045d64d
    L_0045d645:
        mov ecx,80000000h
    L_0045d64a:
        inc esi
    L_0045d64b:
        jmp short L_0045d650
    L_0045d64d:
        mov ecx,dword ptr [ebp-10h]
    L_0045d650:
        cmp si,7FFFh
    L_0045d655:
        jne short L_0045d65e
    L_0045d657:
        mov dword ptr [ebp-4],1
    L_0045d65e:
        mov eax,dword ptr [ebp+0Ch]
    L_0045d661:
        or edi,esi
    L_0045d663:
        mov dword ptr [eax+4],ecx
    L_0045d666:
        mov ecx,dword ptr [ebp-0Ch]
    L_0045d669:
        mov word ptr [eax+8],di
    L_0045d66d:
        pop edi
    L_0045d66e:
        mov dword ptr [eax],ecx
    L_0045d670:
        mov eax,dword ptr [ebp-4]
    L_0045d673:
        pop esi
    L_0045d674:
        leave
    L_0045d675:
        ret
    }
}

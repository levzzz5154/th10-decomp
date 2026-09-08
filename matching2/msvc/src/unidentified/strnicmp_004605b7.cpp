#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004605B7..0x00460635: __strnicmp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strnicmp_004605b7() {
    __asm {
    L_004605b7:
        push ebp
    L_004605b8:
        mov ebp,esp
    L_004605ba:
        push ecx
    L_004605bb:
        push ebx
    L_004605bc:
        call asm_getptd_00456357
    L_004605c1:
        mov ebx,dword ptr [eax+64h]
    L_004605c4:
        cmp ebx,dword ptr [data_0047320c]
    L_004605ca:
        je short L_004605d3
    L_004605cc:
        call asm_updatetlocinfo_00455ade
    L_004605d1:
        mov ebx,eax
    L_004605d3:
        cmp dword ptr [ebp+10h],0
    L_004605d7:
        je short L_00460631
    L_004605d9:
        cmp dword ptr [ebx+14h],0
    L_004605dd:
        jne short L_004605f2
    L_004605df:
        push dword ptr [ebp+10h]
    L_004605e2:
        push dword ptr [ebp+0Ch]
    L_004605e5:
        push dword ptr [ebp+8]
    L_004605e8:
        call asm_ascii_strnicmp_004617e0
    L_004605ed:
        add esp,0Ch
    L_004605f0:
        jmp short L_00460633
    L_004605f2:
        push esi
    L_004605f3:
        mov esi,dword ptr [ebp+8]
    L_004605f6:
        push edi
    L_004605f7:
        mov edi,dword ptr [ebp+0Ch]
    L_004605fa:
        movzx eax,byte ptr [esi]
    L_004605fd:
        push eax
    L_004605fe:
        push ebx
    L_004605ff:
        call asm_tolower_mt_00460c26
    L_00460604:
        mov dword ptr [ebp-4],eax
    L_00460607:
        movzx eax,byte ptr [edi]
    L_0046060a:
        push eax
    L_0046060b:
        push ebx
    L_0046060c:
        inc esi
    L_0046060d:
        call asm_tolower_mt_00460c26
    L_00460612:
        add esp,10h
    L_00460615:
        inc edi
    L_00460616:
        dec dword ptr [ebp+10h]
    L_00460619:
        mov ecx,eax
    L_0046061b:
        je short L_00460628
    L_0046061d:
        cmp dword ptr [ebp-4],0
    L_00460621:
        je short L_00460628
    L_00460623:
        cmp dword ptr [ebp-4],ecx
    L_00460626:
        je short L_004605fa
    L_00460628:
        mov eax,dword ptr [ebp-4]
    L_0046062b:
        pop edi
    L_0046062c:
        sub eax,ecx
    L_0046062e:
        pop esi
    L_0046062f:
        jmp short L_00460633
    L_00460631:
        xor eax,eax
    L_00460633:
        pop ebx
    L_00460634:
        leave
    L_00460635:
        ret
    }
}

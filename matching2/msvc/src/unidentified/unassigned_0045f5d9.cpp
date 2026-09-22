#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

extern "C" __declspec(naked) void __cdecl asm_unassigned_0045f5d9() {
    __asm {
    L_0045f5d9:
        mov ecx,dword ptr [esp+4]
    L_0045f5dd:
        cmp ecx,dword ptr [data_004991e4]
    L_0045f5e3:
        push esi
    L_0045f5e4:
        push edi
    L_0045f5e5:
        jae short L_0045f63c
    L_0045f5e7:
        mov eax,ecx
    L_0045f5e9:
        sar eax,5
    L_0045f5ec:
        lea edi,[eax*4+499200h]
    L_0045f5f3:
        mov eax,ecx
    L_0045f5f5:
        and eax,1Fh
    L_0045f5f8:
        lea esi,[eax+eax*8]
    L_0045f5fb:
        mov eax,dword ptr [edi]
    L_0045f5fd:
        shl esi,2
    L_0045f600:
        cmp dword ptr [esi+eax],0FFFFFFFFh
    L_0045f604:
        jne short L_0045f63c
    L_0045f606:
        cmp dword ptr [data_00473074],1
    L_0045f60d:
        push ebx
    L_0045f60e:
        mov ebx,dword ptr [esp+14h]
    L_0045f612:
        jne short L_0045f632
    L_0045f614:
        sub ecx,0
    L_0045f617:
        je short L_0045f629
    L_0045f619:
        dec ecx
    L_0045f61a:
        je short L_0045f624
    L_0045f61c:
        dec ecx
    L_0045f61d:
        jne short L_0045f632
    L_0045f61f:
        push ebx
    L_0045f620:
        push 0FFFFFFF4h
    L_0045f622:
        jmp short L_0045f62c
    L_0045f624:
        push ebx
    L_0045f625:
        push 0FFFFFFF5h
    L_0045f627:
        jmp short L_0045f62c
    L_0045f629:
        push ebx
    L_0045f62a:
        push 0FFFFFFF6h
    L_0045f62c:
        call dword ptr [data_004661bc]
    L_0045f632:
        mov eax,dword ptr [edi]
    L_0045f634:
        mov dword ptr [esi+eax],ebx
    L_0045f637:
        xor eax,eax
    L_0045f639:
        pop ebx
    L_0045f63a:
        jmp short L_0045f652
    L_0045f63c:
        call asm_FUN_00456af2_00456af2
    L_0045f641:
        mov dword ptr [eax],9
    L_0045f647:
        call asm_FUN_00456afb_00456afb
    L_0045f64c:
        and dword ptr [eax],0
    L_0045f64f:
        or eax,0FFFFFFFFh
    L_0045f652:
        pop edi
    L_0045f653:
        pop esi
    L_0045f654:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441520..0x00441580: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441520() {
    __asm {
    L_00441520:
        test eax,eax
    L_00441522:
        push ebp
    L_00441523:
        mov bp,word ptr [esp+8]
    L_00441528:
        je short L_0044157d
    L_0044152a:
        push ebx
    L_0044152b:
        push esi
    L_0044152c:
        push edi
    L_0044152d:
        mov edi,dword ptr [data_00491c10]
    L_00441533:
        add ecx,394h
    L_00441539:
        mov esi,eax
    L_0044153b:
        jmp short L_00441540
    L_0044153d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00441540:
        mov eax,dword ptr [ecx]
    L_00441542:
        test eax,eax
    L_00441544:
        je short L_00441571
    L_00441546:
        mov eax,dword ptr [eax]
    L_00441548:
        test eax,eax
    L_0044154a:
        jl short L_00441571
    L_0044154c:
        mov eax,dword ptr [edi+eax*4+3AD06Ch]
    L_00441553:
        test eax,eax
    L_00441555:
        je short L_00441571
    L_00441557:
        mov ebx,dword ptr [eax+120h]
    L_0044155d:
        xor edx,edx
    L_0044155f:
        test ebx,ebx
    L_00441561:
        setne dl
    L_00441564:
        mov eax,edx
    L_00441566:
        test eax,eax
    L_00441568:
        je short L_00441571
    L_0044156a:
        mov word ptr [ecx-90h],bp
    L_00441571:
        add ecx,3ACh
    L_00441577:
        dec esi
    L_00441578:
        jne short L_00441540
    L_0044157a:
        pop edi
    L_0044157b:
        pop esi
    L_0044157c:
        pop ebx
    L_0044157d:
        pop ebp
    L_0044157e:
        ret 4
    }
}

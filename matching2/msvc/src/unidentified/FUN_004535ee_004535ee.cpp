#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004535EE..0x00453676: FUN_004535ee
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004535ee_004535ee() {
    __asm {
    L_004535ee:
        push 0Ch
    L_004535f0:
        push 46A760h
    L_004535f5:
        call asm_SEH_prolog_00454bbc
    L_004535fa:
        push dword ptr [data_00473390]
    L_00453600:
        call dword ptr [data_00477378]
    L_00453606:
        mov esi,eax
    L_00453608:
        test esi,esi
    L_0045360a:
        jne short L_00453632
    L_0045360c:
        mov esi,dword ptr [ebp+8]
    L_0045360f:
        push esi
    L_00453610:
        push dword ptr [data_00473390]
    L_00453616:
        call dword ptr [data_0047737c]
    L_0045361c:
        test eax,eax
    L_0045361e:
        jne short L_00453628
    L_00453620:
        push 10h
    L_00453622:
        call asm_amsg_exit_0045373d
    L_00453627:
        pop ecx
    L_00453628:
        call dword ptr [data_0046619c]
    L_0045362e:
        mov dword ptr [esi],eax
    L_00453630:
        jmp short L_00453648
    L_00453632:
        mov eax,dword ptr [ebp+8]
    L_00453635:
        mov ecx,dword ptr [eax+4Ch]
    L_00453638:
        mov dword ptr [esi+4Ch],ecx
    L_0045363b:
        mov ecx,dword ptr [eax+50h]
    L_0045363e:
        mov dword ptr [esi+50h],ecx
    L_00453641:
        push eax
    L_00453642:
        call asm_free_00452422
    L_00453647:
        pop ecx
    L_00453648:
        mov eax,dword ptr [data_004733ac]
    L_0045364d:
        test eax,eax
    L_0045364f:
        je short L_00453653
    L_00453651:
        call eax
    L_00453653:
        and dword ptr [ebp-4],0
    L_00453657:
        push dword ptr [esi+50h]
    L_0045365a:
        call dword ptr [esi+4Ch]
    L_0045365d:
        push eax
    L_0045365e:
        call asm_endthreadex_004535bd
    L_00453663:
        mov eax,dword ptr [ebp-14h]
    L_00453666:
        mov ecx,dword ptr [eax]
    L_00453668:
        mov ecx,dword ptr [ecx]
    L_0045366a:
        mov dword ptr [ebp-1Ch],ecx
    L_0045366d:
        push eax
    L_0045366e:
        push ecx
    L_0045366f:
        call asm_XcptFilter_004577ce
    L_00453674:
        pop ecx
    L_00453675:
        pop ecx
    L_00453676:
        ret
    }
}

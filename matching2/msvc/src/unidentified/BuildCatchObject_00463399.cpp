#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463399..0x00463508: BuildCatchObject
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BuildCatchObject_00463399() {
    __asm {
    L_00463399:
        push 8
    L_0046339b:
        push 46CB08h
    L_004633a0:
        call asm_SEH_prolog_00454bbc
    L_004633a5:
        mov esi,ecx
    L_004633a7:
        mov eax,dword ptr [ebp+0Ch]
    L_004633aa:
        mov edi,edx
    L_004633ac:
        mov ebx,dword ptr [ebp+8]
    L_004633af:
        mov ecx,dword ptr [eax+4]
    L_004633b2:
        test ecx,ecx
    L_004633b4:
        je asm_target_00463503
    L_004633ba:
        cmp byte ptr [ecx+8],0
    L_004633be:
        je asm_target_00463503
    L_004633c4:
        mov ecx,dword ptr [eax+8]
    L_004633c7:
        test ecx,ecx
    L_004633c9:
        jne short L_004633d5
    L_004633cb:
        test byte ptr [eax+3],80h
    L_004633cf:
        je asm_target_00463503
    L_004633d5:
        mov eax,dword ptr [eax]
    L_004633d7:
        test eax,eax
    L_004633d9:
        js short L_004633df
    L_004633db:
        lea edi,[ecx+edi+0Ch]
    L_004633df:
        and dword ptr [ebp-4],0
    L_004633e3:
        push 1
    L_004633e5:
        push dword ptr [ebx+18h]
    L_004633e8:
        test al,8
    L_004633ea:
        je short L_00463421
    L_004633ec:
        call asm_ValidateRead_00463aca
    L_004633f1:
        pop ecx
    L_004633f2:
        pop ecx
    L_004633f3:
        test eax,eax
    L_004633f5:
        je asm_target_004634fa
    L_004633fb:
        push 1
    L_004633fd:
        push edi
    L_004633fe:
        call asm_ValidateWrite_00463ae6
    L_00463403:
        pop ecx
    L_00463404:
        pop ecx
    L_00463405:
        test eax,eax
    L_00463407:
        je asm_target_004634fa
    L_0046340d:
        mov eax,dword ptr [ebx+18h]
    L_00463410:
        mov dword ptr [edi],eax
    L_00463412:
        lea ecx,[esi+8]
    L_00463415:
        call asm_AdjustPointer_00462fc1
    L_0046341a:
        mov dword ptr [edi],eax
    L_0046341c:
        jmp asm_target_004634ff
    L_00463421:
        test byte ptr [esi],1
    L_00463424:
        je short L_0046346c
    L_00463426:
        call asm_ValidateRead_00463aca
    L_0046342b:
        pop ecx
    L_0046342c:
        pop ecx
    L_0046342d:
        test eax,eax
    L_0046342f:
        je asm_target_004634fa
    L_00463435:
        push 1
    L_00463437:
        push edi
    L_00463438:
        call asm_ValidateWrite_00463ae6
    L_0046343d:
        pop ecx
    L_0046343e:
        pop ecx
    L_0046343f:
        test eax,eax
    L_00463441:
        je asm_target_004634fa
    L_00463447:
        push dword ptr [esi+14h]
    L_0046344a:
        push dword ptr [ebx+18h]
    L_0046344d:
        push edi
    L_0046344e:
        call asm_memmove_00453280
    L_00463453:
        add esp,0Ch
    L_00463456:
        cmp dword ptr [esi+14h],4
    L_0046345a:
        jne asm_target_004634ff
    L_00463460:
        mov eax,dword ptr [edi]
    L_00463462:
        test eax,eax
    L_00463464:
        je asm_target_004634ff
    L_0046346a:
        jmp short L_00463412
    L_0046346c:
        cmp dword ptr [esi+18h],0
    L_00463470:
        jne short L_004634a5
    L_00463472:
        call asm_ValidateRead_00463aca
    L_00463477:
        pop ecx
    L_00463478:
        pop ecx
    L_00463479:
        test eax,eax
    L_0046347b:
        je short L_004634fa
    L_0046347d:
        push 1
    L_0046347f:
        push edi
    L_00463480:
        call asm_ValidateWrite_00463ae6
    L_00463485:
        pop ecx
    L_00463486:
        pop ecx
    L_00463487:
        test eax,eax
    L_00463489:
        je short L_004634fa
    L_0046348b:
        push dword ptr [esi+14h]
    L_0046348e:
        lea ecx,[esi+8]
    L_00463491:
        mov eax,dword ptr [ebx+18h]
    L_00463494:
        call asm_AdjustPointer_00462fc1
    L_00463499:
        push eax
    L_0046349a:
        push edi
    L_0046349b:
        call asm_memmove_00453280
    L_004634a0:
        add esp,0Ch
    L_004634a3:
        jmp short L_004634ff
    L_004634a5:
        call asm_ValidateRead_00463aca
    L_004634aa:
        pop ecx
    L_004634ab:
        pop ecx
    L_004634ac:
        test eax,eax
    L_004634ae:
        je short L_004634fa
    L_004634b0:
        push 1
    L_004634b2:
        push edi
    L_004634b3:
        call asm_ValidateWrite_00463ae6
    L_004634b8:
        pop ecx
    L_004634b9:
        pop ecx
    L_004634ba:
        test eax,eax
    L_004634bc:
        je short L_004634fa
    L_004634be:
        push dword ptr [esi+18h]
    L_004634c1:
        call asm_ValidateExecute_00463b02
    L_004634c6:
        pop ecx
    L_004634c7:
        test eax,eax
    L_004634c9:
        je short L_004634fa
    L_004634cb:
        mov eax,dword ptr [ebx+18h]
    L_004634ce:
        lea ecx,[esi+8]
    L_004634d1:
        test byte ptr [esi],4
    L_004634d4:
        je short L_004634e9
    L_004634d6:
        push 1
    L_004634d8:
        call asm_AdjustPointer_00462fc1
    L_004634dd:
        push eax
    L_004634de:
        push dword ptr [esi+18h]
    L_004634e1:
        push edi
    L_004634e2:
        call asm_FID_conflict__CallMemberFunction1_00462714
    L_004634e7:
        jmp short L_004634ff
    L_004634e9:
        call asm_AdjustPointer_00462fc1
    L_004634ee:
        push eax
    L_004634ef:
        push dword ptr [esi+18h]
    L_004634f2:
        push edi
    L_004634f3:
        call asm_FID_conflict__CallMemberFunction1_0046270d
    L_004634f8:
        jmp short L_004634ff
    L_004634fa:
        call asm_inconsistency_004556e0
    L_004634ff:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00463503:
        call asm_SEH_epilog_00454bf7
    L_00463508:
        ret
    }
}

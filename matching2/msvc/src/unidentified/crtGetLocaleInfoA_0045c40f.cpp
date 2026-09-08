#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C40F..0x0045C4F1: crtGetLocaleInfoA
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtGetLocaleInfoA_0045c40f() {
    __asm {
    L_0045c40f:
        push ebp
    L_0045c410:
        mov ebp,esp
    L_0045c412:
        push ebx
    L_0045c413:
        push esi
    L_0045c414:
        push edi
    L_0045c415:
        push 1Ah
    L_0045c417:
        xor esi,esi
    L_0045c419:
        pop edi
    L_0045c41a:
        mov ebx,dword ptr [ebp+14h]
    L_0045c41d:
        lea eax,[edi+esi]
    L_0045c420:
        cdq
    L_0045c421:
        sub eax,edx
    L_0045c423:
        sar eax,1
    L_0045c425:
        mov ecx,eax
    L_0045c427:
        imul ecx,2Ch
    L_0045c42a:
        mov ecx,dword ptr [ecx+46B720h]
    L_0045c430:
        cmp dword ptr [ebp+8],ecx
    L_0045c433:
        je short L_0045c45a
    L_0045c435:
        jae short L_0045c43c
    L_0045c437:
        lea edi,[eax-1]
    L_0045c43a:
        jmp short L_0045c43f
    L_0045c43c:
        lea esi,[eax+1]
    L_0045c43f:
        cmp esi,edi
    L_0045c441:
        jle short L_0045c41a
    L_0045c443:
        push ebx
    L_0045c444:
        push dword ptr [ebp+10h]
    L_0045c447:
        push dword ptr [ebp+0Ch]
    L_0045c44a:
        push dword ptr [ebp+8]
    L_0045c44d:
        call dword ptr [data_0046605c]
    L_0045c453:
        pop edi
    L_0045c454:
        pop esi
    L_0045c455:
        pop ebx
    L_0045c456:
        pop ebp
    L_0045c457:
        ret 10h
    L_0045c45a:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045c45d:
        dec ecx
    L_0045c45e:
        je short L_0045c4bb
    L_0045c460:
        dec ecx
    L_0045c461:
        dec ecx
    L_0045c462:
        je short L_0045c4b1
    L_0045c464:
        sub ecx,4
    L_0045c467:
        je short L_0045c4a7
    L_0045c469:
        sub ecx,4
    L_0045c46c:
        je short L_0045c49d
    L_0045c46e:
        sub ecx,0FF6h
    L_0045c474:
        je short L_0045c492
    L_0045c476:
        dec ecx
    L_0045c477:
        je short L_0045c487
    L_0045c479:
        dec ecx
    L_0045c47a:
        dec ecx
    L_0045c47b:
        jne short L_0045c443
    L_0045c47d:
        imul eax,2Ch
    L_0045c480:
        add eax,46B744h
    L_0045c485:
        jmp short L_0045c4c3
    L_0045c487:
        imul eax,2Ch
    L_0045c48a:
        mov eax,dword ptr [eax+46B734h]
    L_0045c490:
        jmp short L_0045c4c3
    L_0045c492:
        imul eax,2Ch
    L_0045c495:
        mov eax,dword ptr [eax+46B72Ch]
    L_0045c49b:
        jmp short L_0045c4c3
    L_0045c49d:
        imul eax,2Ch
    L_0045c4a0:
        add eax,46B73Ch
    L_0045c4a5:
        jmp short L_0045c4c3
    L_0045c4a7:
        imul eax,2Ch
    L_0045c4aa:
        add eax,46B738h
    L_0045c4af:
        jmp short L_0045c4c3
    L_0045c4b1:
        imul eax,2Ch
    L_0045c4b4:
        add eax,46B730h
    L_0045c4b9:
        jmp short L_0045c4c3
    L_0045c4bb:
        imul eax,2Ch
    L_0045c4be:
        add eax,46B724h
    L_0045c4c3:
        test eax,eax
    L_0045c4c5:
        je asm_target_0045c443
    L_0045c4cb:
        cmp ebx,1
    L_0045c4ce:
        jl asm_target_0045c443
    L_0045c4d4:
        mov esi,dword ptr [ebp+10h]
    L_0045c4d7:
        lea ecx,[ebx-1]
    L_0045c4da:
        push ecx
    L_0045c4db:
        push eax
    L_0045c4dc:
        push esi
    L_0045c4dd:
        call asm_strncpy_00452960
    L_0045c4e2:
        xor eax,eax
    L_0045c4e4:
        add esp,0Ch
    L_0045c4e7:
        mov byte ptr [esi+ebx-1],0
    L_0045c4ec:
        inc eax
    L_0045c4ed:
        jmp asm_target_0045c453
    }
}

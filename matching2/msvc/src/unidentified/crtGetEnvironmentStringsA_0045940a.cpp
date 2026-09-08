#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045940A..0x0045952B: ___crtGetEnvironmentStringsA
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtGetEnvironmentStringsA_0045940a() {
    __asm {
    L_0045940a:
        push ecx
    L_0045940b:
        push ecx
    L_0045940c:
        mov eax,dword ptr [data_004775c0]
    L_00459411:
        push ebx
    L_00459412:
        push ebp
    L_00459413:
        push esi
    L_00459414:
        push edi
    L_00459415:
        mov edi,dword ptr [data_00466088]
    L_0045941b:
        xor ebx,ebx
    L_0045941d:
        xor esi,esi
    L_0045941f:
        cmp eax,ebx
    L_00459421:
        push 2
    L_00459423:
        pop ebp
    L_00459424:
        jne short L_00459453
    L_00459426:
        call edi
    L_00459428:
        mov esi,eax
    L_0045942a:
        cmp esi,ebx
    L_0045942c:
        je short L_0045943a
    L_0045942e:
        mov dword ptr [data_004775c0],1
    L_00459438:
        jmp short L_00459458
    L_0045943a:
        call dword ptr [data_0046610c]
    L_00459440:
        cmp eax,78h
    L_00459443:
        jne short L_0045944e
    L_00459445:
        mov eax,ebp
    L_00459447:
        mov dword ptr [data_004775c0],eax
    L_0045944c:
        jmp short L_00459453
    L_0045944e:
        mov eax,dword ptr [data_004775c0]
    L_00459453:
        cmp eax,1
    L_00459456:
        jne short L_004594d5
    L_00459458:
        cmp esi,ebx
    L_0045945a:
        jne short L_00459464
    L_0045945c:
        call edi
    L_0045945e:
        mov esi,eax
    L_00459460:
        cmp esi,ebx
    L_00459462:
        je short L_004594dd
    L_00459464:
        cmp word ptr [esi],bx
    L_00459467:
        mov eax,esi
    L_00459469:
        je short L_00459479
    L_0045946b:
        add eax,ebp
    L_0045946d:
        cmp word ptr [eax],bx
    L_00459470:
        jne short L_0045946b
    L_00459472:
        add eax,ebp
    L_00459474:
        cmp word ptr [eax],bx
    L_00459477:
        jne short L_0045946b
    L_00459479:
        mov edi,dword ptr [data_00466154]
    L_0045947f:
        push ebx
    L_00459480:
        push ebx
    L_00459481:
        push ebx
    L_00459482:
        sub eax,esi
    L_00459484:
        push ebx
    L_00459485:
        sar eax,1
    L_00459487:
        inc eax
    L_00459488:
        push eax
    L_00459489:
        push esi
    L_0045948a:
        push ebx
    L_0045948b:
        push ebx
    L_0045948c:
        mov dword ptr [esp+34h],eax
    L_00459490:
        call edi
    L_00459492:
        mov ebp,eax
    L_00459494:
        cmp ebp,ebx
    L_00459496:
        je short L_004594ca
    L_00459498:
        push ebp
    L_00459499:
        call asm_malloc_00452706
    L_0045949e:
        cmp eax,ebx
    L_004594a0:
        pop ecx
    L_004594a1:
        mov dword ptr [esp+10h],eax
    L_004594a5:
        je short L_004594ca
    L_004594a7:
        push ebx
    L_004594a8:
        push ebx
    L_004594a9:
        push ebp
    L_004594aa:
        push eax
    L_004594ab:
        push dword ptr [esp+24h]
    L_004594af:
        push esi
    L_004594b0:
        push ebx
    L_004594b1:
        push ebx
    L_004594b2:
        call edi
    L_004594b4:
        test eax,eax
    L_004594b6:
        jne short L_004594c6
    L_004594b8:
        push dword ptr [esp+10h]
    L_004594bc:
        call asm_free_00452422
    L_004594c1:
        pop ecx
    L_004594c2:
        mov dword ptr [esp+10h],ebx
    L_004594c6:
        mov ebx,dword ptr [esp+10h]
    L_004594ca:
        push esi
    L_004594cb:
        call dword ptr [data_0046608c]
    L_004594d1:
        mov eax,ebx
    L_004594d3:
        jmp short L_00459525
    L_004594d5:
        cmp eax,ebp
    L_004594d7:
        je short L_004594e1
    L_004594d9:
        cmp eax,ebx
    L_004594db:
        je short L_004594e1
    L_004594dd:
        xor eax,eax
    L_004594df:
        jmp short L_00459525
    L_004594e1:
        call dword ptr [data_00466090]
    L_004594e7:
        mov esi,eax
    L_004594e9:
        cmp esi,ebx
    L_004594eb:
        je short L_004594dd
    L_004594ed:
        cmp byte ptr [esi],bl
    L_004594ef:
        je short L_004594fb
    L_004594f1:
        inc eax
    L_004594f2:
        cmp byte ptr [eax],bl
    L_004594f4:
        jne short L_004594f1
    L_004594f6:
        inc eax
    L_004594f7:
        cmp byte ptr [eax],bl
    L_004594f9:
        jne short L_004594f1
    L_004594fb:
        sub eax,esi
    L_004594fd:
        inc eax
    L_004594fe:
        mov ebp,eax
    L_00459500:
        push ebp
    L_00459501:
        call asm_malloc_00452706
    L_00459506:
        mov edi,eax
    L_00459508:
        cmp edi,ebx
    L_0045950a:
        pop ecx
    L_0045950b:
        jne short L_00459511
    L_0045950d:
        xor edi,edi
    L_0045950f:
        jmp short L_0045951c
    L_00459511:
        push ebp
    L_00459512:
        push esi
    L_00459513:
        push edi
    L_00459514:
        call asm_memcpy_0045bfc0
    L_00459519:
        add esp,0Ch
    L_0045951c:
        push esi
    L_0045951d:
        call dword ptr [data_00466094]
    L_00459523:
        mov eax,edi
    L_00459525:
        pop edi
    L_00459526:
        pop esi
    L_00459527:
        pop ebp
    L_00459528:
        pop ebx
    L_00459529:
        pop ecx
    L_0045952a:
        pop ecx
    L_0045952b:
        ret
    }
}

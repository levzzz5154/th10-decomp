#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D476..0x0045D5CD: __ld12cvt
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ld12cvt_0045d476() {
    __asm {
    L_0045d476:
        push ebp
    L_0045d477:
        mov ebp,esp
    L_0045d479:
        sub esp,18h
    L_0045d47c:
        mov eax,dword ptr [ebp+8]
    L_0045d47f:
        movzx ecx,word ptr [eax+0Ah]
    L_0045d483:
        push ebx
    L_0045d484:
        push esi
    L_0045d485:
        mov esi,dword ptr [ebp+10h]
    L_0045d488:
        push edi
    L_0045d489:
        mov edi,ecx
    L_0045d48b:
        and ecx,8000h
    L_0045d491:
        mov dword ptr [ebp+8],ecx
    L_0045d494:
        mov ecx,dword ptr [eax+6]
    L_0045d497:
        mov dword ptr [ebp-0Ch],ecx
    L_0045d49a:
        mov ecx,dword ptr [eax+2]
    L_0045d49d:
        movzx eax,word ptr [eax]
    L_0045d4a0:
        shl eax,10h
    L_0045d4a3:
        and edi,7FFFh
    L_0045d4a9:
        sub edi,3FFFh
    L_0045d4af:
        cmp edi,0FFFFC001h
    L_0045d4b5:
        mov dword ptr [ebp-4],eax
    L_0045d4b8:
        lea eax,[ebp-0Ch]
    L_0045d4bb:
        mov dword ptr [ebp-8],ecx
    L_0045d4be:
        push eax
    L_0045d4bf:
        jne short L_0045d4df
    L_0045d4c1:
        xor ebx,ebx
    L_0045d4c3:
        call asm_IsZeroMan_0045d3e2
    L_0045d4c8:
        test eax,eax
    L_0045d4ca:
        pop ecx
    L_0045d4cb:
        jne asm_target_0045d58e
    L_0045d4d1:
        lea edi,[ebp-0Ch]
    L_0045d4d4:
        stosd
    L_0045d4d5:
        stosd
    L_0045d4d6:
        stosd
    L_0045d4d7:
        push 2
    L_0045d4d9:
        pop eax
    L_0045d4da:
        jmp asm_target_0045d590
    L_0045d4df:
        lea eax,[ebp-18h]
    L_0045d4e2:
        push eax
    L_0045d4e3:
        call asm_CopyMan_0045d3bb
    L_0045d4e8:
        push dword ptr [esi+8]
    L_0045d4eb:
        lea eax,[ebp-0Ch]
    L_0045d4ee:
        push eax
    L_0045d4ef:
        call asm_RoundMan_0045d349
    L_0045d4f4:
        add esp,10h
    L_0045d4f7:
        test eax,eax
    L_0045d4f9:
        je short L_0045d4fc
    L_0045d4fb:
        inc edi
    L_0045d4fc:
        mov eax,dword ptr [esi+4]
    L_0045d4ff:
        mov ecx,eax
    L_0045d501:
        sub ecx,dword ptr [esi+8]
    L_0045d504:
        cmp edi,ecx
    L_0045d506:
        jge short L_0045d512
    L_0045d508:
        xor eax,eax
    L_0045d50a:
        lea edi,[ebp-0Ch]
    L_0045d50d:
        stosd
    L_0045d50e:
        stosd
    L_0045d50f:
        stosd
    L_0045d510:
        jmp short L_0045d54e
    L_0045d512:
        cmp edi,eax
    L_0045d514:
        jg short L_0045d552
    L_0045d516:
        sub eax,edi
    L_0045d518:
        mov edi,eax
    L_0045d51a:
        lea eax,[ebp-18h]
    L_0045d51d:
        push eax
    L_0045d51e:
        lea eax,[ebp-0Ch]
    L_0045d521:
        push eax
    L_0045d522:
        call asm_CopyMan_0045d3bb
    L_0045d527:
        lea eax,[ebp-0Ch]
    L_0045d52a:
        push edi
    L_0045d52b:
        push eax
    L_0045d52c:
        call asm_ShrMan_0045d3fb
    L_0045d531:
        push dword ptr [esi+8]
    L_0045d534:
        lea eax,[ebp-0Ch]
    L_0045d537:
        push eax
    L_0045d538:
        call asm_RoundMan_0045d349
    L_0045d53d:
        mov eax,dword ptr [esi+0Ch]
    L_0045d540:
        inc eax
    L_0045d541:
        push eax
    L_0045d542:
        lea eax,[ebp-0Ch]
    L_0045d545:
        push eax
    L_0045d546:
        call asm_ShrMan_0045d3fb
    L_0045d54b:
        add esp,20h
    L_0045d54e:
        xor ebx,ebx
    L_0045d550:
        jmp short L_0045d4d7
    L_0045d552:
        cmp edi,dword ptr [esi]
    L_0045d554:
        push dword ptr [esi+0Ch]
    L_0045d557:
        jl short L_0045d57a
    L_0045d559:
        xor eax,eax
    L_0045d55b:
        lea edi,[ebp-0Ch]
    L_0045d55e:
        stosd
    L_0045d55f:
        stosd
    L_0045d560:
        stosd
    L_0045d561:
        or byte ptr [ebp-9],80h
    L_0045d565:
        lea eax,[ebp-0Ch]
    L_0045d568:
        push eax
    L_0045d569:
        call asm_ShrMan_0045d3fb
    L_0045d56e:
        mov ebx,dword ptr [esi+14h]
    L_0045d571:
        add ebx,dword ptr [esi]
    L_0045d573:
        pop ecx
    L_0045d574:
        xor eax,eax
    L_0045d576:
        pop ecx
    L_0045d577:
        inc eax
    L_0045d578:
        jmp short L_0045d590
    L_0045d57a:
        mov ebx,dword ptr [esi+14h]
    L_0045d57d:
        and byte ptr [ebp-9],7Fh
    L_0045d581:
        lea eax,[ebp-0Ch]
    L_0045d584:
        push eax
    L_0045d585:
        add ebx,edi
    L_0045d587:
        call asm_ShrMan_0045d3fb
    L_0045d58c:
        pop ecx
    L_0045d58d:
        pop ecx
    L_0045d58e:
        xor eax,eax
    L_0045d590:
        push 1Fh
    L_0045d592:
        pop ecx
    L_0045d593:
        sub ecx,dword ptr [esi+0Ch]
    L_0045d596:
        mov esi,dword ptr [esi+10h]
    L_0045d599:
        shl ebx,cl
    L_0045d59b:
        mov ecx,dword ptr [ebp+8]
    L_0045d59e:
        neg ecx
    L_0045d5a0:
        sbb ecx,ecx
    L_0045d5a2:
        and ecx,80000000h
    L_0045d5a8:
        or ebx,ecx
    L_0045d5aa:
        or ebx,dword ptr [ebp-0Ch]
    L_0045d5ad:
        cmp esi,40h
    L_0045d5b0:
        jne short L_0045d5bf
    L_0045d5b2:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045d5b5:
        mov edx,dword ptr [ebp-8]
    L_0045d5b8:
        mov dword ptr [ecx+4],ebx
    L_0045d5bb:
        mov dword ptr [ecx],edx
    L_0045d5bd:
        jmp short L_0045d5c9
    L_0045d5bf:
        cmp esi,20h
    L_0045d5c2:
        jne short L_0045d5c9
    L_0045d5c4:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045d5c7:
        mov dword ptr [ecx],ebx
    L_0045d5c9:
        pop edi
    L_0045d5ca:
        pop esi
    L_0045d5cb:
        pop ebx
    L_0045d5cc:
        leave
    L_0045d5cd:
        ret
    }
}

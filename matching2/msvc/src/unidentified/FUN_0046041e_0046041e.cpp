#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046041E..0x0046054D: FUN_0046041e
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046041e_0046041e() {
    __asm {
    L_0046041e:
        push ebp
    L_0046041f:
        lea ebp,[esp-68h]
    L_00460423:
        sub esp,8Ch
    L_00460429:
        mov eax,dword ptr [data_00473660]
    L_0046042e:
        push ebx
    L_0046042f:
        push esi
    L_00460430:
        mov esi,dword ptr [ebp+7Ch]
    L_00460433:
        xor eax,ebp
    L_00460435:
        xor ebx,ebx
    L_00460437:
        cmp dword ptr [ebp+70h],1
    L_0046043b:
        mov dword ptr [ebp+64h],eax
    L_0046043e:
        push edi
    L_0046043f:
        mov dword ptr [ebp-24h],esi
    L_00460442:
        jne asm_target_00460502
    L_00460448:
        push ebx
    L_00460449:
        lea edi,[ebp-1Ch]
    L_0046044c:
        push 80h
    L_00460451:
        mov eax,edi
    L_00460453:
        push eax
    L_00460454:
        push dword ptr [ebp+78h]
    L_00460457:
        mov dword ptr [ebp-20h],ebx
    L_0046045a:
        push dword ptr [ebp+74h]
    L_0046045d:
        call asm_crtGetLocaleInfoA_00461695
    L_00460462:
        mov esi,eax
    L_00460464:
        add esp,14h
    L_00460467:
        cmp esi,ebx
    L_00460469:
        jne short L_004604b8
    L_0046046b:
        call dword ptr [data_0046610c]
    L_00460471:
        cmp eax,7Ah
    L_00460474:
        jne short L_004604d4
    L_00460476:
        push ebx
    L_00460477:
        push ebx
    L_00460478:
        push ebx
    L_00460479:
        push dword ptr [ebp+78h]
    L_0046047c:
        push dword ptr [ebp+74h]
    L_0046047f:
        call asm_crtGetLocaleInfoA_00461695
    L_00460484:
        mov esi,eax
    L_00460486:
        add esp,14h
    L_00460489:
        cmp esi,ebx
    L_0046048b:
        je short L_004604d4
    L_0046048d:
        push esi
    L_0046048e:
        call asm_malloc_00452706
    L_00460493:
        mov edi,eax
    L_00460495:
        cmp edi,ebx
    L_00460497:
        pop ecx
    L_00460498:
        je short L_004604d4
    L_0046049a:
        push ebx
    L_0046049b:
        push esi
    L_0046049c:
        push edi
    L_0046049d:
        push dword ptr [ebp+78h]
    L_004604a0:
        mov dword ptr [ebp-20h],1
    L_004604a7:
        push dword ptr [ebp+74h]
    L_004604aa:
        call asm_crtGetLocaleInfoA_00461695
    L_004604af:
        mov esi,eax
    L_004604b1:
        add esp,14h
    L_004604b4:
        cmp esi,ebx
    L_004604b6:
        je short L_004604cd
    L_004604b8:
        push esi
    L_004604b9:
        call asm_malloc_00452706
    L_004604be:
        cmp eax,ebx
    L_004604c0:
        pop ecx
    L_004604c1:
        mov ecx,dword ptr [ebp-24h]
    L_004604c4:
        mov dword ptr [ecx],eax
    L_004604c6:
        jne short L_004604e9
    L_004604c8:
        cmp dword ptr [ebp-20h],ebx
    L_004604cb:
        je short L_004604d4
    L_004604cd:
        push edi
    L_004604ce:
        call asm_free_00452422
    L_004604d3:
        pop ecx
    L_004604d4:
        or eax,0FFFFFFFFh
    L_004604d7:
        mov ecx,dword ptr [ebp+64h]
    L_004604da:
        pop edi
    L_004604db:
        pop esi
    L_004604dc:
        xor ecx,ebp
    L_004604de:
        pop ebx
    L_004604df:
        call asm_security_check_cookie_00458ea5
    L_004604e4:
        add ebp,68h
    L_004604e7:
        leave
    L_004604e8:
        ret
    L_004604e9:
        push esi
    L_004604ea:
        push edi
    L_004604eb:
        push eax
    L_004604ec:
        call asm_strncpy_00452960
    L_004604f1:
        add esp,0Ch
    L_004604f4:
        cmp dword ptr [ebp-20h],ebx
    L_004604f7:
        je short L_0046054a
    L_004604f9:
        push edi
    L_004604fa:
        call asm_free_00452422
    L_004604ff:
        pop ecx
    L_00460500:
        jmp short L_0046054a
    L_00460502:
        cmp dword ptr [ebp+70h],ebx
    L_00460505:
        jne short L_004604d4
    L_00460507:
        push ebx
    L_00460508:
        push 4
    L_0046050a:
        mov edi,4776C4h
    L_0046050f:
        push edi
    L_00460510:
        push dword ptr [ebp+78h]
    L_00460513:
        push dword ptr [ebp+74h]
    L_00460516:
        call asm_crtGetLocaleInfoW_00461565
    L_0046051b:
        add esp,14h
    L_0046051e:
        test eax,eax
    L_00460520:
        je short L_004604d4
    L_00460522:
        mov byte ptr [esi],bl
    L_00460524:
        mov bl,byte ptr [edi]
    L_00460526:
        movzx eax,bl
    L_00460529:
        push eax
    L_0046052a:
        call asm_isdigit_0045685e
    L_0046052f:
        test eax,eax
    L_00460531:
        pop ecx
    L_00460532:
        je short L_0046054a
    L_00460534:
        mov al,byte ptr [esi]
    L_00460536:
        mov cl,0Ah
    L_00460538:
        imul cl
    L_0046053a:
        add al,bl
    L_0046053c:
        sub al,30h
    L_0046053e:
        inc edi
    L_0046053f:
        inc edi
    L_00460540:
        cmp edi,4776CCh
    L_00460546:
        mov byte ptr [esi],al
    L_00460548:
        jl short L_00460524
    L_0046054a:
        xor eax,eax
    L_0046054c:
        jmp short L_004604d7
    }
}

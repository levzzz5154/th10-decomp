#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D400..0x0040D4EE: FUN_0040d400
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d400_0040d400() {
    __asm {
    L_0040d400:
        push ecx
    L_0040d401:
        push ebp
    L_0040d402:
        mov ebp,dword ptr [esp+0Ch]
    L_0040d406:
        cmp dword ptr [ebp],4D494E41h
    L_0040d40d:
        mov dword ptr [esp+4],ecx
    L_0040d411:
        je short L_0040d41a
    L_0040d413:
        xor eax,eax
    L_0040d415:
        pop ebp
    L_0040d416:
        pop ecx
    L_0040d417:
        ret 4
    L_0040d41a:
        mov eax,dword ptr [ebp+4]
    L_0040d41d:
        push ebx
    L_0040d41e:
        push esi
    L_0040d41f:
        push edi
    L_0040d420:
        xor edi,edi
    L_0040d422:
        test eax,eax
    L_0040d424:
        lea esi,[ebp+8]
    L_0040d427:
        jbe short L_0040d46d
    L_0040d429:
        mov ebx,34h
    L_0040d42e:
        mov edi,edi
    L_0040d430:
        mov edx,dword ptr [data_00491c10]
    L_0040d436:
        push esi
    L_0040d437:
        lea ecx,[edi+9]
    L_0040d43a:
        call asm_Recovery_LoadCachedResource_00447280
    L_0040d43f:
        test eax,eax
    L_0040d441:
        mov ecx,dword ptr [data_00477704]
    L_0040d447:
        mov dword ptr [ebx+ecx],eax
    L_0040d44a:
        je short L_0040d4a0
    L_0040d44c:
        mov eax,esi
    L_0040d44e:
        lea edx,[eax+1]
    L_0040d451:
        mov cl,byte ptr [eax]
    L_0040d453:
        inc eax
    L_0040d454:
        test cl,cl
    L_0040d456:
        jne short L_0040d451
    L_0040d458:
        sub eax,edx
    L_0040d45a:
        lea esi,[esi+eax+1]
    L_0040d45e:
        mov eax,dword ptr [ebp+4]
    L_0040d461:
        inc edi
    L_0040d462:
        add ebx,4
    L_0040d465:
        cmp edi,eax
    L_0040d467:
        jb short L_0040d430
    L_0040d469:
        mov ecx,dword ptr [esp+10h]
    L_0040d46d:
        mov eax,esi
    L_0040d46f:
        sub eax,ebp
    L_0040d471:
        and eax,80000003h
    L_0040d476:
        jns short L_0040d47d
    L_0040d478:
        dec eax
    L_0040d479:
        or eax,0FFFFFFFCh
    L_0040d47c:
        inc eax
    L_0040d47d:
        je short L_0040d488
    L_0040d47f:
        mov edx,4
    L_0040d484:
        sub edx,eax
    L_0040d486:
        add esi,edx
    L_0040d488:
        cmp dword ptr [esi],494C4345h
    L_0040d48e:
        mov ebx,esi
    L_0040d490:
        jne short L_0040d4e5
    L_0040d492:
        mov eax,dword ptr [ebx+4]
    L_0040d495:
        add esi,8
    L_0040d498:
        xor edi,edi
    L_0040d49a:
        test eax,eax
    L_0040d49c:
        jbe short L_0040d4e5
    L_0040d49e:
        jmp short L_0040d4c1
    L_0040d4a0:
        push 46CB68h
    L_0040d4a5:
        mov ecx,474F70h
    L_0040d4aa:
        call asm_TextLog_Append_0044b810
    L_0040d4af:
        add esp,4
    L_0040d4b2:
        pop edi
    L_0040d4b3:
        pop esi
    L_0040d4b4:
        pop ebx
    L_0040d4b5:
        or eax,0FFFFFFFFh
    L_0040d4b8:
        pop ebp
    L_0040d4b9:
        pop ecx
    L_0040d4ba:
        ret 4
    L_0040d4bd:
        mov ecx,dword ptr [esp+10h]
    L_0040d4c1:
        mov eax,dword ptr [ecx]
    L_0040d4c3:
        push esi
    L_0040d4c4:
        call dword ptr [eax+8]
    L_0040d4c7:
        mov eax,esi
    L_0040d4c9:
        lea edx,[eax+1]
    L_0040d4cc:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040d4d0:
        mov cl,byte ptr [eax]
    L_0040d4d2:
        inc eax
    L_0040d4d3:
        test cl,cl
    L_0040d4d5:
        jne short L_0040d4d0
    L_0040d4d7:
        sub eax,edx
    L_0040d4d9:
        lea esi,[esi+eax+1]
    L_0040d4dd:
        mov eax,dword ptr [ebx+4]
    L_0040d4e0:
        inc edi
    L_0040d4e1:
        cmp edi,eax
    L_0040d4e3:
        jb short L_0040d4bd
    L_0040d4e5:
        pop edi
    L_0040d4e6:
        pop esi
    L_0040d4e7:
        pop ebx
    L_0040d4e8:
        xor eax,eax
    L_0040d4ea:
        pop ebp
    L_0040d4eb:
        pop ecx
    L_0040d4ec:
        ret 4
    }
}

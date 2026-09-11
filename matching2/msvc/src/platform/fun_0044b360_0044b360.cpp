#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A1C0..0x0043A28E: FUN_0043a1c0
// Naked body preserves the retail register/stack ABI.

// 0x0044B360..0x0044B4C7: FUN_0044b360
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044b360_0044b360() {
    __asm {
    L_0044b360:
        push ebx
    L_0044b361:
        push ebp
    L_0044b362:
        mov ebp,dword ptr [esp+0Ch]
    L_0044b366:
        push esi
    L_0044b367:
        push edi
    L_0044b368:
        push 4922A4h
    L_0044b36d:
        mov esi,eax
    L_0044b36f:
        call dword ptr [data_004660b0]
    L_0044b375:
        mov cl,byte ptr [data_0049231e]
    L_0044b37b:
        mov eax,dword ptr [esp+18h]
    L_0044b37f:
        inc cl
    L_0044b381:
        test eax,eax
    L_0044b383:
        mov byte ptr [data_0049231e],cl
    L_0044b389:
        jne asm_target_0044b41f
    L_0044b38f:
        push 5Ch
    L_0044b391:
        push esi
    L_0044b392:
        call asm_strrchr_00452930
    L_0044b397:
        add esp,8
    L_0044b39a:
        test eax,eax
    L_0044b39c:
        jne short L_0044b3a2
    L_0044b39e:
        mov eax,esi
    L_0044b3a0:
        jmp short L_0044b3a3
    L_0044b3a2:
        inc eax
    L_0044b3a3:
        push 2Fh
    L_0044b3a5:
        push eax
    L_0044b3a6:
        call asm_strrchr_00452930
    L_0044b3ab:
        mov ebx,eax
    L_0044b3ad:
        add esp,8
    L_0044b3b0:
        test ebx,ebx
    L_0044b3b2:
        jne short L_0044b3b8
    L_0044b3b4:
        mov ebx,esi
    L_0044b3b6:
        jmp short L_0044b3b9
    L_0044b3b8:
        inc ebx
    L_0044b3b9:
        mov edi,dword ptr [data_00497990]
    L_0044b3bf:
        test edi,edi
    L_0044b3c1:
        je short L_0044b3e8
    L_0044b3c3:
        mov esi,dword ptr [data_00497994]
    L_0044b3c9:
        test esi,esi
    L_0044b3cb:
        jle short L_0044b3e8
    L_0044b3cd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0044b3d0:
        mov eax,dword ptr [edi]
    L_0044b3d2:
        push eax
    L_0044b3d3:
        push ebx
    L_0044b3d4:
        call asm_stricmp_0046054e
    L_0044b3d9:
        add esp,8
    L_0044b3dc:
        test eax,eax
    L_0044b3de:
        je short L_0044b41a
    L_0044b3e0:
        dec esi
    L_0044b3e1:
        add edi,10h
    L_0044b3e4:
        test esi,esi
    L_0044b3e6:
        jg short L_0044b3d0
    L_0044b3e8:
        xor edi,edi
    L_0044b3ea:
        test ebp,ebp
    L_0044b3ec:
        mov dword ptr [esp+14h],edi
    L_0044b3f0:
        je short L_0044b3f5
    L_0044b3f2:
        mov dword ptr [ebp],edi
    L_0044b3f5:
        test edi,edi
    L_0044b3f7:
        je short L_0044b462
    L_0044b3f9:
        push edi
    L_0044b3fa:
        call asm_malloc_00452706
    L_0044b3ff:
        mov esi,eax
    L_0044b401:
        add esp,4
    L_0044b404:
        test esi,esi
    L_0044b406:
        je short L_0044b462
    L_0044b408:
        push esi
    L_0044b409:
        push 497990h
    L_0044b40e:
        mov ecx,ebx
    L_0044b410:
        call asm_DatArchive_Read_00434dd0
    L_0044b415:
        jmp asm_target_0044b4a8
    L_0044b41a:
        mov edi,dword ptr [edi+8]
    L_0044b41d:
        jmp short L_0044b3ea
    L_0044b41f:
        push 0
    L_0044b421:
        push 8000080h
    L_0044b426:
        push 3
    L_0044b428:
        push 0
    L_0044b42a:
        push 1
    L_0044b42c:
        push 80000000h
    L_0044b431:
        push esi
    L_0044b432:
        call dword ptr [data_004660c4]
    L_0044b438:
        mov edi,eax
    L_0044b43a:
        cmp edi,0FFFFFFFFh
    L_0044b43d:
        je short L_0044b462
    L_0044b43f:
        push 0
    L_0044b441:
        push edi
    L_0044b442:
        call dword ptr [data_004660d8]
    L_0044b448:
        push eax
    L_0044b449:
        mov dword ptr [esp+18h],eax
    L_0044b44d:
        call asm_malloc_00452706
    L_0044b452:
        mov esi,eax
    L_0044b454:
        add esp,4
    L_0044b457:
        test esi,esi
    L_0044b459:
        jne short L_0044b482
    L_0044b45b:
        push edi
    L_0044b45c:
        call dword ptr [data_004660cc]
    L_0044b462:
        push 4922A4h
    L_0044b467:
        call dword ptr [data_004660b4]
    L_0044b46d:
        mov al,byte ptr [data_0049231e]
    L_0044b472:
        pop edi
    L_0044b473:
        pop esi
    L_0044b474:
        dec al
    L_0044b476:
        pop ebp
    L_0044b477:
        mov byte ptr [data_0049231e],al
    L_0044b47c:
        xor eax,eax
    L_0044b47e:
        pop ebx
    L_0044b47f:
        ret 8
    L_0044b482:
        mov edx,dword ptr [esp+14h]
    L_0044b486:
        push 0
    L_0044b488:
        lea ecx,[esp+18h]
    L_0044b48c:
        push ecx
    L_0044b48d:
        push edx
    L_0044b48e:
        push esi
    L_0044b48f:
        push edi
    L_0044b490:
        call dword ptr [data_004660d0]
    L_0044b496:
        test ebp,ebp
    L_0044b498:
        je short L_0044b4a1
    L_0044b49a:
        mov eax,dword ptr [esp+14h]
    L_0044b49e:
        mov dword ptr [ebp],eax
    L_0044b4a1:
        push edi
    L_0044b4a2:
        call dword ptr [data_004660cc]
    L_0044b4a8:
        push 4922A4h
    L_0044b4ad:
        call dword ptr [data_004660b4]
    L_0044b4b3:
        mov al,byte ptr [data_0049231e]
    L_0044b4b8:
        dec al
    L_0044b4ba:
        pop edi
    L_0044b4bb:
        mov byte ptr [data_0049231e],al
    L_0044b4c0:
        mov eax,esi
    L_0044b4c2:
        pop esi
    L_0044b4c3:
        pop ebp
    L_0044b4c4:
        pop ebx
    L_0044b4c5:
        ret 8
    }
}

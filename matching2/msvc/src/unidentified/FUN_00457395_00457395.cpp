#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457395..0x004574F4: FUN_00457395
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457395_00457395() {
    __asm {
    L_00457395:
        push 14h
    L_00457397:
        push 46AAF0h
    L_0045739c:
        call asm_SEH_prolog_00454bbc
    L_004573a1:
        mov edi,dword ptr [ebp+8]
    L_004573a4:
        xor ebx,ebx
    L_004573a6:
        cmp edi,ebx
    L_004573a8:
        jne short L_004573b7
    L_004573aa:
        push dword ptr [ebp+0Ch]
    L_004573ad:
        call asm_malloc_00452706
    L_004573b2:
        jmp asm_target_00457540
    L_004573b7:
        mov esi,dword ptr [ebp+0Ch]
    L_004573ba:
        cmp esi,ebx
    L_004573bc:
        jne short L_004573c9
    L_004573be:
        push edi
    L_004573bf:
        call asm_free_00452422
    L_004573c4:
        jmp asm_target_0045753e
    L_004573c9:
        cmp dword ptr [data_00499344],3
    L_004573d0:
        jne asm_target_00457533
    L_004573d6:
        mov dword ptr [ebp-1Ch],ebx
    L_004573d9:
        cmp esi,0FFFFFFE0h
    L_004573dc:
        ja asm_target_00457538
    L_004573e2:
        push 4
    L_004573e4:
        call asm_lock_00453c0c
    L_004573e9:
        pop ecx
    L_004573ea:
        mov dword ptr [ebp-4],ebx
    L_004573ed:
        push edi
    L_004573ee:
        call asm_sbh_find_block_00453c9a
    L_004573f3:
        pop ecx
    L_004573f4:
        mov dword ptr [ebp-20h],eax
    L_004573f7:
        cmp eax,ebx
    L_004573f9:
        je asm_target_004574a3
    L_004573ff:
        cmp esi,dword ptr [data_00499330]
    L_00457405:
        ja short L_00457453
    L_00457407:
        push esi
    L_00457408:
        push edi
    L_00457409:
        push eax
    L_0045740a:
        call asm_sbh_resize_block_0045419a
    L_0045740f:
        add esp,0Ch
    L_00457412:
        test eax,eax
    L_00457414:
        je short L_0045741b
    L_00457416:
        mov dword ptr [ebp-1Ch],edi
    L_00457419:
        jmp short L_00457453
    L_0045741b:
        push esi
    L_0045741c:
        call asm_sbh_alloc_block_004548be
    L_00457421:
        pop ecx
    L_00457422:
        mov dword ptr [ebp-1Ch],eax
    L_00457425:
        cmp eax,ebx
    L_00457427:
        je short L_00457453
    L_00457429:
        mov eax,dword ptr [edi-4]
    L_0045742c:
        dec eax
    L_0045742d:
        mov dword ptr [ebp-24h],eax
    L_00457430:
        cmp eax,esi
    L_00457432:
        jb short L_00457436
    L_00457434:
        mov eax,esi
    L_00457436:
        push eax
    L_00457437:
        push edi
    L_00457438:
        push dword ptr [ebp-1Ch]
    L_0045743b:
        call asm_memcpy_0045bfc0
    L_00457440:
        push edi
    L_00457441:
        call asm_sbh_find_block_00453c9a
    L_00457446:
        mov dword ptr [ebp-20h],eax
    L_00457449:
        push edi
    L_0045744a:
        push eax
    L_0045744b:
        call asm_sbh_free_block_00453cc5
    L_00457450:
        add esp,18h
    L_00457453:
        cmp dword ptr [ebp-1Ch],ebx
    L_00457456:
        jne short L_004574a3
    L_00457458:
        cmp esi,ebx
    L_0045745a:
        jne short L_00457462
    L_0045745c:
        xor esi,esi
    L_0045745e:
        inc esi
    L_0045745f:
        mov dword ptr [ebp+0Ch],esi
    L_00457462:
        add esi,0Fh
    L_00457465:
        and esi,0FFFFFFF0h
    L_00457468:
        mov dword ptr [ebp+0Ch],esi
    L_0045746b:
        push esi
    L_0045746c:
        push ebx
    L_0045746d:
        push dword ptr [data_00499340]
    L_00457473:
        call dword ptr [data_004661e4]
    L_00457479:
        mov dword ptr [ebp-1Ch],eax
    L_0045747c:
        cmp eax,ebx
    L_0045747e:
        je short L_004574a3
    L_00457480:
        mov eax,dword ptr [edi-4]
    L_00457483:
        dec eax
    L_00457484:
        mov dword ptr [ebp-24h],eax
    L_00457487:
        cmp eax,esi
    L_00457489:
        jb short L_0045748d
    L_0045748b:
        mov eax,esi
    L_0045748d:
        push eax
    L_0045748e:
        push edi
    L_0045748f:
        push dword ptr [ebp-1Ch]
    L_00457492:
        call asm_memcpy_0045bfc0
    L_00457497:
        push edi
    L_00457498:
        push dword ptr [ebp-20h]
    L_0045749b:
        call asm_sbh_free_block_00453cc5
    L_004574a0:
        add esp,14h
    L_004574a3:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004574a7:
        call asm_FUN_004574fd_004574fd
    L_004574ac:
        cmp dword ptr [ebp-20h],ebx
    L_004574af:
        jne short L_004574d3
    L_004574b1:
        cmp esi,ebx
    L_004574b3:
        jne short L_004574b8
    L_004574b5:
        xor esi,esi
    L_004574b7:
        inc esi
    L_004574b8:
        add esi,0Fh
    L_004574bb:
        and esi,0FFFFFFF0h
    L_004574be:
        mov dword ptr [ebp+0Ch],esi
    L_004574c1:
        push esi
    L_004574c2:
        push edi
    L_004574c3:
        push ebx
    L_004574c4:
        push dword ptr [data_00499340]
    L_004574ca:
        call dword ptr [data_00466178]
    L_004574d0:
        mov dword ptr [ebp-1Ch],eax
    L_004574d3:
        mov eax,dword ptr [ebp-1Ch]
    L_004574d6:
        cmp eax,ebx
    L_004574d8:
        TH10_REL8(0x75, 0x004574d8, VA_asm_target_00457541)
    L_004574da:
        cmp dword ptr [data_00477364],ebx
    L_004574e0:
        TH10_REL8(0x74, 0x004574e0, VA_asm_target_00457541)
    L_004574e2:
        push esi
    L_004574e3:
        call asm_callnewh_00455737
    L_004574e8:
        pop ecx
    L_004574e9:
        test eax,eax
    L_004574eb:
        jne asm_target_004573d6
    L_004574f1:
        xor eax,eax
    L_004574f3:
        TH10_REL8(0xeb, 0x004574f3, VA_asm_target_00457541)
    }
}

// 0x00457506..0x00457546: FUN_00457395
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457395_part_00457506() {
    __asm {
    L_00457506:
        cmp esi,ebx
    L_00457508:
        jne short L_0045750d
    L_0045750a:
        xor esi,esi
    L_0045750c:
        inc esi
    L_0045750d:
        push esi
    L_0045750e:
        push edi
    L_0045750f:
        push ebx
    L_00457510:
        push dword ptr [data_00499340]
    L_00457516:
        call dword ptr [data_00466178]
    L_0045751c:
        cmp eax,ebx
    L_0045751e:
        jne short L_00457541
    L_00457520:
        cmp dword ptr [data_00477364],ebx
    L_00457526:
        je short L_00457541
    L_00457528:
        push esi
    L_00457529:
        call asm_callnewh_00455737
    L_0045752e:
        pop ecx
    L_0045752f:
        test eax,eax
    L_00457531:
        TH10_REL8(0x74, 0x00457531, VA_asm_target_004574f1)
    L_00457533:
        cmp esi,0FFFFFFE0h
    L_00457536:
        jbe short L_00457506
    L_00457538:
        push esi
    L_00457539:
        call asm_callnewh_00455737
    L_0045753e:
        xor eax,eax
    L_00457540:
        pop ecx
    L_00457541:
        call asm_SEH_epilog_00454bf7
    L_00457546:
        ret
    }
}

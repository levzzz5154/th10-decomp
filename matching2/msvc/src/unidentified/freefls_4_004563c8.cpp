#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004563C8..0x004564F4: __freefls@4
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_freefls_4_004563c8() {
    __asm {
    L_004563c8:
        push 10h
    L_004563ca:
        push 46AA18h
    L_004563cf:
        call asm_SEH_prolog_00454bbc
    L_004563d4:
        mov esi,dword ptr [ebp+8]
    L_004563d7:
        xor edi,edi
    L_004563d9:
        cmp esi,edi
    L_004563db:
        je asm_target_004564ed
    L_004563e1:
        mov eax,dword ptr [esi+24h]
    L_004563e4:
        cmp eax,edi
    L_004563e6:
        je short L_004563ef
    L_004563e8:
        push eax
    L_004563e9:
        call asm_free_00452422
    L_004563ee:
        pop ecx
    L_004563ef:
        mov eax,dword ptr [esi+2Ch]
    L_004563f2:
        cmp eax,edi
    L_004563f4:
        je short L_004563fd
    L_004563f6:
        push eax
    L_004563f7:
        call asm_free_00452422
    L_004563fc:
        pop ecx
    L_004563fd:
        mov eax,dword ptr [esi+34h]
    L_00456400:
        cmp eax,edi
    L_00456402:
        je short L_0045640b
    L_00456404:
        push eax
    L_00456405:
        call asm_free_00452422
    L_0045640a:
        pop ecx
    L_0045640b:
        mov eax,dword ptr [esi+3Ch]
    L_0045640e:
        cmp eax,edi
    L_00456410:
        je short L_00456419
    L_00456412:
        push eax
    L_00456413:
        call asm_free_00452422
    L_00456418:
        pop ecx
    L_00456419:
        mov eax,dword ptr [esi+44h]
    L_0045641c:
        cmp eax,edi
    L_0045641e:
        je short L_00456427
    L_00456420:
        push eax
    L_00456421:
        call asm_free_00452422
    L_00456426:
        pop ecx
    L_00456427:
        mov eax,dword ptr [esi+48h]
    L_0045642a:
        cmp eax,edi
    L_0045642c:
        je short L_00456435
    L_0045642e:
        push eax
    L_0045642f:
        call asm_free_00452422
    L_00456434:
        pop ecx
    L_00456435:
        mov eax,dword ptr [esi+54h]
    L_00456438:
        cmp eax,4735D0h
    L_0045643d:
        je short L_00456446
    L_0045643f:
        push eax
    L_00456440:
        call asm_free_00452422
    L_00456445:
        pop ecx
    L_00456446:
        push 0Dh
    L_00456448:
        call asm_lock_00453c0c
    L_0045644d:
        pop ecx
    L_0045644e:
        mov dword ptr [ebp-4],edi
    L_00456451:
        mov eax,dword ptr [esi+60h]
    L_00456454:
        mov dword ptr [ebp-1Ch],eax
    L_00456457:
        cmp eax,edi
    L_00456459:
        je short L_0045646e
    L_0045645b:
        dec dword ptr [eax]
    L_0045645d:
        jne short L_0045646e
    L_0045645f:
        cmp eax,dword ptr [data_00497f94]
    L_00456465:
        je short L_0045646e
    L_00456467:
        push eax
    L_00456468:
        call asm_free_00452422
    L_0045646d:
        pop ecx
    L_0045646e:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00456472:
        call asm_FUN_004564fa_004564fa
    L_00456477:
        push 0Ch
    L_00456479:
        call asm_lock_00453c0c
    L_0045647e:
        pop ecx
    L_0045647f:
        mov dword ptr [ebp-4],1
    L_00456486:
        mov eax,dword ptr [esi+64h]
    L_00456489:
        mov dword ptr [ebp-20h],eax
    L_0045648c:
        cmp eax,edi
    L_0045648e:
        je short L_004564dd
    L_00456490:
        dec dword ptr [eax]
    L_00456492:
        cmp dword ptr [eax+2Ch],edi
    L_00456495:
        je short L_0045649c
    L_00456497:
        mov ecx,dword ptr [eax+2Ch]
    L_0045649a:
        dec dword ptr [ecx]
    L_0045649c:
        cmp dword ptr [eax+34h],edi
    L_0045649f:
        je short L_004564a6
    L_004564a1:
        mov ecx,dword ptr [eax+34h]
    L_004564a4:
        dec dword ptr [ecx]
    L_004564a6:
        cmp dword ptr [eax+30h],edi
    L_004564a9:
        je short L_004564b0
    L_004564ab:
        mov ecx,dword ptr [eax+30h]
    L_004564ae:
        dec dword ptr [ecx]
    L_004564b0:
        cmp dword ptr [eax+40h],edi
    L_004564b3:
        je short L_004564ba
    L_004564b5:
        mov ecx,dword ptr [eax+40h]
    L_004564b8:
        dec dword ptr [ecx]
    L_004564ba:
        mov ecx,dword ptr [eax+4Ch]
    L_004564bd:
        dec dword ptr [ecx+0B4h]
    L_004564c3:
        cmp eax,dword ptr [data_0047320c]
    L_004564c9:
        je short L_004564dd
    L_004564cb:
        cmp eax,4731B8h
    L_004564d0:
        je short L_004564dd
    L_004564d2:
        cmp dword ptr [eax],edi
    L_004564d4:
        jne short L_004564dd
    L_004564d6:
        push eax
    L_004564d7:
        call asm_freetlocinfo_004557fc
    L_004564dc:
        pop ecx
    L_004564dd:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004564e1:
        call asm_FUN_00456506_00456506
    L_004564e6:
        push esi
    L_004564e7:
        call asm_free_00452422
    L_004564ec:
        pop ecx
    L_004564ed:
        call asm_SEH_epilog_00454bf7
    L_004564f2:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A52B..0x0045A75D: __Gettnames
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Gettnames_0045a52b() {
    __asm {
    L_0045a52b:
        push ebp
    L_0045a52c:
        mov ebp,esp
    L_0045a52e:
        sub esp,10h
    L_0045a531:
        push ebx
    L_0045a532:
        push esi
    L_0045a533:
        mov esi,dword ptr [data_004739e0]
    L_0045a539:
        push edi
    L_0045a53a:
        xor edi,edi
    L_0045a53c:
        mov dword ptr [ebp-4],edi
    L_0045a53f:
        mov ebx,dword ptr [ebp-4]
    L_0045a542:
        shl ebx,2
    L_0045a545:
        push dword ptr [ebx+esi+1Ch]
    L_0045a549:
        call asm_strlen_00456720
    L_0045a54e:
        push dword ptr [ebx+esi]
    L_0045a551:
        mov dword ptr [ebp-10h],eax
    L_0045a554:
        call asm_strlen_00456720
    L_0045a559:
        add eax,edi
    L_0045a55b:
        inc dword ptr [ebp-4]
    L_0045a55e:
        cmp dword ptr [ebp-4],7
    L_0045a562:
        pop ecx
    L_0045a563:
        pop ecx
    L_0045a564:
        mov ecx,dword ptr [ebp-10h]
    L_0045a567:
        lea edi,[eax+ecx+2]
    L_0045a56b:
        jb short L_0045a53f
    L_0045a56d:
        lea eax,[esi+38h]
    L_0045a570:
        mov dword ptr [ebp-0Ch],eax
    L_0045a573:
        mov dword ptr [ebp-8],0Ch
    L_0045a57a:
        mov ebx,dword ptr [ebp-0Ch]
    L_0045a57d:
        push dword ptr [ebx+30h]
    L_0045a580:
        call asm_strlen_00456720
    L_0045a585:
        push dword ptr [ebx]
    L_0045a587:
        mov dword ptr [ebp-10h],eax
    L_0045a58a:
        call asm_strlen_00456720
    L_0045a58f:
        add dword ptr [ebp-0Ch],4
    L_0045a593:
        pop ecx
    L_0045a594:
        pop ecx
    L_0045a595:
        mov ecx,dword ptr [ebp-10h]
    L_0045a598:
        add eax,edi
    L_0045a59a:
        dec dword ptr [ebp-8]
    L_0045a59d:
        lea edi,[eax+ecx+2]
    L_0045a5a1:
        jne short L_0045a57a
    L_0045a5a3:
        push dword ptr [esi+98h]
    L_0045a5a9:
        call asm_strlen_00456720
    L_0045a5ae:
        push dword ptr [esi+9Ch]
    L_0045a5b4:
        mov ebx,eax
    L_0045a5b6:
        call asm_strlen_00456720
    L_0045a5bb:
        push dword ptr [esi+0A0h]
    L_0045a5c1:
        add eax,edi
    L_0045a5c3:
        lea edi,[eax+ebx+2]
    L_0045a5c7:
        call asm_strlen_00456720
    L_0045a5cc:
        push dword ptr [esi+0A4h]
    L_0045a5d2:
        lea edi,[edi+eax+1]
    L_0045a5d6:
        call asm_strlen_00456720
    L_0045a5db:
        push dword ptr [esi+0A8h]
    L_0045a5e1:
        lea edi,[edi+eax+1]
    L_0045a5e5:
        call asm_strlen_00456720
    L_0045a5ea:
        lea eax,[edi+eax+1]
    L_0045a5ee:
        add eax,0B8h
    L_0045a5f3:
        push eax
    L_0045a5f4:
        call asm_malloc_00452706
    L_0045a5f9:
        mov ebx,eax
    L_0045a5fb:
        add esp,18h
    L_0045a5fe:
        test ebx,ebx
    L_0045a600:
        je asm_target_0045a757
    L_0045a606:
        push 0B8h
    L_0045a60b:
        push dword ptr [data_004739e0]
    L_0045a611:
        lea edi,[ebx+0B8h]
    L_0045a617:
        push ebx
    L_0045a618:
        call asm_memcpy_0045bfc0
    L_0045a61d:
        and dword ptr [ebp-4],0
    L_0045a621:
        lea eax,[esi+1Ch]
    L_0045a624:
        mov dword ptr [ebp-0Ch],ebx
    L_0045a627:
        add esp,0Ch
    L_0045a62a:
        sub dword ptr [ebp-0Ch],esi
    L_0045a62d:
        mov dword ptr [ebp-8],eax
    L_0045a630:
        mov eax,dword ptr [ebp-4]
    L_0045a633:
        mov dword ptr [ebx+eax*4],edi
    L_0045a636:
        mov eax,dword ptr [ebp-8]
    L_0045a639:
        push dword ptr [eax-1Ch]
    L_0045a63c:
        push edi
    L_0045a63d:
        call asm_FUN_0045bd80_0045bd80
    L_0045a642:
        push eax
    L_0045a643:
        call asm_strlen_00456720
    L_0045a648:
        mov ecx,dword ptr [ebp-0Ch]
    L_0045a64b:
        lea edi,[edi+eax+1]
    L_0045a64f:
        mov eax,dword ptr [ebp-8]
    L_0045a652:
        mov dword ptr [ecx+eax],edi
    L_0045a655:
        push dword ptr [eax]
    L_0045a657:
        push edi
    L_0045a658:
        call asm_FUN_0045bd80_0045bd80
    L_0045a65d:
        push eax
    L_0045a65e:
        call asm_strlen_00456720
    L_0045a663:
        add dword ptr [ebp-8],4
    L_0045a667:
        add esp,18h
    L_0045a66a:
        inc dword ptr [ebp-4]
    L_0045a66d:
        cmp dword ptr [ebp-4],7
    L_0045a671:
        lea edi,[edi+eax+1]
    L_0045a675:
        jb short L_0045a630
    L_0045a677:
        lea eax,[ebx+68h]
    L_0045a67a:
        mov dword ptr [ebp-4],eax
    L_0045a67d:
        lea eax,[esi+38h]
    L_0045a680:
        mov dword ptr [ebp-8],eax
    L_0045a683:
        mov dword ptr [ebp-10h],0Ch
    L_0045a68a:
        jmp short L_0045a68f
    L_0045a68c:
        mov eax,dword ptr [ebp-8]
    L_0045a68f:
        mov ecx,dword ptr [ebp-0Ch]
    L_0045a692:
        mov dword ptr [eax+ecx],edi
    L_0045a695:
        push dword ptr [eax]
    L_0045a697:
        push edi
    L_0045a698:
        call asm_FUN_0045bd80_0045bd80
    L_0045a69d:
        push eax
    L_0045a69e:
        call asm_strlen_00456720
    L_0045a6a3:
        lea edi,[edi+eax+1]
    L_0045a6a7:
        mov eax,dword ptr [ebp-4]
    L_0045a6aa:
        mov dword ptr [eax],edi
    L_0045a6ac:
        mov eax,dword ptr [ebp-8]
    L_0045a6af:
        push dword ptr [eax+30h]
    L_0045a6b2:
        push edi
    L_0045a6b3:
        call asm_FUN_0045bd80_0045bd80
    L_0045a6b8:
        push eax
    L_0045a6b9:
        call asm_strlen_00456720
    L_0045a6be:
        add dword ptr [ebp-8],4
    L_0045a6c2:
        add dword ptr [ebp-4],4
    L_0045a6c6:
        add esp,18h
    L_0045a6c9:
        dec dword ptr [ebp-10h]
    L_0045a6cc:
        lea edi,[edi+eax+1]
    L_0045a6d0:
        jne short L_0045a68c
    L_0045a6d2:
        mov dword ptr [ebx+98h],edi
    L_0045a6d8:
        push dword ptr [esi+98h]
    L_0045a6de:
        push edi
    L_0045a6df:
        call asm_FUN_0045bd80_0045bd80
    L_0045a6e4:
        push eax
    L_0045a6e5:
        call asm_strlen_00456720
    L_0045a6ea:
        lea edi,[edi+eax+1]
    L_0045a6ee:
        mov dword ptr [ebx+9Ch],edi
    L_0045a6f4:
        push dword ptr [esi+9Ch]
    L_0045a6fa:
        push edi
    L_0045a6fb:
        call asm_FUN_0045bd80_0045bd80
    L_0045a700:
        push eax
    L_0045a701:
        call asm_strlen_00456720
    L_0045a706:
        lea edi,[edi+eax+1]
    L_0045a70a:
        mov dword ptr [ebx+0A0h],edi
    L_0045a710:
        push dword ptr [esi+0A0h]
    L_0045a716:
        push edi
    L_0045a717:
        call asm_FUN_0045bd80_0045bd80
    L_0045a71c:
        push eax
    L_0045a71d:
        call asm_strlen_00456720
    L_0045a722:
        lea edi,[edi+eax+1]
    L_0045a726:
        mov dword ptr [ebx+0A4h],edi
    L_0045a72c:
        push dword ptr [esi+0A4h]
    L_0045a732:
        push edi
    L_0045a733:
        call asm_FUN_0045bd80_0045bd80
    L_0045a738:
        push eax
    L_0045a739:
        call asm_strlen_00456720
    L_0045a73e:
        lea eax,[edi+eax+1]
    L_0045a742:
        mov dword ptr [ebx+0A8h],eax
    L_0045a748:
        push dword ptr [esi+0A8h]
    L_0045a74e:
        push eax
    L_0045a74f:
        call asm_FUN_0045bd80_0045bd80
    L_0045a754:
        add esp,38h
    L_0045a757:
        pop edi
    L_0045a758:
        pop esi
    L_0045a759:
        mov eax,ebx
    L_0045a75b:
        pop ebx
    L_0045a75c:
        leave
    L_0045a75d:
        ret
    }
}

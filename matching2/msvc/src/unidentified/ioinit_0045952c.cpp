#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045952C..0x00459729: __ioinit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ioinit_0045952c() {
    __asm {
    L_0045952c:
        sub esp,48h
    L_0045952f:
        push ebx
    L_00459530:
        mov ebx,480h
    L_00459535:
        push ebx
    L_00459536:
        call asm_malloc_00452706
    L_0045953b:
        test eax,eax
    L_0045953d:
        pop ecx
    L_0045953e:
        jne short L_00459548
    L_00459540:
        or eax,0FFFFFFFFh
    L_00459543:
        jmp asm_target_00459725
    L_00459548:
        mov dword ptr [data_00499200],eax
    L_0045954d:
        mov dword ptr [data_004991e4],20h
    L_00459557:
        lea ecx,[eax+480h]
    L_0045955d:
        jmp short L_0045957d
    L_0045955f:
        or dword ptr [eax],0FFFFFFFFh
    L_00459562:
        and dword ptr [eax+8],0
    L_00459566:
        mov byte ptr [eax+4],0
    L_0045956a:
        mov byte ptr [eax+5],0Ah
    L_0045956e:
        mov ecx,dword ptr [data_00499200]
    L_00459574:
        add eax,24h
    L_00459577:
        add ecx,480h
    L_0045957d:
        cmp eax,ecx
    L_0045957f:
        jb short L_0045955f
    L_00459581:
        push ebp
    L_00459582:
        push esi
    L_00459583:
        push edi
    L_00459584:
        lea eax,[esp+14h]
    L_00459588:
        push eax
    L_00459589:
        call dword ptr [data_00466108]
    L_0045958f:
        cmp word ptr [esp+46h],0
    L_00459595:
        je asm_target_00459684
    L_0045959b:
        mov eax,dword ptr [esp+48h]
    L_0045959f:
        test eax,eax
    L_004595a1:
        je asm_target_00459684
    L_004595a7:
        mov edi,dword ptr [eax]
    L_004595a9:
        lea ebp,[eax+4]
    L_004595ac:
        lea eax,[edi+ebp]
    L_004595af:
        mov dword ptr [esp+10h],eax
    L_004595b3:
        mov eax,800h
    L_004595b8:
        cmp edi,eax
    L_004595ba:
        jl short L_004595be
    L_004595bc:
        mov edi,eax
    L_004595be:
        cmp dword ptr [data_004991e4],edi
    L_004595c4:
        jge short L_00459614
    L_004595c6:
        mov esi,499204h
    L_004595cb:
        push ebx
    L_004595cc:
        call asm_malloc_00452706
    L_004595d1:
        test eax,eax
    L_004595d3:
        pop ecx
    L_004595d4:
        je short L_0045960e
    L_004595d6:
        add dword ptr [data_004991e4],20h
    L_004595dd:
        mov dword ptr [esi],eax
    L_004595df:
        lea ecx,[eax+480h]
    L_004595e5:
        jmp short L_004595fd
    L_004595e7:
        or dword ptr [eax],0FFFFFFFFh
    L_004595ea:
        and dword ptr [eax+8],0
    L_004595ee:
        mov byte ptr [eax+4],0
    L_004595f2:
        mov byte ptr [eax+5],0Ah
    L_004595f6:
        mov ecx,dword ptr [esi]
    L_004595f8:
        add eax,24h
    L_004595fb:
        add ecx,ebx
    L_004595fd:
        cmp eax,ecx
    L_004595ff:
        jb short L_004595e7
    L_00459601:
        add esi,4
    L_00459604:
        cmp dword ptr [data_004991e4],edi
    L_0045960a:
        jl short L_004595cb
    L_0045960c:
        jmp short L_00459614
    L_0045960e:
        mov edi,dword ptr [data_004991e4]
    L_00459614:
        xor ebx,ebx
    L_00459616:
        test edi,edi
    L_00459618:
        jle short L_00459684
    L_0045961a:
        mov eax,dword ptr [esp+10h]
    L_0045961e:
        mov eax,dword ptr [eax]
    L_00459620:
        cmp eax,0FFFFFFFFh
    L_00459623:
        je short L_00459679
    L_00459625:
        mov cl,byte ptr [ebp]
    L_00459628:
        test cl,1
    L_0045962b:
        je short L_00459679
    L_0045962d:
        test cl,8
    L_00459630:
        jne short L_0045963d
    L_00459632:
        push eax
    L_00459633:
        call dword ptr [data_00466080]
    L_00459639:
        test eax,eax
    L_0045963b:
        je short L_00459679
    L_0045963d:
        mov ecx,ebx
    L_0045963f:
        mov eax,ebx
    L_00459641:
        and eax,1Fh
    L_00459644:
        lea eax,[eax+eax*8]
    L_00459647:
        sar ecx,5
    L_0045964a:
        mov ecx,dword ptr [ecx*4+499200h]
    L_00459651:
        lea esi,[ecx+eax*4]
    L_00459654:
        mov eax,dword ptr [esp+10h]
    L_00459658:
        mov eax,dword ptr [eax]
    L_0045965a:
        mov dword ptr [esi],eax
    L_0045965c:
        mov al,byte ptr [ebp]
    L_0045965f:
        mov byte ptr [esi+4],al
    L_00459662:
        lea eax,[esi+0Ch]
    L_00459665:
        push 0FA0h
    L_0045966a:
        push eax
    L_0045966b:
        call asm_crtInitCritSecAndSpinCount_0045980e
    L_00459670:
        test eax,eax
    L_00459672:
        pop ecx
    L_00459673:
        pop ecx
    L_00459674:
        je short L_004596a4
    L_00459676:
        inc dword ptr [esi+8]
    L_00459679:
        add dword ptr [esp+10h],4
    L_0045967e:
        inc ebx
    L_0045967f:
        inc ebp
    L_00459680:
        cmp ebx,edi
    L_00459682:
        jl short L_0045961a
    L_00459684:
        xor ebx,ebx
    L_00459686:
        mov ecx,dword ptr [data_00499200]
    L_0045968c:
        lea eax,[ebx+ebx*8]
    L_0045968f:
        lea esi,[ecx+eax*4]
    L_00459692:
        cmp dword ptr [esi],0FFFFFFFFh
    L_00459695:
        jne short L_00459706
    L_00459697:
        test ebx,ebx
    L_00459699:
        mov byte ptr [esi+4],81h
    L_0045969d:
        jne short L_004596a9
    L_0045969f:
        push 0FFFFFFF6h
    L_004596a1:
        pop eax
    L_004596a2:
        jmp short L_004596b3
    L_004596a4:
        or eax,0FFFFFFFFh
    L_004596a7:
        jmp short L_00459722
    L_004596a9:
        mov eax,ebx
    L_004596ab:
        dec eax
    L_004596ac:
        neg eax
    L_004596ae:
        sbb eax,eax
    L_004596b0:
        add eax,0FFFFFFF5h
    L_004596b3:
        push eax
    L_004596b4:
        call dword ptr [data_00466098]
    L_004596ba:
        mov edi,eax
    L_004596bc:
        cmp edi,0FFFFFFFFh
    L_004596bf:
        je short L_00459700
    L_004596c1:
        push edi
    L_004596c2:
        call dword ptr [data_00466080]
    L_004596c8:
        test eax,eax
    L_004596ca:
        je short L_00459700
    L_004596cc:
        and eax,0FFh
    L_004596d1:
        cmp eax,2
    L_004596d4:
        mov dword ptr [esi],edi
    L_004596d6:
        jne short L_004596de
    L_004596d8:
        or byte ptr [esi+4],40h
    L_004596dc:
        jmp short L_004596e7
    L_004596de:
        cmp eax,3
    L_004596e1:
        jne short L_004596e7
    L_004596e3:
        or byte ptr [esi+4],8
    L_004596e7:
        lea eax,[esi+0Ch]
    L_004596ea:
        push 0FA0h
    L_004596ef:
        push eax
    L_004596f0:
        call asm_crtInitCritSecAndSpinCount_0045980e
    L_004596f5:
        test eax,eax
    L_004596f7:
        pop ecx
    L_004596f8:
        pop ecx
    L_004596f9:
        je short L_004596a4
    L_004596fb:
        inc dword ptr [esi+8]
    L_004596fe:
        jmp short L_0045970a
    L_00459700:
        or byte ptr [esi+4],40h
    L_00459704:
        jmp short L_0045970a
    L_00459706:
        or byte ptr [esi+4],80h
    L_0045970a:
        inc ebx
    L_0045970b:
        cmp ebx,3
    L_0045970e:
        jl asm_target_00459686
    L_00459714:
        push dword ptr [data_004991e4]
    L_0045971a:
        call dword ptr [data_00466084]
    L_00459720:
        xor eax,eax
    L_00459722:
        pop edi
    L_00459723:
        pop esi
    L_00459724:
        pop ebp
    L_00459725:
        pop ebx
    L_00459726:
        add esp,48h
    L_00459729:
        ret
    }
}

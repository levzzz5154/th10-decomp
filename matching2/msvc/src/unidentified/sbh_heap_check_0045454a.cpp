#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045454A..0x00454862: ___sbh_heap_check
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sbh_heap_check_0045454a() {
    __asm {
    L_0045454a:
        push ebp
    L_0045454b:
        mov ebp,esp
    L_0045454d:
        sub esp,138h
    L_00454553:
        mov eax,dword ptr [data_00499328]
    L_00454558:
        lea eax,[eax+eax*4]
    L_0045455b:
        shl eax,2
    L_0045455e:
        push eax
    L_0045455f:
        push dword ptr [data_0049932c]
    L_00454565:
        call dword ptr [data_00466174]
    L_0045456b:
        test eax,eax
    L_0045456d:
        je short L_00454574
    L_0045456f:
        or eax,0FFFFFFFFh
    L_00454572:
        leave
    L_00454573:
        ret
    L_00454574:
        push ebx
    L_00454575:
        mov ebx,dword ptr [data_0049932c]
    L_0045457b:
        push esi
    L_0045457c:
        push edi
    L_0045457d:
        xor edi,edi
    L_0045457f:
        cmp dword ptr [data_00499328],edi
    L_00454585:
        mov dword ptr [ebp-34h],ebx
    L_00454588:
        mov dword ptr [ebp-1Ch],edi
    L_0045458b:
        jg short L_00454596
    L_0045458d:
        xor eax,eax
    L_0045458f:
        pop edi
    L_00454590:
        pop esi
    L_00454591:
        pop ebx
    L_00454592:
        leave
    L_00454593:
        ret
    L_00454594:
        xor edi,edi
    L_00454596:
        mov esi,dword ptr [ebx+10h]
    L_00454599:
        push 41C4h
    L_0045459e:
        push esi
    L_0045459f:
        call dword ptr [data_00466174]
    L_004545a5:
        test eax,eax
    L_004545a7:
        jne asm_target_00454823
    L_004545ad:
        mov eax,dword ptr [ebx+0Ch]
    L_004545b0:
        mov dword ptr [ebp-8],eax
    L_004545b3:
        lea eax,[esi+144h]
    L_004545b9:
        mov dword ptr [ebp-24h],eax
    L_004545bc:
        mov eax,dword ptr [ebx+8]
    L_004545bf:
        add esi,0C4h
    L_004545c5:
        mov dword ptr [ebp-20h],eax
    L_004545c8:
        mov dword ptr [ebp-10h],edi
    L_004545cb:
        mov dword ptr [ebp-14h],edi
    L_004545ce:
        mov dword ptr [ebp-0Ch],edi
    L_004545d1:
        mov dword ptr [ebp-38h],esi
    L_004545d4:
        jmp short L_004545d8
    L_004545d6:
        xor edi,edi
    L_004545d8:
        mov dword ptr [ebp-28h],edi
    L_004545db:
        mov dword ptr [ebp-18h],edi
    L_004545de:
        mov dword ptr [ebp-4],edi
    L_004545e1:
        push 40h
    L_004545e3:
        xor eax,eax
    L_004545e5:
        cmp dword ptr [ebp-20h],eax
    L_004545e8:
        pop ecx
    L_004545e9:
        lea edi,[ebp-138h]
    L_004545ef:
        rep stosd
    L_004545f1:
        jl asm_target_004547bc
    L_004545f7:
        push 8000h
    L_004545fc:
        push dword ptr [ebp-8]
    L_004545ff:
        call dword ptr [data_00466174]
    L_00454605:
        test eax,eax
    L_00454607:
        jne asm_target_0045482b
    L_0045460d:
        mov edx,dword ptr [ebp-8]
    L_00454610:
        xor ebx,ebx
    L_00454612:
        add edx,0FFCh
    L_00454618:
        cmp dword ptr [edx-0FF4h],0FFFFFFFFh
    L_0045461f:
        lea esi,[edx-0FF0h]
    L_00454625:
        jne asm_target_0045483b
    L_0045462b:
        cmp dword ptr [edx],0FFFFFFFFh
    L_0045462e:
        jne asm_target_0045483b
    L_00454634:
        mov ecx,dword ptr [esi]
    L_00454636:
        test cl,1
    L_00454639:
        mov edi,ecx
    L_0045463b:
        je short L_0045464f
    L_0045463d:
        dec ecx
    L_0045463e:
        cmp ecx,400h
    L_00454644:
        jg asm_target_0045482f
    L_0045464a:
        inc dword ptr [ebp-4]
    L_0045464d:
        jmp short L_00454666
    L_0045464f:
        mov eax,ecx
    L_00454651:
        sar eax,4
    L_00454654:
        dec eax
    L_00454655:
        cmp eax,3Fh
    L_00454658:
        jle short L_0045465d
    L_0045465a:
        push 3Fh
    L_0045465c:
        pop eax
    L_0045465d:
        lea eax,[ebp+eax*4-138h]
    L_00454664:
        inc dword ptr [eax]
    L_00454666:
        cmp ecx,10h
    L_00454669:
        jl asm_target_00454837
    L_0045466f:
        test cl,0Fh
    L_00454672:
        jne asm_target_00454837
    L_00454678:
        cmp ecx,0FF0h
    L_0045467e:
        jg asm_target_00454837
    L_00454684:
        lea eax,[ecx+esi]
    L_00454687:
        cmp dword ptr [eax-4],edi
    L_0045468a:
        jne asm_target_00454833
    L_00454690:
        mov esi,eax
    L_00454692:
        cmp esi,edx
    L_00454694:
        jb short L_00454634
    L_00454696:
        jne asm_target_00454833
    L_0045469c:
        add edx,1000h
    L_004546a2:
        inc ebx
    L_004546a3:
        cmp ebx,8
    L_004546a6:
        jl asm_target_00454618
    L_004546ac:
        mov eax,dword ptr [ebp-4]
    L_004546af:
        mov edi,dword ptr [ebp-24h]
    L_004546b2:
        cmp dword ptr [edi],eax
    L_004546b4:
        jne asm_target_0045483f
    L_004546ba:
        xor esi,esi
    L_004546bc:
        and dword ptr [ebp-4],0
    L_004546c0:
        lea ebx,[edi+8]
    L_004546c3:
        mov eax,dword ptr [ebx-4]
    L_004546c6:
        cmp eax,edi
    L_004546c8:
        mov dword ptr [ebp-2Ch],edi
    L_004546cb:
        mov dword ptr [ebp-30h],ebx
    L_004546ce:
        je asm_target_00454786
    L_004546d4:
        mov ecx,dword ptr [ebp-4]
    L_004546d7:
        cmp ecx,dword ptr [ebp+esi*4-138h]
    L_004546de:
        je short L_0045475f
    L_004546e0:
        mov ecx,dword ptr [ebp-8]
    L_004546e3:
        cmp eax,ecx
    L_004546e5:
        jb asm_target_0045484f
    L_004546eb:
        add ecx,8000h
    L_004546f1:
        cmp eax,ecx
    L_004546f3:
        jae asm_target_0045484f
    L_004546f9:
        mov ecx,eax
    L_004546fb:
        and ecx,0FFFFF000h
    L_00454701:
        add ecx,0Ch
    L_00454704:
        lea edx,[ecx+0FF0h]
    L_0045470a:
        cmp ecx,edx
    L_0045470c:
        je asm_target_00454843
    L_00454712:
        cmp ecx,eax
    L_00454714:
        je short L_00454724
    L_00454716:
        mov ebx,dword ptr [ecx]
    L_00454718:
        and ebx,0FFFFFFFEh
    L_0045471b:
        add ecx,ebx
    L_0045471d:
        cmp ecx,edx
    L_0045471f:
        mov ebx,dword ptr [ebp-30h]
    L_00454722:
        jne short L_00454712
    L_00454724:
        cmp ecx,edx
    L_00454726:
        je asm_target_00454843
    L_0045472c:
        mov ecx,dword ptr [eax]
    L_0045472e:
        sar ecx,4
    L_00454731:
        dec ecx
    L_00454732:
        cmp ecx,3Fh
    L_00454735:
        jle short L_0045473a
    L_00454737:
        push 3Fh
    L_00454739:
        pop ecx
    L_0045473a:
        cmp ecx,esi
    L_0045473c:
        jne asm_target_00454847
    L_00454742:
        mov ecx,dword ptr [ebp-2Ch]
    L_00454745:
        cmp dword ptr [eax+8],ecx
    L_00454748:
        jne asm_target_0045484b
    L_0045474e:
        inc dword ptr [ebp-4]
    L_00454751:
        mov dword ptr [ebp-2Ch],eax
    L_00454754:
        mov eax,dword ptr [eax+4]
    L_00454757:
        cmp eax,edi
    L_00454759:
        jne asm_target_004546d4
    L_0045475f:
        cmp dword ptr [ebp-4],0
    L_00454763:
        je short L_00454786
    L_00454765:
        cmp esi,20h
    L_00454768:
        mov eax,80000000h
    L_0045476d:
        jge short L_0045477b
    L_0045476f:
        mov ecx,esi
    L_00454771:
        shr eax,cl
    L_00454773:
        or dword ptr [ebp-28h],eax
    L_00454776:
        or dword ptr [ebp-10h],eax
    L_00454779:
        jmp short L_00454786
    L_0045477b:
        lea ecx,[esi-20h]
    L_0045477e:
        shr eax,cl
    L_00454780:
        or dword ptr [ebp-18h],eax
    L_00454783:
        or dword ptr [ebp-14h],eax
    L_00454786:
        mov eax,dword ptr [ebp-2Ch]
    L_00454789:
        cmp dword ptr [eax+4],edi
    L_0045478c:
        jne asm_target_00454857
    L_00454792:
        mov ecx,dword ptr [ebp-4]
    L_00454795:
        cmp ecx,dword ptr [ebp+esi*4-138h]
    L_0045479c:
        jne asm_target_00454857
    L_004547a2:
        cmp dword ptr [ebx],eax
    L_004547a4:
        jne asm_target_00454853
    L_004547aa:
        inc esi
    L_004547ab:
        cmp esi,40h
    L_004547ae:
        mov edi,ebx
    L_004547b0:
        jl asm_target_004546bc
    L_004547b6:
        mov esi,dword ptr [ebp-38h]
    L_004547b9:
        mov ebx,dword ptr [ebp-34h]
    L_004547bc:
        mov eax,dword ptr [ebp-28h]
    L_004547bf:
        cmp eax,dword ptr [esi-80h]
    L_004547c2:
        jne asm_target_0045485b
    L_004547c8:
        mov eax,dword ptr [ebp-18h]
    L_004547cb:
        cmp eax,dword ptr [esi]
    L_004547cd:
        jne asm_target_0045485b
    L_004547d3:
        add dword ptr [ebp-8],8000h
    L_004547da:
        add dword ptr [ebp-24h],204h
    L_004547e1:
        shl dword ptr [ebp-20h],1
    L_004547e4:
        inc dword ptr [ebp-0Ch]
    L_004547e7:
        add esi,4
    L_004547ea:
        cmp dword ptr [ebp-0Ch],20h
    L_004547ee:
        mov dword ptr [ebp-38h],esi
    L_004547f1:
        jl asm_target_004545d6
    L_004547f7:
        mov eax,dword ptr [ebp-10h]
    L_004547fa:
        cmp eax,dword ptr [ebx]
    L_004547fc:
        jne short L_0045485f
    L_004547fe:
        mov eax,dword ptr [ebp-14h]
    L_00454801:
        cmp eax,dword ptr [ebx+4]
    L_00454804:
        jne short L_0045485f
    L_00454806:
        add ebx,14h
    L_00454809:
        inc dword ptr [ebp-1Ch]
    L_0045480c:
        mov eax,dword ptr [ebp-1Ch]
    L_0045480f:
        cmp eax,dword ptr [data_00499328]
    L_00454815:
        mov dword ptr [ebp-34h],ebx
    L_00454818:
        jl asm_target_00454594
    L_0045481e:
        jmp asm_target_0045458d
    L_00454823:
        push 0FFFFFFFEh
    L_00454825:
        pop eax
    L_00454826:
        jmp asm_target_0045458f
    L_0045482b:
        push 0FFFFFFFCh
    L_0045482d:
        jmp short L_00454825
    L_0045482f:
        push 0FFFFFFFAh
    L_00454831:
        jmp short L_00454825
    L_00454833:
        push 0FFFFFFF8h
    L_00454835:
        jmp short L_00454825
    L_00454837:
        push 0FFFFFFF9h
    L_00454839:
        jmp short L_00454825
    L_0045483b:
        push 0FFFFFFFBh
    L_0045483d:
        jmp short L_00454825
    L_0045483f:
        push 0FFFFFFF7h
    L_00454841:
        jmp short L_00454825
    L_00454843:
        push 0FFFFFFF5h
    L_00454845:
        jmp short L_00454825
    L_00454847:
        push 0FFFFFFF4h
    L_00454849:
        jmp short L_00454825
    L_0045484b:
        push 0FFFFFFF3h
    L_0045484d:
        jmp short L_00454825
    L_0045484f:
        push 0FFFFFFF6h
    L_00454851:
        jmp short L_00454825
    L_00454853:
        push 0FFFFFFF1h
    L_00454855:
        jmp short L_00454825
    L_00454857:
        push 0FFFFFFF2h
    L_00454859:
        jmp short L_00454825
    L_0045485b:
        push 0FFFFFFF0h
    L_0045485d:
        jmp short L_00454825
    L_0045485f:
        push 0FFFFFFEFh
    L_00454861:
        jmp short L_00454825
    }
}

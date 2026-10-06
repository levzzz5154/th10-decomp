// NOT EXACT: the ordinary member candidate emits 834/850 bytes in a native
// LTCG graph with the complete centred formatter (194/194 exact) and text
// dispatcher (127/127 exact). The first non-branch difference is the blank
// loop's counter register at +0xAE; the named-card path keeps the lookup
// result in ESI instead of EAX. Loading the manager before the terminator
// gives 850 bytes but moves the menu to EBX and still does not match.
// See reference/recovery_notes/title_spell_list_native_2026_10_06.md and
// reference/semantic_candidates/title_spell_list_00432690/probe.py.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00432690..0x0043271C: FUN_00432690
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00432690_00432690() {
    __asm {
    L_00432690:
        sub esp,0C0h
    L_00432696:
        mov eax,dword ptr [data_00473660]
    L_0043269b:
        xor eax,esp
    L_0043269d:
        push ebx
    L_0043269e:
        push ebp
    L_0043269f:
        push esi
    L_004326a0:
        mov esi,ecx
    L_004326a2:
        mov dword ptr [esp+0C8h],eax
    L_004326a9:
        mov eax,dword ptr [esi+1D4h]
    L_004326af:
        lea eax,[eax+eax*4]
    L_004326b2:
        push edi
    L_004326b3:
        xor edi,edi
    L_004326b5:
        lea edx,[eax+eax-0Ah]
    L_004326b9:
        xor ecx,ecx
    L_004326bb:
        test edx,edx
    L_004326bd:
        mov dword ptr [esp+1Ch],esi
    L_004326c1:
        mov dword ptr [esp+14h],edi
    L_004326c5:
        jle short L_004326f5
    L_004326c7:
        mov eax,dword ptr [esi+1D4h]
    L_004326cd:
        mov edx,dword ptr [esi+0FCh]
    L_004326d3:
        lea eax,[eax+eax*4]
    L_004326d6:
        lea eax,[eax+eax-0Ah]
    L_004326da:
        lea ebx,[ebx+force_disp32_zero]
    L_004326e0:
        movsx ebx,byte ptr [edi+4743C0h]
    L_004326e7:
        cmp ebx,edx
    L_004326e9:
        jne short L_004326ec
    L_004326eb:
        inc ecx
    L_004326ec:
        inc edi
    L_004326ed:
        cmp ecx,eax
    L_004326ef:
        jl short L_004326e0
    L_004326f1:
        mov dword ptr [esp+14h],edi
    L_004326f5:
        xor ecx,ecx
    L_004326f7:
        lea eax,[esi+5D4h]
    L_004326fd:
        mov dword ptr [esi+2ACh],0
    L_00432707:
        mov dword ptr [esp+18h],ecx
    L_0043270b:
        mov dword ptr [esp+10h],eax
    L_0043270f:
        nop
    L_00432710:
        cmp edi,6Eh
    L_00432713:
        TH10_REL8(0x7d, 0x00432713, VA_asm_target_00432735)
    L_00432715:
        mov eax,dword ptr [esi+0FCh]
    L_0043271b:
        TH10_REL8(0xeb, 0x0043271b, VA_asm_FUN_00432690_part_00432720)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00432720:
        movsx edx,byte ptr [edi+4743C0h]
    L_00432727:
        cmp edx,eax
    L_00432729:
        je short L_00432767
    L_0043272b:
        inc edi
    L_0043272c:
        cmp edi,6Eh
    L_0043272f:
        mov dword ptr [esp+14h],edi
    L_00432733:
        jl short L_00432720
    L_00432735:
        cmp ecx,0Ah
    L_00432738:
        jge asm_target_004329c7
    L_0043273e:
        mov ebx,0Ah
    L_00432743:
        lea edi,[esi+ecx*4+5D4h]
    L_0043274a:
        sub ebx,ecx
    L_0043274c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00432750:
        mov ecx,dword ptr [edi]
    L_00432752:
        test ecx,ecx
    L_00432754:
        mov edx,dword ptr [data_00491c10]
    L_0043275a:
        jne asm_target_0043295f
    L_00432760:
        xor eax,eax
    L_00432762:
        jmp asm_target_004329a5
    L_00432767:
        cmp edi,6Eh
    L_0043276a:
        jge short L_00432735
    L_0043276c:
        mov ebp,dword ptr [data_0047783c]
    L_00432772:
        lea ebx,[edi+edi*8]
    L_00432775:
        shl ebx,4
    L_00432778:
        mov eax,dword ptr [ebx+ebp+19B10h]
    L_0043277f:
        test eax,eax
    L_00432781:
        mov dword ptr [esp+20h],ebx
    L_00432785:
        je asm_target_0043289c
    L_0043278b:
        lea eax,[ebx+ebp+19A8Ch]
    L_00432792:
        lea edx,[esp+24h]
    L_00432796:
        sub edx,eax
    L_00432798:
        mov cl,byte ptr [eax]
    L_0043279a:
        mov byte ptr [edx+eax],cl
    L_0043279d:
        inc eax
    L_0043279e:
        test cl,cl
    L_004327a0:
        jne short L_00432798
    L_004327a2:
        lea edx,[esp+24h]
    L_004327a6:
        lea ecx,[edx+1]
    L_004327a9:
        lea esp,[esp+force_disp32_zero]
    L_004327b0:
        mov al,byte ptr [edx]
    L_004327b2:
        inc edx
    L_004327b3:
        test al,al
    L_004327b5:
        jne short L_004327b0
    L_004327b7:
        sub edx,ecx
    L_004327b9:
        cmp edx,2Ah
    L_004327bc:
        jge short L_004327ec
    L_004327be:
        mov esi,2Ah
    L_004327c3:
        sub esi,edx
    L_004327c5:
        mov ecx,esi
    L_004327c7:
        mov ebx,ecx
    L_004327c9:
        shr ecx,2
    L_004327cc:
        lea edi,[esp+edx+24h]
    L_004327d0:
        mov eax,20202020h
    L_004327d5:
        rep stosd
    L_004327d7:
        mov ecx,ebx
    L_004327d9:
        mov ebx,dword ptr [esp+20h]
    L_004327dd:
        and ecx,3
    L_004327e0:
        rep stosb
    L_004327e2:
        mov edi,dword ptr [esp+14h]
    L_004327e6:
        add edx,esi
    L_004327e8:
        mov esi,dword ptr [esp+1Ch]
    L_004327ec:
        mov eax,dword ptr [esi+24h]
    L_004327ef:
        mov esi,dword ptr [data_00491c10]
    L_004327f5:
        imul eax,437Ch
    L_004327fb:
        mov byte ptr [esp+edx+24h],0
    L_00432800:
        mov edx,dword ptr [esp+10h]
    L_00432804:
        mov edx,dword ptr [edx]
    L_00432806:
        test edx,edx
    L_00432808:
        lea ecx,[eax+ebp+8]
    L_0043280c:
        jne short L_00432812
    L_0043280e:
        xor eax,eax
    L_00432810:
        jmp short L_0043284e
    L_00432812:
        mov eax,dword ptr [esi+72DAD4h]
    L_00432818:
        test eax,eax
    L_0043281a:
        je short L_0043282e
    L_0043281c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00432820:
        mov ebp,dword ptr [eax]
    L_00432822:
        cmp dword ptr [ebp],edx
    L_00432825:
        je short L_00432848
    L_00432827:
        mov eax,dword ptr [eax+4]
    L_0043282a:
        test eax,eax
    L_0043282c:
        jne short L_00432820
    L_0043282e:
        mov eax,dword ptr [esi+72DADCh]
    L_00432834:
        test eax,eax
    L_00432836:
        je short L_0043280e
    L_00432838:
        mov ebp,dword ptr [eax]
    L_0043283a:
        cmp dword ptr [ebp],edx
    L_0043283d:
        je short L_00432848
    L_0043283f:
        mov eax,dword ptr [eax+4]
    L_00432842:
        test eax,eax
    L_00432844:
        jne short L_00432838
    L_00432846:
        jmp short L_0043284e
    L_00432848:
        mov eax,dword ptr [eax]
    L_0043284a:
        test eax,eax
    L_0043284c:
        jne short L_00432858
    L_0043284e:
        mov edx,dword ptr [esp+10h]
    L_00432852:
        mov dword ptr [edx],0
    L_00432858:
        mov edx,dword ptr [ebx+ecx+620h]
    L_0043285f:
        push edx
    L_00432860:
        mov edx,dword ptr [ebx+ecx+61Ch]
    L_00432867:
        mov ecx,dword ptr [ebx+ecx+61Ch]
    L_0043286e:
        push edx
    L_0043286f:
        inc edi
    L_00432870:
        neg ecx
    L_00432872:
        lea edx,[esp+2Ch]
    L_00432876:
        push edx
    L_00432877:
        sbb ecx,ecx
    L_00432879:
        push edi
    L_0043287a:
        and ecx,100F91h
    L_00432880:
        push 46EEF8h
    L_00432885:
        add ecx,0EFEFEFh
    L_0043288b:
        push ecx
    L_0043288c:
        push esi
    L_0043288d:
        mov esi,eax
    L_0043288f:
        call asm_FUN_00447bb0_00447bb0
    L_00432894:
        add esp,1Ch
    L_00432897:
        jmp asm_target_00432926
    L_0043289c:
        mov edx,dword ptr [esi+24h]
    L_0043289f:
        mov eax,dword ptr [esp+10h]
    L_004328a3:
        imul edx,437Ch
    L_004328a9:
        mov ecx,dword ptr [eax]
    L_004328ab:
        test ecx,ecx
    L_004328ad:
        lea ebp,[edx+ebp+8]
    L_004328b1:
        mov edx,dword ptr [data_00491c10]
    L_004328b7:
        jne short L_004328bd
    L_004328b9:
        xor eax,eax
    L_004328bb:
        jmp short L_004328f5
    L_004328bd:
        mov eax,dword ptr [edx+72DAD4h]
    L_004328c3:
        test eax,eax
    L_004328c5:
        je short L_004328d4
    L_004328c7:
        mov esi,dword ptr [eax]
    L_004328c9:
        cmp dword ptr [esi],ecx
    L_004328cb:
        je short L_004328ef
    L_004328cd:
        mov eax,dword ptr [eax+4]
    L_004328d0:
        test eax,eax
    L_004328d2:
        jne short L_004328c7
    L_004328d4:
        mov eax,dword ptr [edx+72DADCh]
    L_004328da:
        test eax,eax
    L_004328dc:
        je short L_004328b9
    L_004328de:
        mov edi,edi
    L_004328e0:
        mov esi,dword ptr [eax]
    L_004328e2:
        cmp dword ptr [esi],ecx
    L_004328e4:
        je short L_004328ef
    L_004328e6:
        mov eax,dword ptr [eax+4]
    L_004328e9:
        test eax,eax
    L_004328eb:
        jne short L_004328e0
    L_004328ed:
        jmp short L_004328f5
    L_004328ef:
        mov eax,dword ptr [eax]
    L_004328f1:
        test eax,eax
    L_004328f3:
        jne short L_004328ff
    L_004328f5:
        mov ecx,dword ptr [esp+10h]
    L_004328f9:
        mov dword ptr [ecx],0
    L_004328ff:
        mov ecx,dword ptr [ebx+ebp+620h]
    L_00432906:
        push ecx
    L_00432907:
        mov ecx,dword ptr [ebx+ebp+61Ch]
    L_0043290e:
        push ecx
    L_0043290f:
        inc edi
    L_00432910:
        push edi
    L_00432911:
        push 46EEBCh
    L_00432916:
        push 808080h
    L_0043291b:
        push edx
    L_0043291c:
        mov esi,eax
    L_0043291e:
        call asm_FUN_00447bb0_00447bb0
    L_00432923:
        add esp,18h
    L_00432926:
        mov eax,dword ptr [esp+1Ch]
    L_0043292a:
        mov ebx,dword ptr [eax+2ACh]
    L_00432930:
        mov edx,dword ptr [esp+10h]
    L_00432934:
        inc ebx
    L_00432935:
        mov dword ptr [eax+2ACh],ebx
    L_0043293b:
        mov eax,dword ptr [esp+18h]
    L_0043293f:
        inc eax
    L_00432940:
        add edx,4
    L_00432943:
        cmp eax,0Ah
    L_00432946:
        mov dword ptr [esp+14h],edi
    L_0043294a:
        mov dword ptr [esp+18h],eax
    L_0043294e:
        mov dword ptr [esp+10h],edx
    L_00432952:
        TH10_REL8(0x7d, 0x00432952, VA_asm_target_004329c7)
    L_00432954:
        mov esi,dword ptr [esp+1Ch]
    L_00432958:
        mov ecx,eax
    L_0043295a:
        jmp asm_target_00432710
    L_0043295f:
        mov eax,dword ptr [edx+72DAD4h]
    L_00432965:
        test eax,eax
    L_00432967:
        je short L_0043297d
    L_00432969:
        lea esp,[esp+force_disp32_zero]
    L_00432970:
        mov esi,dword ptr [eax]
    L_00432972:
        cmp dword ptr [esi],ecx
    L_00432974:
        TH10_REL8(0x74, 0x00432974, VA_asm_target_0043299f)
    L_00432976:
        mov eax,dword ptr [eax+4]
    L_00432979:
        test eax,eax
    L_0043297b:
        jne short L_00432970
    L_0043297d:
        mov eax,dword ptr [edx+72DADCh]
    L_00432983:
        test eax,eax
    L_00432985:
        je asm_target_00432760
    L_0043298b:
        TH10_REL8(0xeb, 0x0043298b, VA_asm_FUN_00432690_part_00432990)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00432990:
        mov esi,dword ptr [eax]
    L_00432992:
        cmp dword ptr [esi],ecx
    L_00432994:
        je short L_0043299f
    L_00432996:
        mov eax,dword ptr [eax+4]
    L_00432999:
        test eax,eax
    L_0043299b:
        jne short L_00432990
    L_0043299d:
        jmp short L_004329a5
    L_0043299f:
        mov eax,dword ptr [eax]
    L_004329a1:
        test eax,eax
    L_004329a3:
        jne short L_004329ab
    L_004329a5:
        mov dword ptr [edi],0
    L_004329ab:
        push 46CFD4h
    L_004329b0:
        push 0FFFFFFFFh
    L_004329b2:
        push edx
    L_004329b3:
        mov esi,eax
    L_004329b5:
        call asm_FUN_00447bb0_00447bb0
    L_004329ba:
        add esp,0Ch
    L_004329bd:
        add edi,4
    L_004329c0:
        dec ebx
    L_004329c1:
        jne asm_target_00432750
    L_004329c7:
        mov ecx,dword ptr [esp+0CCh]
    L_004329ce:
        pop edi
    L_004329cf:
        pop esi
    L_004329d0:
        pop ebp
    L_004329d1:
        pop ebx
    L_004329d2:
        xor ecx,esp
    L_004329d4:
        xor eax,eax
    L_004329d6:
        call asm_security_check_cookie_00458ea5
    L_004329db:
        add esp,0C0h
    L_004329e1:
        ret
    }
}

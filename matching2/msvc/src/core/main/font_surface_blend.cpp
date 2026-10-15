// BLOCKED (H2501): closest_byte_count=645; first_diff=unmeasured;
// residual_class=unexpressible promoted ABI: retail enters with row in EAX,
// mask in EDX, column in ECX and ret 0xC, while every faithful candidate
// promotes only two values and leaves the third on the stack;
// variants_tested=85 native-LTCG contexts, declaration/parameter/calling-
// convention permutations, dispatch forms, member/free forms, and liveness
// variants;
// next_lever=raise register pressure with a semantically faithful body form
// that promotes all three retail parameters, or use a toolkit with that ABI
// promotion; no caller can constrain it because the image has no caller.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00437750..0x004379D4: FUN_00437750
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00437750_00437750() {
    __asm {
    L_00437750:
        sub esp,48h
    L_00437753:
        push ebx
    L_00437754:
        push ebp
    L_00437755:
        mov ebp,dword ptr [esp+5Ch]
    L_00437759:
        push esi
    L_0043775a:
        push edi
    L_0043775b:
        mov esi,edx
    L_0043775d:
        mov edi,eax
    L_0043775f:
        mov eax,dword ptr [esi+11Ch]
    L_00437765:
        test eax,eax
    L_00437767:
        mov ebx,ecx
    L_00437769:
        je asm_target_004377f2
    L_0043776f:
        mov eax,dword ptr [esp+5Ch]
    L_00437773:
        mov ecx,dword ptr [eax]
    L_00437775:
        lea edx,[esp+38h]
    L_00437779:
        push edx
    L_0043777a:
        push eax
    L_0043777b:
        call dword ptr [ecx+30h]
    L_0043777e:
        mov eax,dword ptr [esi+104h]
    L_00437784:
        mov edx,dword ptr [esi+108h]
    L_0043778a:
        xor ecx,ecx
    L_0043778c:
        push ecx
    L_0043778d:
        mov dword ptr [esp+2Ch],ecx
    L_00437791:
        mov dword ptr [esp+30h],ecx
    L_00437795:
        lea ecx,[esp+2Ch]
    L_00437799:
        push ecx
    L_0043779a:
        lea ecx,[esp+28h]
    L_0043779e:
        mov dword ptr [esp+38h],eax
    L_004377a2:
        mov eax,dword ptr [esp+64h]
    L_004377a6:
        push ecx
    L_004377a7:
        mov dword ptr [esp+40h],edx
    L_004377ab:
        mov edx,dword ptr [eax]
    L_004377ad:
        push eax
    L_004377ae:
        call dword ptr [edx+34h]
    L_004377b1:
        test eax,eax
    L_004377b3:
        jne short L_004377f2
    L_004377b5:
        mov edx,dword ptr [esi+110h]
    L_004377bb:
        mov ecx,dword ptr [esi+120h]
    L_004377c1:
        mov esi,dword ptr [esi+100h]
    L_004377c7:
        mov eax,dword ptr [esp+20h]
    L_004377cb:
        mov dword ptr [esp+64h],edx
    L_004377cf:
        cmp dword ptr [esp+38h],esi
    L_004377d3:
        mov dword ptr [esp+10h],eax
    L_004377d7:
        jne asm_target_004379bf
    L_004377dd:
        sub esi,15h
    L_004377e0:
        je asm_target_00437930
    L_004377e6:
        sub esi,4
    L_004377e9:
        je asm_target_004378e0
    L_004377ef:
        dec esi
    L_004377f0:
        je short L_004377fe
    L_004377f2:
        pop edi
    L_004377f3:
        pop esi
    L_004377f4:
        pop ebp
    L_004377f5:
        xor al,al
    L_004377f7:
        pop ebx
    L_004377f8:
        add esp,48h
    L_004377fb:
        ret 0Ch
    L_004377fe:
        mov edx,dword ptr [esp+24h]
    L_00437802:
        imul eax,edi
    L_00437805:
        add eax,edx
    L_00437807:
        test ebp,ebp
    L_00437809:
        lea edi,[eax+ebx*2]
    L_0043780c:
        jle asm_target_004379bf
    L_00437812:
        mov dword ptr [esp+18h],ebp
    L_00437816:
        mov edx,dword ptr [esp+60h]
    L_0043781a:
        xor eax,eax
    L_0043781c:
        test edx,edx
    L_0043781e:
        jle asm_target_004378ba
    L_00437824:
        mov dword ptr [esp+14h],edx
    L_00437828:
        mov dword ptr [esp+1Ch],edx
    L_0043782c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00437830:
        movzx edx,byte ptr [edi]
    L_00437833:
        movzx eax,byte ptr [ecx]
    L_00437836:
        movzx esi,byte ptr [ecx+1]
    L_0043783a:
        shr eax,4
    L_0043783d:
        shr edx,4
    L_00437840:
        sub eax,edx
    L_00437842:
        shr esi,4
    L_00437845:
        imul eax,esi
    L_00437848:
        sar eax,4
    L_0043784b:
        add al,dl
    L_0043784d:
        shl al,4
    L_00437850:
        mov byte ptr [edi],al
    L_00437852:
        xor edx,edx
    L_00437854:
        mov dl,byte ptr [ecx]
    L_00437856:
        xor ebx,ebx
    L_00437858:
        and eax,0Fh
    L_0043785b:
        and edx,0Fh
    L_0043785e:
        sub edx,eax
    L_00437860:
        imul edx,esi
    L_00437863:
        sar edx,4
    L_00437866:
        add dl,al
    L_00437868:
        or byte ptr [edi],dl
    L_0043786a:
        movzx eax,byte ptr [edi+1]
    L_0043786e:
        mov bl,byte ptr [ecx+1]
    L_00437871:
        mov edx,eax
    L_00437873:
        shr eax,2
    L_00437876:
        and eax,3Ch
    L_00437879:
        add eax,esi
    L_0043787b:
        and edx,0Fh
    L_0043787e:
        and ebx,0Fh
    L_00437881:
        cmp eax,10h
    L_00437884:
        mov ebp,ebx
    L_00437886:
        jl short L_0043788d
    L_00437888:
        mov eax,0Fh
    L_0043788d:
        mov ebx,ebp
    L_0043788f:
        sub ebx,edx
    L_00437891:
        imul ebx,esi
    L_00437894:
        sar ebx,4
    L_00437897:
        shl al,4
    L_0043789a:
        add bl,dl
    L_0043789c:
        or bl,al
    L_0043789e:
        mov eax,dword ptr [esp+14h]
    L_004378a2:
        mov byte ptr [edi+1],bl
    L_004378a5:
        add edi,2
    L_004378a8:
        add ecx,2
    L_004378ab:
        dec eax
    L_004378ac:
        mov dword ptr [esp+14h],eax
    L_004378b0:
        jne asm_target_00437830
    L_004378b6:
        mov eax,dword ptr [esp+1Ch]
    L_004378ba:
        mov edx,dword ptr [esp+64h]
    L_004378be:
        add eax,eax
    L_004378c0:
        sub edx,eax
    L_004378c2:
        add ecx,edx
    L_004378c4:
        mov edx,dword ptr [esp+10h]
    L_004378c8:
        sub edx,eax
    L_004378ca:
        mov eax,dword ptr [esp+18h]
    L_004378ce:
        add edi,edx
    L_004378d0:
        dec eax
    L_004378d1:
        mov dword ptr [esp+18h],eax
    L_004378d5:
        jne asm_target_00437816
    L_004378db:
        jmp asm_target_004379bf
    L_004378e0:
        mov esi,dword ptr [esp+24h]
    L_004378e4:
        imul eax,edi
    L_004378e7:
        add eax,esi
    L_004378e9:
        test ebp,ebp
    L_004378eb:
        lea eax,[eax+ebx*2]
    L_004378ee:
        jle asm_target_004379bf
    L_004378f4:
        mov edx,dword ptr [esp+60h]
    L_004378f8:
        xor edi,edi
    L_004378fa:
        test edx,edx
    L_004378fc:
        jle short L_00437915
    L_004378fe:
        mov esi,edx
    L_00437900:
        mov edi,edx
    L_00437902:
        mov dx,word ptr [ecx]
    L_00437905:
        test dh,dh
    L_00437907:
        jns short L_0043790c
    L_00437909:
        mov word ptr [eax],dx
    L_0043790c:
        add eax,2
    L_0043790f:
        add ecx,2
    L_00437912:
        dec esi
    L_00437913:
        jne short L_00437902
    L_00437915:
        mov esi,dword ptr [esp+64h]
    L_00437919:
        lea edx,[edi+edi]
    L_0043791c:
        sub esi,edx
    L_0043791e:
        add ecx,esi
    L_00437920:
        mov esi,dword ptr [esp+10h]
    L_00437924:
        sub esi,edx
    L_00437926:
        add eax,esi
    L_00437928:
        dec ebp
    L_00437929:
        jne short L_004378f4
    L_0043792b:
        jmp asm_target_004379bf
    L_00437930:
        mov edx,dword ptr [esp+24h]
    L_00437934:
        imul eax,edi
    L_00437937:
        add eax,edx
    L_00437939:
        test ebp,ebp
    L_0043793b:
        lea esi,[eax+ebx*4]
    L_0043793e:
        jle asm_target_004379bf
    L_00437944:
        mov dword ptr [esp+18h],ebp
    L_00437948:
        mov ebp,dword ptr [esp+60h]
    L_0043794c:
        xor ebx,ebx
    L_0043794e:
        test ebp,ebp
    L_00437950:
        jle short L_0043799d
    L_00437952:
        mov ebx,ebp
    L_00437954:
        movzx edi,byte ptr [ecx+3]
    L_00437958:
        movzx eax,byte ptr [esi]
    L_0043795b:
        movzx edx,byte ptr [ecx]
    L_0043795e:
        sub edx,eax
    L_00437960:
        imul edx,edi
    L_00437963:
        sar edx,8
    L_00437966:
        add dl,al
    L_00437968:
        movzx eax,byte ptr [esi+1]
    L_0043796c:
        mov byte ptr [esi],dl
    L_0043796e:
        movzx edx,byte ptr [ecx+1]
    L_00437972:
        sub edx,eax
    L_00437974:
        imul edx,edi
    L_00437977:
        sar edx,8
    L_0043797a:
        add dl,al
    L_0043797c:
        movzx eax,byte ptr [esi+2]
    L_00437980:
        mov byte ptr [esi+1],dl
    L_00437983:
        movzx edx,byte ptr [ecx+2]
    L_00437987:
        sub edx,eax
    L_00437989:
        imul edx,edi
    L_0043798c:
        sar edx,8
    L_0043798f:
        add dl,al
    L_00437991:
        mov byte ptr [esi+2],dl
    L_00437994:
        add esi,4
    L_00437997:
        add ecx,4
    L_0043799a:
        dec ebp
    L_0043799b:
        jne short L_00437954
    L_0043799d:
        mov edx,dword ptr [esp+64h]
    L_004379a1:
        lea eax,[ebx*4]
    L_004379a8:
        sub edx,eax
    L_004379aa:
        add ecx,edx
    L_004379ac:
        mov edx,dword ptr [esp+10h]
    L_004379b0:
        sub edx,eax
    L_004379b2:
        mov eax,dword ptr [esp+18h]
    L_004379b6:
        add esi,edx
    L_004379b8:
        dec eax
    L_004379b9:
        mov dword ptr [esp+18h],eax
    L_004379bd:
        jne short L_00437948
    L_004379bf:
        mov eax,dword ptr [esp+5Ch]
    L_004379c3:
        mov ecx,dword ptr [eax]
    L_004379c5:
        push eax
    L_004379c6:
        call dword ptr [ecx+38h]
    L_004379c9:
        pop edi
    L_004379ca:
        pop esi
    L_004379cb:
        pop ebp
    L_004379cc:
        mov al,1
    L_004379ce:
        pop ebx
    L_004379cf:
        add esp,48h
    L_004379d2:
        ret 0Ch
    }
}

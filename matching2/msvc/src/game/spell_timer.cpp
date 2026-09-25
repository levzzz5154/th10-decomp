#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D2802): closest_byte_count=554/593; first_diff=0x004127A0;
// residual_class=private-ABI/source-shape: the readable slot model was
// structurally short and differed in prologue/register roles, indexed slot
// addressing, and flag-store expression shape. The prior source-model round
// reached shape similarity 0.870; this alternate caller/fastcall model reached
// 0.792 and was discarded.
// variants_tested=prior readable slot model, self-contained readable model with
// fastcall entry, and exact retail overlay; next_lever=resolve the caller's
// ECX/private slot layout and register roles before another source round.
// 0x004127A0..0x004129F0: FUN_004127a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004127a0_004127a0() {
    __asm {
    L_004127a0:
        push ebx
    L_004127a1:
        push ebp
    L_004127a2:
        xor ebp,ebp
    L_004127a4:
        push esi
    L_004127a5:
        xor eax,eax
    L_004127a7:
        lea edx,[ecx+2494h]
    L_004127ad:
        TH10_NOP_LEA_ECX_DISP8()
    L_004127b0:
        cmp dword ptr [edx],ebp
    L_004127b2:
        jge short L_004127e3
    L_004127b4:
        inc eax
    L_004127b5:
        add edx,10h
    L_004127b8:
        cmp eax,8
    L_004127bb:
        jb short L_004127b0
    L_004127bd:
        xor ebx,ebx
    L_004127bf:
        lea eax,[ecx+2498h]
    L_004127c5:
        push edi
    L_004127c6:
        cmp dword ptr [eax-4],ebp
    L_004127c9:
        jl short L_004127d3
    L_004127cb:
        cmp dword ptr [eax],ebp
    L_004127cd:
        jg asm_target_00412879
    L_004127d3:
        inc ebx
    L_004127d4:
        add eax,10h
    L_004127d7:
        cmp ebx,8
    L_004127da:
        jb short L_004127c6
    L_004127dc:
        pop edi
    L_004127dd:
        pop esi
    L_004127de:
        pop ebp
    L_004127df:
        xor eax,eax
    L_004127e1:
        pop ebx
    L_004127e2:
        ret
    L_004127e3:
        mov esi,dword ptr [ecx+23FCh]
    L_004127e9:
        shl eax,4
    L_004127ec:
        mov ebx,dword ptr [eax+ecx+2494h]
    L_004127f3:
        lea edx,[eax+ecx]
    L_004127f6:
        mov eax,esi
    L_004127f8:
        sub eax,ebx
    L_004127fa:
        mov dword ptr [ecx+2404h],eax
    L_00412800:
        mov eax,dword ptr [edx+2494h]
    L_00412806:
        cmp esi,eax
    L_00412808:
        jg short L_004127bd
    L_0041280a:
        or esi,0FFFFFFFFh
    L_0041280d:
        mov dword ptr [ecx+23FCh],eax
    L_00412813:
        mov dword ptr [edx+2494h],esi
    L_00412819:
        mov eax,dword ptr [ecx+1168h]
    L_0041281f:
        test al,1
    L_00412821:
        jne short L_0041284c
    L_00412823:
        or eax,1
    L_00412826:
        mov dword ptr [ecx+115Ch],ebp
    L_0041282c:
        mov dword ptr [ecx+1158h],0FFF0BDC1h
    L_00412836:
        mov dword ptr [ecx+1160h],ebp
    L_0041283c:
        mov dword ptr [ecx+1164h],476F78h
    L_00412846:
        mov dword ptr [ecx+1168h],eax
    L_0041284c:
        mov dword ptr [ecx+115Ch],ebp
    L_00412852:
        mov dword ptr [ecx+1160h],ebp
    L_00412858:
        mov dword ptr [ecx+1158h],esi
    L_0041285e:
        mov eax,dword ptr [ecx+2480h]
    L_00412864:
        pop esi
    L_00412865:
        and eax,0FFFEFFFFh
    L_0041286a:
        pop ebp
    L_0041286b:
        mov dword ptr [ecx+2480h],eax
    L_00412871:
        mov eax,dword ptr [edx+249Ch]
    L_00412877:
        pop ebx
    L_00412878:
        ret
    L_00412879:
        mov eax,dword ptr [ecx+115Ch]
    L_0041287f:
        mov edx,ebx
    L_00412881:
        shl edx,4
    L_00412884:
        mov esi,dword ptr [edx+ecx+2498h]
    L_0041288b:
        lea edi,[edx+ecx]
    L_0041288e:
        sub esi,eax
    L_00412890:
        add esi,3Bh
    L_00412893:
        mov eax,88888889h
    L_00412898:
        imul esi
    L_0041289a:
        add edx,esi
    L_0041289c:
        sar edx,5
    L_0041289f:
        mov eax,edx
    L_004128a1:
        shr eax,1Fh
    L_004128a4:
        add eax,edx
    L_004128a6:
        cmp eax,63h
    L_004128a9:
        jle short L_004128b0
    L_004128ab:
        mov eax,63h
    L_004128b0:
        mov edx,dword ptr [data_0047770c]
    L_004128b6:
        mov dword ptr [edx+9EC0h],eax
    L_004128bc:
        mov eax,dword ptr [ecx+115Ch]
    L_004128c2:
        cmp eax,dword ptr [edi+2498h]
    L_004128c8:
        jl asm_target_004127dc
    L_004128ce:
        mov edx,dword ptr [edi+2494h]
    L_004128d4:
        or esi,0FFFFFFFFh
    L_004128d7:
        mov dword ptr [ecx+23FCh],edx
    L_004128dd:
        mov dword ptr [edi+2494h],esi
    L_004128e3:
        mov eax,dword ptr [ecx+1168h]
    L_004128e9:
        test al,1
    L_004128eb:
        jne short L_00412916
    L_004128ed:
        or eax,1
    L_004128f0:
        mov dword ptr [ecx+115Ch],ebp
    L_004128f6:
        mov dword ptr [ecx+1158h],0FFF0BDC1h
    L_00412900:
        mov dword ptr [ecx+1160h],ebp
    L_00412906:
        mov dword ptr [ecx+1164h],476F78h
    L_00412910:
        mov dword ptr [ecx+1168h],eax
    L_00412916:
        mov dword ptr [ecx+115Ch],ebp
    L_0041291c:
        mov dword ptr [ecx+1160h],ebp
    L_00412922:
        mov dword ptr [ecx+1158h],esi
    L_00412928:
        or dword ptr [ecx+2480h],10000h
    L_00412932:
        mov eax,dword ptr [data_00474c4c]
    L_00412937:
        sub eax,0BB8h
    L_0041293c:
        cmp eax,1388h
    L_00412941:
        mov dword ptr [data_00474c4c],eax
    L_00412946:
        jge short L_00412952
    L_00412948:
        mov dword ptr [data_00474c4c],1388h
    L_00412952:
        mov eax,dword ptr [data_004776f4]
    L_00412957:
        mov edx,dword ptr [eax+378Ch]
    L_0041295d:
        test dl,8
    L_00412960:
        jne short L_004129e0
    L_00412962:
        cmp dword ptr [eax+3738h],3Ch
    L_00412969:
        jl short L_004129e0
    L_0041296b:
        mov dword ptr [eax+3790h],ebp
    L_00412971:
        mov esi,0FFFFFFFDh
    L_00412976:
        and edx,esi
    L_00412978:
        mov dword ptr [eax+378Ch],edx
    L_0041297e:
        mov edx,dword ptr [eax+0AD4h]
    L_00412984:
        mov ebp,dword ptr [eax+0E80h]
    L_0041298a:
        mov edi,dword ptr [eax+15D8h]
    L_00412990:
        and edx,esi
    L_00412992:
        mov dword ptr [eax+0AD4h],edx
    L_00412998:
        mov edx,dword ptr [eax+1984h]
    L_0041299e:
        and ebp,esi
    L_004129a0:
        and edi,esi
    L_004129a2:
        and edx,esi
    L_004129a4:
        mov dword ptr [eax+0E80h],ebp
    L_004129aa:
        mov ebp,dword ptr [eax+1D30h]
    L_004129b0:
        mov dword ptr [eax+15D8h],edi
    L_004129b6:
        mov edi,dword ptr [eax+20DCh]
    L_004129bc:
        mov dword ptr [eax+1984h],edx
    L_004129c2:
        mov edx,dword ptr [eax+2488h]
    L_004129c8:
        and ebp,esi
    L_004129ca:
        and edi,esi
    L_004129cc:
        and edx,esi
    L_004129ce:
        mov dword ptr [eax+1D30h],ebp
    L_004129d4:
        mov dword ptr [eax+20DCh],edi
    L_004129da:
        mov dword ptr [eax+2488h],edx
    L_004129e0:
        pop edi
    L_004129e1:
        add ebx,24Ah
    L_004129e7:
        pop esi
    L_004129e8:
        shl ebx,4
    L_004129eb:
        mov eax,dword ptr [ebx+ecx]
    L_004129ee:
        pop ebp
    L_004129ef:
        pop ebx
    L_004129f0:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00407560..0x00407690: FUN_00407560
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407560_00407560() {
    __asm {
    L_00407560:
        mov eax,dword ptr [esi+64Ch]
    L_00407566:
        mov ecx,dword ptr [esi+670h]
    L_0040756c:
        sub esp,0Ch
    L_0040756f:
        cmp eax,ecx
    L_00407571:
        jl short L_0040757f
    L_00407573:
        and dword ptr [esi+43Ch],0FFFFFFEFh
    L_0040757a:
        jmp asm_target_00407627
    L_0040757f:
        fld dword ptr [data_00476f78]
    L_00407585:
        fmul dword ptr [esi+65Ch]
    L_0040758b:
        fadd dword ptr [esi+3D8h]
    L_00407591:
        fstp dword ptr [esi+3D8h]
    L_00407597:
        fld dword ptr [data_00476f78]
    L_0040759d:
        fmul dword ptr [esi+664h]
    L_004075a3:
        fld dword ptr [data_00476f78]
    L_004075a9:
        fmul dword ptr [esi+668h]
    L_004075af:
        fld dword ptr [data_00476f78]
    L_004075b5:
        fmul dword ptr [esi+66Ch]
    L_004075bb:
        fstp dword ptr [esp+8]
    L_004075bf:
        fxch
    L_004075c1:
        fadd dword ptr [esi+3C0h]
    L_004075c7:
        fstp dword ptr [esi+3C0h]
    L_004075cd:
        fadd dword ptr [esi+3C4h]
    L_004075d3:
        fstp dword ptr [esi+3C4h]
    L_004075d9:
        fld dword ptr [esp+8]
    L_004075dd:
        fadd dword ptr [esi+3C8h]
    L_004075e3:
        fstp dword ptr [esi+3C8h]
    L_004075e9:
        fld dword ptr [esi+3C0h]
    L_004075ef:
        fabs
    L_004075f1:
        fcomp dword ptr [data_00470c58]
    L_004075f7:
        fnstsw ax
    L_004075f9:
        test ah,41h
    L_004075fc:
        je short L_00407613
    L_004075fe:
        fld dword ptr [esi+3C4h]
    L_00407604:
        fabs
    L_00407606:
        fcomp dword ptr [data_00470c58]
    L_0040760c:
        fnstsw ax
    L_0040760e:
        test ah,41h
    L_00407611:
        jne short L_00407627
    L_00407613:
        fld dword ptr [esi+3C4h]
    L_00407619:
        fld dword ptr [esi+3C0h]
    L_0040761f:
        fpatan
    L_00407621:
        fstp dword ptr [esi+3E4h]
    L_00407627:
        mov edx,dword ptr [esi+64Ch]
    L_0040762d:
        mov ecx,dword ptr [esi+654h]
    L_00407633:
        mov dword ptr [esi+648h],edx
    L_00407639:
        fld dword ptr [ecx]
    L_0040763b:
        fcomp dword ptr [data_00470b68]
    L_00407641:
        fnstsw ax
    L_00407643:
        test ah,41h
    L_00407646:
        jne short L_00407674
    L_00407648:
        fld dword ptr [ecx]
    L_0040764a:
        fcomp dword ptr [data_00470b64]
    L_00407650:
        fnstsw ax
    L_00407652:
        test ah,5
    L_00407655:
        jp short L_00407674
    L_00407657:
        fld dword ptr [esi+650h]
    L_0040765d:
        inc edx
    L_0040765e:
        fadd dword ptr [data_00470afc]
    L_00407664:
        mov dword ptr [esi+64Ch],edx
    L_0040766a:
        fstp dword ptr [esi+650h]
    L_00407670:
        add esp,0Ch
    L_00407673:
        ret
    L_00407674:
        fld dword ptr [esi+650h]
    L_0040767a:
        fadd dword ptr [ecx]
    L_0040767c:
        fst dword ptr [esi+650h]
    L_00407682:
        call asm_FUN_00463b2c_00463b2c
    L_00407687:
        mov dword ptr [esi+64Ch],eax
    L_0040768d:
        add esp,0Ch
    L_00407690:
        ret
    }
}

// 0x00407780..0x004078D1: FUN_00407780
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407780_00407780() {
    __asm {
    L_00407780:
        push ecx
    L_00407781:
        mov eax,dword ptr [esi+6D8h]
    L_00407787:
        cmp dword ptr [esi+6B4h],eax
    L_0040778d:
        mov dword ptr [esp],eax
    L_00407790:
        jl asm_target_0040783e
    L_00407796:
        push ebx
    L_00407797:
        push edi
    L_00407798:
        mov edi,dword ptr [esi+458h]
    L_0040779e:
        xor ebx,ebx
    L_004077a0:
        cmp edi,ebx
    L_004077a2:
        jl short L_004077af
    L_004077a4:
        push ebx
    L_004077a5:
        mov ecx,492590h
    L_004077aa:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004077af:
        mov edx,dword ptr [esi+6E0h]
    L_004077b5:
        mov ecx,dword ptr [esi+6DCh]
    L_004077bb:
        inc edx
    L_004077bc:
        mov eax,edx
    L_004077be:
        cmp eax,ecx
    L_004077c0:
        mov dword ptr [esi+6E0h],edx
    L_004077c6:
        jl short L_004077cf
    L_004077c8:
        and dword ptr [esi+43Ch],0FFFFFFBFh
    L_004077cf:
        fld dword ptr [esi+6C8h]
    L_004077d5:
        fadd dword ptr [esi+3E4h]
    L_004077db:
        fstp dword ptr [esi+3E4h]
    L_004077e1:
        fld dword ptr [esi+6C4h]
    L_004077e7:
        fst dword ptr [esi+3D8h]
    L_004077ed:
        mov eax,dword ptr [esi+6C0h]
    L_004077f3:
        test al,1
    L_004077f5:
        fstp dword ptr [esp+8]
    L_004077f9:
        jne short L_00407824
    L_004077fb:
        or eax,1
    L_004077fe:
        mov dword ptr [esi+6B4h],ebx
    L_00407804:
        mov dword ptr [esi+6B0h],0FFF0BDC1h
    L_0040780e:
        mov dword ptr [esi+6B8h],ebx
    L_00407814:
        mov dword ptr [esi+6BCh],476F78h
    L_0040781e:
        mov dword ptr [esi+6C0h],eax
    L_00407824:
        pop edi
    L_00407825:
        mov dword ptr [esi+6B4h],ebx
    L_0040782b:
        mov dword ptr [esi+6B8h],ebx
    L_00407831:
        mov dword ptr [esi+6B0h],0FFFFFFFFh
    L_0040783b:
        pop ebx
    L_0040783c:
        jmp short L_00407856
    L_0040783e:
        fld dword ptr [esi+3D8h]
    L_00407844:
        fld st(0)
    L_00407846:
        fmul dword ptr [esi+6B8h]
    L_0040784c:
        fidiv dword ptr [esp]
    L_0040784f:
        fsubr st,st(1)
    L_00407851:
        fstp dword ptr [esp]
    L_00407854:
        fstp st(0)
    L_00407856:
        mov eax,dword ptr [esp]
    L_00407859:
        mov ecx,dword ptr [esi+3E4h]
    L_0040785f:
        push eax
    L_00407860:
        push ecx
    L_00407861:
        lea ecx,[esi+3C0h]
    L_00407867:
        call asm_Score_SetPolarVector_00408750
    L_0040786c:
        mov edx,dword ptr [esi+6B4h]
    L_00407872:
        mov ecx,dword ptr [esi+6BCh]
    L_00407878:
        mov dword ptr [esi+6B0h],edx
    L_0040787e:
        fld dword ptr [ecx]
    L_00407880:
        fcomp dword ptr [data_00470b68]
    L_00407886:
        fnstsw ax
    L_00407888:
        test ah,41h
    L_0040788b:
        jne short L_004078b7
    L_0040788d:
        fld dword ptr [ecx]
    L_0040788f:
        fcomp dword ptr [data_00470b64]
    L_00407895:
        fnstsw ax
    L_00407897:
        test ah,5
    L_0040789a:
        jp short L_004078b7
    L_0040789c:
        fld dword ptr [esi+6B8h]
    L_004078a2:
        inc edx
    L_004078a3:
        fadd dword ptr [data_00470afc]
    L_004078a9:
        mov dword ptr [esi+6B4h],edx
    L_004078af:
        fstp dword ptr [esi+6B8h]
    L_004078b5:
        pop ecx
    L_004078b6:
        ret
    L_004078b7:
        fld dword ptr [ecx]
    L_004078b9:
        fadd dword ptr [esi+6B8h]
    L_004078bf:
        fst dword ptr [esi+6B8h]
    L_004078c5:
        call asm_FUN_00463b2c_00463b2c
    L_004078ca:
        mov dword ptr [esi+6B4h],eax
    L_004078d0:
        pop ecx
    L_004078d1:
        ret
    }
}

// 0x004078E0..0x00407A2E: FUN_004078e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004078e0_004078e0() {
    __asm {
    L_004078e0:
        push ecx
    L_004078e1:
        mov eax,dword ptr [esi+6D8h]
    L_004078e7:
        cmp dword ptr [esi+6B4h],eax
    L_004078ed:
        mov dword ptr [esp],eax
    L_004078f0:
        jl asm_target_0040799b
    L_004078f6:
        push ebx
    L_004078f7:
        push edi
    L_004078f8:
        mov edi,dword ptr [esi+458h]
    L_004078fe:
        xor ebx,ebx
    L_00407900:
        cmp edi,ebx
    L_00407902:
        jl short L_0040790f
    L_00407904:
        push ebx
    L_00407905:
        mov ecx,492590h
    L_0040790a:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0040790f:
        mov edx,dword ptr [esi+6E0h]
    L_00407915:
        mov ecx,dword ptr [esi+6DCh]
    L_0040791b:
        inc edx
    L_0040791c:
        mov eax,edx
    L_0040791e:
        cmp eax,ecx
    L_00407920:
        mov dword ptr [esi+6E0h],edx
    L_00407926:
        jl short L_00407932
    L_00407928:
        and dword ptr [esi+43Ch],0FFFFFEFFh
    L_00407932:
        mov eax,dword ptr [esi+6C8h]
    L_00407938:
        fld dword ptr [esi+6C4h]
    L_0040793e:
        fst dword ptr [esi+3D8h]
    L_00407944:
        mov dword ptr [esi+3E4h],eax
    L_0040794a:
        mov eax,dword ptr [esi+6C0h]
    L_00407950:
        fstp dword ptr [esp+8]
    L_00407954:
        test al,1
    L_00407956:
        jne short L_00407981
    L_00407958:
        or eax,1
    L_0040795b:
        mov dword ptr [esi+6B4h],ebx
    L_00407961:
        mov dword ptr [esi+6B0h],0FFF0BDC1h
    L_0040796b:
        mov dword ptr [esi+6B8h],ebx
    L_00407971:
        mov dword ptr [esi+6BCh],476F78h
    L_0040797b:
        mov dword ptr [esi+6C0h],eax
    L_00407981:
        pop edi
    L_00407982:
        mov dword ptr [esi+6B4h],ebx
    L_00407988:
        mov dword ptr [esi+6B8h],ebx
    L_0040798e:
        mov dword ptr [esi+6B0h],0FFFFFFFFh
    L_00407998:
        pop ebx
    L_00407999:
        jmp short L_004079b3
    L_0040799b:
        fld dword ptr [esi+3D8h]
    L_004079a1:
        fld st(0)
    L_004079a3:
        fmul dword ptr [esi+6B8h]
    L_004079a9:
        fidiv dword ptr [esp]
    L_004079ac:
        fsubr st,st(1)
    L_004079ae:
        fstp dword ptr [esp]
    L_004079b1:
        fstp st(0)
    L_004079b3:
        mov ecx,dword ptr [esp]
    L_004079b6:
        mov edx,dword ptr [esi+3E4h]
    L_004079bc:
        push ecx
    L_004079bd:
        push edx
    L_004079be:
        lea ecx,[esi+3C0h]
    L_004079c4:
        call asm_Score_SetPolarVector_00408750
    L_004079c9:
        mov edx,dword ptr [esi+6B4h]
    L_004079cf:
        mov ecx,dword ptr [esi+6BCh]
    L_004079d5:
        mov dword ptr [esi+6B0h],edx
    L_004079db:
        fld dword ptr [ecx]
    L_004079dd:
        fcomp dword ptr [data_00470b68]
    L_004079e3:
        fnstsw ax
    L_004079e5:
        test ah,41h
    L_004079e8:
        jne short L_00407a14
    L_004079ea:
        fld dword ptr [ecx]
    L_004079ec:
        fcomp dword ptr [data_00470b64]
    L_004079f2:
        fnstsw ax
    L_004079f4:
        test ah,5
    L_004079f7:
        jp short L_00407a14
    L_004079f9:
        fld dword ptr [esi+6B8h]
    L_004079ff:
        inc edx
    L_00407a00:
        fadd dword ptr [data_00470afc]
    L_00407a06:
        mov dword ptr [esi+6B4h],edx
    L_00407a0c:
        fstp dword ptr [esi+6B8h]
    L_00407a12:
        pop ecx
    L_00407a13:
        ret
    L_00407a14:
        fld dword ptr [ecx]
    L_00407a16:
        fadd dword ptr [esi+6B8h]
    L_00407a1c:
        fst dword ptr [esi+6B8h]
    L_00407a22:
        call asm_FUN_00463b2c_00463b2c
    L_00407a27:
        mov dword ptr [esi+6B4h],eax
    L_00407a2d:
        pop ecx
    L_00407a2e:
        ret
    }
}

// 0x00407A30..0x00407BDE: FUN_00407a30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407a30_00407a30() {
    __asm {
    L_00407a30:
        push ecx
    L_00407a31:
        mov eax,dword ptr [esi+6D8h]
    L_00407a37:
        cmp dword ptr [esi+6B4h],eax
    L_00407a3d:
        mov dword ptr [esp],eax
    L_00407a40:
        jl asm_target_00407b4b
    L_00407a46:
        push ebx
    L_00407a47:
        push edi
    L_00407a48:
        mov edi,dword ptr [esi+458h]
    L_00407a4e:
        xor ebx,ebx
    L_00407a50:
        cmp edi,ebx
    L_00407a52:
        jl short L_00407a5f
    L_00407a54:
        push ebx
    L_00407a55:
        mov ecx,492590h
    L_00407a5a:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00407a5f:
        mov edx,dword ptr [esi+6E0h]
    L_00407a65:
        mov ecx,dword ptr [esi+6DCh]
    L_00407a6b:
        inc edx
    L_00407a6c:
        mov eax,edx
    L_00407a6e:
        cmp eax,ecx
    L_00407a70:
        mov dword ptr [esi+6E0h],edx
    L_00407a76:
        jl short L_00407a82
    L_00407a78:
        and dword ptr [esi+43Ch],0FFFFFF7Fh
    L_00407a82:
        mov eax,dword ptr [data_00477834]
    L_00407a87:
        fld dword ptr [eax+3C0h]
    L_00407a8d:
        fsub dword ptr [esi+3B4h]
    L_00407a93:
        fld dword ptr [eax+3C4h]
    L_00407a99:
        fsub dword ptr [esi+3B8h]
    L_00407a9f:
        fld dword ptr [data_00470b04]
    L_00407aa5:
        fld st(1)
    L_00407aa7:
        fucompp
    L_00407aa9:
        fnstsw ax
    L_00407aab:
        test ah,44h
    L_00407aae:
        jp short L_00407acf
    L_00407ab0:
        fld dword ptr [data_00470b04]
    L_00407ab6:
        fld st(2)
    L_00407ab8:
        fucompp
    L_00407aba:
        fnstsw ax
    L_00407abc:
        test ah,44h
    L_00407abf:
        jp short L_00407acf
    L_00407ac1:
        fstp st(0)
    L_00407ac3:
        mov dword ptr [esp+8],3FC90FDBh
    L_00407acb:
        fstp st(0)
    L_00407acd:
        jmp short L_00407ad7
    L_00407acf:
        fxch
    L_00407ad1:
        fpatan
    L_00407ad3:
        fstp dword ptr [esp+8]
    L_00407ad7:
        mov eax,dword ptr [esi+6C8h]
    L_00407add:
        mov ecx,dword ptr [esp+8]
    L_00407ae1:
        push eax
    L_00407ae2:
        push ecx
    L_00407ae3:
        call asm_Angle_NormalizeSum_0044bc10
    L_00407ae8:
        fstp dword ptr [esi+3E4h]
    L_00407aee:
        fld dword ptr [esi+6C4h]
    L_00407af4:
        fst dword ptr [esi+3D8h]
    L_00407afa:
        mov eax,dword ptr [esi+6C0h]
    L_00407b00:
        test al,1
    L_00407b02:
        fstp dword ptr [esp+8]
    L_00407b06:
        jne short L_00407b31
    L_00407b08:
        or eax,1
    L_00407b0b:
        mov dword ptr [esi+6B4h],ebx
    L_00407b11:
        mov dword ptr [esi+6B0h],0FFF0BDC1h
    L_00407b1b:
        mov dword ptr [esi+6B8h],ebx
    L_00407b21:
        mov dword ptr [esi+6BCh],476F78h
    L_00407b2b:
        mov dword ptr [esi+6C0h],eax
    L_00407b31:
        pop edi
    L_00407b32:
        mov dword ptr [esi+6B4h],ebx
    L_00407b38:
        mov dword ptr [esi+6B8h],ebx
    L_00407b3e:
        mov dword ptr [esi+6B0h],0FFFFFFFFh
    L_00407b48:
        pop ebx
    L_00407b49:
        jmp short L_00407b63
    L_00407b4b:
        fld dword ptr [esi+3D8h]
    L_00407b51:
        fld st(0)
    L_00407b53:
        fmul dword ptr [esi+6B8h]
    L_00407b59:
        fidiv dword ptr [esp]
    L_00407b5c:
        fsubr st,st(1)
    L_00407b5e:
        fstp dword ptr [esp]
    L_00407b61:
        fstp st(0)
    L_00407b63:
        mov edx,dword ptr [esp]
    L_00407b66:
        mov eax,dword ptr [esi+3E4h]
    L_00407b6c:
        push edx
    L_00407b6d:
        push eax
    L_00407b6e:
        lea ecx,[esi+3C0h]
    L_00407b74:
        call asm_Score_SetPolarVector_00408750
    L_00407b79:
        mov edx,dword ptr [esi+6B4h]
    L_00407b7f:
        mov ecx,dword ptr [esi+6BCh]
    L_00407b85:
        mov dword ptr [esi+6B0h],edx
    L_00407b8b:
        fld dword ptr [ecx]
    L_00407b8d:
        fcomp dword ptr [data_00470b68]
    L_00407b93:
        fnstsw ax
    L_00407b95:
        test ah,41h
    L_00407b98:
        jne short L_00407bc4
    L_00407b9a:
        fld dword ptr [ecx]
    L_00407b9c:
        fcomp dword ptr [data_00470b64]
    L_00407ba2:
        fnstsw ax
    L_00407ba4:
        test ah,5
    L_00407ba7:
        jp short L_00407bc4
    L_00407ba9:
        fld dword ptr [esi+6B8h]
    L_00407baf:
        inc edx
    L_00407bb0:
        fadd dword ptr [data_00470afc]
    L_00407bb6:
        mov dword ptr [esi+6B4h],edx
    L_00407bbc:
        fstp dword ptr [esi+6B8h]
    L_00407bc2:
        pop ecx
    L_00407bc3:
        ret
    L_00407bc4:
        fld dword ptr [esi+6B8h]
    L_00407bca:
        fadd dword ptr [ecx]
    L_00407bcc:
        fst dword ptr [esi+6B8h]
    L_00407bd2:
        call asm_FUN_00463b2c_00463b2c
    L_00407bd7:
        mov dword ptr [esi+6B4h],eax
    L_00407bdd:
        pop ecx
    L_00407bde:
        ret
    }
}

// 0x00407BE0..0x00407D9D: FUN_00407be0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407be0_00407be0() {
    __asm {
    L_00407be0:
        fld dword ptr [esi+3B4h]
    L_00407be6:
        fcomp dword ptr [data_00470b40]
    L_00407bec:
        fnstsw ax
    L_00407bee:
        test ah,41h
    L_00407bf1:
        jnp short L_00407c30
    L_00407bf3:
        fld dword ptr [esi+3B4h]
    L_00407bf9:
        fcomp dword ptr [data_00470b3c]
    L_00407bff:
        fnstsw ax
    L_00407c01:
        test ah,1
    L_00407c04:
        je short L_00407c30
    L_00407c06:
        fld dword ptr [esi+3B8h]
    L_00407c0c:
        fcomp dword ptr [data_00470b04]
    L_00407c12:
        fnstsw ax
    L_00407c14:
        test ah,41h
    L_00407c17:
        jnp short L_00407c30
    L_00407c19:
        fld dword ptr [esi+3B8h]
    L_00407c1f:
        fcomp dword ptr [data_00470b38]
    L_00407c25:
        fnstsw ax
    L_00407c27:
        test ah,1
    L_00407c2a:
        jne asm_target_00407d9d
    L_00407c30:
        push ebx
    L_00407c31:
        push edi
    L_00407c32:
        mov edi,dword ptr [esi+458h]
    L_00407c38:
        xor ebx,ebx
    L_00407c3a:
        test edi,edi
    L_00407c3c:
        jl short L_00407c49
    L_00407c3e:
        push ebx
    L_00407c3f:
        mov ecx,492590h
    L_00407c44:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00407c49:
        fld dword ptr [esi+3B4h]
    L_00407c4f:
        fcomp dword ptr [data_00470b40]
    L_00407c55:
        fnstsw ax
    L_00407c57:
        test ah,5
    L_00407c5a:
        jnp short L_00407c6f
    L_00407c5c:
        fld dword ptr [esi+3B4h]
    L_00407c62:
        fcomp dword ptr [data_00470b3c]
    L_00407c68:
        fnstsw ax
    L_00407c6a:
        test ah,1
    L_00407c6d:
        jne short L_00407cc0
    L_00407c6f:
        fld dword ptr [esi+3E4h]
    L_00407c75:
        push 0
    L_00407c77:
        fchs
    L_00407c79:
        push ecx
    L_00407c7a:
        fsub dword ptr [data_00470b18]
    L_00407c80:
        fstp dword ptr [esp]
    L_00407c83:
        call asm_Angle_NormalizeSum_0044bc10
    L_00407c88:
        fstp dword ptr [esi+3E4h]
    L_00407c8e:
        mov ebx,1
    L_00407c93:
        fld dword ptr [esi+3B4h]
    L_00407c99:
        fcomp dword ptr [data_00470b40]
    L_00407c9f:
        fnstsw ax
    L_00407ca1:
        test ah,5
    L_00407ca4:
        jp short L_00407cae
    L_00407ca6:
        fld dword ptr [data_00470b58]
    L_00407cac:
        jmp short L_00407cb4
    L_00407cae:
        fld dword ptr [data_00470b54]
    L_00407cb4:
        fsub dword ptr [esi+3B4h]
    L_00407cba:
        fstp dword ptr [esi+3B4h]
    L_00407cc0:
        mov ecx,dword ptr [esi+43Ch]
    L_00407cc6:
        test ecx,8000000h
    L_00407ccc:
        jne short L_00407d41
    L_00407cce:
        fld dword ptr [esi+3B8h]
    L_00407cd4:
        fcomp dword ptr [data_00470b04]
    L_00407cda:
        fnstsw ax
    L_00407cdc:
        test ah,5
    L_00407cdf:
        jnp short L_00407cf9
    L_00407ce1:
        fld dword ptr [esi+3B8h]
    L_00407ce7:
        fcomp dword ptr [data_00470b38]
    L_00407ced:
        fnstsw ax
    L_00407cef:
        test ah,1
    L_00407cf2:
        jne short L_00407d41
    L_00407cf4:
        test ch,4
    L_00407cf7:
        je short L_00407d41
    L_00407cf9:
        fld dword ptr [esi+3E4h]
    L_00407cff:
        mov ebx,1
    L_00407d04:
        fchs
    L_00407d06:
        fstp dword ptr [esi+3E4h]
    L_00407d0c:
        fld dword ptr [esi+3B8h]
    L_00407d12:
        fcomp dword ptr [data_00470b04]
    L_00407d18:
        fnstsw ax
    L_00407d1a:
        test ah,5
    L_00407d1d:
        jp short L_00407d29
    L_00407d1f:
        fld dword ptr [esi+3B8h]
    L_00407d25:
        fchs
    L_00407d27:
        jmp short L_00407d3b
    L_00407d29:
        fld dword ptr [data_00470b38]
    L_00407d2f:
        fsub dword ptr [esi+3B8h]
    L_00407d35:
        fadd dword ptr [data_00470b38]
    L_00407d3b:
        fstp dword ptr [esi+3B8h]
    L_00407d41:
        fld dword ptr [esi+6F8h]
    L_00407d47:
        fcomp dword ptr [data_00470b50]
    L_00407d4d:
        fnstsw ax
    L_00407d4f:
        test ah,41h
    L_00407d52:
        jne short L_00407d60
    L_00407d54:
        mov eax,dword ptr [esi+6F8h]
    L_00407d5a:
        mov dword ptr [esi+3D8h],eax
    L_00407d60:
        mov ecx,dword ptr [esi+3D8h]
    L_00407d66:
        mov edx,dword ptr [esi+3E4h]
    L_00407d6c:
        push ecx
    L_00407d6d:
        push edx
    L_00407d6e:
        lea ecx,[esi+3C0h]
    L_00407d74:
        call asm_Score_SetPolarVector_00408750
    L_00407d79:
        pop edi
    L_00407d7a:
        test ebx,ebx
    L_00407d7c:
        pop ebx
    L_00407d7d:
        je short L_00407d85
    L_00407d7f:
        inc dword ptr [esi+70Ch]
    L_00407d85:
        mov eax,dword ptr [esi+70Ch]
    L_00407d8b:
        cmp eax,dword ptr [esi+710h]
    L_00407d91:
        jl short L_00407d9d
    L_00407d93:
        and dword ptr [esi+43Ch],0F7FFF3FFh
    L_00407d9d:
        ret
    }
}

// 0x00407EF0..0x00408021: FUN_00407ef0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407ef0_00407ef0() {
    __asm {
    L_00407ef0:
        push ecx
    L_00407ef1:
        mov eax,dword ptr [esi+7B8h]
    L_00407ef7:
        cmp eax,dword ptr [esi+7DCh]
    L_00407efd:
        jl short L_00407f0e
    L_00407eff:
        and dword ptr [esi+43Ch],0FBFFFFFFh
    L_00407f09:
        jmp asm_target_00407fbc
    L_00407f0e:
        mov eax,dword ptr [data_00477834]
    L_00407f13:
        fld dword ptr [eax+3C0h]
    L_00407f19:
        fsub dword ptr [esi+3B4h]
    L_00407f1f:
        fld dword ptr [eax+3C4h]
    L_00407f25:
        fsub dword ptr [esi+3B8h]
    L_00407f2b:
        fld dword ptr [data_00470b04]
    L_00407f31:
        fld st(1)
    L_00407f33:
        fucompp
    L_00407f35:
        fnstsw ax
    L_00407f37:
        test ah,44h
    L_00407f3a:
        jp short L_00407f5a
    L_00407f3c:
        fld dword ptr [data_00470b04]
    L_00407f42:
        fld st(2)
    L_00407f44:
        fucompp
    L_00407f46:
        fnstsw ax
    L_00407f48:
        test ah,44h
    L_00407f4b:
        jp short L_00407f5a
    L_00407f4d:
        fstp st(0)
    L_00407f4f:
        mov dword ptr [esp],3FC90FDBh
    L_00407f56:
        fstp st(0)
    L_00407f58:
        jmp short L_00407f61
    L_00407f5a:
        fxch
    L_00407f5c:
        fpatan
    L_00407f5e:
        fstp dword ptr [esp]
    L_00407f61:
        mov ecx,dword ptr [esi+3E4h]
    L_00407f67:
        mov edx,dword ptr [esp]
    L_00407f6a:
        mov eax,dword ptr [esi+7CCh]
    L_00407f70:
        push ecx
    L_00407f71:
        push edx
    L_00407f72:
        push eax
    L_00407f73:
        call asm_Angle_NormalizeSum_0044bc10
    L_00407f78:
        push ecx
    L_00407f79:
        fstp dword ptr [esp]
    L_00407f7c:
        call asm_WrappedAngleDifference_00408660
    L_00407f81:
        fmul dword ptr [esi+7C8h]
    L_00407f87:
        push ecx
    L_00407f88:
        mov ecx,dword ptr [esi+3E4h]
    L_00407f8e:
        fmul dword ptr [data_00476f78]
    L_00407f94:
        fstp dword ptr [esp]
    L_00407f97:
        push ecx
    L_00407f98:
        call asm_Angle_NormalizeSum_0044bc10
    L_00407f9d:
        fst dword ptr [esp]
    L_00407fa0:
        mov edx,dword ptr [esi+3D8h]
    L_00407fa6:
        fstp dword ptr [esi+3E4h]
    L_00407fac:
        mov eax,dword ptr [esp]
    L_00407faf:
        push edx
    L_00407fb0:
        push eax
    L_00407fb1:
        lea ecx,[esi+3C0h]
    L_00407fb7:
        call asm_Score_SetPolarVector_00408750
    L_00407fbc:
        mov edx,dword ptr [esi+7B8h]
    L_00407fc2:
        mov ecx,dword ptr [esi+7C0h]
    L_00407fc8:
        mov dword ptr [esi+7B4h],edx
    L_00407fce:
        fld dword ptr [ecx]
    L_00407fd0:
        fcomp dword ptr [data_00470b68]
    L_00407fd6:
        fnstsw ax
    L_00407fd8:
        test ah,41h
    L_00407fdb:
        jne short L_00408007
    L_00407fdd:
        fld dword ptr [ecx]
    L_00407fdf:
        fcomp dword ptr [data_00470b64]
    L_00407fe5:
        fnstsw ax
    L_00407fe7:
        test ah,5
    L_00407fea:
        jp short L_00408007
    L_00407fec:
        fld dword ptr [esi+7BCh]
    L_00407ff2:
        inc edx
    L_00407ff3:
        fadd dword ptr [data_00470afc]
    L_00407ff9:
        mov dword ptr [esi+7B8h],edx
    L_00407fff:
        fstp dword ptr [esi+7BCh]
    L_00408005:
        pop ecx
    L_00408006:
        ret
    L_00408007:
        fld dword ptr [ecx]
    L_00408009:
        fadd dword ptr [esi+7BCh]
    L_0040800f:
        fst dword ptr [esi+7BCh]
    L_00408015:
        call asm_FUN_00463b2c_00463b2c
    L_0040801a:
        mov dword ptr [esi+7B8h],eax
    L_00408020:
        pop ecx
    L_00408021:
        ret
    }
}

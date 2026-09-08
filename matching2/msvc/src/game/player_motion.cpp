#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040678E..0x00406797: ?Player_ForwardAxisWrap@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_ForwardAxisWrap_0040678e() {
    __asm {
    L_0040678e:
        push esi
    L_0040678f:
        mov esi,ecx
    L_00406791:
        call asm_FUN_004065c0_004065c0
    L_00406796:
        pop esi
    L_00406797:
        ret
    }
}

// 0x004074B0..0x00407553: PlayerAnimation_AdvanceFrame
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_PlayerAnimation_AdvanceFrame_004074b0() {
    __asm {
    L_004074b0:
        cmp dword ptr [esi+618h],10h
    L_004074b7:
        jg short L_004074e9
    L_004074b9:
        fld dword ptr [esi+61Ch]
    L_004074bf:
        mov eax,dword ptr [esi+3E4h]
    L_004074c5:
        fmul dword ptr [data_00470c6c]
    L_004074cb:
        push ecx
    L_004074cc:
        lea ecx,[esi+3C0h]
    L_004074d2:
        fsubr dword ptr [data_00470c68]
    L_004074d8:
        fadd dword ptr [esi+3D8h]
    L_004074de:
        fstp dword ptr [esp]
    L_004074e1:
        push eax
    L_004074e2:
        call asm_Score_SetPolarVector_00408750
    L_004074e7:
        jmp short L_004074f0
    L_004074e9:
        xor dword ptr [esi+43Ch],1
    L_004074f0:
        mov edx,dword ptr [esi+618h]
    L_004074f6:
        mov ecx,dword ptr [esi+620h]
    L_004074fc:
        mov dword ptr [esi+614h],edx
    L_00407502:
        fld dword ptr [ecx]
    L_00407504:
        fcomp dword ptr [data_00470b68]
    L_0040750a:
        fnstsw ax
    L_0040750c:
        test ah,41h
    L_0040750f:
        jne short L_0040753a
    L_00407511:
        fld dword ptr [ecx]
    L_00407513:
        fcomp dword ptr [data_00470b64]
    L_00407519:
        fnstsw ax
    L_0040751b:
        test ah,5
    L_0040751e:
        jp short L_0040753a
    L_00407520:
        fld dword ptr [esi+61Ch]
    L_00407526:
        inc edx
    L_00407527:
        fadd dword ptr [data_00470afc]
    L_0040752d:
        mov dword ptr [esi+618h],edx
    L_00407533:
        fstp dword ptr [esi+61Ch]
    L_00407539:
        ret
    L_0040753a:
        fld dword ptr [ecx]
    L_0040753c:
        fadd dword ptr [esi+61Ch]
    L_00407542:
        fst dword ptr [esi+61Ch]
    L_00407548:
        call asm_FUN_00463b2c_00463b2c
    L_0040754d:
        mov dword ptr [esi+618h],eax
    L_00407553:
        ret
    }
}

// 0x004076A0..0x00407770: Player_DeathShrink
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_DeathShrink_004076a0() {
    __asm {
    L_004076a0:
        push ecx
    L_004076a1:
        mov eax,dword ptr [esi+680h]
    L_004076a7:
        cmp eax,dword ptr [esi+6A4h]
    L_004076ad:
        jl short L_004076b8
    L_004076af:
        and dword ptr [esi+43Ch],0FFFFFFDFh
    L_004076b6:
        jmp short L_0040770b
    L_004076b8:
        fld dword ptr [data_00476f78]
    L_004076be:
        push ecx
    L_004076bf:
        fmul dword ptr [esi+694h]
    L_004076c5:
        mov ecx,dword ptr [esi+3E4h]
    L_004076cb:
        fstp dword ptr [esp]
    L_004076ce:
        push ecx
    L_004076cf:
        call asm_Angle_NormalizeSum_0044bc10
    L_004076d4:
        fstp dword ptr [esi+3E4h]
    L_004076da:
        fld dword ptr [data_00476f78]
    L_004076e0:
        mov eax,dword ptr [esi+3E4h]
    L_004076e6:
        fmul dword ptr [esi+690h]
    L_004076ec:
        lea ecx,[esi+3C0h]
    L_004076f2:
        fadd dword ptr [esi+3D8h]
    L_004076f8:
        fst dword ptr [esp]
    L_004076fb:
        mov edx,dword ptr [esp]
    L_004076fe:
        fstp dword ptr [esi+3D8h]
    L_00407704:
        push edx
    L_00407705:
        push eax
    L_00407706:
        call asm_Score_SetPolarVector_00408750
    L_0040770b:
        mov edx,dword ptr [esi+680h]
    L_00407711:
        mov ecx,dword ptr [esi+688h]
    L_00407717:
        mov dword ptr [esi+67Ch],edx
    L_0040771d:
        fld dword ptr [ecx]
    L_0040771f:
        fcomp dword ptr [data_00470b68]
    L_00407725:
        fnstsw ax
    L_00407727:
        test ah,41h
    L_0040772a:
        jne short L_00407756
    L_0040772c:
        fld dword ptr [ecx]
    L_0040772e:
        fcomp dword ptr [data_00470b64]
    L_00407734:
        fnstsw ax
    L_00407736:
        test ah,5
    L_00407739:
        jp short L_00407756
    L_0040773b:
        fld dword ptr [esi+684h]
    L_00407741:
        inc edx
    L_00407742:
        fadd dword ptr [data_00470afc]
    L_00407748:
        mov dword ptr [esi+680h],edx
    L_0040774e:
        fstp dword ptr [esi+684h]
    L_00407754:
        pop ecx
    L_00407755:
        ret
    L_00407756:
        fld dword ptr [ecx]
    L_00407758:
        fadd dword ptr [esi+684h]
    L_0040775e:
        fst dword ptr [esi+684h]
    L_00407764:
        call asm_FUN_00463b2c_00463b2c
    L_00407769:
        mov dword ptr [esi+680h],eax
    L_0040776f:
        pop ecx
    L_00407770:
        ret
    }
}

// 0x00407DA0..0x00407E33: Player_WrapHorizontal
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_WrapHorizontal_00407da0() {
    __asm {
    L_00407da0:
        mov edx,dword ptr [ebx+39Ch]
    L_00407da6:
        mov eax,dword ptr [edx+30h]
    L_00407da9:
        push eax
    L_00407daa:
        mov eax,dword ptr [edx+34h]
    L_00407dad:
        lea ecx,[ebx+3B4h]
    L_00407db3:
        push eax
    L_00407db4:
        call asm_Entity_PointWithinBoundsInclusive_004061d0
    L_00407db9:
        test eax,eax
    L_00407dbb:
        je short L_00407e33
    L_00407dbd:
        fld dword ptr [ecx]
    L_00407dbf:
        push esi
    L_00407dc0:
        fcomp dword ptr [data_00470b40]
    L_00407dc6:
        push edi
    L_00407dc7:
        fnstsw ax
    L_00407dc9:
        test ah,5
    L_00407dcc:
        jp short L_00407ddb
    L_00407dce:
        fld dword ptr [edx+34h]
    L_00407dd1:
        fadd dword ptr [ecx]
    L_00407dd3:
        fadd dword ptr [data_00470b54]
    L_00407dd9:
        jmp short L_00407df5
    L_00407ddb:
        fld dword ptr [ecx]
    L_00407ddd:
        fcomp dword ptr [data_00470b3c]
    L_00407de3:
        fnstsw ax
    L_00407de5:
        test ah,41h
    L_00407de8:
        jne short L_00407e1d
    L_00407dea:
        fld dword ptr [edx+34h]
    L_00407ded:
        fadd dword ptr [data_00470b54]
    L_00407df3:
        fsubr dword ptr [ecx]
    L_00407df5:
        lea esi,[ebx+74Ch]
    L_00407dfb:
        fstp dword ptr [ecx]
    L_00407dfd:
        push 0BF800000h
    L_00407e02:
        call asm_FrameTimer_Advance_0044bf40
    L_00407e07:
        mov edi,dword ptr [ebx+458h]
    L_00407e0d:
        test edi,edi
    L_00407e0f:
        jl short L_00407e1d
    L_00407e11:
        mov ecx,492590h
    L_00407e16:
        push 0
    L_00407e18:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00407e1d:
        mov eax,dword ptr [ebx+750h]
    L_00407e23:
        test eax,eax
    L_00407e25:
        pop edi
    L_00407e26:
        pop esi
    L_00407e27:
        jg short L_00407e33
    L_00407e29:
        xor dword ptr [ebx+43Ch],100000h
    L_00407e33:
        ret
    }
}

// 0x00407E40..0x00407EEB: Player_WrapVertical
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_WrapVertical_00407e40() {
    __asm {
    L_00407e40:
        mov edx,dword ptr [ebx+39Ch]
    L_00407e46:
        mov eax,dword ptr [edx+30h]
    L_00407e49:
        mov ecx,dword ptr [edx+34h]
    L_00407e4c:
        push eax
    L_00407e4d:
        push ecx
    L_00407e4e:
        lea ecx,[ebx+3B4h]
    L_00407e54:
        call asm_Entity_PointWithinBoundsInclusive_004061d0
    L_00407e59:
        test eax,eax
    L_00407e5b:
        je asm_target_00407eeb
    L_00407e61:
        fld dword ptr [ebx+3B8h]
    L_00407e67:
        push esi
    L_00407e68:
        fcomp qword ptr [data_00470b70]
    L_00407e6e:
        push edi
    L_00407e6f:
        fnstsw ax
    L_00407e71:
        test ah,5
    L_00407e74:
        jp short L_00407e87
    L_00407e76:
        fld dword ptr [edx+30h]
    L_00407e79:
        fadd dword ptr [ebx+3B8h]
    L_00407e7f:
        fadd dword ptr [data_00470b38]
    L_00407e85:
        jmp short L_00407ea9
    L_00407e87:
        fld dword ptr [ebx+3B8h]
    L_00407e8d:
        fcomp dword ptr [data_00470b38]
    L_00407e93:
        fnstsw ax
    L_00407e95:
        test ah,41h
    L_00407e98:
        jne short L_00407ed5
    L_00407e9a:
        fld dword ptr [edx+30h]
    L_00407e9d:
        fadd dword ptr [data_00470b38]
    L_00407ea3:
        fsubr dword ptr [ebx+3B8h]
    L_00407ea9:
        lea esi,[ebx+780h]
    L_00407eaf:
        fstp dword ptr [ebx+3B8h]
    L_00407eb5:
        push 0BF800000h
    L_00407eba:
        call asm_FrameTimer_Advance_0044bf40
    L_00407ebf:
        mov edi,dword ptr [ebx+458h]
    L_00407ec5:
        test edi,edi
    L_00407ec7:
        jl short L_00407ed5
    L_00407ec9:
        mov ecx,492590h
    L_00407ece:
        push 0
    L_00407ed0:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00407ed5:
        mov eax,dword ptr [ebx+784h]
    L_00407edb:
        test eax,eax
    L_00407edd:
        pop edi
    L_00407ede:
        pop esi
    L_00407edf:
        jg short L_00407eeb
    L_00407ee1:
        xor dword ptr [ebx+43Ch],200000h
    L_00407eeb:
        ret
    }
}

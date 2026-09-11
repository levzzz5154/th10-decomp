#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041D3D0..0x0041D7B8: FUN_0041d3d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041d3d0_0041d3d0() {
    __asm {
    L_0041d3d0:
        sub esp,1Ch
    L_0041d3d3:
        push ebp
    L_0041d3d4:
        mov ebp,ecx
    L_0041d3d6:
        mov eax,dword ptr [ebp]
    L_0041d3d9:
        push esi
    L_0041d3da:
        call dword ptr [eax]
    L_0041d3dc:
        mov eax,dword ptr [ebp+404h]
    L_0041d3e2:
        test eax,eax
    L_0041d3e4:
        je asm_target_0041d4cf
    L_0041d3ea:
        test al,1
    L_0041d3ec:
        je short L_0041d3f6
    L_0041d3ee:
        mov edx,dword ptr [ebp]
    L_0041d3f1:
        mov ecx,ebp
    L_0041d3f3:
        call dword ptr [edx+24h]
    L_0041d3f6:
        test byte ptr [ebp+404h],10h
    L_0041d3fd:
        je short L_0041d407
    L_0041d3ff:
        mov eax,dword ptr [ebp]
    L_0041d402:
        mov ecx,ebp
    L_0041d404:
        call dword ptr [eax+28h]
    L_0041d407:
        test byte ptr [ebp+404h],20h
    L_0041d40e:
        je short L_0041d418
    L_0041d410:
        mov edx,dword ptr [ebp]
    L_0041d413:
        mov ecx,ebp
    L_0041d415:
        call dword ptr [edx+2Ch]
    L_0041d418:
        test byte ptr [ebp+404h],40h
    L_0041d41f:
        je short L_0041d429
    L_0041d421:
        mov eax,dword ptr [ebp]
    L_0041d424:
        mov ecx,ebp
    L_0041d426:
        call dword ptr [eax+30h]
    L_0041d429:
        mov eax,dword ptr [ebp+404h]
    L_0041d42f:
        test ah,1
    L_0041d432:
        je short L_0041d43c
    L_0041d434:
        mov edx,dword ptr [ebp]
    L_0041d437:
        mov ecx,ebp
    L_0041d439:
        call dword ptr [edx+34h]
    L_0041d43c:
        mov al,byte ptr [ebp+404h]
    L_0041d442:
        test al,al
    L_0041d444:
        jns short L_0041d44e
    L_0041d446:
        mov eax,dword ptr [ebp]
    L_0041d449:
        mov ecx,ebp
    L_0041d44b:
        call dword ptr [eax+38h]
    L_0041d44e:
        test dword ptr [ebp+404h],8000C00h
    L_0041d458:
        je short L_0041d462
    L_0041d45a:
        mov edx,dword ptr [ebp]
    L_0041d45d:
        mov ecx,ebp
    L_0041d45f:
        call dword ptr [edx+3Ch]
    L_0041d462:
        test dword ptr [ebp+404h],100000h
    L_0041d46c:
        je short L_0041d476
    L_0041d46e:
        mov eax,dword ptr [ebp]
    L_0041d471:
        mov ecx,ebp
    L_0041d473:
        call dword ptr [eax+40h]
    L_0041d476:
        test dword ptr [ebp+404h],200000h
    L_0041d480:
        je short L_0041d48a
    L_0041d482:
        mov edx,dword ptr [ebp]
    L_0041d485:
        mov ecx,ebp
    L_0041d487:
        call dword ptr [edx+44h]
    L_0041d48a:
        test dword ptr [ebp+404h],4000000h
    L_0041d494:
        je short L_0041d49e
    L_0041d496:
        mov eax,dword ptr [ebp]
    L_0041d499:
        mov ecx,ebp
    L_0041d49b:
        call dword ptr [eax+48h]
    L_0041d49e:
        mov eax,dword ptr [ebp+404h]
    L_0041d4a4:
        test ah,ah
    L_0041d4a6:
        jns short L_0041d4cf
    L_0041d4a8:
        mov ecx,dword ptr [ebp+160h]
    L_0041d4ae:
        test ecx,ecx
    L_0041d4b0:
        jg short L_0041d4bf
    L_0041d4b2:
        xor eax,8000h
    L_0041d4b7:
        mov dword ptr [ebp+404h],eax
    L_0041d4bd:
        jmp short L_0041d4cf
    L_0041d4bf:
        push 0BF800000h
    L_0041d4c4:
        lea esi,[ebp+15Ch]
    L_0041d4ca:
        call asm_FrameTimer_Advance_0044bf40
    L_0041d4cf:
        fld dword ptr [ebp+40h]
    L_0041d4d2:
        fcomp dword ptr [ebp+434h]
    L_0041d4d8:
        fld dword ptr [data_00476f78]
    L_0041d4de:
        fmul dword ptr [ebp+48h]
    L_0041d4e1:
        fnstsw ax
    L_0041d4e3:
        test ah,5
    L_0041d4e6:
        jp short L_0041d50d
    L_0041d4e8:
        fadd dword ptr [ebp+40h]
    L_0041d4eb:
        fst dword ptr [ebp+40h]
    L_0041d4ee:
        fcomp dword ptr [ebp+434h]
    L_0041d4f4:
        fnstsw ax
    L_0041d4f6:
        test ah,41h
    L_0041d4f9:
        jne asm_target_0041d592
    L_0041d4ff:
        mov ecx,dword ptr [ebp+434h]
    L_0041d505:
        mov dword ptr [ebp+40h],ecx
    L_0041d508:
        jmp asm_target_0041d592
    L_0041d50d:
        fadd dword ptr [ebp+4Ch]
    L_0041d510:
        fstp dword ptr [ebp+4Ch]
    L_0041d513:
        fld dword ptr [data_00476f78]
    L_0041d519:
        fmul dword ptr [ebp+30h]
    L_0041d51c:
        fld dword ptr [data_00476f78]
    L_0041d522:
        fmul dword ptr [ebp+34h]
    L_0041d525:
        fld dword ptr [data_00476f78]
    L_0041d52b:
        fmul dword ptr [ebp+38h]
    L_0041d52e:
        fstp dword ptr [esp+20h]
    L_0041d532:
        fxch
    L_0041d534:
        fadd dword ptr [ebp+24h]
    L_0041d537:
        fstp dword ptr [ebp+24h]
    L_0041d53a:
        fadd dword ptr [ebp+28h]
    L_0041d53d:
        fstp dword ptr [ebp+28h]
    L_0041d540:
        fld dword ptr [esp+20h]
    L_0041d544:
        fadd dword ptr [ebp+2Ch]
    L_0041d547:
        fstp dword ptr [ebp+2Ch]
    L_0041d54a:
        fld dword ptr [ebp+43Ch]
    L_0041d550:
        fcomp dword ptr [data_00470b04]
    L_0041d556:
        fnstsw ax
    L_0041d558:
        test ah,41h
    L_0041d55b:
        jne short L_0041d592
    L_0041d55d:
        fld dword ptr [ebp+4Ch]
    L_0041d560:
        fadd dword ptr [ebp+40h]
    L_0041d563:
        fcomp dword ptr [ebp+43Ch]
    L_0041d569:
        fnstsw ax
    L_0041d56b:
        test ah,41h
    L_0041d56e:
        jne short L_0041d592
    L_0041d570:
        fld dword ptr [ebp+43Ch]
    L_0041d576:
        fsub dword ptr [ebp+4Ch]
    L_0041d579:
        fst dword ptr [ebp+40h]
    L_0041d57c:
        fstp dword ptr [ebp+434h]
    L_0041d582:
        fld dword ptr [ebp+40h]
    L_0041d585:
        fcomp dword ptr [data_00470b04]
    L_0041d58b:
        fnstsw ax
    L_0041d58d:
        test ah,41h
    L_0041d590:
        jnp short L_0041d5f2
    L_0041d592:
        mov eax,dword ptr [ebp+414h]
    L_0041d598:
        test eax,eax
    L_0041d59a:
        jg short L_0041d5fd
    L_0041d59c:
        mov edx,dword ptr [ebp+40h]
    L_0041d59f:
        mov eax,dword ptr [ebp+3Ch]
    L_0041d5a2:
        push edx
    L_0041d5a3:
        push eax
    L_0041d5a4:
        lea ecx,[esp+14h]
    L_0041d5a8:
        call asm_SetPolar_Vector2_0041f800
    L_0041d5ad:
        fld dword ptr [esp+0Ch]
    L_0041d5b1:
        fadd dword ptr [ebp+24h]
    L_0041d5b4:
        mov edx,dword ptr [ebp+44h]
    L_0041d5b7:
        lea ecx,[ebp+24h]
    L_0041d5ba:
        push edx
    L_0041d5bb:
        fstp dword ptr [esp+10h]
    L_0041d5bf:
        mov eax,edx
    L_0041d5c1:
        fld dword ptr [esp+14h]
    L_0041d5c5:
        push eax
    L_0041d5c6:
        fadd dword ptr [ecx+4]
    L_0041d5c9:
        fstp dword ptr [esp+18h]
    L_0041d5cd:
        fld dword ptr [esp+1Ch]
    L_0041d5d1:
        fadd dword ptr [ecx+8]
    L_0041d5d4:
        fstp dword ptr [esp+1Ch]
    L_0041d5d8:
        call asm_Position_IsPartiallyInViewport_0041f7a0
    L_0041d5dd:
        test eax,eax
    L_0041d5df:
        je short L_0041d60d
    L_0041d5e1:
        mov ecx,edx
    L_0041d5e3:
        push ecx
    L_0041d5e4:
        push edx
    L_0041d5e5:
        lea ecx,[esp+14h]
    L_0041d5e9:
        call asm_Position_IsPartiallyInViewport_0041f7a0
    L_0041d5ee:
        test eax,eax
    L_0041d5f0:
        je short L_0041d60d
    L_0041d5f2:
        pop esi
    L_0041d5f3:
        mov eax,1
    L_0041d5f8:
        pop ebp
    L_0041d5f9:
        add esp,1Ch
    L_0041d5fc:
        ret
    L_0041d5fd:
        push 0BF800000h
    L_0041d602:
        lea esi,[ebp+410h]
    L_0041d608:
        call asm_FrameTimer_Advance_0044bf40
    L_0041d60d:
        fld dword ptr [ebp+40h]
    L_0041d610:
        fcomp dword ptr [data_00470b48]
    L_0041d616:
        fnstsw ax
    L_0041d618:
        test ah,41h
    L_0041d61b:
        jne asm_target_0041d750
    L_0041d621:
        fld dword ptr [ebp+44h]
    L_0041d624:
        fcomp dword ptr [data_00470bd4]
    L_0041d62a:
        fnstsw ax
    L_0041d62c:
        test ah,41h
    L_0041d62f:
        jne asm_target_0041d750
    L_0041d635:
        fld dword ptr [ebp+40h]
    L_0041d638:
        mov eax,dword ptr [ebp+3Ch]
    L_0041d63b:
        fmul dword ptr [data_00470c18]
    L_0041d641:
        push ecx
    L_0041d642:
        lea ecx,[esp+10h]
    L_0041d646:
        fstp dword ptr [esp]
    L_0041d649:
        push eax
    L_0041d64a:
        call asm_SetPolar_Vector2_0041f800
    L_0041d64f:
        fld dword ptr [esp+0Ch]
    L_0041d653:
        fadd dword ptr [ebp+24h]
    L_0041d656:
        fstp dword ptr [esp+0Ch]
    L_0041d65a:
        fld dword ptr [esp+10h]
    L_0041d65e:
        fadd dword ptr [ebp+28h]
    L_0041d661:
        fstp dword ptr [esp+10h]
    L_0041d665:
        fld dword ptr [esp+14h]
    L_0041d669:
        fadd dword ptr [ebp+2Ch]
    L_0041d66c:
        fstp dword ptr [esp+14h]
    L_0041d670:
        fld dword ptr [ebp+44h]
    L_0041d673:
        fcomp dword ptr [data_00470bcc]
    L_0041d679:
        fld dword ptr [ebp+44h]
    L_0041d67c:
        fnstsw ax
    L_0041d67e:
        test ah,5
    L_0041d681:
        jp short L_0041d68b
    L_0041d683:
        fmul dword ptr [data_00470b0c]
    L_0041d689:
        jmp short L_0041d69a
    L_0041d68b:
        fadd dword ptr [data_00470b48]
    L_0041d691:
        fmul dword ptr [data_00470b0c]
    L_0041d697:
        fsubr dword ptr [ebp+44h]
    L_0041d69a:
        mov edx,dword ptr [ebp+3Ch]
    L_0041d69d:
        fstp dword ptr [esp+8]
    L_0041d6a1:
        fld dword ptr [ebp+40h]
    L_0041d6a4:
        push ecx
    L_0041d6a5:
        fmul dword ptr [data_00470cc0]
    L_0041d6ab:
        mov ecx,dword ptr [esp+0Ch]
    L_0041d6af:
        lea eax,[esp+10h]
    L_0041d6b3:
        fstp dword ptr [esp]
    L_0041d6b6:
        push ecx
    L_0041d6b7:
        mov ecx,dword ptr [data_00477834]
    L_0041d6bd:
        push edx
    L_0041d6be:
        call asm_FUN_004267f0_004267f0
    L_0041d6c3:
        cmp eax,1
    L_0041d6c6:
        jne short L_0041d6fe
    L_0041d6c8:
        mov edx,dword ptr [data_00477834]
    L_0041d6ce:
        mov eax,dword ptr [ebp]
    L_0041d6d1:
        push 0
    L_0041d6d3:
        lea ecx,[esp+1Ch]
    L_0041d6d7:
        push ecx
    L_0041d6d8:
        add edx,3C0h
    L_0041d6de:
        push edx
    L_0041d6df:
        mov ecx,ebp
    L_0041d6e1:
        mov dword ptr [esp+24h],42000000h
    L_0041d6e9:
        mov dword ptr [esp+28h],42000000h
    L_0041d6f1:
        mov dword ptr [esp+2Ch],0
    L_0041d6f9:
        call dword ptr [eax+18h]
    L_0041d6fc:
        jmp short L_0041d750
    L_0041d6fe:
        cmp eax,2
    L_0041d701:
        jne short L_0041d750
    L_0041d703:
        mov eax,dword ptr [ebp+14h]
    L_0041d706:
        cdq
    L_0041d707:
        mov ecx,5
    L_0041d70c:
        idiv ecx
    L_0041d70e:
        test edx,edx
    L_0041d710:
        jne short L_0041d750
    L_0041d712:
        mov eax,dword ptr [data_004776f0]
    L_0041d717:
        mov ecx,dword ptr [eax+3E0B50h]
    L_0041d71d:
        push ebx
    L_0041d71e:
        push edi
    L_0041d71f:
        mov edi,dword ptr [data_00477834]
    L_0041d725:
        push 1B2h
    L_0041d72a:
        lea edx,[esp+14h]
    L_0041d72e:
        push edx
    L_0041d72f:
        add edi,3C0h
    L_0041d735:
        push ecx
    L_0041d736:
        call asm_PlayerAnimation_Create_00448db0
    L_0041d73b:
        mov edx,dword ptr [ebp+24h]
    L_0041d73e:
        push edx
    L_0041d73f:
        mov ebx,1Ch
    L_0041d744:
        mov esi,492590h
    L_0041d749:
        call asm_FUN_0043dd10_0043dd10
    L_0041d74e:
        pop edi
    L_0041d74f:
        pop ebx
    L_0041d750:
        mov ecx,dword ptr [ebp+994h]
    L_0041d756:
        fld dword ptr [ebp+44h]
    L_0041d759:
        fdiv dword ptr [ecx+34h]
    L_0041d75c:
        mov esi,dword ptr [ebp+95Ch]
    L_0041d762:
        lea eax,[ebp+600h]
    L_0041d768:
        mov ecx,8
    L_0041d76d:
        or esi,ecx
    L_0041d76f:
        mov dword ptr [eax+35Ch],esi
    L_0041d775:
        push eax
    L_0041d776:
        fstp dword ptr [eax+3Ch]
    L_0041d779:
        fld dword ptr [ebp+40h]
    L_0041d77c:
        mov edx,dword ptr [ebp+994h]
    L_0041d782:
        fdiv dword ptr [edx+30h]
    L_0041d785:
        or dword ptr [eax+35Ch],ecx
    L_0041d78b:
        fstp dword ptr [eax+40h]
    L_0041d78e:
        call asm_FUN_0043ee30_0043ee30
    L_0041d793:
        fld dword ptr [data_00470b04]
    L_0041d799:
        fld dword ptr [ebp+4Ch]
    L_0041d79c:
        fucompp
    L_0041d79e:
        fnstsw ax
    L_0041d7a0:
        test ah,44h
    L_0041d7a3:
        jp short L_0041d7b1
    L_0041d7a5:
        add ebp,9ACh
    L_0041d7ab:
        push ebp
    L_0041d7ac:
        call asm_FUN_0043ee30_0043ee30
    L_0041d7b1:
        pop esi
    L_0041d7b2:
        xor eax,eax
    L_0041d7b4:
        pop ebp
    L_0041d7b5:
        add esp,1Ch
    L_0041d7b8:
        ret
    }
}


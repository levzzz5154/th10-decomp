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

// 0x0041F400..0x0041F66E: FUN_0041f400
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041f400_0041f400() {
    __asm {
    L_0041f400:
        sub esp,30h
    L_0041f403:
        push ebp
    L_0041f404:
        mov ebp,ecx
    L_0041f406:
        mov eax,dword ptr [ebp+3Ch]
    L_0041f409:
        push 40C00000h
    L_0041f40e:
        xor edx,edx
    L_0041f410:
        push eax
    L_0041f411:
        lea ecx,[esp+24h]
    L_0041f415:
        mov dword ptr [esp+10h],edx
    L_0041f419:
        mov dword ptr [esp+0Ch],40C00000h
    L_0041f421:
        call asm_SetPolar_Vector2_0041f800
    L_0041f426:
        fld dword ptr [esp+1Ch]
    L_0041f42a:
        fadd dword ptr [ebp+24h]
    L_0041f42d:
        mov ecx,dword ptr [ebp+2Ch]
    L_0041f430:
        mov dword ptr [esp+30h],ecx
    L_0041f434:
        mov dword ptr [esp+24h],edx
    L_0041f438:
        fstp dword ptr [esp+28h]
    L_0041f43c:
        mov eax,dword ptr [esp+28h]
    L_0041f440:
        fld dword ptr [esp+20h]
    L_0041f444:
        mov dword ptr [esp+10h],eax
    L_0041f448:
        fadd dword ptr [ebp+28h]
    L_0041f44b:
        mov eax,dword ptr [esp+30h]
    L_0041f44f:
        mov dword ptr [esp+18h],eax
    L_0041f453:
        fstp dword ptr [esp+2Ch]
    L_0041f457:
        mov ecx,dword ptr [esp+2Ch]
    L_0041f45b:
        fld dword ptr [esp+1Ch]
    L_0041f45f:
        mov dword ptr [esp+14h],ecx
    L_0041f463:
        fadd st(0),st
    L_0041f465:
        fstp dword ptr [esp+1Ch]
    L_0041f469:
        fld dword ptr [esp+20h]
    L_0041f46d:
        fadd st(0),st
    L_0041f46f:
        fstp dword ptr [esp+20h]
    L_0041f473:
        fld dword ptr [data_00470cd8]
    L_0041f479:
        fcomp dword ptr [ebp+40h]
    L_0041f47c:
        fnstsw ax
    L_0041f47e:
        test ah,5
    L_0041f481:
        jp asm_target_0041f65f
    L_0041f487:
        push ebx
    L_0041f488:
        push esi
    L_0041f489:
        push edi
    L_0041f48a:
        lea ebx,[ebx+force_disp32_zero]
    L_0041f490:
        fld dword ptr [esp+1Ch]
    L_0041f494:
        mov eax,dword ptr [esp+14h]
    L_0041f498:
        fadd dword ptr [data_00470b48]
    L_0041f49e:
        inc eax
    L_0041f49f:
        mov dword ptr [esp+14h],eax
    L_0041f4a3:
        fcomp dword ptr [data_00470b40]
    L_0041f4a9:
        fnstsw ax
    L_0041f4ab:
        test ah,41h
    L_0041f4ae:
        jnp asm_target_0041f604
    L_0041f4b4:
        fld dword ptr [esp+1Ch]
    L_0041f4b8:
        fsub dword ptr [data_00470b48]
    L_0041f4be:
        fcomp dword ptr [data_00470b3c]
    L_0041f4c4:
        fnstsw ax
    L_0041f4c6:
        test ah,1
    L_0041f4c9:
        je asm_target_0041f604
    L_0041f4cf:
        fld dword ptr [esp+20h]
    L_0041f4d3:
        fadd dword ptr [data_00470b48]
    L_0041f4d9:
        fst dword ptr [esp+18h]
    L_0041f4dd:
        fcomp dword ptr [data_00470b04]
    L_0041f4e3:
        fnstsw ax
    L_0041f4e5:
        test ah,41h
    L_0041f4e8:
        jnp asm_target_0041f604
    L_0041f4ee:
        fld dword ptr [esp+20h]
    L_0041f4f2:
        fsub dword ptr [data_00470b48]
    L_0041f4f8:
        fcomp dword ptr [data_00470b38]
    L_0041f4fe:
        fnstsw ax
    L_0041f500:
        test ah,1
    L_0041f503:
        je asm_target_0041f604
    L_0041f509:
        movsx ebx,word ptr [ebp+466h]
    L_0041f510:
        mov ecx,dword ptr [data_0047781c]
    L_0041f516:
        mov esi,dword ptr [data_00491c10]
    L_0041f51c:
        mov edi,dword ptr [ecx+458h]
    L_0041f522:
        lea ebx,[ebx+ebx+11h]
    L_0041f526:
        call asm_FUN_00449950_00449950
    L_0041f52b:
        mov edx,dword ptr [esp+18h]
    L_0041f52f:
        fld dword ptr [esp+1Ch]
    L_0041f533:
        mov esi,eax
    L_0041f535:
        mov ecx,dword ptr [esi+35Ch]
    L_0041f53b:
        fadd dword ptr [data_00470b4c]
    L_0041f541:
        mov eax,dword ptr [esp+24h]
    L_0041f545:
        or ecx,40000000h
    L_0041f54b:
        mov dword ptr [esi+35Ch],ecx
    L_0041f551:
        mov dword ptr [esi+20h],0
    L_0041f558:
        mov dword ptr [esi+348h],eax
    L_0041f55e:
        fstp dword ptr [esi+340h]
    L_0041f564:
        mov eax,esi
    L_0041f566:
        mov ecx,edi
    L_0041f568:
        mov dword ptr [esi+344h],edx
    L_0041f56e:
        call asm_AnimationObject_LoadScript_0043e710
    L_0041f573:
        mov edx,dword ptr [data_00491c10]
    L_0041f579:
        mov ebx,esi
    L_0041f57b:
        lea eax,[esp+18h]
    L_0041f57f:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0041f584:
        mov eax,dword ptr [esp+44h]
    L_0041f588:
        test eax,eax
    L_0041f58a:
        je short L_0041f604
    L_0041f58c:
        fld dword ptr [esp+1Ch]
    L_0041f590:
        fadd dword ptr [data_00470bcc]
    L_0041f596:
        fcomp dword ptr [data_00470b40]
    L_0041f59c:
        fnstsw ax
    L_0041f59e:
        test ah,41h
    L_0041f5a1:
        jnp short L_0041f604
    L_0041f5a3:
        fld dword ptr [esp+1Ch]
    L_0041f5a7:
        fsub dword ptr [data_00470bcc]
    L_0041f5ad:
        fcomp dword ptr [data_00470b3c]
    L_0041f5b3:
        fnstsw ax
    L_0041f5b5:
        test ah,1
    L_0041f5b8:
        je short L_0041f604
    L_0041f5ba:
        fld dword ptr [esp+20h]
    L_0041f5be:
        fadd dword ptr [data_00470bcc]
    L_0041f5c4:
        fcomp dword ptr [data_00470b04]
    L_0041f5ca:
        fnstsw ax
    L_0041f5cc:
        test ah,41h
    L_0041f5cf:
        jnp short L_0041f604
    L_0041f5d1:
        fld dword ptr [esp+20h]
    L_0041f5d5:
        fsub dword ptr [data_00470bcc]
    L_0041f5db:
        fcomp dword ptr [data_00470b38]
    L_0041f5e1:
        fnstsw ax
    L_0041f5e3:
        test ah,1
    L_0041f5e6:
        je short L_0041f604
    L_0041f5e8:
        mov eax,dword ptr [data_00477818]
    L_0041f5ed:
        push 3F19999Ah
    L_0041f5f2:
        push 0BFC90FDBh
    L_0041f5f7:
        push 0FFFFFFFFh
    L_0041f5f9:
        push 8
    L_0041f5fb:
        lea ecx,[esp+2Ch]
    L_0041f5ff:
        call asm_FUN_0041bb00_0041bb00
    L_0041f604:
        fld dword ptr [esp+1Ch]
    L_0041f608:
        fadd dword ptr [esp+28h]
    L_0041f60c:
        fstp dword ptr [esp+1Ch]
    L_0041f610:
        fld dword ptr [esp+20h]
    L_0041f614:
        fadd dword ptr [esp+2Ch]
    L_0041f618:
        fstp dword ptr [esp+20h]
    L_0041f61c:
        fld dword ptr [esp+24h]
    L_0041f620:
        fadd dword ptr [esp+30h]
    L_0041f624:
        fstp dword ptr [esp+24h]
    L_0041f628:
        fld dword ptr [esp+10h]
    L_0041f62c:
        fadd dword ptr [data_00470cd8]
    L_0041f632:
        fst dword ptr [esp+10h]
    L_0041f636:
        fadd dword ptr [data_00470d1c]
    L_0041f63c:
        fcomp dword ptr [ebp+40h]
    L_0041f63f:
        fnstsw ax
    L_0041f641:
        test ah,5
    L_0041f644:
        jnp asm_target_0041f490
    L_0041f64a:
        mov eax,dword ptr [esp+14h]
    L_0041f64e:
        pop edi
    L_0041f64f:
        pop esi
    L_0041f650:
        pop ebx
    L_0041f651:
        mov dword ptr [ebp+0Ch],1
    L_0041f658:
        pop ebp
    L_0041f659:
        add esp,30h
    L_0041f65c:
        ret 4
    L_0041f65f:
        mov dword ptr [ebp+0Ch],1
    L_0041f666:
        mov eax,edx
    L_0041f668:
        pop ebp
    L_0041f669:
        add esp,30h
    L_0041f66c:
        ret 4
    }
}

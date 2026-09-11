#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041D3D0..0x0041D7B8: FUN_0041d3d0
// Naked body preserves the retail register/stack ABI.

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

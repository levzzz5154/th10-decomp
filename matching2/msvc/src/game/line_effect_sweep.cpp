#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041E260..0x0041E4C0: FUN_0041e260
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041e260_0041e260() {
    __asm {
    L_0041e260:
        sub esp,30h
    L_0041e263:
        push esi
    L_0041e264:
        mov edx,ecx
    L_0041e266:
        mov eax,dword ptr [edx+3Ch]
    L_0041e269:
        push 40C00000h
    L_0041e26e:
        xor esi,esi
    L_0041e270:
        push eax
    L_0041e271:
        lea ecx,[esp+24h]
    L_0041e275:
        mov dword ptr [esp+10h],edx
    L_0041e279:
        mov dword ptr [esp+14h],esi
    L_0041e27d:
        mov dword ptr [esp+0Ch],40C00000h
    L_0041e285:
        call asm_SetPolar_Vector2_0041f800
    L_0041e28a:
        fld dword ptr [esp+1Ch]
    L_0041e28e:
        fadd dword ptr [edx+24h]
    L_0041e291:
        mov ecx,dword ptr [edx+2Ch]
    L_0041e294:
        mov dword ptr [esp+30h],ecx
    L_0041e298:
        mov dword ptr [esp+24h],esi
    L_0041e29c:
        fstp dword ptr [esp+28h]
    L_0041e2a0:
        mov eax,dword ptr [esp+28h]
    L_0041e2a4:
        fld dword ptr [esp+20h]
    L_0041e2a8:
        mov dword ptr [esp+10h],eax
    L_0041e2ac:
        fadd dword ptr [edx+28h]
    L_0041e2af:
        mov eax,dword ptr [esp+30h]
    L_0041e2b3:
        mov dword ptr [esp+18h],eax
    L_0041e2b7:
        fstp dword ptr [esp+2Ch]
    L_0041e2bb:
        mov ecx,dword ptr [esp+2Ch]
    L_0041e2bf:
        fld dword ptr [esp+1Ch]
    L_0041e2c3:
        mov dword ptr [esp+14h],ecx
    L_0041e2c7:
        fadd st(0),st
    L_0041e2c9:
        fstp dword ptr [esp+1Ch]
    L_0041e2cd:
        fld dword ptr [esp+20h]
    L_0041e2d1:
        fadd st(0),st
    L_0041e2d3:
        fstp dword ptr [esp+20h]
    L_0041e2d7:
        fld dword ptr [data_00470cd8]
    L_0041e2dd:
        fcomp dword ptr [edx+40h]
    L_0041e2e0:
        fnstsw ax
    L_0041e2e2:
        test ah,5
    L_0041e2e5:
        jp asm_target_0041e4b1
    L_0041e2eb:
        mov esi,dword ptr [data_00491c10]
    L_0041e2f1:
        push ebx
    L_0041e2f2:
        push ebp
    L_0041e2f3:
        push edi
    L_0041e2f4:
        mov edi,dword ptr [esp+18h]
    L_0041e2f8:
        movsx ebx,word ptr [edx+44Ah]
    L_0041e2ff:
        mov ecx,dword ptr [data_0047781c]
    L_0041e305:
        mov ebp,dword ptr [ecx+458h]
    L_0041e30b:
        inc edi
    L_0041e30c:
        mov dword ptr [esp+18h],edi
    L_0041e310:
        lea ebx,[ebx+ebx+11h]
    L_0041e314:
        call asm_FUN_00449950_00449950
    L_0041e319:
        mov edi,eax
    L_0041e31b:
        mov edx,dword ptr [edi+35Ch]
    L_0041e321:
        fld dword ptr [esp+1Ch]
    L_0041e325:
        fadd dword ptr [data_00470b4c]
    L_0041e32b:
        or edx,40000000h
    L_0041e331:
        mov dword ptr [edi+35Ch],edx
    L_0041e337:
        mov edx,dword ptr [esp+24h]
    L_0041e33b:
        xor esi,esi
    L_0041e33d:
        mov dword ptr [edi+20h],esi
    L_0041e340:
        fstp dword ptr [edi+340h]
    L_0041e346:
        mov ecx,ebp
    L_0041e348:
        fld dword ptr [esp+20h]
    L_0041e34c:
        mov dword ptr [edi+348h],edx
    L_0041e352:
        fadd dword ptr [data_00470b48]
    L_0041e358:
        fstp dword ptr [edi+344h]
    L_0041e35e:
        call asm_AnimationObject_LoadScript_0043e710
    L_0041e363:
        lea eax,[edi+4]
    L_0041e366:
        mov dword ptr [eax+4],esi
    L_0041e369:
        mov dword ptr [eax+8],esi
    L_0041e36c:
        mov esi,dword ptr [data_00491c10]
    L_0041e372:
        mov dword ptr [eax],edi
    L_0041e374:
        mov ecx,dword ptr [esi+72DAD4h]
    L_0041e37a:
        test ecx,ecx
    L_0041e37c:
        jne short L_0041e386
    L_0041e37e:
        mov dword ptr [esi+72DAD4h],eax
    L_0041e384:
        jmp short L_0041e3a2
    L_0041e386:
        mov ecx,dword ptr [esi+72DAD8h]
    L_0041e38c:
        mov edx,dword ptr [ecx+4]
    L_0041e38f:
        test edx,edx
    L_0041e391:
        je short L_0041e39c
    L_0041e393:
        mov dword ptr [eax+4],edx
    L_0041e396:
        mov edx,dword ptr [ecx+4]
    L_0041e399:
        mov dword ptr [edx+8],eax
    L_0041e39c:
        mov dword ptr [ecx+4],eax
    L_0041e39f:
        mov dword ptr [eax+8],ecx
    L_0041e3a2:
        mov dword ptr [esi+72DAD8h],eax
    L_0041e3a8:
        mov ecx,dword ptr [esi+732454h]
    L_0041e3ae:
        inc ecx
    L_0041e3af:
        mov eax,ecx
    L_0041e3b1:
        test eax,eax
    L_0041e3b3:
        mov dword ptr [esi+732454h],ecx
    L_0041e3b9:
        jne short L_0041e3c2
    L_0041e3bb:
        inc eax
    L_0041e3bc:
        mov dword ptr [esi+732454h],eax
    L_0041e3c2:
        mov eax,dword ptr [esi+732454h]
    L_0041e3c8:
        mov dword ptr [edi],eax
    L_0041e3ca:
        mov eax,dword ptr [esp+44h]
    L_0041e3ce:
        test eax,eax
    L_0041e3d0:
        je short L_0041e450
    L_0041e3d2:
        fld dword ptr [esp+1Ch]
    L_0041e3d6:
        fadd dword ptr [data_00470bcc]
    L_0041e3dc:
        fcomp dword ptr [data_00470b40]
    L_0041e3e2:
        fnstsw ax
    L_0041e3e4:
        test ah,41h
    L_0041e3e7:
        jnp short L_0041e450
    L_0041e3e9:
        fld dword ptr [esp+1Ch]
    L_0041e3ed:
        fsub dword ptr [data_00470bcc]
    L_0041e3f3:
        fcomp dword ptr [data_00470b3c]
    L_0041e3f9:
        fnstsw ax
    L_0041e3fb:
        test ah,1
    L_0041e3fe:
        je short L_0041e450
    L_0041e400:
        fld dword ptr [esp+20h]
    L_0041e404:
        fadd dword ptr [data_00470bcc]
    L_0041e40a:
        fcomp dword ptr [data_00470b04]
    L_0041e410:
        fnstsw ax
    L_0041e412:
        test ah,41h
    L_0041e415:
        jnp short L_0041e450
    L_0041e417:
        fld dword ptr [esp+20h]
    L_0041e41b:
        fsub dword ptr [data_00470bcc]
    L_0041e421:
        fcomp dword ptr [data_00470b38]
    L_0041e427:
        fnstsw ax
    L_0041e429:
        test ah,1
    L_0041e42c:
        je short L_0041e450
    L_0041e42e:
        mov eax,dword ptr [data_00477818]
    L_0041e433:
        push 3F19999Ah
    L_0041e438:
        push 0BFC90FDBh
    L_0041e43d:
        push 0FFFFFFFFh
    L_0041e43f:
        push 8
    L_0041e441:
        lea ecx,[esp+2Ch]
    L_0041e445:
        call asm_FUN_0041bb00_0041bb00
    L_0041e44a:
        mov esi,dword ptr [data_00491c10]
    L_0041e450:
        fld dword ptr [esp+1Ch]
    L_0041e454:
        mov ecx,dword ptr [esp+14h]
    L_0041e458:
        fadd dword ptr [esp+28h]
    L_0041e45c:
        mov edx,ecx
    L_0041e45e:
        fstp dword ptr [esp+1Ch]
    L_0041e462:
        fld dword ptr [esp+20h]
    L_0041e466:
        fadd dword ptr [esp+2Ch]
    L_0041e46a:
        fstp dword ptr [esp+20h]
    L_0041e46e:
        fld dword ptr [esp+24h]
    L_0041e472:
        fadd dword ptr [esp+30h]
    L_0041e476:
        fstp dword ptr [esp+24h]
    L_0041e47a:
        fld dword ptr [esp+10h]
    L_0041e47e:
        fadd dword ptr [data_00470cd8]
    L_0041e484:
        fst dword ptr [esp+10h]
    L_0041e488:
        fadd dword ptr [data_00470d1c]
    L_0041e48e:
        fcomp dword ptr [ecx+40h]
    L_0041e491:
        fnstsw ax
    L_0041e493:
        test ah,5
    L_0041e496:
        jnp asm_target_0041e2f4
    L_0041e49c:
        mov eax,dword ptr [esp+18h]
    L_0041e4a0:
        pop edi
    L_0041e4a1:
        pop ebp
    L_0041e4a2:
        pop ebx
    L_0041e4a3:
        mov dword ptr [edx+0Ch],1
    L_0041e4aa:
        pop esi
    L_0041e4ab:
        add esp,30h
    L_0041e4ae:
        ret 4
    L_0041e4b1:
        mov eax,esi
    L_0041e4b3:
        mov dword ptr [edx+0Ch],1
    L_0041e4ba:
        pop esi
    L_0041e4bb:
        add esp,30h
    L_0041e4be:
        ret 4
    }
}

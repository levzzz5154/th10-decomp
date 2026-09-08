#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B430..0x0042B4B5: EffectManager_ResetAndPublishRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EffectManager_ResetAndPublishRetail_0042b430() {
    __asm {
    L_0042b430:
        lea edx,[ebx+18h]
    L_0042b433:
        push esi
    L_0042b434:
        push edi
    L_0042b435:
        mov edi,dword ptr [edx+6Ch]
    L_0042b438:
        mov esi,0FFFFFFFEh
    L_0042b43d:
        and edi,esi
    L_0042b43f:
        mov dword ptr [edx+6Ch],edi
    L_0042b442:
        and dword ptr [edx+0B0h],esi
    L_0042b448:
        and dword ptr [edx+0FCh],esi
    L_0042b44e:
        and dword ptr [edx+128h],esi
    L_0042b454:
        and dword ptr [edx+174h],esi
    L_0042b45a:
        and dword ptr [edx+1B0h],esi
    L_0042b460:
        and dword ptr [edx+1FCh],esi
    L_0042b466:
        and dword ptr [edx+228h],esi
    L_0042b46c:
        and dword ptr [edx+378h],esi
    L_0042b472:
        xor eax,eax
    L_0042b474:
        mov ecx,0EBh
    L_0042b479:
        mov edi,edx
    L_0042b47b:
        rep stosd
    L_0042b47d:
        mov word ptr [edx+384h],0FFFFh
    L_0042b486:
        lea eax,[ebx+3F0h]
    L_0042b48c:
        mov ecx,2D3h
    L_0042b491:
        and dword ptr [eax],esi
    L_0042b493:
        add eax,40h
    L_0042b496:
        dec ecx
    L_0042b497:
        jne short L_0042b491
    L_0042b499:
        xor eax,eax
    L_0042b49b:
        mov ecx,2E21h
    L_0042b4a0:
        mov edi,ebx
    L_0042b4a2:
        rep stosd
    L_0042b4a4:
        mov eax,dword ptr [ebx]
    L_0042b4a6:
        or eax,2
    L_0042b4a9:
        pop edi
    L_0042b4aa:
        mov dword ptr [ebx],eax
    L_0042b4ac:
        mov dword ptr [data_00477840],ebx
    L_0042b4b2:
        mov eax,ebx
    L_0042b4b4:
        pop esi
    L_0042b4b5:
        ret
    }
}

// 0x0042C920..0x0042C9EB: FUN_0042c920
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042c920_0042c920() {
    __asm {
    L_0042c920:
        mov dword ptr [edx],46ECF0h
    L_0042c926:
        xor eax,eax
    L_0042c928:
        mov dword ptr [edx+0B0h],eax
    L_0042c92e:
        mov dword ptr [edx+24h],eax
    L_0042c931:
        mov dword ptr [edx+0F8h],eax
    L_0042c937:
        push esi
    L_0042c938:
        mov esi,1
    L_0042c93d:
        mov dword ptr [edx+0F4h],esi
    L_0042c943:
        mov ecx,3E7h
    L_0042c948:
        mov dword ptr [edx+2Ch],ecx
    L_0042c94b:
        mov dword ptr [edx+188h],eax
    L_0042c951:
        mov dword ptr [edx+0FCh],eax
    L_0042c957:
        mov dword ptr [edx+1D0h],eax
    L_0042c95d:
        mov dword ptr [edx+1CCh],esi
    L_0042c963:
        mov dword ptr [edx+104h],ecx
    L_0042c969:
        mov dword ptr [edx+260h],eax
    L_0042c96f:
        mov dword ptr [edx+1D4h],eax
    L_0042c975:
        mov dword ptr [edx+2A8h],eax
    L_0042c97b:
        mov dword ptr [edx+2A4h],esi
    L_0042c981:
        mov dword ptr [edx+1DCh],ecx
    L_0042c987:
        push edi
    L_0042c988:
        and dword ptr [edx+2C0h],0FFFFFFFEh
    L_0042c98f:
        mov dword ptr [edx+5980h],eax
    L_0042c995:
        mov dword ptr [edx+58F4h],eax
    L_0042c99b:
        mov dword ptr [edx+59C8h],eax
    L_0042c9a1:
        mov dword ptr [edx+58FCh],ecx
    L_0042c9a7:
        mov dword ptr [edx+59C4h],esi
    L_0042c9ad:
        mov dword ptr [edx+5AB4h],eax
    L_0042c9b3:
        mov dword ptr [edx+5AB8h],eax
    L_0042c9b9:
        mov dword ptr [edx+5ABCh],eax
    L_0042c9bf:
        mov dword ptr [edx+5AC0h],eax
    L_0042c9c5:
        mov dword ptr [edx+5AB0h],4703E4h
    L_0042c9cf:
        mov ecx,16B3h
    L_0042c9d4:
        mov edi,edx
    L_0042c9d6:
        rep stosd
    L_0042c9d8:
        mov eax,dword ptr [edx+4]
    L_0042c9db:
        or eax,2
    L_0042c9de:
        pop edi
    L_0042c9df:
        mov dword ptr [edx+4],eax
    L_0042c9e2:
        mov dword ptr [data_0047784c],edx
    L_0042c9e8:
        mov eax,edx
    L_0042c9ea:
        pop esi
    L_0042c9eb:
        ret
    }
}

// 0x0043E5A0..0x0043E703: ?AnimationObject_ConfigureFromResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_ConfigureFromResource_0043e5a0() {
    __asm {
    L_0043e5a0:
        push esi
    L_0043e5a1:
        mov esi,ecx
    L_0043e5a3:
        push edi
    L_0043e5a4:
        mov edi,dword ptr [esi+108h]
    L_0043e5aa:
        xor ecx,ecx
    L_0043e5ac:
        cmp edi,ecx
    L_0043e5ae:
        je asm_target_0043e6fe
    L_0043e5b4:
        cmp dword ptr [esi+124h],ecx
    L_0043e5ba:
        jne asm_target_0043e6fe
    L_0043e5c0:
        mov word ptr [eax+384h],dx
    L_0043e5c7:
        imul edx,44h
    L_0043e5ca:
        mov dword ptr [eax+308h],esi
    L_0043e5d0:
        mov esi,dword ptr [esi+118h]
    L_0043e5d6:
        add edx,esi
    L_0043e5d8:
        mov dword ptr [eax+394h],edx
    L_0043e5de:
        mov edx,dword ptr [edx+34h]
    L_0043e5e1:
        mov dword ptr [eax+4Ch],edx
    L_0043e5e4:
        mov edx,dword ptr [eax+394h]
    L_0043e5ea:
        mov edx,dword ptr [edx+30h]
    L_0043e5ed:
        mov dword ptr [eax+50h],edx
    L_0043e5f0:
        mov dword ptr [eax+274h],ecx
    L_0043e5f6:
        mov dword ptr [eax+270h],ecx
    L_0043e5fc:
        mov dword ptr [eax+26Ch],ecx
    L_0043e602:
        mov dword ptr [eax+268h],ecx
    L_0043e608:
        mov dword ptr [eax+260h],ecx
    L_0043e60e:
        mov dword ptr [eax+25Ch],ecx
    L_0043e614:
        mov dword ptr [eax+258h],ecx
    L_0043e61a:
        mov dword ptr [eax+254h],ecx
    L_0043e620:
        mov dword ptr [eax+24Ch],ecx
    L_0043e626:
        mov dword ptr [eax+248h],ecx
    L_0043e62c:
        mov dword ptr [eax+244h],ecx
    L_0043e632:
        mov dword ptr [eax+240h],ecx
    L_0043e638:
        lea esi,[eax+23Ch]
    L_0043e63e:
        mov edx,3F800000h
    L_0043e643:
        mov dword ptr [esi+3Ch],edx
    L_0043e646:
        mov dword ptr [esi+28h],edx
    L_0043e649:
        mov dword ptr [esi+14h],edx
    L_0043e64c:
        mov dword ptr [esi],edx
    L_0043e64e:
        mov dword ptr [eax+2F4h],ecx
    L_0043e654:
        mov dword ptr [eax+2F0h],ecx
    L_0043e65a:
        mov dword ptr [eax+2ECh],ecx
    L_0043e660:
        mov dword ptr [eax+2E8h],ecx
    L_0043e666:
        mov dword ptr [eax+2E0h],ecx
    L_0043e66c:
        mov dword ptr [eax+2DCh],ecx
    L_0043e672:
        mov dword ptr [eax+2D8h],ecx
    L_0043e678:
        mov dword ptr [eax+2D4h],ecx
    L_0043e67e:
        mov dword ptr [eax+2CCh],ecx
    L_0043e684:
        mov dword ptr [eax+2C8h],ecx
    L_0043e68a:
        mov dword ptr [eax+2C4h],ecx
    L_0043e690:
        mov dword ptr [eax+2C0h],ecx
    L_0043e696:
        mov dword ptr [eax+2F8h],edx
    L_0043e69c:
        mov dword ptr [eax+2E4h],edx
    L_0043e6a2:
        mov dword ptr [eax+2D0h],edx
    L_0043e6a8:
        mov dword ptr [eax+2BCh],edx
    L_0043e6ae:
        mov ecx,dword ptr [eax+394h]
    L_0043e6b4:
        fld dword ptr [eax+4Ch]
    L_0043e6b7:
        lea edi,[eax+27Ch]
    L_0043e6bd:
        fmul dword ptr [data_00470b7c]
    L_0043e6c3:
        fstp dword ptr [esi]
    L_0043e6c5:
        fld dword ptr [eax+50h]
    L_0043e6c8:
        fmul dword ptr [data_00470b7c]
    L_0043e6ce:
        fstp dword ptr [eax+250h]
    L_0043e6d4:
        fld dword ptr [ecx+38h]
    L_0043e6d7:
        fdiv dword ptr [ecx+1Ch]
    L_0043e6da:
        fmul dword ptr [eax+4Ch]
    L_0043e6dd:
        fstp dword ptr [eax+2BCh]
    L_0043e6e3:
        fld dword ptr [ecx+3Ch]
    L_0043e6e6:
        fdiv dword ptr [ecx+18h]
    L_0043e6e9:
        mov ecx,10h
    L_0043e6ee:
        rep movsd
    L_0043e6f0:
        pop edi
    L_0043e6f1:
        pop esi
    L_0043e6f2:
        fmul dword ptr [eax+50h]
    L_0043e6f5:
        fstp dword ptr [eax+2D0h]
    L_0043e6fb:
        xor eax,eax
    L_0043e6fd:
        ret
    L_0043e6fe:
        pop edi
    L_0043e6ff:
        or eax,0FFFFFFFFh
    L_0043e702:
        pop esi
    L_0043e703:
        ret
    }
}

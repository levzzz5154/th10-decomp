#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436210..0x0043625F: ?MemoryFile_RemoveNode@@
// Naked body preserves the retail register/stack ABI.

// 0x0043D390..0x0043D63B: FUN_0043d390
// Naked body preserves the retail register/stack ABI.
// BLOCKED (D3601): closest_byte_count=61/684; first_diff=0x0043D390;
// residual_class=fastcall index/state ABI, security-cookie frame, resource
// parser object/vtable layout, and lock-buffer callback sequencing;
// variants_tested=live Ghidra decompilation with caller 0x0043CD30 and callee
// 0x0043D250, plus MSVC 13.10 readable RIFF candidate (281-byte extent, 61
// non-relocation bytes equal); next_lever=native-LTCG schema2 with the real
// sound-device caller, Resource_FindChunk contract, and buffer vtable layout.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d390_0043d390() {
    __asm {
    L_0043d390:
        sub esp,5Ch
    L_0043d393:
        mov eax,dword ptr [data_00473660]
    L_0043d398:
        xor eax,esp
    L_0043d39a:
        mov dword ptr [esp+58h],eax
    L_0043d39e:
        mov eax,dword ptr [esp+60h]
    L_0043d3a2:
        push ebx
    L_0043d3a3:
        mov ebx,edx
    L_0043d3a5:
        mov dword ptr [esp+8],eax
    L_0043d3a9:
        mov eax,dword ptr [ebx+610h]
    L_0043d3af:
        test eax,eax
    L_0043d3b1:
        push esi
    L_0043d3b2:
        mov esi,ecx
    L_0043d3b4:
        jne short L_0043d3cb
    L_0043d3b6:
        pop esi
    L_0043d3b7:
        xor eax,eax
    L_0043d3b9:
        pop ebx
    L_0043d3ba:
        mov ecx,dword ptr [esp+58h]
    L_0043d3be:
        xor ecx,esp
    L_0043d3c0:
        call asm_security_check_cookie_00458ea5
    L_0043d3c5:
        add esp,5Ch
    L_0043d3c8:
        ret 4
    L_0043d3cb:
        mov eax,dword ptr [ebx+esi*4+8]
    L_0043d3cf:
        test eax,eax
    L_0043d3d1:
        push edi
    L_0043d3d2:
        lea edi,[ebx+esi*4+8]
    L_0043d3d6:
        mov dword ptr [esp+24h],edi
    L_0043d3da:
        je short L_0043d3e8
    L_0043d3dc:
        mov ecx,dword ptr [eax]
    L_0043d3de:
        push eax
    L_0043d3df:
        call dword ptr [ecx+8]
    L_0043d3e2:
        mov dword ptr [edi],0
    L_0043d3e8:
        mov eax,dword ptr [ebx+esi*4+5230h]
    L_0043d3ef:
        test eax,eax
    L_0043d3f1:
        push ebp
    L_0043d3f2:
        jne short L_0043d41b
    L_0043d3f4:
        mov edi,dword ptr [data_004660ac]
    L_0043d3fa:
        mov ebp,2
    L_0043d3ff:
        nop
    L_0043d400:
        push 0Ah
    L_0043d402:
        call edi
    L_0043d404:
        cmp dword ptr [data_004977b4],ebp
    L_0043d40a:
        je asm_target_0043d625
    L_0043d410:
        mov eax,dword ptr [ebx+esi*4+5230h]
    L_0043d417:
        test eax,eax
    L_0043d419:
        je short L_0043d400
    L_0043d41b:
        mov edi,dword ptr [ebx+esi*4+5230h]
    L_0043d422:
        test edi,edi
    L_0043d424:
        mov dword ptr [esp+10h],edi
    L_0043d428:
        mov dword ptr [ebx+esi*4+5230h],0
    L_0043d433:
        je short L_0043d466
    L_0043d435:
        push 4
    L_0043d437:
        push 46FDA4h
    L_0043d43c:
        push edi
    L_0043d43d:
        call asm_strncmp_00452f80
    L_0043d442:
        add esp,0Ch
    L_0043d445:
        test eax,eax
    L_0043d447:
        je short L_0043d47e
    L_0043d449:
        mov edx,dword ptr [esp+14h]
    L_0043d44d:
        push edx
    L_0043d44e:
        push 46FD88h
    L_0043d453:
        mov ecx,474F70h
    L_0043d458:
        call asm_TextLog_Append_0044b810
    L_0043d45d:
        push edi
    L_0043d45e:
        call asm_free_00452422
    L_0043d463:
        add esp,0Ch
    L_0043d466:
        pop ebp
    L_0043d467:
        pop edi
    L_0043d468:
        pop esi
    L_0043d469:
        or eax,0FFFFFFFFh
    L_0043d46c:
        pop ebx
    L_0043d46d:
        mov ecx,dword ptr [esp+58h]
    L_0043d471:
        xor ecx,esp
    L_0043d473:
        call asm_security_check_cookie_00458ea5
    L_0043d478:
        add esp,5Ch
    L_0043d47b:
        ret 4
    L_0043d47e:
        mov ebp,dword ptr [edi+4]
    L_0043d481:
        lea esi,[edi+4]
    L_0043d484:
        push 4
    L_0043d486:
        add esi,4
    L_0043d489:
        push 46FD80h
    L_0043d48e:
        push esi
    L_0043d48f:
        call asm_strncmp_00452f80
    L_0043d494:
        add esp,0Ch
    L_0043d497:
        test eax,eax
    L_0043d499:
        je short L_0043d4a7
    L_0043d49b:
        mov eax,dword ptr [esp+14h]
    L_0043d49f:
        push eax
    L_0043d4a0:
        push 46FD64h
    L_0043d4a5:
        jmp short L_0043d453
    L_0043d4a7:
        add esi,4
    L_0043d4aa:
        add ebp,0FFFFFFF4h
    L_0043d4ad:
        push 46FD5Ch
    L_0043d4b2:
        mov eax,ebp
    L_0043d4b4:
        lea edi,[esp+30h]
    L_0043d4b8:
        mov ecx,esi
    L_0043d4ba:
        call asm_Resource_FindChunk_0043d250
    L_0043d4bf:
        test eax,eax
    L_0043d4c1:
        je short L_0043d4fb
    L_0043d4c3:
        mov ecx,dword ptr [eax]
    L_0043d4c5:
        mov dword ptr [esp+30h],ecx
    L_0043d4c9:
        mov edx,dword ptr [eax+4]
    L_0043d4cc:
        mov dword ptr [esp+34h],edx
    L_0043d4d0:
        mov ecx,dword ptr [eax+8]
    L_0043d4d3:
        mov dword ptr [esp+38h],ecx
    L_0043d4d7:
        mov edx,dword ptr [eax+0Ch]
    L_0043d4da:
        mov dword ptr [esp+3Ch],edx
    L_0043d4de:
        mov ax,word ptr [eax+10h]
    L_0043d4e2:
        mov word ptr [esp+40h],ax
    L_0043d4e7:
        push 46FD54h
    L_0043d4ec:
        mov eax,ebp
    L_0043d4ee:
        mov ecx,esi
    L_0043d4f0:
        call asm_Resource_FindChunk_0043d250
    L_0043d4f5:
        mov ebp,eax
    L_0043d4f7:
        test ebp,ebp
    L_0043d4f9:
        jne short L_0043d519
    L_0043d4fb:
        mov ecx,dword ptr [esp+14h]
    L_0043d4ff:
        push ecx
    L_0043d500:
        push 46FD64h
    L_0043d505:
        mov ecx,474F70h
    L_0043d50a:
        call asm_TextLog_Append_0044b810
    L_0043d50f:
        mov edx,dword ptr [esp+18h]
    L_0043d513:
        push edx
    L_0043d514:
        jmp asm_target_0043d45e
    L_0043d519:
        mov edi,dword ptr [esp+28h]
    L_0043d51d:
        mov ebx,dword ptr [ebx]
    L_0043d51f:
        mov esi,dword ptr [esp+2Ch]
    L_0043d523:
        xor eax,eax
    L_0043d525:
        mov dword ptr [esp+44h],eax
    L_0043d529:
        mov dword ptr [esp+48h],eax
    L_0043d52d:
        mov dword ptr [esp+4Ch],eax
    L_0043d531:
        mov dword ptr [esp+50h],eax
    L_0043d535:
        mov dword ptr [esp+54h],eax
    L_0043d539:
        mov dword ptr [esp+58h],eax
    L_0043d53d:
        mov dword ptr [esp+5Ch],eax
    L_0043d541:
        mov dword ptr [esp+60h],eax
    L_0043d545:
        push eax
    L_0043d546:
        mov dword ptr [esp+68h],eax
    L_0043d54a:
        push edi
    L_0043d54b:
        lea eax,[esp+4Ch]
    L_0043d54f:
        lea ecx,[esp+38h]
    L_0043d553:
        push eax
    L_0043d554:
        mov dword ptr [esp+50h],24h
    L_0043d55c:
        mov dword ptr [esp+54h],80C8h
    L_0043d564:
        mov dword ptr [esp+58h],esi
    L_0043d568:
        mov dword ptr [esp+60h],ecx
    L_0043d56c:
        mov edx,dword ptr [ebx]
    L_0043d56e:
        push ebx
    L_0043d56f:
        call dword ptr [edx+0Ch]
    L_0043d572:
        test eax,eax
    L_0043d574:
        jge short L_0043d588
    L_0043d576:
        mov ecx,dword ptr [esp+10h]
    L_0043d57a:
        push ecx
    L_0043d57b:
        call asm_free_00452422
    L_0043d580:
        add esp,4
    L_0043d583:
        jmp asm_target_0043d466
    L_0043d588:
        mov eax,dword ptr [edi]
    L_0043d58a:
        mov edx,dword ptr [eax]
    L_0043d58c:
        push 0
    L_0043d58e:
        lea ecx,[esp+20h]
    L_0043d592:
        push ecx
    L_0043d593:
        lea ecx,[esp+28h]
    L_0043d597:
        push ecx
    L_0043d598:
        lea ecx,[esp+24h]
    L_0043d59c:
        push ecx
    L_0043d59d:
        lea ecx,[esp+34h]
    L_0043d5a1:
        push ecx
    L_0043d5a2:
        push esi
    L_0043d5a3:
        push 0
    L_0043d5a5:
        push eax
    L_0043d5a6:
        call dword ptr [edx+2Ch]
    L_0043d5a9:
        test eax,eax
    L_0043d5ab:
        jge short L_0043d5bf
    L_0043d5ad:
        mov edx,dword ptr [esp+10h]
    L_0043d5b1:
        push edx
    L_0043d5b2:
        call asm_free_00452422
    L_0043d5b7:
        add esp,4
    L_0043d5ba:
        jmp asm_target_0043d466
    L_0043d5bf:
        mov ecx,dword ptr [esp+18h]
    L_0043d5c3:
        mov edi,dword ptr [esp+24h]
    L_0043d5c7:
        mov eax,ecx
    L_0043d5c9:
        shr ecx,2
    L_0043d5cc:
        mov esi,ebp
    L_0043d5ce:
        rep movsd
    L_0043d5d0:
        mov ecx,eax
    L_0043d5d2:
        and ecx,3
    L_0043d5d5:
        rep movsb
    L_0043d5d7:
        mov ecx,dword ptr [esp+1Ch]
    L_0043d5db:
        test ecx,ecx
    L_0043d5dd:
        je short L_0043d5fc
    L_0043d5df:
        mov edx,dword ptr [esp+18h]
    L_0043d5e3:
        mov edi,dword ptr [esp+20h]
    L_0043d5e7:
        mov eax,ecx
    L_0043d5e9:
        shr ecx,2
    L_0043d5ec:
        lea esi,[edx+ebp]
    L_0043d5ef:
        rep movsd
    L_0043d5f1:
        mov ecx,eax
    L_0043d5f3:
        and ecx,3
    L_0043d5f6:
        rep movsb
    L_0043d5f8:
        mov ecx,dword ptr [esp+1Ch]
    L_0043d5fc:
        mov edx,dword ptr [esp+28h]
    L_0043d600:
        mov eax,dword ptr [edx]
    L_0043d602:
        mov edx,dword ptr [eax]
    L_0043d604:
        push ecx
    L_0043d605:
        mov ecx,dword ptr [esp+24h]
    L_0043d609:
        push ecx
    L_0043d60a:
        mov ecx,dword ptr [esp+20h]
    L_0043d60e:
        push ecx
    L_0043d60f:
        mov ecx,dword ptr [esp+30h]
    L_0043d613:
        push ecx
    L_0043d614:
        push eax
    L_0043d615:
        call dword ptr [edx+4Ch]
    L_0043d618:
        mov edx,dword ptr [esp+10h]
    L_0043d61c:
        push edx
    L_0043d61d:
        call asm_free_00452422
    L_0043d622:
        add esp,4
    L_0043d625:
        mov ecx,dword ptr [esp+68h]
    L_0043d629:
        pop ebp
    L_0043d62a:
        pop edi
    L_0043d62b:
        pop esi
    L_0043d62c:
        pop ebx
    L_0043d62d:
        xor ecx,esp
    L_0043d62f:
        xor eax,eax
    L_0043d631:
        call asm_security_check_cookie_00458ea5
    L_0043d636:
        add esp,5Ch
    L_0043d639:
        ret 4
    }
}

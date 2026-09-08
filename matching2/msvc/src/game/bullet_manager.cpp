#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00402720_00402720() {
    __asm {
    L_00402720:
        sub esp,10h
    L_00402723:
        push ebx
    L_00402724:
        mov ebx,eax
    L_00402726:
        mov eax,dword ptr [ebx+2A18h]
    L_0040272c:
        test al,8
    L_0040272e:
        jne asm_target_00402846
    L_00402734:
        test al,4
    L_00402736:
        je short L_00402745
    L_00402738:
        cmp dword ptr [ebx+2A20h],3Ch
    L_0040273f:
        jge asm_target_00402846
    L_00402745:
        mov dword ptr [esp+8],0
    L_0040274d:
        mov ecx,dword ptr [esp+8]
    L_00402751:
        lea eax,[ebx+2B3Ch]
    L_00402757:
        mov dword ptr [eax],ecx
    L_00402759:
        push esi
    L_0040275a:
        mov dword ptr [esp+10h],0
    L_00402762:
        mov edx,dword ptr [esp+10h]
    L_00402766:
        mov dword ptr [eax+4],edx
    L_00402769:
        push edi
    L_0040276a:
        mov dword ptr [esp+18h],0
    L_00402772:
        mov ecx,dword ptr [esp+18h]
    L_00402776:
        lea edx,[ebx+2A58h]
    L_0040277c:
        mov dword ptr [eax+8],ecx
    L_0040277f:
        push edx
    L_00402780:
        lea eax,[ebx+2A70h]
    L_00402786:
        push eax
    L_00402787:
        mov dword ptr [ebx+2B34h],0
    L_00402791:
        mov dword ptr [ebx+2B38h],0
    L_0040279b:
        call asm_D3DXVec3Normalize_0045217c
    L_004027a0:
        mov dword ptr [ebx+1EE8h],808080h
    L_004027aa:
        call asm_FUN_00403990_00403990
    L_004027af:
        push ebx
    L_004027b0:
        call asm_FUN_00403c80_00403c80
    L_004027b5:
        lea esi,[ebx+180h]
    L_004027bb:
        mov edi,8
    L_004027c0:
        push esi
    L_004027c1:
        call asm_FUN_0043ee30_0043ee30
    L_004027c6:
        add esi,3ACh
    L_004027cc:
        dec edi
    L_004027cd:
        jne short L_004027c0
    L_004027cf:
        mov eax,dword ptr [ebx+1EECh]
    L_004027d5:
        test eax,eax
    L_004027d7:
        je short L_0040281b
    L_004027d9:
        mov ecx,dword ptr [data_00476f78]
    L_004027df:
        lea edx,[ebx+1F08h]
    L_004027e5:
        push edx
    L_004027e6:
        mov dword ptr [esp+10h],ecx
    L_004027ea:
        mov dword ptr [data_00476f78],3F800000h
    L_004027f4:
        call asm_FUN_0043ee30_0043ee30
    L_004027f9:
        lea eax,[ebx+22B4h]
    L_004027ff:
        push eax
    L_00402800:
        call asm_FUN_0043ee30_0043ee30
    L_00402805:
        lea ecx,[ebx+2660h]
    L_0040280b:
        push ecx
    L_0040280c:
        call asm_FUN_0043ee30_0043ee30
    L_00402811:
        mov edx,dword ptr [esp+0Ch]
    L_00402815:
        mov dword ptr [data_00476f78],edx
    L_0040281b:
        lea esi,[ebx+2A4Ch]
    L_00402821:
        mov ecx,46h
    L_00402826:
        mov edi,491D7Ch
    L_0040282b:
        mov dword ptr [ebx+1EECh],0
    L_00402835:
        rep movsd
    L_00402837:
        mov eax,dword ptr [ebx+2A34h]
    L_0040283d:
        inc eax
    L_0040283e:
        pop edi
    L_0040283f:
        mov dword ptr [ebx+2A34h],eax
    L_00402845:
        pop esi
    L_00402846:
        mov eax,1
    L_0040284b:
        pop ebx
    L_0040284c:
        add esp,10h
    L_0040284f:
        ret
    }
}

// 0x00404450..0x004044B4: FUN_00404450
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404450_00404450() {
    __asm {
    L_00404450:
        push ecx
    L_00404451:
        push ebx
    L_00404452:
        push ebp
    L_00404453:
        mov ebp,dword ptr [esp+10h]
    L_00404457:
        mov eax,dword ptr [ebp+8]
    L_0040445a:
        mov ebx,dword ptr [eax+4]
    L_0040445d:
        mov ecx,2
    L_00404462:
        or ebx,ecx
    L_00404464:
        mov dword ptr [eax+4],ebx
    L_00404467:
        mov eax,dword ptr [ebp+0Ch]
    L_0040446a:
        push esi
    L_0040446b:
        push edi
    L_0040446c:
        or dword ptr [eax+4],ecx
    L_0040446f:
        mov eax,dword ptr [ebp+2A40h]
    L_00404475:
        or dword ptr [eax+4],ecx
    L_00404478:
        mov ecx,dword ptr [ebp+10h]
    L_0040447b:
        xor eax,eax
    L_0040447d:
        cmp word ptr [ecx],ax
    L_00404480:
        mov dword ptr [esp+18h],eax
    L_00404484:
        mov dword ptr [esp+10h],eax
    L_00404488:
        jle asm_target_00404518
    L_0040448e:
        mov edi,edi
    L_00404490:
        mov edx,dword ptr [ebp+14h]
    L_00404493:
        mov ecx,dword ptr [edx+eax*4]
    L_00404496:
        mov byte ptr [ecx+3],1
    L_0040449a:
        mov edx,dword ptr [ebp+14h]
    L_0040449d:
        mov edi,dword ptr [edx+eax*4]
    L_004044a0:
        add edi,1Ch
    L_004044a3:
        cmp word ptr [edi],0
    L_004044a7:
        TH10_REL8(0x7c, 0x004044a7, VA_asm_target_004044fb)
    L_004044a9:
        mov ebx,dword ptr [esp+18h]
    L_004044ad:
        imul ebx,3ACh
    L_004044b3:
        TH10_REL8(0xeb, 0x004044b3, VA_asm_FUN_00404450_part_004044c0)
    }
}

// 0x004044C0..0x00404525: FUN_00404450
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404450_part_004044c0() {
    __asm {
    L_004044c0:
        mov esi,dword ptr [ebp+17Ch]
    L_004044c6:
        mov ecx,dword ptr [ebp+178h]
    L_004044cc:
        movsx eax,word ptr [edi+4]
    L_004044d0:
        add esi,ebx
    L_004044d2:
        push ecx
    L_004044d3:
        call asm_FUN_00404f30_00404f30
    L_004044d8:
        mov eax,dword ptr [esp+18h]
    L_004044dc:
        movsx edx,word ptr [edi+2]
    L_004044e0:
        mov word ptr [edi+6],ax
    L_004044e4:
        inc eax
    L_004044e5:
        add edi,edx
    L_004044e7:
        add ebx,3ACh
    L_004044ed:
        cmp word ptr [edi],0
    L_004044f1:
        mov dword ptr [esp+18h],eax
    L_004044f5:
        jge short L_004044c0
    L_004044f7:
        mov eax,dword ptr [esp+10h]
    L_004044fb:
        mov ecx,dword ptr [ebp+10h]
    L_004044fe:
        movsx edx,word ptr [ecx]
    L_00404501:
        inc eax
    L_00404502:
        cmp eax,edx
    L_00404504:
        mov dword ptr [esp+10h],eax
    L_00404508:
        TH10_REL8(0x7c, 0x00404508, VA_asm_target_00404490)
    L_0040450a:
        mov eax,dword ptr [ebp+1Ch]
    L_0040450d:
        pop edi
    L_0040450e:
        pop esi
    L_0040450f:
        mov dword ptr [ebp+4Ch],eax
    L_00404512:
        pop ebp
    L_00404513:
        pop ebx
    L_00404514:
        pop ecx
    L_00404515:
        ret 4
    L_00404518:
        mov ecx,dword ptr [ebp+1Ch]
    L_0040451b:
        pop edi
    L_0040451c:
        pop esi
    L_0040451d:
        mov dword ptr [ebp+4Ch],ecx
    L_00404520:
        pop ebp
    L_00404521:
        pop ebx
    L_00404522:
        pop ecx
    L_00404523:
        ret 4
    }
}

// 0x00404F30..0x00404FF9: FUN_00404f30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404f30_00404f30() {
    __asm {
    L_00404f30:
        sub esp,0Ch
    L_00404f33:
        push ebx
    L_00404f34:
        mov edx,esi
    L_00404f36:
        mov ebx,eax
    L_00404f38:
        call asm_InitializeEntity_00401de0
    L_00404f3d:
        mov dword ptr [esp+4],0
    L_00404f45:
        mov ecx,dword ptr [esp+4]
    L_00404f49:
        lea eax,[esi+340h]
    L_00404f4f:
        mov dword ptr [eax],ecx
    L_00404f51:
        mov dword ptr [esp+8],0
    L_00404f59:
        mov edx,dword ptr [esp+8]
    L_00404f5d:
        mov dword ptr [eax+4],edx
    L_00404f60:
        mov dword ptr [esp+0Ch],0
    L_00404f68:
        mov ecx,dword ptr [esp+0Ch]
    L_00404f6c:
        mov dword ptr [eax+8],ecx
    L_00404f6f:
        mov dword ptr [esp+4],0
    L_00404f77:
        mov eax,dword ptr [esp+4]
    L_00404f7b:
        lea edx,[esi+334h]
    L_00404f81:
        mov dword ptr [edx],eax
    L_00404f83:
        mov dword ptr [esp+8],0
    L_00404f8b:
        mov ecx,dword ptr [esp+8]
    L_00404f8f:
        mov dword ptr [edx+4],ecx
    L_00404f92:
        mov dword ptr [esp+0Ch],0
    L_00404f9a:
        mov eax,dword ptr [esp+0Ch]
    L_00404f9e:
        mov dword ptr [edx+8],eax
    L_00404fa1:
        mov dword ptr [esp+4],0
    L_00404fa9:
        mov edx,dword ptr [esp+4]
    L_00404fad:
        lea ecx,[esi+34Ch]
    L_00404fb3:
        mov dword ptr [ecx],edx
    L_00404fb5:
        mov dword ptr [esp+8],0
    L_00404fbd:
        mov eax,dword ptr [esp+8]
    L_00404fc1:
        mov dword ptr [ecx+4],eax
    L_00404fc4:
        mov al,10h
    L_00404fc6:
        mov dword ptr [esp+0Ch],0
    L_00404fce:
        mov edx,dword ptr [esp+0Ch]
    L_00404fd2:
        mov dword ptr [ecx+8],edx
    L_00404fd5:
        mov ecx,dword ptr [esp+14h]
    L_00404fd9:
        mov byte ptr [esi+3A1h],al
    L_00404fdf:
        mov byte ptr [esi+3A0h],al
    L_00404fe5:
        mov eax,esi
    L_00404fe7:
        mov word ptr [esi+38Ah],bx
    L_00404fee:
        call asm_AnimationObject_LoadScript_0043e710
    L_00404ff3:
        pop ebx
    L_00404ff4:
        add esp,0Ch
    L_00404ff7:
        ret 4
    }
}

// 0x00405300..0x0040533B: FUN_00405300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405300_00405300() {
    __asm {
    L_00405300:
        mov eax,ebx
    L_00405302:
        imul eax,118h
    L_00405308:
        push edi
    L_00405309:
        lea edi,[eax+esi+154h]
    L_00405310:
        mov dword ptr [esi+384h],edi
    L_00405316:
        call asm_Camera_ApplyRetail_00421480
    L_0040531b:
        mov edx,dword ptr [esi+384h]
    L_00405321:
        mov eax,dword ptr [esi+8]
    L_00405324:
        mov ecx,dword ptr [eax]
    L_00405326:
        add edx,0CCh
    L_0040532c:
        push edx
    L_0040532d:
        push eax
    L_0040532e:
        call dword ptr [ecx+0BCh]
    L_00405334:
        mov dword ptr [esi+388h],ebx
    L_0040533a:
        pop edi
    L_0040533b:
        ret
    }
}

// 0x00405E20..0x00405EC2: FUN_00405e20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405e20_00405e20() {
    __asm {
    L_00405e20:
        mov edx,dword ptr [data_00491c10]
    L_00405e26:
        push 46CD88h
    L_00405e2b:
        mov ecx,7
    L_00405e30:
        call asm_Recovery_LoadCachedResource_00447280
    L_00405e35:
        test eax,eax
    L_00405e37:
        mov dword ptr [ebx+3E0B50h],eax
    L_00405e3d:
        jne short L_00405e55
    L_00405e3f:
        push 46CD54h
    L_00405e44:
        mov ecx,474F70h
    L_00405e49:
        call asm_TextLog_Append_0044b810
    L_00405e4e:
        add esp,4
    L_00405e51:
        or eax,0FFFFFFFFh
    L_00405e54:
        ret
    L_00405e55:
        push esi
    L_00405e56:
        push edi
    L_00405e57:
        lea eax,[ebx+60h]
    L_00405e5a:
        push 406770h
    L_00405e5f:
        mov dword ptr [ebx+10h],eax
    L_00405e62:
        mov word ptr [ebx+3E07A6h],5
    L_00405e6b:
        call asm_SchedulerCallback_Create_00449ed0
    L_00405e70:
        mov ecx,dword ptr [data_00491be4]
    L_00405e76:
        mov esi,eax
    L_00405e78:
        mov eax,dword ptr [esi+4]
    L_00405e7b:
        and eax,0FFFFFFFDh
    L_00405e7e:
        push ecx
    L_00405e7f:
        mov edi,14h
    L_00405e84:
        mov dword ptr [esi+20h],ebx
    L_00405e87:
        mov dword ptr [esi+4],eax
    L_00405e8a:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_00405e8f:
        push 4067A0h
    L_00405e94:
        mov dword ptr [ebx+8],esi
    L_00405e97:
        call asm_SchedulerCallback_Create_00449ed0
    L_00405e9c:
        mov edx,dword ptr [data_00491be4]
    L_00405ea2:
        mov esi,eax
    L_00405ea4:
        mov ecx,dword ptr [esi+4]
    L_00405ea7:
        and ecx,0FFFFFFFDh
    L_00405eaa:
        push edx
    L_00405eab:
        mov edi,1Dh
    L_00405eb0:
        mov dword ptr [esi+20h],ebx
    L_00405eb3:
        mov dword ptr [esi+4],ecx
    L_00405eb6:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00405ebb:
        pop edi
    L_00405ebc:
        mov dword ptr [ebx+0Ch],esi
    L_00405ebf:
        xor eax,eax
    L_00405ec1:
        pop esi
    L_00405ec2:
        ret
    }
}

// 0x00405ED0..0x00405EFC: BulletPool_ResetRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BulletPool_ResetRetail_00405ed0() {
    __asm {
    L_00405ed0:
        mov edx,dword ptr [esi+3E0B50h]
    L_00405ed6:
        mov eax,dword ptr [data_00491c10]
    L_00405edb:
        push edi
    L_00405edc:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_00405ee1:
        lea edx,[esi+60h]
    L_00405ee4:
        mov ecx,0F82BCh
    L_00405ee9:
        xor eax,eax
    L_00405eeb:
        mov edi,edx
    L_00405eed:
        rep stosd
    L_00405eef:
        mov dword ptr [esi+10h],edx
    L_00405ef2:
        mov word ptr [esi+3E07A6h],5
    L_00405efb:
        pop edi
    L_00405efc:
        ret
    }
}

// 0x00406060..0x00406115: FUN_00406060
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00406060_00406060() {
    __asm {
    L_00406060:
        push 0FFFFFFFFh
    L_00406062:
        push 4658ABh
    L_00406067:
        mov eax,dword ptr fs:[0]
    L_0040606d:
        push eax
    L_0040606e:
        mov dword ptr fs:[0],esp
    L_00406075:
        push ecx
    L_00406076:
        push esi
    L_00406077:
        push 3E0B54h
    L_0040607c:
        call asm_operator_new_00452493
    L_00406081:
        mov esi,eax
    L_00406083:
        add esp,4
    L_00406086:
        mov dword ptr [esp+4],esi
    L_0040608a:
        test esi,esi
    L_0040608c:
        mov dword ptr [esp+10h],0
    L_00406094:
        je short L_004060c8
    L_00406096:
        push edi
    L_00406097:
        push 405DE0h
    L_0040609c:
        push 405D00h
    L_004060a1:
        push 7D1h
    L_004060a6:
        push 7F0h
    L_004060ab:
        lea eax,[esi+60h]
    L_004060ae:
        push eax
    L_004060af:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004060b4:
        mov ecx,0F82D5h
    L_004060b9:
        xor eax,eax
    L_004060bb:
        mov edi,esi
    L_004060bd:
        rep stosd
    L_004060bf:
        mov dword ptr [data_004776f0],esi
    L_004060c5:
        pop edi
    L_004060c6:
        jmp short L_004060ca
    L_004060c8:
        xor esi,esi
    L_004060ca:
        push ebx
    L_004060cb:
        mov ebx,esi
    L_004060cd:
        mov dword ptr [esp+14h],0FFFFFFFFh
    L_004060d5:
        call asm_FUN_00405e20_00405e20
    L_004060da:
        test eax,eax
    L_004060dc:
        pop ebx
    L_004060dd:
        je short L_00406104
    L_004060df:
        test esi,esi
    L_004060e1:
        je short L_004060f2
    L_004060e3:
        push esi
    L_004060e4:
        call asm_ItemManager_DestroyRetail_00405f70
    L_004060e9:
        push esi
    L_004060ea:
        call asm_free_004524a1
    L_004060ef:
        add esp,4
    L_004060f2:
        xor eax,eax
    L_004060f4:
        pop esi
    L_004060f5:
        mov ecx,dword ptr [esp+4]
    L_004060f9:
        mov dword ptr fs:[0],ecx
    L_00406100:
        add esp,10h
    L_00406103:
        ret
    L_00406104:
        mov ecx,dword ptr [esp+8]
    L_00406108:
        mov eax,esi
    L_0040610a:
        pop esi
    L_0040610b:
        mov dword ptr fs:[0],ecx
    L_00406112:
        add esp,10h
    L_00406115:
        ret
    }
}

// 0x004065C0..0x004066B8: FUN_004065c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004065c0_004065c0() {
    __asm {
    L_004065c0:
        push ecx
    L_004065c1:
        push ebx
    L_004065c2:
        push ebp
    L_004065c3:
        xor ebp,ebp
    L_004065c5:
        lea ebx,[esi+60h]
    L_004065c8:
        push edi
    L_004065c9:
        mov dword ptr [esi+5Ch],ebp
    L_004065cc:
        mov dword ptr [esi+28h],ebp
    L_004065cf:
        mov dword ptr [esi+24h],ebp
    L_004065d2:
        mov dword ptr [esi+20h],ebp
    L_004065d5:
        mov dword ptr [esi+1Ch],ebp
    L_004065d8:
        mov dword ptr [esi+18h],ebp
    L_004065db:
        mov dword ptr [esi+14h],ebp
    L_004065de:
        mov dword ptr [esi+40h],ebp
    L_004065e1:
        mov dword ptr [esi+3Ch],ebp
    L_004065e4:
        mov dword ptr [esi+38h],ebp
    L_004065e7:
        mov dword ptr [esi+34h],ebp
    L_004065ea:
        mov dword ptr [esi+30h],ebp
    L_004065ed:
        mov dword ptr [esi+2Ch],ebp
    L_004065f0:
        lea edi,[ebx+400h]
    L_004065f6:
        mov dword ptr [esp+0Ch],7D0h
    L_004065fe:
        mov edi,edi
    L_00406600:
        cmp word ptr [edi+46h],bp
    L_00406604:
        je asm_target_00406694
    L_0040660a:
        mov eax,dword ptr [data_00477810]
    L_0040660f:
        cmp eax,ebp
    L_00406611:
        je short L_0040661f
    L_00406613:
        mov eax,dword ptr [eax+58h]
    L_00406616:
        test al,2
    L_00406618:
        je short L_0040661f
    L_0040661a:
        test ah,4
    L_0040661d:
        jne short L_00406629
    L_0040661f:
        push ebx
    L_00406620:
        call asm_FUN_00406240_00406240
    L_00406625:
        test eax,eax
    L_00406627:
        jne short L_00406694
    L_00406629:
        mov eax,dword ptr [edi+60h]
    L_0040662c:
        cmp dword ptr [esi+eax*4+14h],ebp
    L_00406630:
        je short L_0040663e
    L_00406632:
        mov eax,dword ptr [esi+eax*4+2Ch]
    L_00406636:
        mov dword ptr [eax+44Ch],ebx
    L_0040663c:
        jmp short L_00406642
    L_0040663e:
        mov dword ptr [esi+eax*4+14h],ebx
    L_00406642:
        mov ecx,dword ptr [edi+60h]
    L_00406645:
        mov dword ptr [esi+ecx*4+2Ch],ebx
    L_00406649:
        mov dword ptr [edi+4Ch],ebp
    L_0040664c:
        inc dword ptr [esi+5Ch]
    L_0040664f:
        mov edx,dword ptr [edi-4]
    L_00406652:
        mov ecx,dword ptr [edi+4]
    L_00406655:
        mov dword ptr [edi-8],edx
    L_00406658:
        fld dword ptr [ecx]
    L_0040665a:
        fcomp dword ptr [data_00470b68]
    L_00406660:
        fnstsw ax
    L_00406662:
        test ah,41h
    L_00406665:
        jne short L_00406686
    L_00406667:
        fld dword ptr [ecx]
    L_00406669:
        fcomp dword ptr [data_00470b64]
    L_0040666f:
        fnstsw ax
    L_00406671:
        test ah,5
    L_00406674:
        jp short L_00406686
    L_00406676:
        fld dword ptr [edi]
    L_00406678:
        inc edx
    L_00406679:
        fadd dword ptr [data_00470afc]
    L_0040667f:
        mov dword ptr [edi-4],edx
    L_00406682:
        fstp dword ptr [edi]
    L_00406684:
        jmp short L_00406694
    L_00406686:
        fld dword ptr [edi]
    L_00406688:
        fadd dword ptr [ecx]
    L_0040668a:
        fst dword ptr [edi]
    L_0040668c:
        call asm_FUN_00463b2c_00463b2c
    L_00406691:
        mov dword ptr [edi-4],eax
    L_00406694:
        mov eax,dword ptr [esp+0Ch]
    L_00406698:
        add ebx,7F0h
    L_0040669e:
        add edi,7F0h
    L_004066a4:
        dec eax
    L_004066a5:
        mov dword ptr [esp+0Ch],eax
    L_004066a9:
        jne asm_target_00406600
    L_004066af:
        pop edi
    L_004066b0:
        pop ebp
    L_004066b1:
        mov eax,1
    L_004066b6:
        pop ebx
    L_004066b7:
        pop ecx
    L_004066b8:
        ret
    }
}

// 0x0040C730..0x0040C776: FUN_0040c730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c730_0040c730() {
    __asm {
    L_0040c730:
        push esi
    L_0040c731:
        mov esi,dword ptr [eax+1028h]
    L_0040c737:
        xor edx,edx
    L_0040c739:
        lea ecx,[eax+8]
    L_0040c73c:
        and esi,0FFFFFFFEh
    L_0040c73f:
        mov dword ptr [eax+1028h],esi
    L_0040c745:
        mov dword ptr [ecx],edx
    L_0040c747:
        mov dword ptr [eax+0Ch],edx
    L_0040c74a:
        mov dword ptr [eax+101Ch],eax
    L_0040c750:
        mov dword ptr [eax+1018h],0FFFFFFFFh
    L_0040c75a:
        mov dword ptr [eax+1020h],edx
    L_0040c760:
        mov dword ptr [eax+4],ecx
    L_0040c763:
        mov dword ptr [eax+1030h],ecx
    L_0040c769:
        mov dword ptr [eax+1034h],edx
    L_0040c76f:
        mov dword ptr [eax+1038h],edx
    L_0040c775:
        pop esi
    L_0040c776:
        ret
    }
}

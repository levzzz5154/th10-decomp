#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_PlayerManager_ConstructRetail_00408910() {
    __asm {
    L_00408910:
        mov eax,dword ptr fs:[0]
    L_00408916:
        push 0FFFFFFFFh
    L_00408918:
        push 465514h
    L_0040891d:
        push eax
    L_0040891e:
        mov dword ptr fs:[0],esp
    L_00408925:
        push esi
    L_00408926:
        mov esi,dword ptr [esp+14h]
    L_0040892a:
        push edi
    L_0040892b:
        push 401FF0h
    L_00408930:
        push 402050h
    L_00408935:
        push 2
    L_00408937:
        push 3ACh
    L_0040893c:
        lea eax,[esi+10h]
    L_0040893f:
        push eax
    L_00408940:
        call asm_eh_vector_constructor_iterator_0045252d
    L_00408945:
        push 401FF0h
    L_0040894a:
        push 402050h
    L_0040894f:
        push 8
    L_00408951:
        push 3ACh
    L_00408956:
        lea ecx,[esi+778h]
    L_0040895c:
        push ecx
    L_0040895d:
        mov dword ptr [esp+24h],0
    L_00408965:
        call asm_eh_vector_constructor_iterator_0045252d
    L_0040896a:
        push 401FF0h
    L_0040896f:
        push 402050h
    L_00408974:
        push 5
    L_00408976:
        push 3ACh
    L_0040897b:
        lea edx,[esi+24D8h]
    L_00408981:
        push edx
    L_00408982:
        mov byte ptr [esp+24h],1
    L_00408987:
        call asm_eh_vector_constructor_iterator_0045252d
    L_0040898c:
        and dword ptr [esi+3744h],0FFFFFFFEh
    L_00408993:
        xor eax,eax
    L_00408995:
        mov edi,esi
    L_00408997:
        mov ecx,0DECh
    L_0040899c:
        rep stosd
    L_0040899e:
        mov eax,dword ptr [esi]
    L_004089a0:
        mov ecx,dword ptr [esp+8]
    L_004089a4:
        or eax,2
    L_004089a7:
        mov dword ptr [esi],eax
    L_004089a9:
        pop edi
    L_004089aa:
        mov dword ptr [data_004776f4],esi
    L_004089b0:
        mov eax,esi
    L_004089b2:
        mov dword ptr fs:[0],ecx
    L_004089b9:
        pop esi
    L_004089ba:
        add esp,0Ch
    L_004089bd:
        ret 4
    }
}



// 0x00413810..0x0041397E: FUN_00413810
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413810_00413810() {
    __asm {
    L_00413810:
        mov eax,dword ptr fs:[0]
    L_00413816:
        push 0FFFFFFFFh
    L_00413818:
        push 4654B5h
    L_0041381d:
        push eax
    L_0041381e:
        mov dword ptr fs:[0],esp
    L_00413825:
        push ebx
    L_00413826:
        push esi
    L_00413827:
        mov esi,dword ptr [esp+18h]
    L_0041382b:
        push edi
    L_0041382c:
        push 401FF0h
    L_00413831:
        push 402050h
    L_00413836:
        push 0Ah
    L_00413838:
        push 3ACh
    L_0041383d:
        lea eax,[esi+10h]
    L_00413840:
        push eax
    L_00413841:
        call asm_eh_vector_constructor_iterator_0045252d
    L_00413846:
        push 401FF0h
    L_0041384b:
        push 402050h
    L_00413850:
        push 0Ah
    L_00413852:
        push 3ACh
    L_00413857:
        lea ecx,[esi+24C8h]
    L_0041385d:
        push ecx
    L_0041385e:
        mov dword ptr [esp+28h],0
    L_00413866:
        call asm_eh_vector_constructor_iterator_0045252d
    L_0041386b:
        push 401FF0h
    L_00413870:
        push 402050h
    L_00413875:
        push 9
    L_00413877:
        push 3ACh
    L_0041387c:
        lea edx,[esi+4980h]
    L_00413882:
        push edx
    L_00413883:
        mov byte ptr [esp+28h],1
    L_00413888:
        call asm_eh_vector_constructor_iterator_0045252d
    L_0041388d:
        push 401FF0h
    L_00413892:
        push 402050h
    L_00413897:
        push 4
    L_00413899:
        push 3ACh
    L_0041389e:
        lea eax,[esi+6A8Ch]
    L_004138a4:
        push eax
    L_004138a5:
        mov byte ptr [esp+28h],2
    L_004138aa:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004138af:
        push 401FF0h
    L_004138b4:
        push 402050h
    L_004138b9:
        push 2
    L_004138bb:
        push 3ACh
    L_004138c0:
        lea ecx,[esi+793Ch]
    L_004138c6:
        push ecx
    L_004138c7:
        mov byte ptr [esp+28h],3
    L_004138cc:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004138d1:
        push 401FF0h
    L_004138d6:
        push 402050h
    L_004138db:
        push 7
    L_004138dd:
        push 3ACh
    L_004138e2:
        lea edx,[esi+8094h]
    L_004138e8:
        push edx
    L_004138e9:
        mov byte ptr [esp+28h],4
    L_004138ee:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004138f3:
        mov ecx,dword ptr [esi+9AB4h]
    L_004138f9:
        lea edx,[esi+9A48h]
    L_004138ff:
        mov ebx,0FFFFFFFEh
    L_00413904:
        and ecx,ebx
    L_00413906:
        mov dword ptr [edx+6Ch],ecx
    L_00413909:
        and dword ptr [edx+0B0h],ebx
    L_0041390f:
        and dword ptr [edx+0FCh],ebx
    L_00413915:
        and dword ptr [edx+128h],ebx
    L_0041391b:
        and dword ptr [edx+174h],ebx
    L_00413921:
        and dword ptr [edx+1B0h],ebx
    L_00413927:
        and dword ptr [edx+1FCh],ebx
    L_0041392d:
        and dword ptr [edx+228h],ebx
    L_00413933:
        and dword ptr [edx+378h],ebx
    L_00413939:
        xor eax,eax
    L_0041393b:
        mov ecx,0EBh
    L_00413940:
        mov edi,edx
    L_00413942:
        rep stosd
    L_00413944:
        mov word ptr [edx+384h],0FFFFh
    L_0041394d:
        and dword ptr [esi+9E70h],ebx
    L_00413953:
        mov edi,esi
    L_00413955:
        mov ecx,27B4h
    L_0041395a:
        rep stosd
    L_0041395c:
        mov eax,dword ptr [esi]
    L_0041395e:
        mov ecx,dword ptr [esp+0Ch]
    L_00413962:
        or eax,2
    L_00413965:
        mov dword ptr [esi],eax
    L_00413967:
        pop edi
    L_00413968:
        mov dword ptr [data_0047770c],esi
    L_0041396e:
        mov eax,esi
    L_00413970:
        pop esi
    L_00413971:
        mov dword ptr fs:[0],ecx
    L_00413978:
        pop ebx
    L_00413979:
        add esp,0Ch
    L_0041397c:
        ret 4
    }
}



// 0x0041AFD0..0x0041B007: FUN_0041afd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041afd0_0041afd0() {
    __asm {
    L_0041afd0:
        sub esp,58h
    L_0041afd3:
        mov eax,dword ptr [esp+5Ch]
    L_0041afd7:
        push ebx
    L_0041afd8:
        push ebp
    L_0041afd9:
        push esi
    L_0041afda:
        xor ecx,ecx
    L_0041afdc:
        lea esi,[eax+14h]
    L_0041afdf:
        push edi
    L_0041afe0:
        mov dword ptr [esp+10h],esi
    L_0041afe4:
        mov dword ptr [esp+14h],ecx
    L_0041afe8:
        mov dword ptr [eax+21CEBCh],ecx
    L_0041afee:
        mov dword ptr [eax+21CEB4h],ecx
    L_0041aff4:
        lea ebp,[esi+3B0h]
    L_0041affa:
        mov dword ptr [esp+1Ch],896h
    L_0041b002:
        TH10_REL8(0xeb, 0x0041b002, VA_asm_FUN_0041afd0_part_0041b010)
    L_0041b004:
        xor ecx,ecx
    L_0041b006:
        TH10_REL8(0xeb, 0x0041b006, VA_asm_FUN_0041afd0_part_0041b010)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_0041b010:
        mov eax,dword ptr [ebp+2Ch]
    L_0041b013:
        cmp eax,ecx
    L_0041b015:
        je asm_target_0041b85a
    L_0041b01b:
        cmp eax,5
    L_0041b01e:
        jne short L_0041b04f
    L_0041b020:
        dec dword ptr [ebp+3Ch]
    L_0041b023:
        jns asm_target_0041b85a
    L_0041b029:
        mov ecx,dword ptr [data_004776f0]
    L_0041b02f:
        mov eax,dword ptr [ebp+30h]
    L_0041b032:
        mov dword ptr [ebp+2Ch],2
    L_0041b039:
        mov edx,dword ptr [ecx+3E0B50h]
    L_0041b03f:
        add eax,176h
    L_0041b044:
        push edx
    L_0041b045:
        call asm_FUN_00404f30_00404f30
    L_0041b04a:
        jmp asm_target_0041b85a
    L_0041b04f:
        mov ebx,1
    L_0041b054:
        cmp eax,ebx
    L_0041b056:
        jne asm_target_0041b133
    L_0041b05c:
        mov edx,dword ptr [data_00477834]
    L_0041b062:
        mov eax,dword ptr [edx+458h]
    L_0041b068:
        cmp eax,2
    L_0041b06b:
        je short L_0041b085
    L_0041b06d:
        cmp eax,4
    L_0041b070:
        je short L_0041b085
    L_0041b072:
        fld dword ptr [edx+3C4h]
    L_0041b078:
        fcomp dword ptr [data_00470bf4]
    L_0041b07e:
        fnstsw ax
    L_0041b080:
        test ah,5
    L_0041b083:
        jnp short L_0041b08f
    L_0041b085:
        mov eax,dword ptr [data_004776ec]
    L_0041b08a:
        cmp dword ptr [eax+28h],ecx
    L_0041b08d:
        je short L_0041b0a7
    L_0041b08f:
        mov ecx,dword ptr [edx+45Ch]
    L_0041b095:
        mov eax,dword ptr [ecx+8]
    L_0041b098:
        mov dword ptr [ebp+38h],eax
    L_0041b09b:
        mov dword ptr [ebp+2Ch],3
    L_0041b0a2:
        jmp asm_target_0041b1e7
    L_0041b0a7:
        fld dword ptr [data_00476f78]
    L_0041b0ad:
        fmul dword ptr [ebp+8]
    L_0041b0b0:
        fld dword ptr [data_00476f78]
    L_0041b0b6:
        fmul dword ptr [ebp+0Ch]
    L_0041b0b9:
        fld dword ptr [data_00476f78]
    L_0041b0bf:
        fmul dword ptr [ebp+10h]
    L_0041b0c2:
        fstp dword ptr [esp+40h]
    L_0041b0c6:
        fxch
    L_0041b0c8:
        fadd dword ptr [ebp-4]
    L_0041b0cb:
        fstp dword ptr [ebp-4]
    L_0041b0ce:
        fadd dword ptr [ebp]
    L_0041b0d1:
        fstp dword ptr [ebp]
    L_0041b0d4:
        fld dword ptr [esp+40h]
    L_0041b0d8:
        fadd dword ptr [ebp+4]
    L_0041b0db:
        fstp dword ptr [ebp+4]
    L_0041b0de:
        fld dword ptr [data_00476f78]
    L_0041b0e4:
        fmul dword ptr [data_00470cdc]
    L_0041b0ea:
        fadd dword ptr [ebp+0Ch]
    L_0041b0ed:
        fst dword ptr [ebp+0Ch]
    L_0041b0f0:
        fcomp dword ptr [data_00470b04]
    L_0041b0f6:
        fnstsw ax
    L_0041b0f8:
        test ah,1
    L_0041b0fb:
        jne short L_0041b100
    L_0041b0fd:
        mov dword ptr [ebp+8],ecx
    L_0041b100:
        fld dword ptr [ebp+0Ch]
    L_0041b103:
        fcomp dword ptr [data_00470b08]
    L_0041b109:
        fnstsw ax
    L_0041b10b:
        test ah,41h
    L_0041b10e:
        jne short L_0041b117
    L_0041b110:
        mov dword ptr [ebp+0Ch],40000000h
    L_0041b117:
        fld dword ptr [ebp]
    L_0041b11a:
        fcomp dword ptr [data_00470be0]
    L_0041b120:
        fnstsw ax
    L_0041b122:
        test ah,41h
    L_0041b125:
        jne asm_target_0041b347
    L_0041b12b:
        mov dword ptr [ebp+2Ch],ecx
    L_0041b12e:
        jmp asm_target_0041b85a
    L_0041b133:
        cmp eax,2
    L_0041b136:
        jne asm_target_0041b1d8
    L_0041b13c:
        fld dword ptr [data_00476f78]
    L_0041b142:
        fmul dword ptr [ebp+8]
    L_0041b145:
        fld dword ptr [data_00476f78]
    L_0041b14b:
        fmul dword ptr [ebp+0Ch]
    L_0041b14e:
        fld dword ptr [data_00476f78]
    L_0041b154:
        fmul dword ptr [ebp+10h]
    L_0041b157:
        fstp dword ptr [esp+4Ch]
    L_0041b15b:
        fxch
    L_0041b15d:
        fadd dword ptr [ebp-4]
    L_0041b160:
        fstp dword ptr [ebp-4]
    L_0041b163:
        fadd dword ptr [ebp]
    L_0041b166:
        fstp dword ptr [ebp]
    L_0041b169:
        fld dword ptr [esp+4Ch]
    L_0041b16d:
        fadd dword ptr [ebp+4]
    L_0041b170:
        fstp dword ptr [ebp+4]
    L_0041b173:
        fld dword ptr [data_00476f78]
    L_0041b179:
        fmul dword ptr [data_00470cdc]
    L_0041b17f:
        fadd dword ptr [ebp+0Ch]
    L_0041b182:
        fst dword ptr [ebp+0Ch]
    L_0041b185:
        fcomp dword ptr [data_00470b04]
    L_0041b18b:
        fnstsw ax
    L_0041b18d:
        test ah,1
    L_0041b190:
        jne short L_0041b1ad
    L_0041b192:
        mov ecx,dword ptr [data_00477834]
    L_0041b198:
        mov edx,dword ptr [ecx+45Ch]
    L_0041b19e:
        mov eax,dword ptr [edx+8]
    L_0041b1a1:
        mov dword ptr [ebp+38h],eax
    L_0041b1a4:
        mov dword ptr [ebp+2Ch],3
    L_0041b1ab:
        jmp short L_0041b1e1
    L_0041b1ad:
        fld dword ptr [ebp]
    L_0041b1b0:
        fcomp dword ptr [data_00470be0]
    L_0041b1b6:
        fnstsw ax
    L_0041b1b8:
        test ah,41h
    L_0041b1bb:
        jne asm_target_0041b341
    L_0041b1c1:
        mov dword ptr [ebp+2Ch],ecx
    L_0041b1c4:
        mov ecx,0FFFFFFFCh
    L_0041b1c9:
        mov eax,474C40h
    L_0041b1ce:
        call asm_Player_AdjustPower_00405b60
    L_0041b1d3:
        jmp asm_target_0041b85a
    L_0041b1d8:
        cmp eax,3
    L_0041b1db:
        jne asm_target_0041b2a1
    L_0041b1e1:
        mov edx,dword ptr [data_00477834]
    L_0041b1e7:
        fld dword ptr [edx+3C0h]
    L_0041b1ed:
        fsub dword ptr [ebp-4]
    L_0041b1f0:
        fld dword ptr [edx+3C4h]
    L_0041b1f6:
        fsub dword ptr [ebp]
    L_0041b1f9:
        fld dword ptr [data_00470b04]
    L_0041b1ff:
        fld st(1)
    L_0041b201:
        fucompp
    L_0041b203:
        fnstsw ax
    L_0041b205:
        test ah,44h
    L_0041b208:
        jp short L_0041b229
    L_0041b20a:
        fld dword ptr [data_00470b04]
    L_0041b210:
        fld st(2)
    L_0041b212:
        fucompp
    L_0041b214:
        fnstsw ax
    L_0041b216:
        test ah,44h
    L_0041b219:
        jp short L_0041b229
    L_0041b21b:
        fstp st(0)
    L_0041b21d:
        mov dword ptr [esp+18h],3FC90FDBh
    L_0041b225:
        fstp st(0)
    L_0041b227:
        jmp short L_0041b231
    L_0041b229:
        fxch
    L_0041b22b:
        fpatan
    L_0041b22d:
        fstp dword ptr [esp+18h]
    L_0041b231:
        mov ecx,dword ptr [ebp+38h]
    L_0041b234:
        mov eax,dword ptr [esp+18h]
    L_0041b238:
        push ecx
    L_0041b239:
        lea edi,[ebp+8]
    L_0041b23c:
        push eax
    L_0041b23d:
        mov ecx,edi
    L_0041b23f:
        call asm_FUN_0041beb0_0041beb0
    L_0041b244:
        fld dword ptr [data_00476f78]
    L_0041b24a:
        fmul dword ptr [edi]
    L_0041b24c:
        fld dword ptr [data_00476f78]
    L_0041b252:
        fmul dword ptr [ebp+0Ch]
    L_0041b255:
        fld dword ptr [data_00476f78]
    L_0041b25b:
        fmul dword ptr [ebp+10h]
    L_0041b25e:
        fstp dword ptr [esp+58h]
    L_0041b262:
        fxch
    L_0041b264:
        fadd dword ptr [ebp-4]
    L_0041b267:
        fstp dword ptr [ebp-4]
    L_0041b26a:
        fadd dword ptr [ebp]
    L_0041b26d:
        fstp dword ptr [ebp]
    L_0041b270:
        fld dword ptr [esp+58h]
    L_0041b274:
        fadd dword ptr [ebp+4]
    L_0041b277:
        fstp dword ptr [ebp+4]
    L_0041b27a:
        fld dword ptr [ebp+38h]
    L_0041b27d:
        fcomp dword ptr [data_00470cd8]
    L_0041b283:
        fnstsw ax
    L_0041b285:
        test ah,5
    L_0041b288:
        jp short L_0041b296
    L_0041b28a:
        fld dword ptr [ebp+38h]
    L_0041b28d:
        fadd dword ptr [data_00470c38]
    L_0041b293:
        fstp dword ptr [ebp+38h]
    L_0041b296:
        mov eax,dword ptr [edx+458h]
    L_0041b29c:
        jmp asm_target_0041b32a
    L_0041b2a1:
        cmp eax,4
    L_0041b2a4:
        jne asm_target_0041b341
    L_0041b2aa:
        mov ecx,dword ptr [ebp+38h]
    L_0041b2ad:
        mov esi,dword ptr [data_00477834]
    L_0041b2b3:
        lea edx,[ebp-4]
    L_0041b2b6:
        push ecx
    L_0041b2b7:
        mov eax,edx
    L_0041b2b9:
        mov ecx,esi
    L_0041b2bb:
        lea edi,[ebp+8]
    L_0041b2be:
        call asm_Entity_AngleFromPoint_00426660
    L_0041b2c3:
        push ecx
    L_0041b2c4:
        mov ecx,edi
    L_0041b2c6:
        fstp dword ptr [esp]
    L_0041b2c9:
        call asm_FUN_0041beb0_0041beb0
    L_0041b2ce:
        fld dword ptr [data_00476f78]
    L_0041b2d4:
        fmul dword ptr [edi]
    L_0041b2d6:
        fld dword ptr [data_00476f78]
    L_0041b2dc:
        fmul dword ptr [ebp+0Ch]
    L_0041b2df:
        fld dword ptr [data_00476f78]
    L_0041b2e5:
        fmul dword ptr [ebp+10h]
    L_0041b2e8:
        fstp dword ptr [esp+64h]
    L_0041b2ec:
        fxch
    L_0041b2ee:
        fadd dword ptr [edx]
    L_0041b2f0:
        fstp dword ptr [edx]
    L_0041b2f2:
        fadd dword ptr [ebp]
    L_0041b2f5:
        fstp dword ptr [ebp]
    L_0041b2f8:
        fld dword ptr [esp+64h]
    L_0041b2fc:
        fadd dword ptr [ebp+4]
    L_0041b2ff:
        fstp dword ptr [ebp+4]
    L_0041b302:
        fld dword ptr [ebp+38h]
    L_0041b305:
        fcomp dword ptr [data_00470cd8]
    L_0041b30b:
        fnstsw ax
    L_0041b30d:
        test ah,5
    L_0041b310:
        jp short L_0041b31e
    L_0041b312:
        fld dword ptr [ebp+38h]
    L_0041b315:
        fadd dword ptr [data_00470c38]
    L_0041b31b:
        fstp dword ptr [ebp+38h]
    L_0041b31e:
        mov eax,dword ptr [esi+458h]
    L_0041b324:
        mov edx,dword ptr [data_00477834]
    L_0041b32a:
        cmp eax,4
    L_0041b32d:
        jne short L_0041b347
    L_0041b32f:
        mov dword ptr [ebp+2Ch],ebx
    L_0041b332:
        mov dword ptr [edi],0
    L_0041b338:
        mov dword ptr [ebp+0Ch],0
    L_0041b33f:
        jmp short L_0041b347
    L_0041b341:
        mov edx,dword ptr [data_00477834]
    L_0041b347:
        cmp dword ptr [edx+458h],2
    L_0041b34e:
        je asm_target_0041b7fd
    L_0041b354:
        mov eax,dword ptr [ebp-4]
    L_0041b357:
        fld dword ptr [edx+4324h]
    L_0041b35d:
        mov ecx,dword ptr [ebp]
    L_0041b360:
        lea edi,[ebp-4]
    L_0041b363:
        mov dword ptr [esp+20h],eax
    L_0041b367:
        fcomp dword ptr [esp+20h]
    L_0041b36b:
        mov dword ptr [esp+2Ch],eax
    L_0041b36f:
        mov dword ptr [esp+30h],ecx
    L_0041b373:
        mov dword ptr [esp+24h],ecx
    L_0041b377:
        fnstsw ax
    L_0041b379:
        test ah,41h
    L_0041b37c:
        je asm_target_0041b737
    L_0041b382:
        fld dword ptr [edx+4328h]
    L_0041b388:
        fcomp dword ptr [esp+24h]
    L_0041b38c:
        fnstsw ax
    L_0041b38e:
        test ah,41h
    L_0041b391:
        je asm_target_0041b737
    L_0041b397:
        fld dword ptr [edx+4330h]
    L_0041b39d:
        fcomp dword ptr [esp+2Ch]
    L_0041b3a1:
        fnstsw ax
    L_0041b3a3:
        test ah,5
    L_0041b3a6:
        jnp asm_target_0041b737
    L_0041b3ac:
        fld dword ptr [edx+4334h]
    L_0041b3b2:
        fcomp dword ptr [esp+30h]
    L_0041b3b6:
        fnstsw ax
    L_0041b3b8:
        test ah,5
    L_0041b3bb:
        jnp asm_target_0041b737
    L_0041b3c1:
        mov eax,dword ptr [ebp+30h]
    L_0041b3c4:
        dec eax
    L_0041b3c5:
        cmp eax,0Ah
    L_0041b3c8:
        ja asm_target_0041b718
    L_0041b3ce:
        jmp dword ptr [eax*4+41B8A0h]
    L_0041b3d5:
        push ebx
    L_0041b3d6:
        mov eax,474C40h
    L_0041b3db:
        call asm_FaithGauge_AddRetail_00418930
    L_0041b3e0:
        mov ebx,eax
    L_0041b3e2:
        movsx eax,word ptr [data_00474c48]
    L_0041b3e9:
        cdq
    L_0041b3ea:
        mov ecx,14h
    L_0041b3ef:
        idiv ecx
    L_0041b3f1:
        mov esi,dword ptr [data_0047770c]
    L_0041b3f7:
        imul edx,64h
    L_0041b3fa:
        mov ecx,eax
    L_0041b3fc:
        mov eax,66666667h
    L_0041b401:
        imul edx
    L_0041b403:
        sar edx,3
    L_0041b406:
        mov eax,edx
    L_0041b408:
        shr eax,1Fh
    L_0041b40b:
        add eax,edx
    L_0041b40d:
        push eax
    L_0041b40e:
        mov edx,ecx
    L_0041b410:
        call asm_FUN_004054b0_004054b0
    L_0041b415:
        test ebx,ebx
    L_0041b417:
        je short L_0041b47d
    L_0041b419:
        mov ecx,dword ptr [data_00477834]
    L_0041b41f:
        push ecx
    L_0041b420:
        call asm_FUN_00426f70_00426f70
    L_0041b425:
        mov esi,dword ptr [data_00477840]
    L_0041b42b:
        push 0FFFFFF40h
    L_0041b430:
        or eax,0FFFFFFFFh
    L_0041b433:
        call asm_FUN_0042b9c0_0042b9c0
    L_0041b438:
        mov edx,dword ptr [ebp-4]
    L_0041b43b:
        push edx
    L_0041b43c:
        mov ebx,1Dh
    L_0041b441:
        mov esi,492590h
    L_0041b446:
        call asm_FUN_0043dd10_0043dd10
    L_0041b44b:
        cmp word ptr [data_00474c48],64h
    L_0041b453:
        jl short L_0041b45d
    L_0041b455:
        mov dword ptr [esp+14h],1
    L_0041b45d:
        mov ecx,0Ch
    L_0041b462:
        mov eax,474C40h
    L_0041b467:
        call asm_Player_AdjustPower_00405b60
    L_0041b46c:
        push 3Ch
    L_0041b46e:
        mov edi,474C40h
    L_0041b473:
        call asm_FUN_00412ff0_00412ff0
    L_0041b478:
        jmp asm_target_0041b718
    L_0041b47d:
        movsx eax,word ptr [data_00474c48]
    L_0041b484:
        mov esi,dword ptr [data_00477840]
    L_0041b48a:
        cdq
    L_0041b48b:
        sub eax,edx
    L_0041b48d:
        push 0FFFF4040h
    L_0041b492:
        sar eax,1
    L_0041b494:
        call asm_FUN_0042b9c0_0042b9c0
    L_0041b499:
        push 3Ch
    L_0041b49b:
        mov edi,474C40h
    L_0041b4a0:
        call asm_FUN_00412ff0_00412ff0
    L_0041b4a5:
        jmp asm_target_0041b718
    L_0041b4aa:
        fld dword ptr [edx+3C4h]
    L_0041b4b0:
        fcomp dword ptr [data_00470cd4]
    L_0041b4b6:
        fnstsw ax
    L_0041b4b8:
        test ah,5
    L_0041b4bb:
        jp short L_0041b4d5
    L_0041b4bd:
        mov eax,dword ptr [data_00474c4c]
    L_0041b4c2:
        lea ebx,[eax+eax*4]
    L_0041b4c5:
        shl ebx,1
    L_0041b4c7:
        mov eax,ebx
    L_0041b4c9:
        cdq
    L_0041b4ca:
        mov ecx,0Ah
    L_0041b4cf:
        idiv ecx
    L_0041b4d1:
        sub ebx,edx
    L_0041b4d3:
        jmp short L_0041b542
    L_0041b4d5:
        fld dword ptr [edx+3C4h]
    L_0041b4db:
        fsub dword ptr [data_00470cd4]
    L_0041b4e1:
        fmul dword ptr [data_00470cd0]
    L_0041b4e7:
        fild dword ptr [data_00474c4c]
    L_0041b4ed:
        fmul dword ptr [data_00470b0c]
    L_0041b4f3:
        fsub dword ptr [data_00470ce0]
    L_0041b4f9:
        fmulp st(1),st
    L_0041b4fb:
        call asm_FUN_00463b2c_00463b2c
    L_0041b500:
        mov ecx,eax
    L_0041b502:
        mov eax,dword ptr [data_00474c4c]
    L_0041b507:
        lea eax,[eax+eax*4]
    L_0041b50a:
        shl eax,1
    L_0041b50c:
        cdq
    L_0041b50d:
        sub eax,edx
    L_0041b50f:
        mov ebx,eax
    L_0041b511:
        sar ebx,1
    L_0041b513:
        sub ebx,ecx
    L_0041b515:
        mov eax,ebx
    L_0041b517:
        cdq
    L_0041b518:
        mov ecx,0Ah
    L_0041b51d:
        idiv ecx
    L_0041b51f:
        mov esi,dword ptr [data_00477840]
    L_0041b525:
        push 0FFFFFFFFh
    L_0041b527:
        sub ebx,edx
    L_0041b529:
        mov eax,ebx
    L_0041b52b:
        call asm_FUN_0042b9c0_0042b9c0
    L_0041b530:
        mov ecx,1
    L_0041b535:
        jmp short L_0041b559
    L_0041b537:
        mov ebx,dword ptr [data_00474c4c]
    L_0041b53d:
        lea ebx,[ebx+ebx*4]
    L_0041b540:
        shl ebx,1
    L_0041b542:
        mov esi,dword ptr [data_00477840]
    L_0041b548:
        mov eax,ebx
    L_0041b54a:
        push 0FFFFFF00h
    L_0041b54f:
        call asm_FUN_0042b9c0_0042b9c0
    L_0041b554:
        mov ecx,8
    L_0041b559:
        mov eax,474C40h
    L_0041b55e:
        call asm_Player_AdjustPower_00405b60
    L_0041b563:
        push ebx
    L_0041b564:
        mov ecx,474C40h
    L_0041b569:
        call asm_AddScaled_GameScore_00409d90
    L_0041b56e:
        push 64h
    L_0041b570:
        mov edi,474C40h
    L_0041b575:
        call asm_FUN_00412ff0_00412ff0
    L_0041b57a:
        jmp asm_target_0041b718
    L_0041b57f:
        mov eax,dword ptr [data_00474c74]
    L_0041b584:
        cmp eax,4
    L_0041b587:
        mov ebx,1388h
    L_0041b58c:
        ja short L_0041b5a8
    L_0041b58e:
        jmp dword ptr [eax*4+41B8CCh]
    L_0041b595:
        mov ebx,1388h
    L_0041b59a:
        jmp short L_0041b5a8
    L_0041b59c:
        mov ebx,1F40h
    L_0041b5a1:
        jmp short L_0041b5a8
    L_0041b5a3:
        mov ebx,2710h
    L_0041b5a8:
        mov esi,dword ptr [data_00477840]
    L_0041b5ae:
        push 0FF00FF00h
    L_0041b5b3:
        mov eax,ebx
    L_0041b5b5:
        call asm_FUN_0042b9c0_0042b9c0
    L_0041b5ba:
        push ebx
    L_0041b5bb:
        mov ecx,474C40h
    L_0041b5c0:
        call asm_AddScaled_ScoreCounter_0041be80
    L_0041b5c5:
        push 78h
    L_0041b5c7:
        mov edi,474C40h
    L_0041b5cc:
        call asm_FUN_00412ff0_00412ff0
    L_0041b5d1:
        jmp asm_target_0041b718
    L_0041b5d6:
        push 0Ah
    L_0041b5d8:
        mov ecx,474C40h
    L_0041b5dd:
        call asm_AddScaled_ScoreCounter_0041be80
    L_0041b5e2:
        push 3
    L_0041b5e4:
        mov edi,474C40h
    L_0041b5e9:
        call asm_FUN_00412ff0_00412ff0
    L_0041b5ee:
        push 0Ah
    L_0041b5f0:
        mov ecx,edi
    L_0041b5f2:
        call asm_AddScaled_GameScore_00409d90
    L_0041b5f7:
        jmp asm_target_0041b718
    L_0041b5fc:
        mov esi,dword ptr [data_00477840]
    L_0041b602:
        push 0FF00FF00h
    L_0041b607:
        mov eax,64h
    L_0041b60c:
        call asm_FUN_0042b9c0_0042b9c0
    L_0041b611:
        push 64h
    L_0041b613:
        mov ecx,474C40h
    L_0041b618:
        call asm_AddScaled_ScoreCounter_0041be80
    L_0041b61d:
        push 3Ch
    L_0041b61f:
        mov edi,474C40h
    L_0041b624:
        call asm_FUN_00412ff0_00412ff0
    L_0041b629:
        jmp asm_target_0041b718
    L_0041b62e:
        push 14h
    L_0041b630:
        mov eax,474C40h
    L_0041b635:
        call asm_FaithGauge_AddRetail_00418930
    L_0041b63a:
        mov ebx,eax
    L_0041b63c:
        movsx eax,word ptr [data_00474c48]
    L_0041b643:
        cdq
    L_0041b644:
        mov ecx,14h
    L_0041b649:
        idiv ecx
    L_0041b64b:
        mov esi,dword ptr [data_0047770c]
    L_0041b651:
        imul edx,64h
    L_0041b654:
        mov ecx,eax
    L_0041b656:
        mov eax,66666667h
    L_0041b65b:
        imul edx
    L_0041b65d:
        sar edx,3
    L_0041b660:
        mov eax,edx
    L_0041b662:
        shr eax,1Fh
    L_0041b665:
        add eax,edx
    L_0041b667:
        push eax
    L_0041b668:
        mov edx,ecx
    L_0041b66a:
        call asm_FUN_004054b0_004054b0
    L_0041b66f:
        test ebx,ebx
    L_0041b671:
        je short L_0041b6d3
    L_0041b673:
        mov ecx,dword ptr [data_00477834]
    L_0041b679:
        push ecx
    L_0041b67a:
        call asm_FUN_00426f70_00426f70
    L_0041b67f:
        mov edx,dword ptr [edi]
    L_0041b681:
        push edx
    L_0041b682:
        mov ebx,1Dh
    L_0041b687:
        mov esi,492590h
    L_0041b68c:
        call asm_FUN_0043dd10_0043dd10
    L_0041b691:
        mov esi,dword ptr [data_00477840]
    L_0041b697:
        push 0FFFFFF40h
    L_0041b69c:
        or eax,0FFFFFFFFh
    L_0041b69f:
        call asm_FUN_0042b9c0_0042b9c0
    L_0041b6a4:
        mov ecx,18h
    L_0041b6a9:
        mov eax,474C40h
    L_0041b6ae:
        call asm_Player_AdjustPower_00405b60
    L_0041b6b3:
        cmp word ptr [data_00474c48],64h
    L_0041b6bb:
        jl short L_0041b6ef
    L_0041b6bd:
        push 14h
    L_0041b6bf:
        mov edi,474C40h
    L_0041b6c4:
        mov dword ptr [esp+18h],1
    L_0041b6cc:
        call asm_FUN_00412ff0_00412ff0
    L_0041b6d1:
        jmp short L_0041b718
    L_0041b6d3:
        movsx eax,word ptr [data_00474c48]
    L_0041b6da:
        mov esi,dword ptr [data_00477840]
    L_0041b6e0:
        cdq
    L_0041b6e1:
        sub eax,edx
    L_0041b6e3:
        push 0FFFF4040h
    L_0041b6e8:
        sar eax,1
    L_0041b6ea:
        call asm_FUN_0042b9c0_0042b9c0
    L_0041b6ef:
        push 14h
    L_0041b6f1:
        mov edi,474C40h
    L_0041b6f6:
        call asm_FUN_00412ff0_00412ff0
    L_0041b6fb:
        jmp short L_0041b718
    L_0041b6fd:
        mov ecx,ebx
    L_0041b6ff:
        mov eax,474C40h
    L_0041b704:
        call asm_Recovery_IncrementAnimationCount_004188a0
    L_0041b709:
        mov ecx,100h
    L_0041b70e:
        mov eax,474C40h
    L_0041b713:
        call asm_Player_AdjustPower_00405b60
    L_0041b718:
        mov eax,dword ptr [ebp-4]
    L_0041b71b:
        push eax
    L_0041b71c:
        mov ebx,14h
    L_0041b721:
        mov esi,492590h
    L_0041b726:
        mov dword ptr [ebp+2Ch],0
    L_0041b72d:
        call asm_FUN_0043dd10_0043dd10
    L_0041b732:
        jmp asm_target_0041b85a
    L_0041b737:
        mov eax,dword ptr [ebp+2Ch]
    L_0041b73a:
        cmp eax,4
    L_0041b73d:
        je asm_target_0041b7fd
    L_0041b743:
        cmp eax,3
    L_0041b746:
        je asm_target_0041b7fd
    L_0041b74c:
        mov ecx,dword ptr [data_00474e5c]
    L_0041b752:
        and ecx,4
    L_0041b755:
        je short L_0041b79b
    L_0041b757:
        fld dword ptr [edx+433Ch]
    L_0041b75d:
        fcomp dword ptr [esp+20h]
    L_0041b761:
        fnstsw ax
    L_0041b763:
        test ah,41h
    L_0041b766:
        je short L_0041b79b
    L_0041b768:
        fld dword ptr [edx+4340h]
    L_0041b76e:
        fcomp dword ptr [esp+24h]
    L_0041b772:
        fnstsw ax
    L_0041b774:
        test ah,41h
    L_0041b777:
        je short L_0041b79b
    L_0041b779:
        fld dword ptr [edx+4348h]
    L_0041b77f:
        fcomp dword ptr [esp+2Ch]
    L_0041b783:
        fnstsw ax
    L_0041b785:
        test ah,5
    L_0041b788:
        jnp short L_0041b79b
    L_0041b78a:
        fld dword ptr [edx+434Ch]
    L_0041b790:
        fcomp dword ptr [esp+30h]
    L_0041b794:
        fnstsw ax
    L_0041b796:
        test ah,5
    L_0041b799:
        jp short L_0041b7e4
    L_0041b79b:
        test cx,cx
    L_0041b79e:
        jne short L_0041b7fd
    L_0041b7a0:
        fld dword ptr [edx+4354h]
    L_0041b7a6:
        fcomp dword ptr [esp+20h]
    L_0041b7aa:
        fnstsw ax
    L_0041b7ac:
        test ah,41h
    L_0041b7af:
        je short L_0041b7fd
    L_0041b7b1:
        fld dword ptr [edx+4358h]
    L_0041b7b7:
        fcomp dword ptr [esp+24h]
    L_0041b7bb:
        fnstsw ax
    L_0041b7bd:
        test ah,41h
    L_0041b7c0:
        je short L_0041b7fd
    L_0041b7c2:
        fld dword ptr [edx+4360h]
    L_0041b7c8:
        fcomp dword ptr [esp+2Ch]
    L_0041b7cc:
        fnstsw ax
    L_0041b7ce:
        test ah,5
    L_0041b7d1:
        jnp short L_0041b7fd
    L_0041b7d3:
        fld dword ptr [edx+4364h]
    L_0041b7d9:
        fcomp dword ptr [esp+30h]
    L_0041b7dd:
        fnstsw ax
    L_0041b7df:
        test ah,5
    L_0041b7e2:
        jnp short L_0041b7fd
    L_0041b7e4:
        mov ecx,dword ptr [edx+45Ch]
    L_0041b7ea:
        fld dword ptr [ecx+8]
    L_0041b7ed:
        mov dword ptr [ebp+2Ch],4
    L_0041b7f4:
        fmul dword ptr [data_00470cc4]
    L_0041b7fa:
        fstp dword ptr [ebp+38h]
    L_0041b7fd:
        mov edx,dword ptr [esp+10h]
    L_0041b801:
        push edx
    L_0041b802:
        call asm_FUN_0043ee30_0043ee30
    L_0041b807:
        mov edx,dword ptr [ebp+1Ch]
    L_0041b80a:
        mov ecx,dword ptr [ebp+24h]
    L_0041b80d:
        mov dword ptr [ebp+18h],edx
    L_0041b810:
        fld dword ptr [ecx]
    L_0041b812:
        fcomp dword ptr [data_00470b68]
    L_0041b818:
        fnstsw ax
    L_0041b81a:
        test ah,41h
    L_0041b81d:
        jne short L_0041b840
    L_0041b81f:
        fld dword ptr [ecx]
    L_0041b821:
        fcomp dword ptr [data_00470b64]
    L_0041b827:
        fnstsw ax
    L_0041b829:
        test ah,5
    L_0041b82c:
        jp short L_0041b840
    L_0041b82e:
        fld dword ptr [ebp+20h]
    L_0041b831:
        inc edx
    L_0041b832:
        fadd dword ptr [data_00470afc]
    L_0041b838:
        mov dword ptr [ebp+1Ch],edx
    L_0041b83b:
        fstp dword ptr [ebp+20h]
    L_0041b83e:
        jmp short L_0041b850
    L_0041b840:
        fld dword ptr [ebp+20h]
    L_0041b843:
        fadd dword ptr [ecx]
    L_0041b845:
        fst dword ptr [ebp+20h]
    L_0041b848:
        call asm_FUN_00463b2c_00463b2c
    L_0041b84d:
        mov dword ptr [ebp+1Ch],eax
    L_0041b850:
        mov eax,dword ptr [esp+6Ch]
    L_0041b854:
        inc dword ptr [eax+21CEB4h]
    L_0041b85a:
        mov esi,dword ptr [esp+10h]
    L_0041b85e:
        mov eax,dword ptr [esp+1Ch]
    L_0041b862:
        add esi,3F0h
    L_0041b868:
        add ebp,3F0h
    L_0041b86e:
        dec eax
    L_0041b86f:
        mov dword ptr [esp+10h],esi
    L_0041b873:
        mov dword ptr [esp+1Ch],eax
    L_0041b877:
        jne asm_target_0041b004
    L_0041b87d:
        mov eax,dword ptr [esp+14h]
    L_0041b881:
        test eax,eax
    L_0041b883:
        je short L_0041b88e
    L_0041b885:
        mov esi,dword ptr [esp+6Ch]
    L_0041b889:
        call asm_Enemy_SweepPendingDropsRetail_0041ba50
    L_0041b88e:
        pop edi
    L_0041b88f:
        pop esi
    L_0041b890:
        pop ebp
    L_0041b891:
        mov eax,1
    L_0041b896:
        pop ebx
    L_0041b897:
        add esp,58h
    L_0041b89a:
        ret 4
        _emit 0x8d
        _emit 0x49
        _emit 0x00
        _emit 0xd5
        _emit 0xb3
        _emit 0x41
        _emit 0x00
        _emit 0xaa
        _emit 0xb4
        _emit 0x41
        _emit 0x00
        _emit 0x7f
        _emit 0xb5
        _emit 0x41
        _emit 0x00
        _emit 0x2e
        _emit 0xb6
        _emit 0x41
        _emit 0x00
        _emit 0x37
        _emit 0xb5
        _emit 0x41
        _emit 0x00
        _emit 0x18
        _emit 0xb7
        _emit 0x41
        _emit 0x00
        _emit 0xfd
        _emit 0xb6
        _emit 0x41
        _emit 0x00
        _emit 0xd6
        _emit 0xb5
        _emit 0x41
        _emit 0x00
        _emit 0xfc
        _emit 0xb5
        _emit 0x41
        _emit 0x00
        _emit 0xd5
        _emit 0xb3
        _emit 0x41
        _emit 0x00
        _emit 0x2e
        _emit 0xb6
        _emit 0x41
        _emit 0x00
        _emit 0x95
        _emit 0xb5
        _emit 0x41
        _emit 0x00
        _emit 0x95
        _emit 0xb5
        _emit 0x41
        _emit 0x00
        _emit 0x9c
        _emit 0xb5
        _emit 0x41
        _emit 0x00
        _emit 0xa3
        _emit 0xb5
        _emit 0x41
        _emit 0x00
        _emit 0xa3
        _emit 0xb5
        _emit 0x41
        _emit 0x00
    }
}







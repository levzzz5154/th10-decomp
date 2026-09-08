#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401DE0..0x00401EF0: InitializeEntity
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_InitializeEntity_00401de0() {
    __asm {
    L_00401de0:
        sub esp,10h
    L_00401de3:
        push ebx
    L_00401de4:
        push ebp
    L_00401de5:
        push esi
    L_00401de6:
        lea esi,[edx+340h]
    L_00401dec:
        mov eax,esi
    L_00401dee:
        mov ebx,dword ptr [eax]
    L_00401df0:
        mov ebp,dword ptr [eax+4]
    L_00401df3:
        mov ecx,dword ptr [eax+8]
    L_00401df6:
        mov eax,dword ptr [edx+20h]
    L_00401df9:
        push edi
    L_00401dfa:
        mov dword ptr [esp+1Ch],ecx
    L_00401dfe:
        mov dword ptr [esp+10h],eax
    L_00401e02:
        xor eax,eax
    L_00401e04:
        mov ecx,0EBh
    L_00401e09:
        mov edi,edx
    L_00401e0b:
        rep stosd
    L_00401e0d:
        mov ecx,dword ptr [esp+10h]
    L_00401e11:
        mov eax,dword ptr [esp+1Ch]
    L_00401e15:
        mov dword ptr [esi],ebx
    L_00401e17:
        mov dword ptr [esi+4],ebp
    L_00401e1a:
        mov dword ptr [edx+20h],ecx
    L_00401e1d:
        mov dword ptr [esi+8],eax
    L_00401e20:
        xor eax,eax
    L_00401e22:
        mov dword ptr [edx+2FCh],0FFFFFFFFh
    L_00401e2c:
        mov ecx,3F800000h
    L_00401e31:
        mov dword ptr [edx+3Ch],ecx
    L_00401e34:
        mov dword ptr [edx+40h],ecx
    L_00401e37:
        mov dword ptr [edx+274h],eax
    L_00401e3d:
        mov dword ptr [edx+270h],eax
    L_00401e43:
        mov dword ptr [edx+26Ch],eax
    L_00401e49:
        mov dword ptr [edx+268h],eax
    L_00401e4f:
        mov dword ptr [edx+260h],eax
    L_00401e55:
        mov dword ptr [edx+25Ch],eax
    L_00401e5b:
        mov dword ptr [edx+258h],eax
    L_00401e61:
        mov dword ptr [edx+254h],eax
    L_00401e67:
        mov dword ptr [edx+24Ch],eax
    L_00401e6d:
        mov dword ptr [edx+248h],eax
    L_00401e73:
        mov dword ptr [edx+244h],eax
    L_00401e79:
        mov dword ptr [edx+240h],eax
    L_00401e7f:
        mov dword ptr [edx+278h],ecx
    L_00401e85:
        mov dword ptr [edx+264h],ecx
    L_00401e8b:
        mov dword ptr [edx+250h],ecx
    L_00401e91:
        mov dword ptr [edx+23Ch],ecx
    L_00401e97:
        mov word ptr [edx+35Ch],7
    L_00401ea0:
        mov dword ptr [edx+60h],eax
    L_00401ea3:
        mov dword ptr [edx+5Ch],0FFF0BDC1h
    L_00401eaa:
        mov dword ptr [edx+64h],eax
    L_00401ead:
        pop edi
    L_00401eae:
        mov dword ptr [edx+0B4h],eax
    L_00401eb4:
        mov dword ptr [edx+100h],eax
    L_00401eba:
        mov dword ptr [edx+12Ch],eax
    L_00401ec0:
        mov dword ptr [edx+178h],eax
    L_00401ec6:
        mov dword ptr [edx+1B4h],eax
    L_00401ecc:
        mov dword ptr [edx+200h],eax
    L_00401ed2:
        mov dword ptr [edx+22Ch],eax
    L_00401ed8:
        pop esi
    L_00401ed9:
        mov dword ptr [edx+4],edx
    L_00401edc:
        mov dword ptr [edx+8],eax
    L_00401edf:
        mov dword ptr [edx+0Ch],eax
    L_00401ee2:
        pop ebp
    L_00401ee3:
        mov dword ptr [edx+10h],edx
    L_00401ee6:
        mov dword ptr [edx+14h],eax
    L_00401ee9:
        mov dword ptr [edx+18h],eax
    L_00401eec:
        pop ebx
    L_00401eed:
        add esp,10h
    L_00401ef0:
        ret
    }
}

// 0x00402050..0x004020A7: Entity_Constructor
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Entity_Constructor_00402050() {
    __asm {
    L_00402050:
        mov edx,ecx
    L_00402052:
        mov ecx,dword ptr [edx+6Ch]
    L_00402055:
        mov eax,0FFFFFFFEh
    L_0040205a:
        and ecx,eax
    L_0040205c:
        mov dword ptr [edx+6Ch],ecx
    L_0040205f:
        push edi
    L_00402060:
        and dword ptr [edx+0B0h],eax
    L_00402066:
        and dword ptr [edx+0FCh],eax
    L_0040206c:
        and dword ptr [edx+128h],eax
    L_00402072:
        and dword ptr [edx+174h],eax
    L_00402078:
        and dword ptr [edx+1B0h],eax
    L_0040207e:
        and dword ptr [edx+1FCh],eax
    L_00402084:
        and dword ptr [edx+228h],eax
    L_0040208a:
        and dword ptr [edx+378h],eax
    L_00402090:
        xor eax,eax
    L_00402092:
        mov ecx,0EBh
    L_00402097:
        mov edi,edx
    L_00402099:
        rep stosd
    L_0040209b:
        mov word ptr [edx+384h],0FFFFh
    L_004020a4:
        mov eax,edx
    L_004020a6:
        pop edi
    L_004020a7:
        ret
    }
}

// 0x00405D00..0x00405DD6: FUN_00405d00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405d00_00405d00() {
    __asm {
    L_00405d00:
        push ebx
    L_00405d01:
        mov ebx,ecx
    L_00405d03:
        mov eax,dword ptr [ebx+74h]
    L_00405d06:
        lea edx,[ebx+8]
    L_00405d09:
        push esi
    L_00405d0a:
        mov esi,0FFFFFFFEh
    L_00405d0f:
        and eax,esi
    L_00405d11:
        mov dword ptr [edx+6Ch],eax
    L_00405d14:
        push edi
    L_00405d15:
        and dword ptr [edx+0B0h],esi
    L_00405d1b:
        and dword ptr [edx+0FCh],esi
    L_00405d21:
        and dword ptr [edx+128h],esi
    L_00405d27:
        and dword ptr [edx+174h],esi
    L_00405d2d:
        and dword ptr [edx+1B0h],esi
    L_00405d33:
        and dword ptr [edx+1FCh],esi
    L_00405d39:
        and dword ptr [edx+228h],esi
    L_00405d3f:
        mov ecx,dword ptr [edx+378h]
    L_00405d45:
        xor eax,eax
    L_00405d47:
        and ecx,esi
    L_00405d49:
        mov dword ptr [edx+378h],ecx
    L_00405d4f:
        mov edi,edx
    L_00405d51:
        mov ecx,0EBh
    L_00405d56:
        rep stosd
    L_00405d58:
        mov word ptr [edx+384h],0FFFFh
    L_00405d61:
        and dword ptr [ebx+408h],esi
    L_00405d67:
        and dword ptr [ebx+41Ch],esi
    L_00405d6d:
        mov edx,dword ptr [ebx+624h]
    L_00405d73:
        lea eax,[ebx+614h]
    L_00405d79:
        add eax,34h
    L_00405d7c:
        and edx,esi
    L_00405d7e:
        mov dword ptr [eax-24h],edx
    L_00405d81:
        mov edi,dword ptr [eax+10h]
    L_00405d84:
        add eax,34h
    L_00405d87:
        and edi,esi
    L_00405d89:
        mov dword ptr [eax-24h],edi
    L_00405d8c:
        mov ecx,dword ptr [eax+10h]
    L_00405d8f:
        add eax,34h
    L_00405d92:
        and ecx,esi
    L_00405d94:
        mov dword ptr [eax-24h],ecx
    L_00405d97:
        mov edx,dword ptr [eax+10h]
    L_00405d9a:
        add eax,34h
    L_00405d9d:
        and edx,esi
    L_00405d9f:
        mov dword ptr [eax-24h],edx
    L_00405da2:
        and dword ptr [eax+10h],esi
    L_00405da5:
        mov ecx,dword ptr [eax+44h]
    L_00405da8:
        add eax,34h
    L_00405dab:
        and ecx,esi
    L_00405dad:
        mov dword ptr [eax+10h],ecx
    L_00405db0:
        mov edx,dword ptr [eax+44h]
    L_00405db3:
        add eax,34h
    L_00405db6:
        and edx,esi
    L_00405db8:
        mov dword ptr [eax+10h],edx
    L_00405dbb:
        mov edi,dword ptr [eax+44h]
    L_00405dbe:
        add eax,34h
    L_00405dc1:
        and edi,esi
    L_00405dc3:
        mov dword ptr [eax+10h],edi
    L_00405dc6:
        mov ecx,dword ptr [eax+44h]
    L_00405dc9:
        add eax,34h
    L_00405dcc:
        and ecx,esi
    L_00405dce:
        mov dword ptr [eax+10h],ecx
    L_00405dd1:
        mov eax,ebx
    L_00405dd3:
        pop edi
    L_00405dd4:
        pop esi
    L_00405dd5:
        pop ebx
    L_00405dd6:
        ret
    }
}

// 0x00406160..0x004061CC: ?Entity_PointWithinBounds@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Entity_PointWithinBounds_00406160() {
    __asm {
    L_00406160:
        fld dword ptr [esp+4]
    L_00406164:
        fmul dword ptr [data_00470b0c]
    L_0040616a:
        fld st(0)
    L_0040616c:
        fadd dword ptr [ecx]
    L_0040616e:
        fcomp dword ptr [data_00470b40]
    L_00406174:
        fnstsw ax
    L_00406176:
        test ah,41h
    L_00406179:
        jnp short L_004061c3
    L_0040617b:
        fld dword ptr [ecx]
    L_0040617d:
        fsub st,st(1)
    L_0040617f:
        fcomp dword ptr [data_00470b3c]
    L_00406185:
        fnstsw ax
    L_00406187:
        fstp st(0)
    L_00406189:
        test ah,1
    L_0040618c:
        je short L_004061c5
    L_0040618e:
        fld dword ptr [esp+8]
    L_00406192:
        fmul dword ptr [data_00470b0c]
    L_00406198:
        fld st(0)
    L_0040619a:
        fadd dword ptr [ecx+4]
    L_0040619d:
        fcomp dword ptr [data_00470b5c]
    L_004061a3:
        fnstsw ax
    L_004061a5:
        test ah,41h
    L_004061a8:
        jnp short L_004061c3
    L_004061aa:
        fld dword ptr [ecx+4]
    L_004061ad:
        fsub st,st(1)
    L_004061af:
        fcomp dword ptr [data_00470b38]
    L_004061b5:
        fnstsw ax
    L_004061b7:
        fstp st(0)
    L_004061b9:
        test ah,1
    L_004061bc:
        je short L_004061c5
    L_004061be:
        xor eax,eax
    L_004061c0:
        ret 8
    L_004061c3:
        fstp st(0)
    L_004061c5:
        mov eax,1
    L_004061ca:
        ret 8
    }
}

// 0x004061D0..0x0040623C: ?Entity_PointWithinBoundsInclusive@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Entity_PointWithinBoundsInclusive_004061d0() {
    __asm {
    L_004061d0:
        fld dword ptr [esp+4]
    L_004061d4:
        fmul dword ptr [data_00470b0c]
    L_004061da:
        fld st(0)
    L_004061dc:
        fadd dword ptr [ecx]
    L_004061de:
        fcomp dword ptr [data_00470b40]
    L_004061e4:
        fnstsw ax
    L_004061e6:
        test ah,41h
    L_004061e9:
        jnp short L_00406233
    L_004061eb:
        fld dword ptr [ecx]
    L_004061ed:
        fsub st,st(1)
    L_004061ef:
        fcomp dword ptr [data_00470b3c]
    L_004061f5:
        fnstsw ax
    L_004061f7:
        fstp st(0)
    L_004061f9:
        test ah,1
    L_004061fc:
        je short L_00406235
    L_004061fe:
        fld dword ptr [esp+8]
    L_00406202:
        fmul dword ptr [data_00470b0c]
    L_00406208:
        fld st(0)
    L_0040620a:
        fadd dword ptr [ecx+4]
    L_0040620d:
        fcomp dword ptr [data_00470b04]
    L_00406213:
        fnstsw ax
    L_00406215:
        test ah,41h
    L_00406218:
        jnp short L_00406233
    L_0040621a:
        fld dword ptr [ecx+4]
    L_0040621d:
        fsub st,st(1)
    L_0040621f:
        fcomp dword ptr [data_00470b38]
    L_00406225:
        fnstsw ax
    L_00406227:
        fstp st(0)
    L_00406229:
        test ah,1
    L_0040622c:
        je short L_00406235
    L_0040622e:
        xor eax,eax
    L_00406230:
        ret 8
    L_00406233:
        fstp st(0)
    L_00406235:
        mov eax,1
    L_0040623a:
        ret 8
    }
}

// 0x00438A30..0x00438A5A: DestroyEntityList
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DestroyEntityList_00438a30() {
    __asm {
    L_00438a30:
        push esi
    L_00438a31:
        mov esi,eax
    L_00438a33:
        push edi
    L_00438a34:
        add esi,3AD4E0h
    L_00438a3a:
        mov edi,20h
    L_00438a3f:
        nop
    L_00438a40:
        mov eax,dword ptr [esi]
    L_00438a42:
        test eax,eax
    L_00438a44:
        je short L_00438a52
    L_00438a46:
        mov ecx,dword ptr [eax]
    L_00438a48:
        push eax
    L_00438a49:
        call dword ptr [ecx+8]
    L_00438a4c:
        mov dword ptr [esi],0
    L_00438a52:
        add esi,4
    L_00438a55:
        dec edi
    L_00438a56:
        jne short L_00438a40
    L_00438a58:
        pop edi
    L_00438a59:
        pop esi
    L_00438a5a:
        ret
    }
}

// Recovered semantic C++ definitions.
#include "th10/game/entity.hpp"

extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void* __cdecl operator_new(uint32_t);

void __fastcall Entity_Destructor(Entity* entity) {
    void* resource = entity->resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->resource = 0;
}

void __fastcall EntitySecondaryResource_Release(Entity* entity) {
    void* resource = entity->secondary_resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->secondary_resource = 0;
}

void __fastcall EntityAnimation_Release(Entity* entity) {
    void* resource = entity->resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->resource = 0;
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3307): closest_byte_count=0/1681; first_diff=0x00429B60;
// residual_class=the 0x00429B60 body is a security-cookie worker with a
// private ECX/EDX/stack entry, nested replay-buffer layout, x87 arithmetic,
// Win32 import slots, and several compiler-selected helper conventions.
// variants_tested=live Ghidra complete decompilation with callers/xrefs,
// callees, disassembly/variable audit, and full pseudocode; exact MSVC 13.10
// naked baseline (1681/1681); ordinary __fastcall skeleton (5-byte body,
// decorated @12 symbol) and cdecl/member source-shape review.
// next_lever=schema-2 native-LTCG cluster over real callers 0x00423F16 and
// 0x0043399D, this body, and its replay/compression/Win32 helper edges; first
// recover the state/header/record layouts and private helper ABIs before
// replacing the exact overlay.

// 0x00429B60..0x0042A1F0: FUN_00429b60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00429b60_00429b60() {
    __asm {
    L_00429b60:
        sub esp,124h
    L_00429b66:
        mov eax,dword ptr [data_00473660]
    L_00429b6b:
        xor eax,esp
    L_00429b6d:
        push ebx
    L_00429b6e:
        push ebp
    L_00429b6f:
        push esi
    L_00429b70:
        mov dword ptr [esp+12Ch],eax
    L_00429b77:
        mov eax,dword ptr [esp+134h]
    L_00429b7e:
        push edi
    L_00429b7f:
        mov edi,ecx
    L_00429b81:
        xor ebp,ebp
    L_00429b83:
        mov esi,edx
    L_00429b85:
        mov edx,dword ptr [edi+18h]
    L_00429b88:
        mov dword ptr [esp+28h],edi
    L_00429b8c:
        mov dword ptr [esp+24h],ebp
    L_00429b90:
        mov dword ptr [esp+1Ch],ebp
    L_00429b94:
        mov ecx,eax
    L_00429b96:
        mov bl,byte ptr [ecx]
    L_00429b98:
        inc ecx
    L_00429b99:
        mov byte ptr [edx],bl
    L_00429b9b:
        inc edx
    L_00429b9c:
        test bl,bl
    L_00429b9e:
        jne short L_00429b96
    L_00429ba0:
        lea edx,[eax+1]
    L_00429ba3:
        mov cl,byte ptr [eax]
    L_00429ba5:
        inc eax
    L_00429ba6:
        test cl,cl
    L_00429ba8:
        jne short L_00429ba3
    L_00429baa:
        sub eax,edx
    L_00429bac:
        cmp eax,8
    L_00429baf:
        jge short L_00429bbe
    L_00429bb1:
        mov ecx,dword ptr [edi+18h]
    L_00429bb4:
        mov byte ptr [eax+ecx],20h
    L_00429bb8:
        inc eax
    L_00429bb9:
        cmp eax,8
    L_00429bbc:
        jl short L_00429bb1
    L_00429bbe:
        push 46E650h
    L_00429bc3:
        call asm_FUN_00452abc_00452abc
    L_00429bc8:
        push esi
    L_00429bc9:
        lea edx,[esp+38h]
    L_00429bcd:
        push 46E644h
    L_00429bd2:
        push edx
    L_00429bd3:
        call asm_sprintf_00452ae8
    L_00429bd8:
        add esp,10h
    L_00429bdb:
        xor eax,eax
    L_00429bdd:
        lea ecx,[edi+40h]
    L_00429be0:
        mov dword ptr [esp+14h],ebp
    L_00429be4:
        mov ebx,64h
    L_00429be9:
        mov dword ptr [esp+20h],eax
    L_00429bed:
        lea ebp,[edi+1Ch]
    L_00429bf0:
        mov dword ptr [esp+10h],ecx
    L_00429bf4:
        mov ecx,dword ptr [ebp]
    L_00429bf7:
        test ecx,ecx
    L_00429bf9:
        je asm_target_00429cc6
    L_00429bff:
        mov edx,dword ptr [esp+24h]
    L_00429c03:
        test edx,edx
    L_00429c05:
        jne short L_00429c0b
    L_00429c07:
        mov dword ptr [esp+24h],eax
    L_00429c0b:
        mov dword ptr [ecx+8],0
    L_00429c12:
        mov ecx,dword ptr [esp+10h]
    L_00429c16:
        mov esi,dword ptr [ecx]
    L_00429c18:
        add ebx,1C4h
    L_00429c1e:
        test esi,esi
    L_00429c20:
        mov dword ptr [esp+1Ch],eax
    L_00429c24:
        je asm_target_00429cc2
    L_00429c2a:
        lea ebx,[ebx+force_disp32_zero]
    L_00429c30:
        mov ecx,dword ptr [esi]
    L_00429c32:
        mov edx,dword ptr [ecx+5460h]
    L_00429c38:
        sub edx,ecx
    L_00429c3a:
        mov eax,2AAAAAABh
    L_00429c3f:
        imul edx
    L_00429c41:
        mov eax,edx
    L_00429c43:
        shr eax,1Fh
    L_00429c46:
        add eax,edx
    L_00429c48:
        lea edx,[eax+eax*2]
    L_00429c4b:
        mov eax,dword ptr [ecx+6274h]
    L_00429c51:
        lea edx,[eax+edx*2]
    L_00429c54:
        sub edx,ecx
    L_00429c56:
        mov edi,dword ptr [ebp]
    L_00429c59:
        lea ebx,[ebx+edx-5464h]
    L_00429c60:
        mov edx,dword ptr [ecx+5460h]
    L_00429c66:
        sub edx,ecx
    L_00429c68:
        mov eax,2AAAAAABh
    L_00429c6d:
        imul edx
    L_00429c6f:
        mov eax,edx
    L_00429c71:
        shr eax,1Fh
    L_00429c74:
        add eax,edx
    L_00429c76:
        mov edx,dword ptr [ecx+6274h]
    L_00429c7c:
        lea eax,[eax+eax*2]
    L_00429c7f:
        lea eax,[edx+eax*2]
    L_00429c82:
        sub eax,ecx
    L_00429c84:
        mov ecx,dword ptr [edi+8]
    L_00429c87:
        sub eax,5464h
    L_00429c8c:
        add ecx,eax
    L_00429c8e:
        mov dword ptr [edi+8],ecx
    L_00429c91:
        mov eax,dword ptr [esi]
    L_00429c93:
        mov ecx,dword ptr [eax+5460h]
    L_00429c99:
        mov edi,dword ptr [ebp]
    L_00429c9c:
        sub ecx,eax
    L_00429c9e:
        mov eax,2AAAAAABh
    L_00429ca3:
        imul ecx
    L_00429ca5:
        mov ecx,edx
    L_00429ca7:
        shr ecx,1Fh
    L_00429caa:
        add ecx,edx
    L_00429cac:
        add dword ptr [edi+4],ecx
    L_00429caf:
        mov esi,dword ptr [esi+4]
    L_00429cb2:
        test esi,esi
    L_00429cb4:
        jne asm_target_00429c30
    L_00429cba:
        mov eax,dword ptr [esp+20h]
    L_00429cbe:
        mov edi,dword ptr [esp+28h]
    L_00429cc2:
        inc dword ptr [esp+14h]
    L_00429cc6:
        mov edx,dword ptr [esp+10h]
    L_00429cca:
        inc eax
    L_00429ccb:
        add edx,0Ch
    L_00429cce:
        add ebp,4
    L_00429cd1:
        cmp eax,8
    L_00429cd4:
        mov dword ptr [esp+20h],eax
    L_00429cd8:
        mov dword ptr [esp+10h],edx
    L_00429cdc:
        jl asm_target_00429bf4
    L_00429ce2:
        mov edx,dword ptr [edi+18h]
    L_00429ce5:
        mov eax,dword ptr [esp+14h]
    L_00429ce9:
        mov dword ptr [edx+4Ch],eax
    L_00429cec:
        mov ecx,dword ptr [edi+18h]
    L_00429cef:
        mov edx,dword ptr [data_00474c44]
    L_00429cf5:
        mov eax,dword ptr [data_00477708]
    L_00429cfa:
        mov dword ptr [ecx+10h],edx
    L_00429cfd:
        fld qword ptr [eax+24h]
    L_00429d00:
        fdiv qword ptr [eax+2Ch]
    L_00429d03:
        mov eax,dword ptr [edi+18h]
    L_00429d06:
        push ebx
    L_00429d07:
        fmul dword ptr [data_00470b44]
    L_00429d0d:
        fsubr dword ptr [data_00470b44]
    L_00429d13:
        fstp dword ptr [eax+48h]
    L_00429d16:
        call asm_malloc_00452706
    L_00429d1b:
        mov esi,dword ptr [edi+18h]
    L_00429d1e:
        mov ebp,eax
    L_00429d20:
        mov ecx,19h
    L_00429d25:
        mov edi,ebp
    L_00429d27:
        rep movsd
    L_00429d29:
        mov ecx,dword ptr [esp+2Ch]
    L_00429d2d:
        lea eax,[ecx+40h]
    L_00429d30:
        mov dword ptr [esp+14h],eax
    L_00429d34:
        lea eax,[ecx+1Ch]
    L_00429d37:
        add esp,4
    L_00429d3a:
        mov dword ptr [esp+14h],ebp
    L_00429d3e:
        mov ebx,64h
    L_00429d43:
        mov dword ptr [esp+2Ch],eax
    L_00429d47:
        mov dword ptr [esp+18h],8
    L_00429d4f:
        nop
    L_00429d50:
        mov esi,dword ptr [eax]
    L_00429d52:
        test esi,esi
    L_00429d54:
        je asm_target_00429e31
    L_00429d5a:
        lea edi,[ebx+ebp]
    L_00429d5d:
        mov ecx,71h
    L_00429d62:
        rep movsd
    L_00429d64:
        mov ecx,dword ptr [esp+10h]
    L_00429d68:
        mov eax,dword ptr [ecx]
    L_00429d6a:
        add ebx,1C4h
    L_00429d70:
        test eax,eax
    L_00429d72:
        mov dword ptr [esp+20h],eax
    L_00429d76:
        je short L_00429de3
    L_00429d78:
        jmp short L_00429d80
    L_00429d7a:
        mov eax,dword ptr [esp+20h]
    L_00429d7e:
        mov edi,edi
    L_00429d80:
        mov ebp,dword ptr [eax]
    L_00429d82:
        mov ecx,dword ptr [ebp+5460h]
    L_00429d88:
        sub ecx,ebp
    L_00429d8a:
        mov eax,2AAAAAABh
    L_00429d8f:
        imul ecx
    L_00429d91:
        mov eax,edx
    L_00429d93:
        shr eax,1Fh
    L_00429d96:
        add eax,edx
    L_00429d98:
        mov edx,dword ptr [esp+14h]
    L_00429d9c:
        lea ecx,[eax+eax*2]
    L_00429d9f:
        shl ecx,1
    L_00429da1:
        mov eax,ecx
    L_00429da3:
        shr ecx,2
    L_00429da6:
        lea edi,[edx+ebx]
    L_00429da9:
        mov esi,ebp
    L_00429dab:
        rep movsd
    L_00429dad:
        mov ecx,eax
    L_00429daf:
        and ecx,3
    L_00429db2:
        rep movsb
    L_00429db4:
        mov ecx,dword ptr [ebp+5460h]
    L_00429dba:
        sub ecx,ebp
    L_00429dbc:
        mov eax,2AAAAAABh
    L_00429dc1:
        imul ecx
    L_00429dc3:
        mov eax,edx
    L_00429dc5:
        shr eax,1Fh
    L_00429dc8:
        add eax,edx
    L_00429dca:
        mov edx,dword ptr [esp+20h]
    L_00429dce:
        lea ecx,[eax+eax*2]
    L_00429dd1:
        mov eax,dword ptr [edx+4]
    L_00429dd4:
        test eax,eax
    L_00429dd6:
        lea ebx,[ebx+ecx*2]
    L_00429dd9:
        mov dword ptr [esp+20h],eax
    L_00429ddd:
        jne short L_00429d7a
    L_00429ddf:
        mov ebp,dword ptr [esp+14h]
    L_00429de3:
        mov eax,dword ptr [esp+10h]
    L_00429de7:
        mov edx,dword ptr [eax]
    L_00429de9:
        test edx,edx
    L_00429deb:
        je short L_00429e31
    L_00429ded:
        TH10_NOP_LEA_ECX_DISP8()
    L_00429df0:
        mov eax,dword ptr [edx]
    L_00429df2:
        mov ecx,dword ptr [eax+6274h]
    L_00429df8:
        sub ecx,eax
    L_00429dfa:
        sub ecx,5464h
    L_00429e00:
        lea edi,[ebx+ebp]
    L_00429e03:
        mov ebp,ecx
    L_00429e05:
        shr ecx,2
    L_00429e08:
        lea esi,[eax+5464h]
    L_00429e0e:
        rep movsd
    L_00429e10:
        mov ecx,ebp
    L_00429e12:
        mov ebp,dword ptr [esp+14h]
    L_00429e16:
        and ecx,3
    L_00429e19:
        rep movsb
    L_00429e1b:
        mov ecx,dword ptr [eax+6274h]
    L_00429e21:
        mov edx,dword ptr [edx+4]
    L_00429e24:
        sub ecx,eax
    L_00429e26:
        test edx,edx
    L_00429e28:
        lea ebx,[ebx+ecx-5464h]
    L_00429e2f:
        jne short L_00429df0
    L_00429e31:
        mov eax,dword ptr [esp+2Ch]
    L_00429e35:
        mov edx,dword ptr [esp+10h]
    L_00429e39:
        mov ecx,dword ptr [esp+18h]
    L_00429e3d:
        add eax,4
    L_00429e40:
        add edx,0Ch
    L_00429e43:
        dec ecx
    L_00429e44:
        mov dword ptr [esp+2Ch],eax
    L_00429e48:
        mov dword ptr [esp+10h],edx
    L_00429e4c:
        mov dword ptr [esp+18h],ecx
    L_00429e50:
        jne asm_target_00429d50
    L_00429e56:
        lea edx,[esp+18h]
    L_00429e5a:
        push edx
    L_00429e5b:
        push ebx
    L_00429e5c:
        push ebp
    L_00429e5d:
        call Lzss_Compress_004359B0
    L_00429e62:
        push ebp
    L_00429e63:
        mov edi,eax
    L_00429e65:
        call asm_free_00452422
    L_00429e6a:
        mov esi,dword ptr [esp+1Ch]
    L_00429e6e:
        add esp,4
    L_00429e71:
        push esi
    L_00429e72:
        push 80h
    L_00429e77:
        push 7Ah
    L_00429e79:
        push esi
    L_00429e7a:
        push edi
    L_00429e7b:
        mov al,3Dh
    L_00429e7d:
        call asm_EncryptDatBuffer_0044b220
    L_00429e82:
        push esi
    L_00429e83:
        push 400h
    L_00429e88:
        push 0E1h
    L_00429e8d:
        push esi
    L_00429e8e:
        push edi
    L_00429e8f:
        mov al,0AAh
    L_00429e91:
        call asm_EncryptDatBuffer_0044b220
    L_00429e96:
        mov ebp,dword ptr [esp+28h]
    L_00429e9a:
        mov eax,dword ptr [ebp+14h]
    L_00429e9d:
        mov dword ptr [eax+20h],ebx
    L_00429ea0:
        mov ecx,dword ptr [ebp+14h]
    L_00429ea3:
        mov dword ptr [ecx+1Ch],esi
    L_00429ea6:
        mov eax,dword ptr [ebp+14h]
    L_00429ea9:
        mov edx,dword ptr [eax+1Ch]
    L_00429eac:
        add edx,24h
    L_00429eaf:
        mov dword ptr [eax+0Ch],edx
    L_00429eb2:
        lea eax,[esp+30h]
    L_00429eb6:
        push eax
    L_00429eb7:
        call asm_File_OpenSharedWrite_0044b620
    L_00429ebc:
        mov eax,dword ptr [data_00474c38]
    L_00429ec1:
        cmp eax,0FFFFFFFFh
    L_00429ec4:
        je short L_00429f3a
    L_00429ec6:
        mov edx,dword ptr [ebp+14h]
    L_00429ec9:
        mov ebx,dword ptr [data_004660d4]
    L_00429ecf:
        push 0
    L_00429ed1:
        lea ecx,[esp+1Ch]
    L_00429ed5:
        push ecx
    L_00429ed6:
        push 24h
    L_00429ed8:
        push edx
    L_00429ed9:
        push eax
    L_00429eda:
        call ebx
    L_00429edc:
        cmp dword ptr [esp+18h],24h
    L_00429ee1:
        je short L_00429f00
    L_00429ee3:
        mov eax,dword ptr [data_00474c38]
    L_00429ee8:
        push eax
    L_00429ee9:
        call dword ptr [data_004660cc]
    L_00429eef:
        push 4922A4h
    L_00429ef4:
        call dword ptr [data_004660b4]
    L_00429efa:
        dec byte ptr [data_0049231e]
    L_00429f00:
        mov eax,dword ptr [data_00474c38]
    L_00429f05:
        cmp eax,0FFFFFFFFh
    L_00429f08:
        je short L_00429f3a
    L_00429f0a:
        push 0
    L_00429f0c:
        lea ecx,[esp+1Ch]
    L_00429f10:
        push ecx
    L_00429f11:
        push esi
    L_00429f12:
        push edi
    L_00429f13:
        push eax
    L_00429f14:
        call ebx
    L_00429f16:
        cmp esi,dword ptr [esp+18h]
    L_00429f1a:
        je short L_00429f3a
    L_00429f1c:
        mov edx,dword ptr [data_00474c38]
    L_00429f22:
        push edx
    L_00429f23:
        call dword ptr [data_004660cc]
    L_00429f29:
        push 4922A4h
    L_00429f2e:
        call dword ptr [data_004660b4]
    L_00429f34:
        dec byte ptr [data_0049231e]
    L_00429f3a:
        test edi,edi
    L_00429f3c:
        je short L_00429f47
    L_00429f3e:
        push edi
    L_00429f3f:
        call asm_free_00452422
    L_00429f44:
        add esp,4
    L_00429f47:
        push 0FFFFh
    L_00429f4c:
        call asm_malloc_00452706
    L_00429f51:
        mov ebx,eax
    L_00429f53:
        xor eax,eax
    L_00429f55:
        mov ecx,3FFFh
    L_00429f5a:
        mov edi,ebx
    L_00429f5c:
        rep stosd
    L_00429f5e:
        stosw
    L_00429f60:
        stosb
    L_00429f61:
        lea esi,[ebx+0Ch]
    L_00429f64:
        push 46E5E0h
    L_00429f69:
        push esi
    L_00429f6a:
        mov dword ptr [ebx],52455355h
    L_00429f70:
        mov byte ptr [ebx+8],0
    L_00429f74:
        call asm_sprintf_00452ae8
    L_00429f79:
        push 46E5D8h
    L_00429f7e:
        add esi,eax
    L_00429f80:
        push 46E5C8h
    L_00429f85:
        push esi
    L_00429f86:
        call asm_sprintf_00452ae8
    L_00429f8b:
        add esi,eax
    L_00429f8d:
        mov eax,dword ptr [ebp+18h]
    L_00429f90:
        push eax
    L_00429f91:
        push 46E5BCh
    L_00429f96:
        push esi
    L_00429f97:
        call asm_sprintf_00452ae8
    L_00429f9c:
        mov ecx,dword ptr [ebp+18h]
    L_00429f9f:
        add ecx,0Ch
    L_00429fa2:
        push ecx
    L_00429fa3:
        add esi,eax
    L_00429fa5:
        call asm_localtime_00452baa
    L_00429faa:
        mov edx,dword ptr [eax+4]
    L_00429fad:
        mov ecx,dword ptr [eax+8]
    L_00429fb0:
        push edx
    L_00429fb1:
        mov edx,dword ptr [eax+0Ch]
    L_00429fb4:
        push ecx
    L_00429fb5:
        mov ecx,dword ptr [eax+10h]
    L_00429fb8:
        mov eax,dword ptr [eax+14h]
    L_00429fbb:
        push edx
    L_00429fbc:
        inc ecx
    L_00429fbd:
        push ecx
    L_00429fbe:
        cdq
    L_00429fbf:
        mov ecx,64h
    L_00429fc4:
        idiv ecx
    L_00429fc6:
        push edx
    L_00429fc7:
        push 46E59Ch
    L_00429fcc:
        push esi
    L_00429fcd:
        call asm_sprintf_00452ae8
    L_00429fd2:
        add esi,eax
    L_00429fd4:
        mov eax,dword ptr [ebp+18h]
    L_00429fd7:
        mov ecx,dword ptr [eax+50h]
    L_00429fda:
        mov edi,dword ptr [eax+54h]
    L_00429fdd:
        lea edx,[ecx+ecx*2]
    L_00429fe0:
        add edx,edi
    L_00429fe2:
        mov eax,dword ptr [edx*4+4746DCh]
    L_00429fe9:
        add esp,44h
    L_00429fec:
        push eax
    L_00429fed:
        push 46E590h
    L_00429ff2:
        push esi
    L_00429ff3:
        call asm_sprintf_00452ae8
    L_00429ff8:
        mov ecx,dword ptr [ebp+18h]
    L_00429ffb:
        mov edx,dword ptr [ecx+58h]
    L_00429ffe:
        add esi,eax
    L_0042a000:
        mov eax,dword ptr [edx*4+4746F4h]
    L_0042a007:
        push eax
    L_0042a008:
        push 46E584h
    L_0042a00d:
        push esi
    L_0042a00e:
        call asm_sprintf_00452ae8
    L_0042a013:
        mov edx,dword ptr [ebp+18h]
    L_0042a016:
        add esi,eax
    L_0042a018:
        mov eax,dword ptr [edx+5Ch]
    L_0042a01b:
        mov ecx,7
    L_0042a020:
        add esp,18h
    L_0042a023:
        cmp eax,ecx
    L_0042a025:
        jle short L_0042a04d
    L_0042a027:
        cmp dword ptr [esp+24h],ecx
    L_0042a02b:
        jne short L_0042a03d
    L_0042a02d:
        push 46E570h
    L_0042a032:
        push esi
    L_0042a033:
        call asm_sprintf_00452ae8
    L_0042a038:
        add esp,8
    L_0042a03b:
        jmp short L_0042a08e
    L_0042a03d:
        push 46E55Ch
    L_0042a042:
        push esi
    L_0042a043:
        call asm_sprintf_00452ae8
    L_0042a048:
        add esp,8
    L_0042a04b:
        jmp short L_0042a08e
    L_0042a04d:
        mov eax,dword ptr [esp+24h]
    L_0042a051:
        mov edx,dword ptr [esp+1Ch]
    L_0042a055:
        cmp eax,edx
    L_0042a057:
        jne short L_0042a07e
    L_0042a059:
        cmp eax,ecx
    L_0042a05b:
        jne short L_0042a06d
    L_0042a05d:
        push 46E54Ch
    L_0042a062:
        push esi
    L_0042a063:
        call asm_sprintf_00452ae8
    L_0042a068:
        add esp,8
    L_0042a06b:
        jmp short L_0042a08e
    L_0042a06d:
        push eax
    L_0042a06e:
        push 46E540h
    L_0042a073:
        push esi
    L_0042a074:
        call asm_sprintf_00452ae8
    L_0042a079:
        add esp,0Ch
    L_0042a07c:
        jmp short L_0042a08e
    L_0042a07e:
        push edx
    L_0042a07f:
        push eax
    L_0042a080:
        push 46E52Ch
    L_0042a085:
        push esi
    L_0042a086:
        call asm_sprintf_00452ae8
    L_0042a08b:
        add esp,10h
    L_0042a08e:
        add esi,eax
    L_0042a090:
        mov eax,dword ptr [ebp+18h]
    L_0042a093:
        mov ecx,dword ptr [eax+10h]
    L_0042a096:
        push ecx
    L_0042a097:
        push 46E520h
    L_0042a09c:
        push esi
    L_0042a09d:
        call asm_sprintf_00452ae8
    L_0042a0a2:
        mov edx,dword ptr [ebp+18h]
    L_0042a0a5:
        fld dword ptr [edx+48h]
    L_0042a0a8:
        add esp,4
    L_0042a0ab:
        fstp qword ptr [esp]
    L_0042a0ae:
        add esi,eax
    L_0042a0b0:
        push 46E50Ch
    L_0042a0b5:
        push esi
    L_0042a0b6:
        call asm_sprintf_00452ae8
    L_0042a0bb:
        lea esi,[esi+eax+1]
    L_0042a0bf:
        mov eax,esi
    L_0042a0c1:
        sub eax,ebx
    L_0042a0c3:
        add esp,10h
    L_0042a0c6:
        and eax,80000003h
    L_0042a0cb:
        jns short L_0042a0d2
    L_0042a0cd:
        dec eax
    L_0042a0ce:
        or eax,0FFFFFFFCh
    L_0042a0d1:
        inc eax
    L_0042a0d2:
        je short L_0042a0dd
    L_0042a0d4:
        mov ecx,4
    L_0042a0d9:
        sub ecx,eax
    L_0042a0db:
        add esi,ecx
    L_0042a0dd:
        mov eax,dword ptr [data_00474c38]
    L_0042a0e2:
        sub esi,ebx
    L_0042a0e4:
        cmp eax,0FFFFFFFFh
    L_0042a0e7:
        mov dword ptr [ebx+4],esi
    L_0042a0ea:
        je short L_0042a11f
    L_0042a0ec:
        push 0
    L_0042a0ee:
        lea edx,[esp+20h]
    L_0042a0f2:
        push edx
    L_0042a0f3:
        push esi
    L_0042a0f4:
        push ebx
    L_0042a0f5:
        push eax
    L_0042a0f6:
        call dword ptr [data_004660d4]
    L_0042a0fc:
        cmp esi,dword ptr [esp+1Ch]
    L_0042a100:
        je short L_0042a11f
    L_0042a102:
        mov eax,dword ptr [data_00474c38]
    L_0042a107:
        push eax
    L_0042a108:
        call dword ptr [data_004660cc]
    L_0042a10e:
        push 4922A4h
    L_0042a113:
        call dword ptr [data_004660b4]
    L_0042a119:
        dec byte ptr [data_0049231e]
    L_0042a11f:
        xor eax,eax
    L_0042a121:
        mov ecx,3FFFh
    L_0042a126:
        mov edi,ebx
    L_0042a128:
        rep stosd
    L_0042a12a:
        stosw
    L_0042a12c:
        stosb
    L_0042a12d:
        push 46E4F8h
    L_0042a132:
        lea esi,[ebx+0Ch]
    L_0042a135:
        push esi
    L_0042a136:
        mov dword ptr [ebx],52455355h
    L_0042a13c:
        mov byte ptr [ebx+8],1
    L_0042a140:
        call asm_sprintf_00452ae8
    L_0042a145:
        lea esi,[esi+eax+1]
    L_0042a149:
        mov eax,esi
    L_0042a14b:
        sub eax,ebx
    L_0042a14d:
        add esp,8
    L_0042a150:
        and eax,80000003h
    L_0042a155:
        jns short L_0042a15c
    L_0042a157:
        dec eax
    L_0042a158:
        or eax,0FFFFFFFCh
    L_0042a15b:
        inc eax
    L_0042a15c:
        je short L_0042a167
    L_0042a15e:
        mov ecx,4
    L_0042a163:
        sub ecx,eax
    L_0042a165:
        add esi,ecx
    L_0042a167:
        mov eax,dword ptr [data_00474c38]
    L_0042a16c:
        sub esi,ebx
    L_0042a16e:
        cmp eax,0FFFFFFFFh
    L_0042a171:
        mov dword ptr [ebx+4],esi
    L_0042a174:
        je short L_0042a1a9
    L_0042a176:
        push 0
    L_0042a178:
        lea edx,[esp+20h]
    L_0042a17c:
        push edx
    L_0042a17d:
        push esi
    L_0042a17e:
        push ebx
    L_0042a17f:
        push eax
    L_0042a180:
        call dword ptr [data_004660d4]
    L_0042a186:
        cmp esi,dword ptr [esp+1Ch]
    L_0042a18a:
        je short L_0042a1a9
    L_0042a18c:
        mov eax,dword ptr [data_00474c38]
    L_0042a191:
        push eax
    L_0042a192:
        call dword ptr [data_004660cc]
    L_0042a198:
        push 4922A4h
    L_0042a19d:
        call dword ptr [data_004660b4]
    L_0042a1a3:
        dec byte ptr [data_0049231e]
    L_0042a1a9:
        push ebx
    L_0042a1aa:
        call asm_free_00452422
    L_0042a1af:
        mov eax,dword ptr [data_00474c38]
    L_0042a1b4:
        add esp,4
    L_0042a1b7:
        cmp eax,0FFFFFFFFh
    L_0042a1ba:
        pop edi
    L_0042a1bb:
        pop esi
    L_0042a1bc:
        pop ebp
    L_0042a1bd:
        pop ebx
    L_0042a1be:
        je short L_0042a1d8
    L_0042a1c0:
        push eax
    L_0042a1c1:
        call dword ptr [data_004660cc]
    L_0042a1c7:
        push 4922A4h
    L_0042a1cc:
        call dword ptr [data_004660b4]
    L_0042a1d2:
        dec byte ptr [data_0049231e]
    L_0042a1d8:
        mov ecx,dword ptr [esp+120h]
    L_0042a1df:
        xor ecx,esp
    L_0042a1e1:
        xor eax,eax
    L_0042a1e3:
        call asm_security_check_cookie_00458ea5
    L_0042a1e8:
        add esp,124h
    L_0042a1ee:
        ret 4
    }
}

// BLOCKED (D3307): closest_byte_count=0/1968; first_diff=0x00431EE0;
// residual_class=the 0x00431EE0 state-machine worker combines a private
// EDX:EAX/ECX/stack entry, jump-table control flow, many private animation
// and input helper ABIs, and a large unresolved replay/game-state layout.
// variants_tested=live Ghidra complete decompilation with callers/xrefs,
// callees, disassembly/variable audit, and full pseudocode; exact MSVC 13.10
// naked baseline (1968/1968); ordinary __stdcall ABI skeleton (8-byte body,
// decorated @16 symbol) and cdecl/member source-shape review.
// next_lever=schema-2 native-LTCG cluster over real caller 0x0042D192 and
// this body plus the animation/input helper family, preserving the EDX:EAX
// split argument and jump-table state machine before any readable cutover.

// 0x00431EE0..0x004323D6: FUN_00431ee0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00431ee0_00431ee0() {
    __asm {
    L_00431ee0:
        push ecx
    L_00431ee1:
        push ebp
    L_00431ee2:
        mov ebp,dword ptr [esp+0Ch]
    L_00431ee6:
        mov eax,dword ptr [ebp+20h]
    L_00431ee9:
        cmp eax,3
    L_00431eec:
        push esi
    L_00431eed:
        mov esi,1
    L_00431ef2:
        ja asm_target_00432672
    L_00431ef8:
        push ebx
    L_00431ef9:
        push edi
    L_00431efa:
        mov ebx,6
    L_00431eff:
        jmp dword ptr [eax*4+432680h]
    L_00431f06:
        mov eax,ebx
    L_00431f08:
        xor edi,edi
    L_00431f0a:
        cmp eax,edi
    L_00431f0c:
        mov dword ptr [ebp+2Ch],ebx
    L_00431f0f:
        je short L_00431f20
    L_00431f11:
        jg short L_00431f19
    L_00431f13:
        dec eax
    L_00431f14:
        mov dword ptr [ebp+24h],eax
    L_00431f17:
        jmp short L_00431f23
    L_00431f19:
        xor eax,eax
    L_00431f1b:
        mov dword ptr [ebp+24h],eax
    L_00431f1e:
        jmp short L_00431f23
    L_00431f20:
        mov dword ptr [ebp+24h],edi
    L_00431f23:
        mov dword ptr [ebp+104h],5
    L_00431f2d:
        mov eax,dword ptr [ebp+104h]
    L_00431f33:
        cmp eax,edi
    L_00431f35:
        je short L_00431f4e
    L_00431f37:
        cmp eax,esi
    L_00431f39:
        jg short L_00431f44
    L_00431f3b:
        dec eax
    L_00431f3c:
        mov dword ptr [ebp+0FCh],eax
    L_00431f42:
        jmp short L_00431f54
    L_00431f44:
        mov eax,esi
    L_00431f46:
        mov dword ptr [ebp+0FCh],eax
    L_00431f4c:
        jmp short L_00431f54
    L_00431f4e:
        mov dword ptr [ebp+0FCh],esi
    L_00431f54:
        mov edx,dword ptr [ebp+0FCh]
    L_00431f5a:
        mov dword ptr [ebp+1CCh],esi
    L_00431f60:
        call asm_CountPatternMatches_004088c0
    L_00431f65:
        mov ecx,eax
    L_00431f67:
        add ecx,9
    L_00431f6a:
        mov eax,66666667h
    L_00431f6f:
        imul ecx
    L_00431f71:
        sar edx,2
    L_00431f74:
        mov eax,edx
    L_00431f76:
        shr eax,1Fh
    L_00431f79:
        lea ecx,[edx+eax+1]
    L_00431f7d:
        mov eax,ecx
    L_00431f7f:
        cmp eax,edi
    L_00431f81:
        mov dword ptr [ebp+1DCh],ecx
    L_00431f87:
        je short L_00431f9e
    L_00431f89:
        jg short L_00431f94
    L_00431f8b:
        dec eax
    L_00431f8c:
        mov dword ptr [ebp+1D4h],eax
    L_00431f92:
        jmp short L_00431fa4
    L_00431f94:
        xor eax,eax
    L_00431f96:
        mov dword ptr [ebp+1D4h],eax
    L_00431f9c:
        jmp short L_00431fa4
    L_00431f9e:
        mov dword ptr [ebp+1D4h],edi
    L_00431fa4:
        mov dword ptr [ebp+2A4h],esi
    L_00431faa:
        mov edx,dword ptr [ebp+43Ch]
    L_00431fb0:
        push edx
    L_00431fb1:
        mov edx,dword ptr [data_00491c10]
    L_00431fb7:
        call asm_AnimationManager_Find_004491c0
    L_00431fbc:
        test eax,eax
    L_00431fbe:
        jne short L_00431fec
    L_00431fc0:
        push ebp
    L_00431fc1:
        mov edi,5Eh
    L_00431fc6:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00431fcb:
        mov eax,dword ptr [data_004776e0]
    L_00431fd0:
        mov eax,dword ptr [eax+8994h]
    L_00431fd6:
        push 0Fh
    L_00431fd8:
        push 8
    L_00431fda:
        push eax
    L_00431fdb:
        lea edi,[esp+24h]
    L_00431fdf:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00431fe4:
        mov ecx,dword ptr [eax]
    L_00431fe6:
        mov dword ptr [ebp+5D0h],ecx
    L_00431fec:
        push ebp
    L_00431fed:
        mov edi,66h
    L_00431ff2:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00431ff7:
        mov ecx,esi
    L_00431ff9:
        mov eax,ebp
    L_00431ffb:
        call asm_GameState_SetTimerTarget_0042c620
    L_00432000:
        mov ecx,dword ptr [ebp+24h]
    L_00432003:
        mov eax,55555556h
    L_00432008:
        imul ecx
    L_0043200a:
        mov eax,edx
    L_0043200c:
        shr eax,1Fh
    L_0043200f:
        lea edi,[edx+eax+98h]
    L_00432016:
        push ebp
    L_00432017:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0043201c:
        mov edi,dword ptr [ebp+24h]
    L_0043201f:
        add edi,9Ah
    L_00432025:
        push ebp
    L_00432026:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0043202b:
        mov edi,dword ptr [ebp+0FCh]
    L_00432031:
        add edi,0A0h
    L_00432037:
        push ebp
    L_00432038:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0043203d:
        push ebp
    L_0043203e:
        mov edi,0A8h
    L_00432043:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432048:
        push ebp
    L_00432049:
        mov edi,0A9h
    L_0043204e:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432053:
        push ebp
    L_00432054:
        mov edi,0AAh
    L_00432059:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0043205e:
        push ebp
    L_0043205f:
        mov edi,0ABh
    L_00432064:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432069:
        push ebp
    L_0043206a:
        mov edi,0A5h
    L_0043206f:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432074:
        push ebp
    L_00432075:
        mov edi,0A6h
    L_0043207a:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0043207f:
        push ebp
    L_00432080:
        mov edi,0A7h
    L_00432085:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0043208a:
        push ebp
    L_0043208b:
        mov edi,0ACh
    L_00432090:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432095:
        cmp dword ptr [ebp+2B4h],ebx
    L_0043209b:
        jle asm_target_00432670
    L_004320a1:
        mov ecx,2
    L_004320a6:
        mov eax,ebp
    L_004320a8:
        call asm_GameState_SetTimerTarget_0042c620
    L_004320ad:
        pop edi
    L_004320ae:
        pop ebx
    L_004320af:
        pop esi
    L_004320b0:
        mov eax,1
    L_004320b5:
        pop ebp
    L_004320b6:
        pop ecx
    L_004320b7:
        ret 4
    L_004320ba:
        mov ecx,dword ptr [ebp+24h]
    L_004320bd:
        mov dword ptr [ebp+28h],ecx
    L_004320c0:
        mov edx,dword ptr [ebp+0FCh]
    L_004320c6:
        lea ebx,[ebp+0FCh]
    L_004320cc:
        mov dword ptr [ebx+4],edx
    L_004320cf:
        mov eax,dword ptr [ebp+1D4h]
    L_004320d5:
        mov dword ptr [ebp+1D8h],eax
    L_004320db:
        mov cl,byte ptr [data_00474e36]
    L_004320e1:
        mov al,10h
    L_004320e3:
        test cl,al
    L_004320e5:
        jne short L_004320ef
    L_004320e7:
        test byte ptr [data_00474e34],al
    L_004320ed:
        je short L_0043210f
    L_004320ef:
        push 0FFFFFFFFh
    L_004320f1:
        mov eax,ebx
    L_004320f3:
        call asm_MenuCursor_Advance_0044bea0
    L_004320f8:
        mov ecx,dword ptr [ebp+56Ch]
    L_004320fe:
        mov edx,dword ptr [data_00491c10]
    L_00432104:
        push ecx
    L_00432105:
        mov edi,2
    L_0043210a:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0043210f:
        mov cl,byte ptr [data_00474e36]
    L_00432115:
        mov al,20h
    L_00432117:
        test cl,al
    L_00432119:
        jne short L_00432123
    L_0043211b:
        test byte ptr [data_00474e34],al
    L_00432121:
        je short L_00432142
    L_00432123:
        push esi
    L_00432124:
        mov eax,ebx
    L_00432126:
        call asm_MenuCursor_Advance_0044bea0
    L_0043212b:
        mov edx,dword ptr [ebp+570h]
    L_00432131:
        push edx
    L_00432132:
        mov edx,dword ptr [data_00491c10]
    L_00432138:
        mov edi,2
    L_0043213d:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_00432142:
        mov eax,dword ptr [ebx+4]
    L_00432145:
        cmp eax,dword ptr [ebx]
    L_00432147:
        je asm_target_004321e9
    L_0043214d:
        push 0
    L_0043214f:
        mov edi,0Ch
    L_00432154:
        mov ecx,492590h
    L_00432159:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043215e:
        mov esi,dword ptr [ebp+100h]
    L_00432164:
        add esi,0A0h
    L_0043216a:
        mov edi,ebp
    L_0043216c:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00432171:
        mov edi,dword ptr [ebx]
    L_00432173:
        add edi,0A0h
    L_00432179:
        push ebp
    L_0043217a:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0043217f:
        mov eax,dword ptr [ebp+1D4h]
    L_00432185:
        test eax,eax
    L_00432187:
        jle short L_004321bf
    L_00432189:
        mov eax,dword ptr [ebp+1DCh]
    L_0043218f:
        test eax,eax
    L_00432191:
        je short L_004321ae
    L_00432193:
        cmp eax,1
    L_00432196:
        jg short L_004321a1
    L_00432198:
        dec eax
    L_00432199:
        mov dword ptr [ebp+1D4h],eax
    L_0043219f:
        jmp short L_004321b8
    L_004321a1:
        mov eax,1
    L_004321a6:
        mov dword ptr [ebp+1D4h],eax
    L_004321ac:
        jmp short L_004321b8
    L_004321ae:
        mov dword ptr [ebp+1D4h],1
    L_004321b8:
        mov ecx,ebp
    L_004321ba:
        call asm_FUN_00432690_00432690
    L_004321bf:
        mov edx,dword ptr [ebx]
    L_004321c1:
        call asm_CountPatternMatches_004088c0
    L_004321c6:
        mov ecx,eax
    L_004321c8:
        add ecx,9
    L_004321cb:
        mov eax,66666667h
    L_004321d0:
        imul ecx
    L_004321d2:
        sar edx,2
    L_004321d5:
        mov ecx,edx
    L_004321d7:
        shr ecx,1Fh
    L_004321da:
        lea edx,[edx+ecx+1]
    L_004321de:
        mov dword ptr [ebp+1DCh],edx
    L_004321e4:
        mov esi,1
    L_004321e9:
        test byte ptr [data_00474e36],40h
    L_004321f0:
        jne short L_004321fb
    L_004321f2:
        test byte ptr [data_00474e34],40h
    L_004321f9:
        je short L_0043221c
    L_004321fb:
        push 0FFFFFFFFh
    L_004321fd:
        lea eax,[ebp+24h]
    L_00432200:
        call asm_MenuCursor_Advance_0044bea0
    L_00432205:
        mov eax,dword ptr [ebp+564h]
    L_0043220b:
        mov edx,dword ptr [data_00491c10]
    L_00432211:
        push eax
    L_00432212:
        mov edi,2
    L_00432217:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0043221c:
        mov al,byte ptr [data_00474e36]
    L_00432221:
        test al,al
    L_00432223:
        js short L_0043222e
    L_00432225:
        mov al,byte ptr [data_00474e34]
    L_0043222a:
        test al,al
    L_0043222c:
        jns short L_0043224e
    L_0043222e:
        push esi
    L_0043222f:
        lea eax,[ebp+24h]
    L_00432232:
        call asm_MenuCursor_Advance_0044bea0
    L_00432237:
        mov ecx,dword ptr [ebp+568h]
    L_0043223d:
        mov edx,dword ptr [data_00491c10]
    L_00432243:
        push ecx
    L_00432244:
        mov edi,2
    L_00432249:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0043224e:
        mov edx,dword ptr [ebp+28h]
    L_00432251:
        cmp edx,dword ptr [ebp+24h]
    L_00432254:
        je asm_target_004322ea
    L_0043225a:
        push 0
    L_0043225c:
        mov edi,0Ch
    L_00432261:
        mov ecx,492590h
    L_00432266:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043226b:
        mov ecx,dword ptr [ebp+28h]
    L_0043226e:
        mov eax,55555556h
    L_00432273:
        imul ecx
    L_00432275:
        mov ecx,edx
    L_00432277:
        shr ecx,1Fh
    L_0043227a:
        add ecx,edx
    L_0043227c:
        mov edx,dword ptr [ebp+24h]
    L_0043227f:
        mov eax,55555556h
    L_00432284:
        imul edx
    L_00432286:
        mov eax,edx
    L_00432288:
        shr eax,1Fh
    L_0043228b:
        add eax,edx
    L_0043228d:
        cmp eax,ecx
    L_0043228f:
        je short L_004322ba
    L_00432291:
        lea esi,[ecx+98h]
    L_00432297:
        mov edi,ebp
    L_00432299:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043229e:
        mov ecx,dword ptr [ebp+24h]
    L_004322a1:
        mov eax,55555556h
    L_004322a6:
        imul ecx
    L_004322a8:
        mov ecx,edx
    L_004322aa:
        shr ecx,1Fh
    L_004322ad:
        lea edi,[edx+ecx+98h]
    L_004322b4:
        push ebp
    L_004322b5:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_004322ba:
        mov esi,dword ptr [ebp+28h]
    L_004322bd:
        add esi,9Ah
    L_004322c3:
        mov edi,ebp
    L_004322c5:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004322ca:
        mov edi,dword ptr [ebp+24h]
    L_004322cd:
        add edi,9Ah
    L_004322d3:
        push ebp
    L_004322d4:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_004322d9:
        mov eax,dword ptr [ebp+1D4h]
    L_004322df:
        test eax,eax
    L_004322e1:
        jle short L_004322ea
    L_004322e3:
        mov ecx,ebp
    L_004322e5:
        call asm_FUN_00432690_00432690
    L_004322ea:
        test dword ptr [data_00474e36],1001h
    L_004322f4:
        je asm_target_0043237f
    L_004322fa:
        mov eax,dword ptr [ebp+1D4h]
    L_00432300:
        test eax,eax
    L_00432302:
        jne short L_00432339
    L_00432304:
        xor esi,esi
    L_00432306:
        lea ebx,[ebp+5D4h]
    L_0043230c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00432310:
        mov edx,dword ptr [data_004776e0]
    L_00432316:
        mov eax,dword ptr [edx+899Ch]
    L_0043231c:
        push 0Fh
    L_0043231e:
        lea ecx,[esi+17h]
    L_00432321:
        push ecx
    L_00432322:
        push eax
    L_00432323:
        lea edi,[esp+1Ch]
    L_00432327:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0043232c:
        mov edx,dword ptr [eax]
    L_0043232e:
        mov dword ptr [ebx],edx
    L_00432330:
        inc esi
    L_00432331:
        add ebx,4
    L_00432334:
        cmp esi,0Ah
    L_00432337:
        jl short L_00432310
    L_00432339:
        lea esi,[ebp+1D4h]
    L_0043233f:
        push 1
    L_00432341:
        mov eax,esi
    L_00432343:
        call asm_MenuCursor_Advance_0044bea0
    L_00432348:
        cmp dword ptr [esi],0
    L_0043234b:
        jne short L_00432367
    L_0043234d:
        lea esi,[ebp+5D4h]
    L_00432353:
        mov edi,0Ah
    L_00432358:
        mov eax,esi
    L_0043235a:
        call asm_FUN_00409e50_00409e50
    L_0043235f:
        add esi,4
    L_00432362:
        dec edi
    L_00432363:
        jne short L_00432358
    L_00432365:
        jmp short L_0043236e
    L_00432367:
        mov ecx,ebp
    L_00432369:
        call asm_FUN_00432690_00432690
    L_0043236e:
        push 0
    L_00432370:
        mov edi,0Ah
    L_00432375:
        mov ecx,492590h
    L_0043237a:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043237f:
        cmp dword ptr [ebp+0FCh],4
    L_00432386:
        jne asm_target_004324d4
    L_0043238c:
        cmp dword ptr [ebp+24h],2
    L_00432390:
        jne asm_target_004324d4
    L_00432396:
        mov eax,dword ptr [data_00474e36]
    L_0043239b:
        xor ebx,ebx
    L_0043239d:
        test eax,160Bh
    L_004323a2:
        je short L_004323b0
    L_004323a4:
        mov dword ptr [data_004979a4],ebx
    L_004323aa:
        mov dword ptr [data_004979a0],ebx
    L_004323b0:
        mov ecx,40h
    L_004323b5:
        mov esi,497E90h
    L_004323ba:
        mov edi,497D90h
    L_004323bf:
        mov edx,497E90h
    L_004323c4:
        rep movsd
    L_004323c6:
        call asm_Input_UpdateKeyboardState_0044b010
    L_004323cb:
        test eax,eax
    L_004323cd:
        je asm_target_004324b6
    L_004323d3:
        xor eax,eax
    L_004323d5:
        TH10_REL8(0xeb, 0x004323d5, VA_asm_FUN_00431ee0_part_004323e0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_004323e0:
        mov cl,byte ptr [eax+497E90h]
    L_004323e6:
        mov dl,byte ptr [eax+497D90h]
    L_004323ec:
        xor dl,cl
    L_004323ee:
        and dl,cl
    L_004323f0:
        mov cl,byte ptr [eax+497E91h]
    L_004323f6:
        mov byte ptr [eax+4979A8h],dl
    L_004323fc:
        mov dl,byte ptr [eax+497D91h]
    L_00432402:
        xor dl,cl
    L_00432404:
        and dl,cl
    L_00432406:
        mov cl,byte ptr [eax+497E92h]
    L_0043240c:
        mov byte ptr [eax+4979A9h],dl
    L_00432412:
        mov dl,byte ptr [eax+497D92h]
    L_00432418:
        xor dl,cl
    L_0043241a:
        and dl,cl
    L_0043241c:
        mov cl,byte ptr [eax+497E93h]
    L_00432422:
        mov byte ptr [eax+4979AAh],dl
    L_00432428:
        mov dl,byte ptr [eax+497D93h]
    L_0043242e:
        xor dl,cl
    L_00432430:
        and dl,cl
    L_00432432:
        mov byte ptr [eax+4979ABh],dl
    L_00432438:
        add eax,4
    L_0043243b:
        cmp eax,100h
    L_00432440:
        jl short L_004323e0
    L_00432442:
        mov eax,dword ptr [data_004979a4]
    L_00432447:
        cmp eax,16h
    L_0043244a:
        jb short L_00432468
    L_0043244c:
        mov eax,dword ptr [data_0047783c]
    L_00432451:
        call asm_GameProgress_UnlockAllStages_0042c8c0
    L_00432456:
        push ebx
    L_00432457:
        mov edi,2Ch
    L_0043245c:
        mov ecx,492590h
    L_00432461:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00432466:
        TH10_REL8(0xeb, 0x00432466, VA_asm_target_004324b0)
    L_00432468:
        mov ecx,dword ptr [eax*4+46EF10h]
    L_0043246f:
        mov dl,byte ptr [ecx+4979A8h]
    L_00432475:
        test dl,dl
    L_00432477:
        jns short L_00432487
    L_00432479:
        inc eax
    L_0043247a:
        mov dword ptr [data_004979a4],eax
    L_0043247f:
        mov dword ptr [data_004979a0],ebx
    L_00432485:
        TH10_REL8(0xeb, 0x00432485, VA_asm_target_004324b6)
    L_00432487:
        xor cl,cl
    L_00432489:
        xor eax,eax
    L_0043248b:
        TH10_REL8(0xeb, 0x0043248b, VA_asm_FUN_00431ee0_part_00432490)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00432490:
        mov dl,byte ptr [eax+4979A8h]
    L_00432496:
        or dl,byte ptr [eax+4979AAh]
    L_0043249c:
        add eax,3
    L_0043249f:
        or dl,byte ptr [eax+4979A6h]
    L_004324a5:
        or cl,dl
    L_004324a7:
        cmp eax,39h
    L_004324aa:
        jl short L_00432490
    L_004324ac:
        test cl,cl
    L_004324ae:
        jns short L_004324b6
    L_004324b0:
        mov dword ptr [data_004979a4],ebx
    L_004324b6:
        mov eax,dword ptr [data_004979a0]
    L_004324bb:
        inc eax
    L_004324bc:
        cmp eax,12Ch
    L_004324c1:
        mov dword ptr [data_004979a0],eax
    L_004324c6:
        jle short L_004324d4
    L_004324c8:
        mov dword ptr [data_004979a4],ebx
    L_004324ce:
        mov dword ptr [data_004979a0],ebx
    L_004324d4:
        test byte ptr [data_00474e36],0Ah
    L_004324db:
        je asm_target_00432670
    L_004324e1:
        mov ecx,3
    L_004324e6:
        mov eax,ebp
    L_004324e8:
        call asm_GameState_SetTimerTarget_0042c620
    L_004324ed:
        push 0
    L_004324ef:
        mov edi,0Bh
    L_004324f4:
        mov ecx,492590h
    L_004324f9:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004324fe:
        mov esi,dword ptr [ebp+0FCh]
    L_00432504:
        add esi,0A0h
    L_0043250a:
        mov edi,ebp
    L_0043250c:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00432511:
        mov esi,dword ptr [ebp+24h]
    L_00432514:
        add esi,9Ah
    L_0043251a:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043251f:
        mov ecx,dword ptr [ebp+24h]
    L_00432522:
        mov eax,55555556h
    L_00432527:
        imul ecx
    L_00432529:
        mov eax,edx
    L_0043252b:
        shr eax,1Fh
    L_0043252e:
        lea esi,[edx+eax+98h]
    L_00432535:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043253a:
        mov esi,0A8h
    L_0043253f:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00432544:
        mov esi,0A9h
    L_00432549:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043254e:
        mov esi,0AAh
    L_00432553:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00432558:
        mov esi,0ABh
    L_0043255d:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00432562:
        mov esi,0A5h
    L_00432567:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043256c:
        mov esi,0A6h
    L_00432571:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00432576:
        mov esi,0A7h
    L_0043257b:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00432580:
        mov esi,0ACh
    L_00432585:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043258a:
        mov esi,dword ptr [data_00491c10]
    L_00432590:
        add ebp,5D4h
    L_00432596:
        mov edx,0Ah
    L_0043259b:
        mov edi,1
    L_004325a0:
        mov ecx,dword ptr [ebp]
    L_004325a3:
        test ecx,ecx
    L_004325a5:
        je short L_00432602
    L_004325a7:
        mov eax,dword ptr [esi+72DAD4h]
    L_004325ad:
        test eax,eax
    L_004325af:
        je short L_004325be
    L_004325b1:
        mov ebx,dword ptr [eax]
    L_004325b3:
        cmp dword ptr [ebx],ecx
    L_004325b5:
        je short L_004325d7
    L_004325b7:
        mov eax,dword ptr [eax+4]
    L_004325ba:
        test eax,eax
    L_004325bc:
        jne short L_004325b1
    L_004325be:
        mov eax,dword ptr [esi+72DADCh]
    L_004325c4:
        test eax,eax
    L_004325c6:
        je short L_00432602
    L_004325c8:
        mov ebx,dword ptr [eax]
    L_004325ca:
        cmp dword ptr [ebx],ecx
    L_004325cc:
        je short L_004325d7
    L_004325ce:
        mov eax,dword ptr [eax+4]
    L_004325d1:
        test eax,eax
    L_004325d3:
        jne short L_004325c8
    L_004325d5:
        jmp short L_00432602
    L_004325d7:
        mov eax,dword ptr [eax]
    L_004325d9:
        test eax,eax
    L_004325db:
        je short L_00432602
    L_004325dd:
        mov ecx,dword ptr [eax+18h]
    L_004325e0:
        test ecx,ecx
    L_004325e2:
        mov word ptr [eax+304h],di
    L_004325e9:
        jne short L_00432602
    L_004325eb:
        mov eax,dword ptr [eax+14h]
    L_004325ee:
        test eax,eax
    L_004325f0:
        je short L_00432602
    L_004325f2:
        mov ecx,dword ptr [eax]
    L_004325f4:
        mov word ptr [ecx+304h],di
    L_004325fb:
        mov eax,dword ptr [eax+4]
    L_004325fe:
        test eax,eax
    L_00432600:
        jne short L_004325f2
    L_00432602:
        add ebp,4
    L_00432605:
        dec edx
    L_00432606:
        jne short L_004325a0
    L_00432608:
        pop edi
    L_00432609:
        pop ebx
    L_0043260a:
        pop esi
    L_0043260b:
        mov eax,1
    L_00432610:
        pop ebp
    L_00432611:
        pop ecx
    L_00432612:
        ret 4
    L_00432615:
        cmp dword ptr [ebp+2B4h],6
    L_0043261c:
        jl short L_00432670
    L_0043261e:
        mov esi,66h
    L_00432623:
        mov edi,ebp
    L_00432625:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043262a:
        mov esi,8
    L_0043262f:
        mov ecx,5Ah
    L_00432634:
        mov eax,ebp
    L_00432636:
        call asm_FUN_0042c770_0042c770
    L_0043263b:
        mov ecx,5Bh
    L_00432640:
        mov eax,ebp
    L_00432642:
        call asm_FUN_0042c770_0042c770
    L_00432647:
        mov esi,5Eh
    L_0043264c:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00432651:
        lea eax,[ebp+5D0h]
    L_00432657:
        call asm_FUN_00409e50_00409e50
    L_0043265c:
        mov ecx,2
    L_00432661:
        mov eax,ebp
    L_00432663:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00432668:
        lea eax,[ebp+24h]
    L_0043266b:
        call asm_Score_InputHistoryStep_0044be70
    L_00432670:
        pop edi
    L_00432671:
        pop ebx
    L_00432672:
        pop esi
    L_00432673:
        mov eax,1
    L_00432678:
        pop ebp
    L_00432679:
        pop ecx
    L_0043267a:
        ret 4
        _emit 0x8d
        _emit 0x49
        _emit 0x00
        _emit 0x06
        _emit 0x1f
        _emit 0x43
        _emit 0x00
        _emit 0x95
        _emit 0x20
        _emit 0x43
        _emit 0x00
        _emit 0xba
        _emit 0x20
        _emit 0x43
        _emit 0x00
        _emit 0x15
        _emit 0x26
        _emit 0x43
        _emit 0x00
    }
}

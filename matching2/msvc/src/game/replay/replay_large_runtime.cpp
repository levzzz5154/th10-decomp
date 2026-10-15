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
        mov eax,dword ptr [g_fps]
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

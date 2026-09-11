#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_Reset_00434c20() {
    __asm {
    L_00434c20:
        push esi
    L_00434c21:
        mov esi,ecx
    L_00434c23:
        call asm_DatArchive_Close_00434d10
    L_00434c28:
        pop esi
    L_00434c29:
        ret
    }
}

// 0x00434C30..0x00434C9B: ?DatArchive_Open@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_Open_00434c30() {
    __asm {
    L_00434c30:
        push esi
    L_00434c31:
        push edi
    L_00434c32:
        mov esi,ecx
    L_00434c34:
        mov edi,eax
    L_00434c36:
        call asm_DatArchive_Close_00434d10
    L_00434c3b:
        push 0Ch
    L_00434c3d:
        call asm_operator_new_00452493
    L_00434c42:
        add esp,4
    L_00434c45:
        test eax,eax
    L_00434c47:
        je short L_00434c5f
    L_00434c49:
        mov dword ptr [eax],46F230h
    L_00434c4f:
        mov dword ptr [eax+4],0FFFFFFFFh
    L_00434c56:
        mov dword ptr [eax+8],0
    L_00434c5d:
        jmp short L_00434c61
    L_00434c5f:
        xor eax,eax
    L_00434c61:
        test eax,eax
    L_00434c63:
        mov dword ptr [esi+0Ch],eax
    L_00434c66:
        je short L_00434c97
    L_00434c68:
        push edi
    L_00434c69:
        call asm_DatArchive_LoadIndex_00434f70
    L_00434c6e:
        test al,al
    L_00434c70:
        je short L_00434c92
    L_00434c72:
        call asm_LegacyString_Duplicate_00435220
    L_00434c77:
        test eax,eax
    L_00434c79:
        mov dword ptr [esi+8],eax
    L_00434c7c:
        je short L_00434c92
    L_00434c7e:
        mov ecx,dword ptr [esi+0Ch]
    L_00434c81:
        mov esi,dword ptr [data_00474908]
    L_00434c87:
        mov edx,dword ptr [ecx]
    L_00434c89:
        push esi
    L_00434c8a:
        push eax
    L_00434c8b:
        call dword ptr [edx]
    L_00434c8d:
        pop edi
    L_00434c8e:
        mov al,1
    L_00434c90:
        pop esi
    L_00434c91:
        ret
    L_00434c92:
        call asm_DatArchive_Close_00434d10
    L_00434c97:
        pop edi
    L_00434c98:
        xor al,al
    L_00434c9a:
        pop esi
    L_00434c9b:
        ret
    }
}

// 0x00434D10..0x00434D65: ?DatArchive_Close@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_Close_00434d10() {
    __asm {
    L_00434d10:
        mov eax,dword ptr [esi+8]
    L_00434d13:
        push edi
    L_00434d14:
        xor edi,edi
    L_00434d16:
        cmp eax,edi
    L_00434d18:
        je short L_00434d26
    L_00434d1a:
        push eax
    L_00434d1b:
        call asm_free_00452422
    L_00434d20:
        add esp,4
    L_00434d23:
        mov dword ptr [esi+8],edi
    L_00434d26:
        mov eax,dword ptr [esi]
    L_00434d28:
        cmp eax,edi
    L_00434d2a:
        mov dword ptr [esi+8],edi
    L_00434d2d:
        je short L_00434d4e
    L_00434d2f:
        mov ecx,dword ptr [eax-4]
    L_00434d32:
        push ebx
    L_00434d33:
        lea ebx,[eax-4]
    L_00434d36:
        push 435250h
    L_00434d3b:
        push ecx
    L_00434d3c:
        push 10h
    L_00434d3e:
        push eax
    L_00434d3f:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00434d44:
        push ebx
    L_00434d45:
        call asm_free_004524a1
    L_00434d4a:
        add esp,4
    L_00434d4d:
        pop ebx
    L_00434d4e:
        mov ecx,dword ptr [esi+0Ch]
    L_00434d51:
        cmp ecx,edi
    L_00434d53:
        mov dword ptr [esi],edi
    L_00434d55:
        je short L_00434d5e
    L_00434d57:
        mov edx,dword ptr [ecx]
    L_00434d59:
        push 1
    L_00434d5b:
        call dword ptr [edx+1Ch]
    L_00434d5e:
        mov dword ptr [esi+0Ch],edi
    L_00434d61:
        mov dword ptr [esi+4],edi
    L_00434d64:
        pop edi
    L_00434d65:
        ret
    }
}

// 0x00434DD0..0x00434E5C: ?DatArchive_Read@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_Read_00434dd0() {
    __asm {
    L_00434dd0:
        push ebp
    L_00434dd1:
        mov ebp,dword ptr [esp+8]
    L_00434dd5:
        mov eax,dword ptr [ebp+0Ch]
    L_00434dd8:
        test eax,eax
    L_00434dda:
        jne short L_00434de2
    L_00434ddc:
        xor eax,eax
    L_00434dde:
        pop ebp
    L_00434ddf:
        ret 8
    L_00434de2:
        push ebx
    L_00434de3:
        push esi
    L_00434de4:
        push edi
    L_00434de5:
        mov ebx,ecx
    L_00434de7:
        mov eax,ebp
    L_00434de9:
        call asm_DatArchive_FindEntry_00434f30
    L_00434dee:
        mov ebx,eax
    L_00434df0:
        test ebx,ebx
    L_00434df2:
        je short L_00434e4b
    L_00434df4:
        mov esi,dword ptr [ebx+14h]
    L_00434df7:
        mov edx,dword ptr [ebx+4]
    L_00434dfa:
        mov eax,dword ptr [ebx+8]
    L_00434dfd:
        sub esi,edx
    L_00434dff:
        cmp esi,eax
    L_00434e01:
        mov dword ptr [esp+14h],eax
    L_00434e05:
        jne short L_00434e0f
    L_00434e07:
        mov edi,dword ptr [esp+18h]
    L_00434e0b:
        test edi,edi
    L_00434e0d:
        jne short L_00434e1e
    L_00434e0f:
        push esi
    L_00434e10:
        call asm_malloc_00452706
    L_00434e15:
        mov edi,eax
    L_00434e17:
        add esp,4
    L_00434e1a:
        test edi,edi
    L_00434e1c:
        je short L_00434e4b
    L_00434e1e:
        mov ecx,dword ptr [ebp+0Ch]
    L_00434e21:
        mov edx,dword ptr [ebx+4]
    L_00434e24:
        mov eax,dword ptr [ecx]
    L_00434e26:
        push 0
    L_00434e28:
        push edx
    L_00434e29:
        call dword ptr [eax+18h]
    L_00434e2c:
        test al,al
    L_00434e2e:
        je short L_00434e3e
    L_00434e30:
        mov ecx,dword ptr [ebp+0Ch]
    L_00434e33:
        mov eax,dword ptr [ecx]
    L_00434e35:
        push esi
    L_00434e36:
        push edi
    L_00434e37:
        call dword ptr [eax+8]
    L_00434e3a:
        test eax,eax
    L_00434e3c:
        jne short L_00434e54
    L_00434e3e:
        test edi,edi
    L_00434e40:
        je short L_00434e4b
    L_00434e42:
        push edi
    L_00434e43:
        call asm_free_00452422
    L_00434e48:
        add esp,4
    L_00434e4b:
        pop edi
    L_00434e4c:
        pop esi
    L_00434e4d:
        pop ebx
    L_00434e4e:
        xor eax,eax
    L_00434e50:
        pop ebp
    L_00434e51:
        ret 8
    L_00434e54:
        mov ebx,dword ptr [ebx]
    L_00434e56:
        mov eax,ebx
    L_00434e58:
        lea edx,[eax+1]
    L_00434e5b:
        TH10_REL8(0xeb, 0x00434e5b, VA_asm_DatArchive_Read_part_00434e60)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00434e60:
        mov cl,byte ptr [eax]
    L_00434e62:
        inc eax
    L_00434e63:
        test cl,cl
    L_00434e65:
        jne short L_00434e60
    L_00434e67:
        sub eax,edx
    L_00434e69:
        mov edx,ebx
    L_00434e6b:
        je short L_00434e76
    L_00434e6d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00434e70:
        add cl,byte ptr [edx]
    L_00434e72:
        inc edx
    L_00434e73:
        dec eax
    L_00434e74:
        jne short L_00434e70
    L_00434e76:
        movzx eax,cl
    L_00434e79:
        and eax,80000007h
    L_00434e7e:
        jns short L_00434e85
    L_00434e80:
        dec eax
    L_00434e81:
        or eax,0FFFFFFF8h
    L_00434e84:
        inc eax
    L_00434e85:
        movzx eax,al
    L_00434e88:
        lea eax,[eax+eax*2]
    L_00434e8b:
        shl eax,2
    L_00434e8e:
        mov ecx,dword ptr [eax+474BE0h]
    L_00434e94:
        mov edx,dword ptr [eax+474BDCh]
    L_00434e9a:
        push ecx
    L_00434e9b:
        xor ecx,ecx
    L_00434e9d:
        mov cl,byte ptr [eax+474BD9h]
    L_00434ea3:
        mov al,byte ptr [eax+474BD8h]
    L_00434ea9:
        push edx
    L_00434eaa:
        push ecx
    L_00434eab:
        push esi
    L_00434eac:
        push edi
    L_00434ead:
        call asm_DecryptDatBuffer_0044b0d0
    L_00434eb2:
        mov eax,dword ptr [esp+14h]
    L_00434eb6:
        cmp esi,eax
    L_00434eb8:
        je short L_00434ecb
    L_00434eba:
        mov edx,dword ptr [esp+18h]
    L_00434ebe:
        push eax
    L_00434ebf:
        push edx
    L_00434ec0:
        push esi
    L_00434ec1:
        push edi
    L_00434ec2:
        call asm_DecompressDatLzss_00435dc0
    L_00434ec7:
        mov esi,eax
    L_00434ec9:
        jmp short L_00434ecd
    L_00434ecb:
        mov esi,edi
    L_00434ecd:
        cmp edi,dword ptr [esp+18h]
    L_00434ed1:
        je short L_00434ee0
    L_00434ed3:
        test edi,edi
    L_00434ed5:
        je short L_00434ee0
    L_00434ed7:
        push edi
    L_00434ed8:
        call asm_free_00452422
    L_00434edd:
        add esp,4
    L_00434ee0:
        pop edi
    L_00434ee1:
        mov eax,esi
    L_00434ee3:
        pop esi
    L_00434ee4:
        pop ebx
    L_00434ee5:
        pop ebp
    L_00434ee6:
        ret 8
    }
}

// 0x00434EF0..0x00434F22: ?DatArchive_FindSize@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_FindSize_00434ef0() {
    __asm {
    L_00434ef0:
        push esi
    L_00434ef1:
        push edi
    L_00434ef2:
        mov edi,dword ptr [eax]
    L_00434ef4:
        test edi,edi
    L_00434ef6:
        je short L_00434f18
    L_00434ef8:
        mov esi,dword ptr [eax+4]
    L_00434efb:
        test esi,esi
    L_00434efd:
        jle short L_00434f18
    L_00434eff:
        nop
    L_00434f00:
        mov eax,dword ptr [edi]
    L_00434f02:
        push eax
    L_00434f03:
        push ebx
    L_00434f04:
        call asm_stricmp_0046054e
    L_00434f09:
        add esp,8
    L_00434f0c:
        test eax,eax
    L_00434f0e:
        je short L_00434f1d
    L_00434f10:
        dec esi
    L_00434f11:
        add edi,10h
    L_00434f14:
        test esi,esi
    L_00434f16:
        jg short L_00434f00
    L_00434f18:
        pop edi
    L_00434f19:
        xor eax,eax
    L_00434f1b:
        pop esi
    L_00434f1c:
        ret
    L_00434f1d:
        mov eax,dword ptr [edi+8]
    L_00434f20:
        pop edi
    L_00434f21:
        pop esi
    L_00434f22:
        ret
    }
}

// 0x00434F30..0x00434F64: ?DatArchive_FindEntry@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_FindEntry_00434f30() {
    __asm {
    L_00434f30:
        push edi
    L_00434f31:
        mov edi,dword ptr [eax]
    L_00434f33:
        test edi,edi
    L_00434f35:
        jne short L_00434f3b
    L_00434f37:
        xor eax,eax
    L_00434f39:
        pop edi
    L_00434f3a:
        ret
    L_00434f3b:
        push esi
    L_00434f3c:
        mov esi,dword ptr [eax+4]
    L_00434f3f:
        test esi,esi
    L_00434f41:
        jle short L_00434f5b
    L_00434f43:
        mov eax,dword ptr [edi]
    L_00434f45:
        push eax
    L_00434f46:
        push ebx
    L_00434f47:
        call asm_stricmp_0046054e
    L_00434f4c:
        add esp,8
    L_00434f4f:
        test eax,eax
    L_00434f51:
        je short L_00434f60
    L_00434f53:
        dec esi
    L_00434f54:
        add edi,10h
    L_00434f57:
        test esi,esi
    L_00434f59:
        jg short L_00434f43
    L_00434f5b:
        pop esi
    L_00434f5c:
        xor eax,eax
    L_00434f5e:
        pop edi
    L_00434f5f:
        ret
    L_00434f60:
        pop esi
    L_00434f61:
        mov eax,edi
    L_00434f63:
        pop edi
    L_00434f64:
        ret
    }
}

// 0x00434F70..0x004350CD: ?DatArchive_LoadIndex@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_LoadIndex_00434f70() {
    __asm {
    L_00434f70:
        sub esp,14h
    L_00434f73:
        mov ecx,dword ptr [esi+0Ch]
    L_00434f76:
        test ecx,ecx
    L_00434f78:
        mov dword ptr [esp],0
    L_00434f7f:
        jne short L_00434f89
    L_00434f81:
        xor al,al
    L_00434f83:
        add esp,14h
    L_00434f86:
        ret 4
    L_00434f89:
        mov edx,dword ptr [data_00474908]
    L_00434f8f:
        mov eax,dword ptr [ecx]
    L_00434f91:
        push ebx
    L_00434f92:
        push ebp
    L_00434f93:
        push edi
    L_00434f94:
        push edx
    L_00434f95:
        mov edx,dword ptr [esp+28h]
    L_00434f99:
        push edx
    L_00434f9a:
        call dword ptr [eax]
    L_00434f9c:
        test al,al
    L_00434f9e:
        je asm_target_004350ae
    L_00434fa4:
        mov ecx,dword ptr [esi+0Ch]
    L_00434fa7:
        mov eax,dword ptr [ecx]
    L_00434fa9:
        push 10h
    L_00434fab:
        lea edx,[esp+14h]
    L_00434faf:
        push edx
    L_00434fb0:
        call dword ptr [eax+8]
    L_00434fb3:
        test eax,eax
    L_00434fb5:
        je asm_target_004350ae
    L_00434fbb:
        push 10h
    L_00434fbd:
        push 10h
    L_00434fbf:
        push 37h
    L_00434fc1:
        lea eax,[esp+1Ch]
    L_00434fc5:
        push 10h
    L_00434fc7:
        push eax
    L_00434fc8:
        mov al,1Bh
    L_00434fca:
        call asm_DecryptDatBuffer_0044b0d0
    L_00434fcf:
        cmp dword ptr [esp+10h],31414854h
    L_00434fd7:
        jne asm_target_004350ae
    L_00434fdd:
        mov ecx,dword ptr [esp+14h]
    L_00434fe1:
        mov eax,dword ptr [esp+18h]
    L_00434fe5:
        sub ecx,75BCD15h
    L_00434feb:
        mov dword ptr [esp+14h],ecx
    L_00434fef:
        mov ecx,dword ptr [esp+1Ch]
    L_00434ff3:
        add ecx,0F7E7F8ACh
    L_00434ff9:
        mov dword ptr [esi+4],ecx
    L_00434ffc:
        mov ecx,dword ptr [esi+0Ch]
    L_00434fff:
        sub eax,3ADE68B1h
    L_00435004:
        mov dword ptr [esp+18h],eax
    L_00435008:
        mov edx,dword ptr [ecx]
    L_0043500a:
        call dword ptr [edx+14h]
    L_0043500d:
        mov ebp,dword ptr [esp+18h]
    L_00435011:
        mov ecx,dword ptr [esi+0Ch]
    L_00435014:
        sub eax,ebp
    L_00435016:
        mov ebp,eax
    L_00435018:
        mov eax,dword ptr [ecx]
    L_0043501a:
        push 0
    L_0043501c:
        push ebp
    L_0043501d:
        call dword ptr [eax+18h]
    L_00435020:
        mov ebx,dword ptr [esp+18h]
    L_00435024:
        push ebx
    L_00435025:
        call asm_malloc_00452706
    L_0043502a:
        mov edi,eax
    L_0043502c:
        add esp,4
    L_0043502f:
        test edi,edi
    L_00435031:
        je short L_004350ae
    L_00435033:
        mov ecx,dword ptr [esi+0Ch]
    L_00435036:
        mov edx,dword ptr [ecx]
    L_00435038:
        push ebx
    L_00435039:
        push edi
    L_0043503a:
        call dword ptr [edx+8]
    L_0043503d:
        test eax,eax
    L_0043503f:
        je short L_00435094
    L_00435041:
        push ebx
    L_00435042:
        push 80h
    L_00435047:
        push 9Bh
    L_0043504c:
        push ebx
    L_0043504d:
        push edi
    L_0043504e:
        mov al,3Eh
    L_00435050:
        call asm_DecryptDatBuffer_0044b0d0
    L_00435055:
        mov eax,dword ptr [esp+14h]
    L_00435059:
        push eax
    L_0043505a:
        push 0
    L_0043505c:
        push ebx
    L_0043505d:
        push edi
    L_0043505e:
        call asm_DecompressDatLzss_00435dc0
    L_00435063:
        mov ebx,eax
    L_00435065:
        test ebx,ebx
    L_00435067:
        je short L_00435098
    L_00435069:
        mov ecx,dword ptr [esi+4]
    L_0043506c:
        push ebp
    L_0043506d:
        push ecx
    L_0043506e:
        push ebx
    L_0043506f:
        call asm_FUN_004350d0_004350d0
    L_00435074:
        test eax,eax
    L_00435076:
        mov dword ptr [esi],eax
    L_00435078:
        je short L_00435098
    L_0043507a:
        push edi
    L_0043507b:
        call asm_free_00452422
    L_00435080:
        push ebx
    L_00435081:
        call asm_free_00452422
    L_00435086:
        add esp,8
    L_00435089:
        pop edi
    L_0043508a:
        pop ebp
    L_0043508b:
        mov al,1
    L_0043508d:
        pop ebx
    L_0043508e:
        add esp,14h
    L_00435091:
        ret 4
    L_00435094:
        mov ebx,dword ptr [esp+0Ch]
    L_00435098:
        push edi
    L_00435099:
        call asm_free_00452422
    L_0043509e:
        add esp,4
    L_004350a1:
        test ebx,ebx
    L_004350a3:
        je short L_004350ae
    L_004350a5:
        push ebx
    L_004350a6:
        call asm_free_00452422
    L_004350ab:
        add esp,4
    L_004350ae:
        mov ecx,dword ptr [esi+0Ch]
    L_004350b1:
        test ecx,ecx
    L_004350b3:
        je short L_004350bc
    L_004350b5:
        mov edx,dword ptr [ecx]
    L_004350b7:
        push 1
    L_004350b9:
        call dword ptr [edx+1Ch]
    L_004350bc:
        pop edi
    L_004350bd:
        pop ebp
    L_004350be:
        mov dword ptr [esi+0Ch],0
    L_004350c5:
        xor al,al
    L_004350c7:
        pop ebx
    L_004350c8:
        add esp,14h
    L_004350cb:
        ret 4
    }
}

// 0x004350D0..0x00435216: FUN_004350d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004350d0_004350d0() {
    __asm {
    L_004350d0:
        push 0FFFFFFFFh
    L_004350d2:
        push 4653CBh
    L_004350d7:
        mov eax,dword ptr fs:[0]
    L_004350dd:
        push eax
    L_004350de:
        mov dword ptr fs:[0],esp
    L_004350e5:
        sub esp,8
    L_004350e8:
        push ebp
    L_004350e9:
        mov ebp,dword ptr [esp+20h]
    L_004350ed:
        push esi
    L_004350ee:
        lea esi,[ebp+1]
    L_004350f1:
        mov eax,esi
    L_004350f3:
        shl eax,4
    L_004350f6:
        add eax,4
    L_004350f9:
        push edi
    L_004350fa:
        push eax
    L_004350fb:
        call asm_operator_new_00452493
    L_00435100:
        add esp,4
    L_00435103:
        mov dword ptr [esp+10h],eax
    L_00435107:
        test eax,eax
    L_00435109:
        mov dword ptr [esp+1Ch],0
    L_00435111:
        je short L_00435133
    L_00435113:
        push 435250h
    L_00435118:
        push 4352C0h
    L_0043511d:
        push esi
    L_0043511e:
        lea edi,[eax+4]
    L_00435121:
        push 10h
    L_00435123:
        push edi
    L_00435124:
        mov dword ptr [eax],esi
    L_00435126:
        mov dword ptr [esp+20h],edi
    L_0043512a:
        call asm_eh_vector_constructor_iterator_0045252d
    L_0043512f:
        test edi,edi
    L_00435131:
        jne short L_00435149
    L_00435133:
        pop edi
    L_00435134:
        pop esi
    L_00435135:
        xor eax,eax
    L_00435137:
        pop ebp
    L_00435138:
        mov ecx,dword ptr [esp+8]
    L_0043513c:
        mov dword ptr fs:[0],ecx
    L_00435143:
        add esp,14h
    L_00435146:
        ret 0Ch
    L_00435149:
        test ebp,ebp
    L_0043514b:
        mov esi,dword ptr [esp+24h]
    L_0043514f:
        jle asm_target_004351ed
    L_00435155:
        mov ecx,dword ptr [esp+28h]
    L_00435159:
        lea ebp,[edi+8]
    L_0043515c:
        mov dword ptr [esp+24h],ecx
    L_00435160:
        mov eax,esi
    L_00435162:
        lea edx,[eax+1]
    L_00435165:
        mov cl,byte ptr [eax]
    L_00435167:
        inc eax
    L_00435168:
        test cl,cl
    L_0043516a:
        jne short L_00435165
    L_0043516c:
        sub eax,edx
    L_0043516e:
        inc eax
    L_0043516f:
        push eax
    L_00435170:
        call asm_malloc_00452706
    L_00435175:
        add esp,4
    L_00435178:
        test eax,eax
    L_0043517a:
        je short L_00435190
    L_0043517c:
        mov edi,eax
    L_0043517e:
        mov ecx,esi
    L_00435180:
        sub edi,esi
    L_00435182:
        mov dl,byte ptr [ecx]
    L_00435184:
        mov byte ptr [edi+ecx],dl
    L_00435187:
        inc ecx
    L_00435188:
        test dl,dl
    L_0043518a:
        jne short L_00435182
    L_0043518c:
        mov edi,dword ptr [esp+0Ch]
    L_00435190:
        mov dword ptr [ebp-8],eax
    L_00435193:
        mov eax,esi
    L_00435195:
        lea edx,[eax+1]
    L_00435198:
        mov cl,byte ptr [eax]
    L_0043519a:
        inc eax
    L_0043519b:
        test cl,cl
    L_0043519d:
        jne short L_00435198
    L_0043519f:
        sub eax,edx
    L_004351a1:
        inc eax
    L_004351a2:
        mov ecx,eax
    L_004351a4:
        and ecx,80000003h
    L_004351aa:
        jns short L_004351b1
    L_004351ac:
        dec ecx
    L_004351ad:
        or ecx,0FFFFFFFCh
    L_004351b0:
        inc ecx
    L_004351b1:
        je short L_004351bc
    L_004351b3:
        mov edx,4
    L_004351b8:
        sub edx,ecx
    L_004351ba:
        add eax,edx
    L_004351bc:
        add esi,eax
    L_004351be:
        mov eax,dword ptr [esi]
    L_004351c0:
        mov dword ptr [ebp-4],eax
    L_004351c3:
        mov ecx,dword ptr [esi+4]
    L_004351c6:
        mov eax,dword ptr [esp+24h]
    L_004351ca:
        add esi,4
    L_004351cd:
        add esi,4
    L_004351d0:
        mov dword ptr [ebp],ecx
    L_004351d3:
        mov edx,dword ptr [esi]
    L_004351d5:
        mov dword ptr [ebp+4],edx
    L_004351d8:
        add esi,4
    L_004351db:
        add ebp,10h
    L_004351de:
        dec eax
    L_004351df:
        mov dword ptr [esp+24h],eax
    L_004351e3:
        jne asm_target_00435160
    L_004351e9:
        mov ebp,dword ptr [esp+28h]
    L_004351ed:
        mov ecx,dword ptr [esp+2Ch]
    L_004351f1:
        shl ebp,4
    L_004351f4:
        lea eax,[edi+ebp]
    L_004351f7:
        mov dword ptr [eax+4],ecx
    L_004351fa:
        mov ecx,dword ptr [esp+14h]
    L_004351fe:
        mov dword ptr [eax+8],0
    L_00435205:
        mov eax,edi
    L_00435207:
        pop edi
    L_00435208:
        pop esi
    L_00435209:
        pop ebp
    L_0043520a:
        mov dword ptr fs:[0],ecx
    L_00435211:
        add esp,14h
    L_00435214:
        ret 0Ch
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453CC5..0x00453FDC: ___sbh_free_block
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sbh_free_block_00453cc5() {
    __asm {
    L_00453cc5:
        push ebp
    L_00453cc6:
        mov ebp,esp
    L_00453cc8:
        sub esp,10h
    L_00453ccb:
        mov ecx,dword ptr [ebp+8]
    L_00453cce:
        mov eax,dword ptr [ecx+10h]
    L_00453cd1:
        push esi
    L_00453cd2:
        mov esi,dword ptr [ebp+0Ch]
    L_00453cd5:
        push edi
    L_00453cd6:
        mov edi,esi
    L_00453cd8:
        sub edi,dword ptr [ecx+0Ch]
    L_00453cdb:
        add esi,0FFFFFFFCh
    L_00453cde:
        shr edi,0Fh
    L_00453ce1:
        mov ecx,edi
    L_00453ce3:
        imul ecx,204h
    L_00453ce9:
        lea ecx,[ecx+eax+144h]
    L_00453cf0:
        mov dword ptr [ebp-10h],ecx
    L_00453cf3:
        mov ecx,dword ptr [esi]
    L_00453cf5:
        dec ecx
    L_00453cf6:
        test cl,1
    L_00453cf9:
        mov dword ptr [ebp-4],ecx
    L_00453cfc:
        jne asm_target_00453fd9
    L_00453d02:
        push ebx
    L_00453d03:
        lea ebx,[ecx+esi]
    L_00453d06:
        mov edx,dword ptr [ebx]
    L_00453d08:
        mov dword ptr [ebp-0Ch],edx
    L_00453d0b:
        mov edx,dword ptr [esi-4]
    L_00453d0e:
        mov dword ptr [ebp-8],edx
    L_00453d11:
        mov edx,dword ptr [ebp-0Ch]
    L_00453d14:
        test dl,1
    L_00453d17:
        mov dword ptr [ebp+0Ch],ebx
    L_00453d1a:
        jne short L_00453d90
    L_00453d1c:
        sar edx,4
    L_00453d1f:
        dec edx
    L_00453d20:
        cmp edx,3Fh
    L_00453d23:
        jbe short L_00453d28
    L_00453d25:
        push 3Fh
    L_00453d27:
        pop edx
    L_00453d28:
        mov ecx,dword ptr [ebx+4]
    L_00453d2b:
        cmp ecx,dword ptr [ebx+8]
    L_00453d2e:
        jne short L_00453d72
    L_00453d30:
        cmp edx,20h
    L_00453d33:
        mov ebx,80000000h
    L_00453d38:
        jae short L_00453d53
    L_00453d3a:
        mov ecx,edx
    L_00453d3c:
        shr ebx,cl
    L_00453d3e:
        lea ecx,[edx+eax+4]
    L_00453d42:
        not ebx
    L_00453d44:
        and dword ptr [eax+edi*4+44h],ebx
    L_00453d48:
        dec byte ptr [ecx]
    L_00453d4a:
        jne short L_00453d6f
    L_00453d4c:
        mov ecx,dword ptr [ebp+8]
    L_00453d4f:
        and dword ptr [ecx],ebx
    L_00453d51:
        jmp short L_00453d6f
    L_00453d53:
        lea ecx,[edx-20h]
    L_00453d56:
        shr ebx,cl
    L_00453d58:
        lea ecx,[edx+eax+4]
    L_00453d5c:
        not ebx
    L_00453d5e:
        and dword ptr [eax+edi*4+0C4h],ebx
    L_00453d65:
        dec byte ptr [ecx]
    L_00453d67:
        jne short L_00453d6f
    L_00453d69:
        mov ecx,dword ptr [ebp+8]
    L_00453d6c:
        and dword ptr [ecx+4],ebx
    L_00453d6f:
        mov ebx,dword ptr [ebp+0Ch]
    L_00453d72:
        mov edx,dword ptr [ebx+8]
    L_00453d75:
        mov ebx,dword ptr [ebx+4]
    L_00453d78:
        mov ecx,dword ptr [ebp-4]
    L_00453d7b:
        add ecx,dword ptr [ebp-0Ch]
    L_00453d7e:
        mov dword ptr [edx+4],ebx
    L_00453d81:
        mov edx,dword ptr [ebp+0Ch]
    L_00453d84:
        mov ebx,dword ptr [edx+4]
    L_00453d87:
        mov edx,dword ptr [edx+8]
    L_00453d8a:
        mov dword ptr [ebx+8],edx
    L_00453d8d:
        mov dword ptr [ebp-4],ecx
    L_00453d90:
        mov edx,ecx
    L_00453d92:
        sar edx,4
    L_00453d95:
        dec edx
    L_00453d96:
        cmp edx,3Fh
    L_00453d99:
        jbe short L_00453d9e
    L_00453d9b:
        push 3Fh
    L_00453d9d:
        pop edx
    L_00453d9e:
        mov ebx,dword ptr [ebp-8]
    L_00453da1:
        and ebx,1
    L_00453da4:
        mov dword ptr [ebp-0Ch],ebx
    L_00453da7:
        jne asm_target_00453e3c
    L_00453dad:
        sub esi,dword ptr [ebp-8]
    L_00453db0:
        mov ebx,dword ptr [ebp-8]
    L_00453db3:
        sar ebx,4
    L_00453db6:
        push 3Fh
    L_00453db8:
        mov dword ptr [ebp+0Ch],esi
    L_00453dbb:
        dec ebx
    L_00453dbc:
        pop esi
    L_00453dbd:
        cmp ebx,esi
    L_00453dbf:
        jbe short L_00453dc3
    L_00453dc1:
        mov ebx,esi
    L_00453dc3:
        add ecx,dword ptr [ebp-8]
    L_00453dc6:
        mov edx,ecx
    L_00453dc8:
        sar edx,4
    L_00453dcb:
        dec edx
    L_00453dcc:
        cmp edx,esi
    L_00453dce:
        mov dword ptr [ebp-4],ecx
    L_00453dd1:
        jbe short L_00453dd5
    L_00453dd3:
        mov edx,esi
    L_00453dd5:
        cmp ebx,edx
    L_00453dd7:
        je short L_00453e37
    L_00453dd9:
        mov ecx,dword ptr [ebp+0Ch]
    L_00453ddc:
        mov esi,dword ptr [ecx+4]
    L_00453ddf:
        cmp esi,dword ptr [ecx+8]
    L_00453de2:
        jne short L_00453e1f
    L_00453de4:
        cmp ebx,20h
    L_00453de7:
        mov esi,80000000h
    L_00453dec:
        jae short L_00453e05
    L_00453dee:
        mov ecx,ebx
    L_00453df0:
        shr esi,cl
    L_00453df2:
        not esi
    L_00453df4:
        and dword ptr [eax+edi*4+44h],esi
    L_00453df8:
        dec byte ptr [ebx+eax+4]
    L_00453dfc:
        jne short L_00453e1f
    L_00453dfe:
        mov ecx,dword ptr [ebp+8]
    L_00453e01:
        and dword ptr [ecx],esi
    L_00453e03:
        jmp short L_00453e1f
    L_00453e05:
        lea ecx,[ebx-20h]
    L_00453e08:
        shr esi,cl
    L_00453e0a:
        not esi
    L_00453e0c:
        and dword ptr [eax+edi*4+0C4h],esi
    L_00453e13:
        dec byte ptr [ebx+eax+4]
    L_00453e17:
        jne short L_00453e1f
    L_00453e19:
        mov ecx,dword ptr [ebp+8]
    L_00453e1c:
        and dword ptr [ecx+4],esi
    L_00453e1f:
        mov ecx,dword ptr [ebp+0Ch]
    L_00453e22:
        mov esi,dword ptr [ecx+8]
    L_00453e25:
        mov ecx,dword ptr [ecx+4]
    L_00453e28:
        mov dword ptr [esi+4],ecx
    L_00453e2b:
        mov ecx,dword ptr [ebp+0Ch]
    L_00453e2e:
        mov esi,dword ptr [ecx+4]
    L_00453e31:
        mov ecx,dword ptr [ecx+8]
    L_00453e34:
        mov dword ptr [esi+8],ecx
    L_00453e37:
        mov esi,dword ptr [ebp+0Ch]
    L_00453e3a:
        jmp short L_00453e3f
    L_00453e3c:
        mov ebx,dword ptr [ebp+8]
    L_00453e3f:
        cmp dword ptr [ebp-0Ch],0
    L_00453e43:
        jne short L_00453e4d
    L_00453e45:
        cmp ebx,edx
    L_00453e47:
        je asm_target_00453ecd
    L_00453e4d:
        mov ecx,dword ptr [ebp-10h]
    L_00453e50:
        lea ecx,[ecx+edx*8]
    L_00453e53:
        mov ebx,dword ptr [ecx+4]
    L_00453e56:
        mov dword ptr [esi+8],ecx
    L_00453e59:
        mov dword ptr [esi+4],ebx
    L_00453e5c:
        mov dword ptr [ecx+4],esi
    L_00453e5f:
        mov ecx,dword ptr [esi+4]
    L_00453e62:
        mov dword ptr [ecx+8],esi
    L_00453e65:
        mov ecx,dword ptr [esi+4]
    L_00453e68:
        cmp ecx,dword ptr [esi+8]
    L_00453e6b:
        jne short L_00453ecd
    L_00453e6d:
        mov cl,byte ptr [edx+eax+4]
    L_00453e71:
        mov byte ptr [ebp+0Fh],cl
    L_00453e74:
        inc cl
    L_00453e76:
        cmp edx,20h
    L_00453e79:
        mov byte ptr [edx+eax+4],cl
    L_00453e7d:
        jae short L_00453ea4
    L_00453e7f:
        cmp byte ptr [ebp+0Fh],0
    L_00453e83:
        jne short L_00453e93
    L_00453e85:
        mov ecx,edx
    L_00453e87:
        mov ebx,80000000h
    L_00453e8c:
        shr ebx,cl
    L_00453e8e:
        mov ecx,dword ptr [ebp+8]
    L_00453e91:
        or dword ptr [ecx],ebx
    L_00453e93:
        mov ebx,80000000h
    L_00453e98:
        mov ecx,edx
    L_00453e9a:
        shr ebx,cl
    L_00453e9c:
        lea eax,[eax+edi*4+44h]
    L_00453ea0:
        or dword ptr [eax],ebx
    L_00453ea2:
        jmp short L_00453ecd
    L_00453ea4:
        cmp byte ptr [ebp+0Fh],0
    L_00453ea8:
        jne short L_00453eba
    L_00453eaa:
        lea ecx,[edx-20h]
    L_00453ead:
        mov ebx,80000000h
    L_00453eb2:
        shr ebx,cl
    L_00453eb4:
        mov ecx,dword ptr [ebp+8]
    L_00453eb7:
        or dword ptr [ecx+4],ebx
    L_00453eba:
        lea ecx,[edx-20h]
    L_00453ebd:
        mov edx,80000000h
    L_00453ec2:
        shr edx,cl
    L_00453ec4:
        lea eax,[eax+edi*4+0C4h]
    L_00453ecb:
        or dword ptr [eax],edx
    L_00453ecd:
        mov eax,dword ptr [ebp-4]
    L_00453ed0:
        mov dword ptr [esi],eax
    L_00453ed2:
        mov dword ptr [eax+esi-4],eax
    L_00453ed6:
        mov eax,dword ptr [ebp-10h]
    L_00453ed9:
        dec dword ptr [eax]
    L_00453edb:
        jne asm_target_00453fd8
    L_00453ee1:
        mov eax,dword ptr [data_00499324]
    L_00453ee6:
        test eax,eax
    L_00453ee8:
        je asm_target_00453fca
    L_00453eee:
        mov ecx,dword ptr [data_0049933c]
    L_00453ef4:
        mov esi,dword ptr [data_00466188]
    L_00453efa:
        push 4000h
    L_00453eff:
        shl ecx,0Fh
    L_00453f02:
        add ecx,dword ptr [eax+0Ch]
    L_00453f05:
        mov ebx,8000h
    L_00453f0a:
        push ebx
    L_00453f0b:
        push ecx
    L_00453f0c:
        call esi
    L_00453f0e:
        mov ecx,dword ptr [data_0049933c]
    L_00453f14:
        mov eax,dword ptr [data_00499324]
    L_00453f19:
        mov edx,80000000h
    L_00453f1e:
        shr edx,cl
    L_00453f20:
        or dword ptr [eax+8],edx
    L_00453f23:
        mov eax,dword ptr [data_00499324]
    L_00453f28:
        mov eax,dword ptr [eax+10h]
    L_00453f2b:
        mov ecx,dword ptr [data_0049933c]
    L_00453f31:
        and dword ptr [eax+ecx*4+0C4h],0
    L_00453f39:
        mov eax,dword ptr [data_00499324]
    L_00453f3e:
        mov eax,dword ptr [eax+10h]
    L_00453f41:
        dec byte ptr [eax+43h]
    L_00453f44:
        mov eax,dword ptr [data_00499324]
    L_00453f49:
        mov ecx,dword ptr [eax+10h]
    L_00453f4c:
        cmp byte ptr [ecx+43h],0
    L_00453f50:
        jne short L_00453f5b
    L_00453f52:
        and dword ptr [eax+4],0FFFFFFFEh
    L_00453f56:
        mov eax,dword ptr [data_00499324]
    L_00453f5b:
        cmp dword ptr [eax+8],0FFFFFFFFh
    L_00453f5f:
        jne short L_00453fca
    L_00453f61:
        push ebx
    L_00453f62:
        push 0
    L_00453f64:
        push dword ptr [eax+0Ch]
    L_00453f67:
        call esi
    L_00453f69:
        mov eax,dword ptr [data_00499324]
    L_00453f6e:
        push dword ptr [eax+10h]
    L_00453f71:
        push 0
    L_00453f73:
        push dword ptr [data_00499340]
    L_00453f79:
        call dword ptr [data_004661e8]
    L_00453f7f:
        mov eax,dword ptr [data_00499328]
    L_00453f84:
        mov edx,dword ptr [data_0049932c]
    L_00453f8a:
        lea eax,[eax+eax*4]
    L_00453f8d:
        shl eax,2
    L_00453f90:
        mov ecx,eax
    L_00453f92:
        mov eax,dword ptr [data_00499324]
    L_00453f97:
        sub ecx,eax
    L_00453f99:
        lea ecx,[ecx+edx-14h]
    L_00453f9d:
        push ecx
    L_00453f9e:
        lea ecx,[eax+14h]
    L_00453fa1:
        push ecx
    L_00453fa2:
        push eax
    L_00453fa3:
        call asm_memmove_00453280
    L_00453fa8:
        mov eax,dword ptr [ebp+8]
    L_00453fab:
        add esp,0Ch
    L_00453fae:
        dec dword ptr [data_00499328]
    L_00453fb4:
        cmp eax,dword ptr [data_00499324]
    L_00453fba:
        jbe short L_00453fc0
    L_00453fbc:
        sub dword ptr [ebp+8],14h
    L_00453fc0:
        mov eax,dword ptr [data_0049932c]
    L_00453fc5:
        mov dword ptr [data_00499334],eax
    L_00453fca:
        mov eax,dword ptr [ebp+8]
    L_00453fcd:
        mov dword ptr [data_00499324],eax
    L_00453fd2:
        mov dword ptr [data_0049933c],edi
    L_00453fd8:
        pop ebx
    L_00453fd9:
        pop edi
    L_00453fda:
        pop esi
    L_00453fdb:
        leave
    L_00453fdc:
        ret
    }
}

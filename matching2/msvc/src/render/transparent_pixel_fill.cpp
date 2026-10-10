// 0x00436DA0: fill the transparent pixels of the font atlas from their opaque
// neighbours.  stdcall (atlas, rows) -> true.
//
// Equivalent recovery in the default build:
// equivalent/platform/font_atlas_fill_transparent_00436da0.cpp (284 of 316
// instructions identical).  This assembly is used by `make EXACT=1` only.  The
// open differences are the byte-wide nibble packing at the end of the 4-bit
// path and the zero register and per-row pointer of the 32-bit path; see
// reference/recovery_notes/font_atlas_convert_00436da0_regalloc_2026_10_10.md.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436DA0..0x00436FD8: FUN_00436da0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436da0_00436da0() {
    __asm {
    L_00436da0:
        sub esp,14h
    L_00436da3:
        push ebx
    L_00436da4:
        push ebp
    L_00436da5:
        push esi
    L_00436da6:
        mov esi,dword ptr [esp+24h]
    L_00436daa:
        mov eax,dword ptr [esi+100h]
    L_00436db0:
        cmp eax,15h
    L_00436db3:
        push edi
    L_00436db4:
        je asm_target_00436fa3
    L_00436dba:
        cmp eax,1Ah
    L_00436dbd:
        jne asm_target_00437146
    L_00436dc3:
        mov eax,dword ptr [esp+2Ch]
    L_00436dc7:
        test eax,eax
    L_00436dc9:
        mov edi,dword ptr [esi+120h]
    L_00436dcf:
        mov dword ptr [esp+10h],0
    L_00436dd7:
        jbe asm_target_00437146
    L_00436ddd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00436de0:
        mov edx,dword ptr [esi+104h]
    L_00436de6:
        xor ebp,ebp
    L_00436de8:
        test edx,edx
    L_00436dea:
        mov dword ptr [esp+14h],ebp
    L_00436dee:
        jbe asm_target_00436f82
    L_00436df4:
        test byte ptr [edi+1],0F0h
    L_00436df8:
        jne asm_target_00436f6c
    L_00436dfe:
        xor ecx,ecx
    L_00436e00:
        xor ebx,ebx
    L_00436e02:
        xor esi,esi
    L_00436e04:
        test ebp,ebp
    L_00436e06:
        mov dword ptr [esp+20h],ecx
    L_00436e0a:
        jbe short L_00436e34
    L_00436e0c:
        mov ax,word ptr [edi-2]
    L_00436e10:
        test ah,0F0h
    L_00436e13:
        je short L_00436e34
    L_00436e15:
        movzx eax,ax
    L_00436e18:
        mov ecx,eax
    L_00436e1a:
        mov ebx,eax
    L_00436e1c:
        shr ecx,8
    L_00436e1f:
        shr ebx,4
    L_00436e22:
        and ecx,0Fh
    L_00436e25:
        and ebx,0Fh
    L_00436e28:
        and eax,0Fh
    L_00436e2b:
        mov dword ptr [esp+20h],eax
    L_00436e2f:
        mov esi,1
    L_00436e34:
        dec edx
    L_00436e35:
        cmp ebp,edx
    L_00436e37:
        jae short L_00436e67
    L_00436e39:
        mov ax,word ptr [edi+2]
    L_00436e3d:
        test ah,0F0h
    L_00436e40:
        je short L_00436e67
    L_00436e42:
        movzx eax,ax
    L_00436e45:
        mov edx,eax
    L_00436e47:
        shr edx,8
    L_00436e4a:
        and edx,0Fh
    L_00436e4d:
        add ecx,edx
    L_00436e4f:
        mov edx,eax
    L_00436e51:
        shr edx,4
    L_00436e54:
        and edx,0Fh
    L_00436e57:
        add ebx,edx
    L_00436e59:
        mov edx,dword ptr [esp+20h]
    L_00436e5d:
        and eax,0Fh
    L_00436e60:
        add edx,eax
    L_00436e62:
        mov dword ptr [esp+20h],edx
    L_00436e66:
        inc esi
    L_00436e67:
        mov eax,dword ptr [esp+10h]
    L_00436e6b:
        test eax,eax
    L_00436e6d:
        mov ebp,dword ptr [esp+28h]
    L_00436e71:
        jbe short L_00436eb3
    L_00436e73:
        mov eax,dword ptr [ebp+110h]
    L_00436e79:
        cdq
    L_00436e7a:
        sub eax,edx
    L_00436e7c:
        sar eax,1
    L_00436e7e:
        shl eax,1
    L_00436e80:
        mov edx,eax
    L_00436e82:
        mov eax,edi
    L_00436e84:
        sub eax,edx
    L_00436e86:
        mov ax,word ptr [eax]
    L_00436e89:
        test ah,0F0h
    L_00436e8c:
        je short L_00436eb3
    L_00436e8e:
        movzx eax,ax
    L_00436e91:
        mov edx,eax
    L_00436e93:
        shr edx,8
    L_00436e96:
        and edx,0Fh
    L_00436e99:
        add ecx,edx
    L_00436e9b:
        mov edx,eax
    L_00436e9d:
        shr edx,4
    L_00436ea0:
        and edx,0Fh
    L_00436ea3:
        add ebx,edx
    L_00436ea5:
        mov edx,dword ptr [esp+20h]
    L_00436ea9:
        and eax,0Fh
    L_00436eac:
        add edx,eax
    L_00436eae:
        mov dword ptr [esp+20h],edx
    L_00436eb2:
        inc esi
    L_00436eb3:
        mov eax,dword ptr [ebp+108h]
    L_00436eb9:
        mov edx,dword ptr [esp+10h]
    L_00436ebd:
        dec eax
    L_00436ebe:
        cmp edx,eax
    L_00436ec0:
        jae short L_00436efd
    L_00436ec2:
        mov eax,dword ptr [ebp+110h]
    L_00436ec8:
        cdq
    L_00436ec9:
        sub eax,edx
    L_00436ecb:
        sar eax,1
    L_00436ecd:
        lea eax,[edi+eax*2]
    L_00436ed0:
        mov ax,word ptr [eax]
    L_00436ed3:
        test ah,0F0h
    L_00436ed6:
        je short L_00436efd
    L_00436ed8:
        movzx eax,ax
    L_00436edb:
        mov edx,eax
    L_00436edd:
        shr edx,8
    L_00436ee0:
        and edx,0Fh
    L_00436ee3:
        add ecx,edx
    L_00436ee5:
        mov edx,eax
    L_00436ee7:
        shr edx,4
    L_00436eea:
        and edx,0Fh
    L_00436eed:
        add ebx,edx
    L_00436eef:
        mov edx,dword ptr [esp+20h]
    L_00436ef3:
        and eax,0Fh
    L_00436ef6:
        add edx,eax
    L_00436ef8:
        mov dword ptr [esp+20h],edx
    L_00436efc:
        inc esi
    L_00436efd:
        cmp esi,1
    L_00436f00:
        jbe short L_00436f1e
    L_00436f02:
        xor edx,edx
    L_00436f04:
        mov eax,ecx
    L_00436f06:
        div esi
    L_00436f08:
        xor edx,edx
    L_00436f0a:
        mov ecx,eax
    L_00436f0c:
        mov eax,ebx
    L_00436f0e:
        div esi
    L_00436f10:
        xor edx,edx
    L_00436f12:
        mov ebx,eax
    L_00436f14:
        mov eax,dword ptr [esp+20h]
    L_00436f18:
        div esi
    L_00436f1a:
        mov dword ptr [esp+20h],eax
    L_00436f1e:
        mov edx,dword ptr [esp+20h]
    L_00436f22:
        shr ecx,1
    L_00436f24:
        and cl,0Fh
    L_00436f27:
        shr ebx,1
    L_00436f29:
        shr edx,1
    L_00436f2b:
        movzx ax,cl
    L_00436f2f:
        mov esi,dword ptr [esp+28h]
    L_00436f33:
        mov ebp,dword ptr [esp+14h]
    L_00436f37:
        and bl,0Fh
    L_00436f3a:
        mov dword ptr [esp+20h],edx
    L_00436f3e:
        movzx cx,bl
    L_00436f42:
        xor edx,edx
    L_00436f44:
        mov dx,word ptr [edi]
    L_00436f47:
        shl eax,4
    L_00436f4a:
        or eax,ecx
    L_00436f4c:
        mov cl,byte ptr [esp+20h]
    L_00436f50:
        shl eax,4
    L_00436f53:
        and edx,0F00Fh
    L_00436f59:
        or eax,edx
    L_00436f5b:
        and cl,0Fh
    L_00436f5e:
        movzx dx,cl
    L_00436f62:
        and eax,0FFF0h
    L_00436f67:
        or eax,edx
    L_00436f69:
        mov word ptr [edi],ax
    L_00436f6c:
        mov edx,dword ptr [esi+104h]
    L_00436f72:
        add edi,2
    L_00436f75:
        inc ebp
    L_00436f76:
        cmp ebp,edx
    L_00436f78:
        mov dword ptr [esp+14h],ebp
    L_00436f7c:
        jb asm_target_00436df4
    L_00436f82:
        mov eax,dword ptr [esp+10h]
    L_00436f86:
        mov ecx,dword ptr [esp+2Ch]
    L_00436f8a:
        inc eax
    L_00436f8b:
        cmp eax,ecx
    L_00436f8d:
        mov dword ptr [esp+10h],eax
    L_00436f91:
        jb asm_target_00436de0
    L_00436f97:
        pop edi
    L_00436f98:
        pop esi
    L_00436f99:
        pop ebp
    L_00436f9a:
        mov al,1
    L_00436f9c:
        pop ebx
    L_00436f9d:
        add esp,14h
    L_00436fa0:
        ret 8
    L_00436fa3:
        mov eax,dword ptr [esp+2Ch]
    L_00436fa7:
        mov ebp,dword ptr [esi+120h]
    L_00436fad:
        xor ebx,ebx
    L_00436faf:
        xor edx,edx
    L_00436fb1:
        cmp eax,ebx
    L_00436fb3:
        mov dword ptr [esp+10h],edx
    L_00436fb7:
        jbe asm_target_00437146
    L_00436fbd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00436fc0:
        mov edi,dword ptr [esi+104h]
    L_00436fc6:
        xor eax,eax
    L_00436fc8:
        cmp edi,ebx
    L_00436fca:
        mov dword ptr [esp+14h],eax
    L_00436fce:
        jbe asm_target_00437135
    L_00436fd4:
        lea ecx,[ebp-2]
    L_00436fd7:
        TH10_REL8(0xeb, 0x00436fd7, VA_asm_FUN_00436da0_part_00436fe0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00436fe0:
        cmp byte ptr [ecx+5],0
    L_00436fe4:
        jne asm_target_0043711c
    L_00436fea:
        xor esi,esi
    L_00436fec:
        test eax,eax
    L_00436fee:
        mov dword ptr [esp+20h],ebx
    L_00436ff2:
        mov dword ptr [esp+1Ch],ebx
    L_00436ff6:
        jbe short L_00437016
    L_00436ff8:
        cmp byte ptr [ecx+1],0
    L_00436ffc:
        je short L_00437016
    L_00436ffe:
        movzx esi,byte ptr [ecx-1]
    L_00437002:
        movzx ebx,byte ptr [ecx]
    L_00437005:
        mov dword ptr [esp+1Ch],esi
    L_00437009:
        movzx esi,byte ptr [ecx-2]
    L_0043700d:
        mov dword ptr [esp+20h],esi
    L_00437011:
        mov esi,1
    L_00437016:
        dec edi
    L_00437017:
        cmp eax,edi
    L_00437019:
        jae short L_0043703f
    L_0043701b:
        mov al,byte ptr [ecx+9]
    L_0043701e:
        test al,al
    L_00437020:
        je short L_0043703f
    L_00437022:
        movzx eax,byte ptr [ecx+8]
    L_00437026:
        mov edi,dword ptr [esp+1Ch]
    L_0043702a:
        add ebx,eax
    L_0043702c:
        movzx eax,byte ptr [ecx+7]
    L_00437030:
        add edi,eax
    L_00437032:
        movzx eax,byte ptr [ecx+6]
    L_00437036:
        mov dword ptr [esp+1Ch],edi
    L_0043703a:
        add dword ptr [esp+20h],eax
    L_0043703e:
        inc esi
    L_0043703f:
        test edx,edx
    L_00437041:
        jbe short L_00437088
    L_00437043:
        mov edx,dword ptr [esp+28h]
    L_00437047:
        mov eax,dword ptr [edx+110h]
    L_0043704d:
        cdq
    L_0043704e:
        and edx,3
    L_00437051:
        add eax,edx
    L_00437053:
        sar eax,2
    L_00437056:
        shl eax,2
    L_00437059:
        mov edx,eax
    L_0043705b:
        mov eax,ebp
    L_0043705d:
        sub eax,edx
    L_0043705f:
        mov dl,byte ptr [eax+3]
    L_00437062:
        test dl,dl
    L_00437064:
        je short L_00437088
    L_00437066:
        movzx edx,byte ptr [eax+2]
    L_0043706a:
        mov edi,dword ptr [esp+1Ch]
    L_0043706e:
        add ebx,edx
    L_00437070:
        movzx edx,byte ptr [eax+1]
    L_00437074:
        movzx eax,byte ptr [eax]
    L_00437077:
        add edi,edx
    L_00437079:
        mov edx,dword ptr [esp+20h]
    L_0043707d:
        add edx,eax
    L_0043707f:
        mov dword ptr [esp+1Ch],edi
    L_00437083:
        mov dword ptr [esp+20h],edx
    L_00437087:
        inc esi
    L_00437088:
        mov eax,dword ptr [esp+28h]
    L_0043708c:
        mov edx,dword ptr [eax+108h]
    L_00437092:
        mov edi,dword ptr [esp+10h]
    L_00437096:
        dec edx
    L_00437097:
        cmp edi,edx
    L_00437099:
        jae short L_004370d8
    L_0043709b:
        mov eax,dword ptr [eax+110h]
    L_004370a1:
        cdq
    L_004370a2:
        and edx,3
    L_004370a5:
        add eax,edx
    L_004370a7:
        sar eax,2
    L_004370aa:
        mov dl,byte ptr [ebp+eax*4+3]
    L_004370ae:
        test dl,dl
    L_004370b0:
        lea eax,[ebp+eax*4]
    L_004370b4:
        je short L_004370d8
    L_004370b6:
        movzx edx,byte ptr [eax+2]
    L_004370ba:
        mov edi,dword ptr [esp+1Ch]
    L_004370be:
        add ebx,edx
    L_004370c0:
        movzx edx,byte ptr [eax+1]
    L_004370c4:
        movzx eax,byte ptr [eax]
    L_004370c7:
        add edi,edx
    L_004370c9:
        mov edx,dword ptr [esp+20h]
    L_004370cd:
        add edx,eax
    L_004370cf:
        mov dword ptr [esp+1Ch],edi
    L_004370d3:
        mov dword ptr [esp+20h],edx
    L_004370d7:
        inc esi
    L_004370d8:
        cmp esi,1
    L_004370db:
        jbe short L_004370fd
    L_004370dd:
        xor edx,edx
    L_004370df:
        mov eax,ebx
    L_004370e1:
        div esi
    L_004370e3:
        xor edx,edx
    L_004370e5:
        mov ebx,eax
    L_004370e7:
        mov eax,dword ptr [esp+1Ch]
    L_004370eb:
        div esi
    L_004370ed:
        xor edx,edx
    L_004370ef:
        mov dword ptr [esp+1Ch],eax
    L_004370f3:
        mov eax,dword ptr [esp+20h]
    L_004370f7:
        div esi
    L_004370f9:
        mov dword ptr [esp+20h],eax
    L_004370fd:
        mov dl,byte ptr [esp+1Ch]
    L_00437101:
        mov al,byte ptr [esp+20h]
    L_00437105:
        mov esi,dword ptr [esp+28h]
    L_00437109:
        mov byte ptr [ecx+4],bl
    L_0043710c:
        mov byte ptr [ecx+3],dl
    L_0043710f:
        mov edx,dword ptr [esp+10h]
    L_00437113:
        mov byte ptr [ebp],al
    L_00437116:
        mov eax,dword ptr [esp+14h]
    L_0043711a:
        xor ebx,ebx
    L_0043711c:
        mov edi,dword ptr [esi+104h]
    L_00437122:
        add ebp,4
    L_00437125:
        add ecx,4
    L_00437128:
        inc eax
    L_00437129:
        cmp eax,edi
    L_0043712b:
        mov dword ptr [esp+14h],eax
    L_0043712f:
        jb asm_FUN_00436da0_part_00436fe0
    L_00437135:
        mov eax,dword ptr [esp+2Ch]
    L_00437139:
        inc edx
    L_0043713a:
        cmp edx,eax
    L_0043713c:
        mov dword ptr [esp+10h],edx
    L_00437140:
        jb asm_target_00436fc0
    L_00437146:
        pop edi
    L_00437147:
        pop esi
    L_00437148:
        pop ebp
    L_00437149:
        mov al,1
    L_0043714b:
        pop ebx
    L_0043714c:
        add esp,14h
    L_0043714f:
        ret 8
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.

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

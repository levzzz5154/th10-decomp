#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00447C80..0x00447EBF: FUN_00447c80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00447c80_00447c80() {
    __asm {
    L_00447c80:
        sub esp,118h
    L_00447c86:
        mov eax,dword ptr [data_00473660]
    L_00447c8b:
        xor eax,esp
    L_00447c8d:
        push ebx
    L_00447c8e:
        push ebp
    L_00447c8f:
        mov ebp,dword ptr [esp+124h]
    L_00447c96:
        push esi
    L_00447c97:
        push edi
    L_00447c98:
        mov edi,ecx
    L_00447c9a:
        mov ecx,dword ptr [edi+ebp*4+3AD4E0h]
    L_00447ca1:
        test ecx,ecx
    L_00447ca3:
        mov dword ptr [esp+124h],eax
    L_00447caa:
        lea eax,[edi+ebp*4+3AD4E0h]
    L_00447cb1:
        mov ebx,edx
    L_00447cb3:
        mov dword ptr [esp+18h],eax
    L_00447cb7:
        je short L_00447cc0
    L_00447cb9:
        mov esi,ebp
    L_00447cbb:
        call asm_AnimationManager_ClearIndexedResources_00447f70
    L_00447cc0:
        mov eax,dword ptr [edi+ebp*4+3AD5E0h]
    L_00447cc7:
        test eax,eax
    L_00447cc9:
        jne short L_00447d11
    L_00447ccb:
        push ebx
    L_00447ccc:
        lea eax,[esp+24h]
    L_00447cd0:
        push 46E1C8h
    L_00447cd5:
        push eax
    L_00447cd6:
        call asm_sprintf_00452ae8
    L_00447cdb:
        add esp,0Ch
    L_00447cde:
        push 0
    L_00447ce0:
        lea ecx,[esp+20h]
    L_00447ce4:
        push ecx
    L_00447ce5:
        lea eax,[esp+28h]
    L_00447ce9:
        call asm_FUN_0044b360_0044b360
    L_00447cee:
        test eax,eax
    L_00447cf0:
        mov dword ptr [esp+14h],eax
    L_00447cf4:
        jne short L_00447d2b
    L_00447cf6:
        push ebx
    L_00447cf7:
        push 470150h
    L_00447cfc:
        mov edi,474F70h
    L_00447d01:
        call asm_TextLog_AppendLine_0044b8e0
    L_00447d06:
        add esp,8
    L_00447d09:
        or eax,0FFFFFFFFh
    L_00447d0c:
        jmp asm_target_00447ea5
    L_00447d11:
        mov edx,dword ptr [edi+ebp*4+3AD660h]
    L_00447d18:
        mov dword ptr [esp+14h],eax
    L_00447d1c:
        mov dword ptr [esp+1Ch],edx
    L_00447d20:
        mov dword ptr [edi+ebp*4+3AD5E0h],0
    L_00447d2b:
        mov eax,dword ptr [data_00491c30]
    L_00447d30:
        mov ecx,dword ptr [eax]
    L_00447d32:
        push 0
    L_00447d34:
        lea edx,[esp+14h]
    L_00447d38:
        push edx
    L_00447d39:
        mov edx,dword ptr [data_00491d14]
    L_00447d3f:
        push 3
    L_00447d41:
        push edx
    L_00447d42:
        push 400h
    L_00447d47:
        push 280h
    L_00447d4c:
        push eax
    L_00447d4d:
        call dword ptr [ecx+90h]
    L_00447d53:
        test eax,eax
    L_00447d55:
        jne asm_target_00447e77
    L_00447d5b:
        mov ecx,dword ptr [esp+1Ch]
    L_00447d5f:
        mov edx,dword ptr [esp+14h]
    L_00447d63:
        mov eax,ebp
    L_00447d65:
        imul eax,1Ch
    L_00447d68:
        lea ebx,[eax+edi]
    L_00447d6b:
        mov eax,dword ptr [esp+10h]
    L_00447d6f:
        lea esi,[ebx+3AD6E0h]
    L_00447d75:
        push esi
    L_00447d76:
        push 0
    L_00447d78:
        push 1
    L_00447d7a:
        push 0
    L_00447d7c:
        push ecx
    L_00447d7d:
        push edx
    L_00447d7e:
        push 0
    L_00447d80:
        push 0
    L_00447d82:
        push eax
    L_00447d83:
        call asm_D3DXLoadSurfaceFromFileInMemory_004521d0
    L_00447d88:
        test eax,eax
    L_00447d8a:
        jne asm_target_00447e50
    L_00447d90:
        mov edx,dword ptr [esp+18h]
    L_00447d94:
        mov eax,dword ptr [data_00491c30]
    L_00447d99:
        mov ecx,dword ptr [eax]
    L_00447d9b:
        push 0
    L_00447d9d:
        push edx
    L_00447d9e:
        mov edx,dword ptr [data_00491d14]
    L_00447da4:
        push 1
    L_00447da6:
        push 0
    L_00447da8:
        push 0
    L_00447daa:
        push edx
    L_00447dab:
        mov edx,dword ptr [ebx+3AD6E4h]
    L_00447db1:
        push edx
    L_00447db2:
        mov edx,dword ptr [esi]
    L_00447db4:
        push edx
    L_00447db5:
        push eax
    L_00447db6:
        call dword ptr [ecx+70h]
    L_00447db9:
        test eax,eax
    L_00447dbb:
        je short L_00447de9
    L_00447dbd:
        mov edx,dword ptr [esp+18h]
    L_00447dc1:
        mov eax,dword ptr [data_00491c30]
    L_00447dc6:
        mov ecx,dword ptr [eax]
    L_00447dc8:
        push 0
    L_00447dca:
        push edx
    L_00447dcb:
        mov edx,dword ptr [data_00491d14]
    L_00447dd1:
        push 3
    L_00447dd3:
        push edx
    L_00447dd4:
        mov edx,dword ptr [ebx+3AD6E4h]
    L_00447dda:
        push edx
    L_00447ddb:
        mov edx,dword ptr [esi]
    L_00447ddd:
        push edx
    L_00447dde:
        push eax
    L_00447ddf:
        call dword ptr [ecx+90h]
    L_00447de5:
        test eax,eax
    L_00447de7:
        jne short L_00447e50
    L_00447de9:
        mov edx,dword ptr [data_00491d14]
    L_00447def:
        mov eax,dword ptr [data_00491c30]
    L_00447df4:
        mov ecx,dword ptr [eax]
    L_00447df6:
        push 0
    L_00447df8:
        lea edi,[edi+ebp*4+3AD560h]
    L_00447dff:
        push edi
    L_00447e00:
        push 3
    L_00447e02:
        push edx
    L_00447e03:
        mov edx,dword ptr [ebx+3AD6E4h]
    L_00447e09:
        push edx
    L_00447e0a:
        mov edx,dword ptr [esi]
    L_00447e0c:
        push edx
    L_00447e0d:
        push eax
    L_00447e0e:
        call dword ptr [ecx+90h]
    L_00447e14:
        test eax,eax
    L_00447e16:
        jne short L_00447e50
    L_00447e18:
        mov ecx,dword ptr [esp+18h]
    L_00447e1c:
        mov edx,dword ptr [ecx]
    L_00447e1e:
        push eax
    L_00447e1f:
        push 1
    L_00447e21:
        push eax
    L_00447e22:
        push eax
    L_00447e23:
        mov eax,dword ptr [esp+20h]
    L_00447e27:
        push eax
    L_00447e28:
        push 0
    L_00447e2a:
        push 0
    L_00447e2c:
        push edx
    L_00447e2d:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_00447e32:
        test eax,eax
    L_00447e34:
        jne short L_00447e50
    L_00447e36:
        mov ecx,dword ptr [edi]
    L_00447e38:
        push eax
    L_00447e39:
        push 1
    L_00447e3b:
        push eax
    L_00447e3c:
        push eax
    L_00447e3d:
        mov eax,dword ptr [esp+20h]
    L_00447e41:
        push eax
    L_00447e42:
        push 0
    L_00447e44:
        push 0
    L_00447e46:
        push ecx
    L_00447e47:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_00447e4c:
        test eax,eax
    L_00447e4e:
        je short L_00447e7c
    L_00447e50:
        mov eax,dword ptr [esp+10h]
    L_00447e54:
        test eax,eax
    L_00447e56:
        je short L_00447e66
    L_00447e58:
        mov edx,dword ptr [eax]
    L_00447e5a:
        push eax
    L_00447e5b:
        call dword ptr [edx+8]
    L_00447e5e:
        mov dword ptr [esp+10h],0
    L_00447e66:
        mov eax,dword ptr [esp+14h]
    L_00447e6a:
        test eax,eax
    L_00447e6c:
        je short L_00447e77
    L_00447e6e:
        push eax
    L_00447e6f:
        call asm_free_00452422
    L_00447e74:
        add esp,4
    L_00447e77:
        or eax,0FFFFFFFFh
    L_00447e7a:
        jmp short L_00447ea5
    L_00447e7c:
        mov eax,dword ptr [esp+10h]
    L_00447e80:
        test eax,eax
    L_00447e82:
        je short L_00447e92
    L_00447e84:
        mov ecx,dword ptr [eax]
    L_00447e86:
        push eax
    L_00447e87:
        call dword ptr [ecx+8]
    L_00447e8a:
        mov dword ptr [esp+10h],0
    L_00447e92:
        mov eax,dword ptr [esp+14h]
    L_00447e96:
        test eax,eax
    L_00447e98:
        je short L_00447ea3
    L_00447e9a:
        push eax
    L_00447e9b:
        call asm_free_00452422
    L_00447ea0:
        add esp,4
    L_00447ea3:
        xor eax,eax
    L_00447ea5:
        mov ecx,dword ptr [esp+124h]
    L_00447eac:
        pop edi
    L_00447ead:
        pop esi
    L_00447eae:
        pop ebp
    L_00447eaf:
        pop ebx
    L_00447eb0:
        xor ecx,esp
    L_00447eb2:
        call asm_security_check_cookie_00458ea5
    L_00447eb7:
        add esp,118h
    L_00447ebd:
        ret 4
    }
}

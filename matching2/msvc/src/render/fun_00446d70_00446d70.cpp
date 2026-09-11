#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446D70..0x00446EAF: FUN_00446d70
// Naked body preserves the retail register/stack ABI.

// 0x00446D70..0x00446EAF: FUN_00446d70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00446d70_00446d70() {
    __asm {
    L_00446d70:
        sub esp,34h
    L_00446d73:
        push ebx
    L_00446d74:
        push ebp
    L_00446d75:
        mov ebp,dword ptr [esp+48h]
    L_00446d79:
        push esi
    L_00446d7a:
        mov esi,ecx
    L_00446d7c:
        mov cl,byte ptr [data_00491d78]
    L_00446d82:
        xor ebx,ebx
    L_00446d84:
        test cl,1
    L_00446d87:
        mov dword ptr [esp+0Ch],eax
    L_00446d8b:
        je short L_00446db4
    L_00446d8d:
        mov eax,dword ptr [eax*4+46F288h]
    L_00446d94:
        cmp eax,15h
    L_00446d97:
        je short L_00446dac
    L_00446d99:
        cmp eax,ebx
    L_00446d9b:
        je short L_00446dac
    L_00446d9d:
        cmp eax,14h
    L_00446da0:
        jne short L_00446db4
    L_00446da2:
        mov dword ptr [esp+0Ch],3
    L_00446daa:
        jmp short L_00446db4
    L_00446dac:
        mov dword ptr [esp+0Ch],5
    L_00446db4:
        mov eax,dword ptr [esp+48h]
    L_00446db8:
        lea edx,[esp+4Ch]
    L_00446dbc:
        push edx
    L_00446dbd:
        mov dword ptr [eax+8],ebp
    L_00446dc0:
        mov eax,dword ptr [eax]
    L_00446dc2:
        push ebx
    L_00446dc3:
        mov dword ptr [esp+54h],ebx
    L_00446dc7:
        mov ecx,dword ptr [eax]
    L_00446dc9:
        push eax
    L_00446dca:
        call dword ptr [ecx+48h]
    L_00446dcd:
        cmp dword ptr [esp+50h],ebx
    L_00446dd1:
        jne short L_00446e13
    L_00446dd3:
        mov eax,dword ptr [esp+4Ch]
    L_00446dd7:
        mov ecx,dword ptr [eax]
    L_00446dd9:
        lea edx,[esp+20h]
    L_00446ddd:
        push edx
    L_00446dde:
        push eax
    L_00446ddf:
        call dword ptr [ecx+30h]
    L_00446de2:
        mov eax,dword ptr [esp+38h]
    L_00446de6:
        mov ecx,dword ptr [esp+3Ch]
    L_00446dea:
        push ebx
    L_00446deb:
        push ebx
    L_00446dec:
        push 1
    L_00446dee:
        push ebx
    L_00446def:
        push ebp
    L_00446df0:
        push edi
    L_00446df1:
        lea edx,[esp+28h]
    L_00446df5:
        push edx
    L_00446df6:
        mov dword ptr [esp+34h],eax
    L_00446dfa:
        mov eax,dword ptr [esp+68h]
    L_00446dfe:
        push ebx
    L_00446dff:
        push eax
    L_00446e00:
        mov dword ptr [esp+34h],ebx
    L_00446e04:
        mov dword ptr [esp+38h],esi
    L_00446e08:
        mov dword ptr [esp+40h],ecx
    L_00446e0c:
        call asm_D3DXLoadSurfaceFromFileInMemory_004521d0
    L_00446e11:
        jmp short L_00446e82
    L_00446e13:
        mov ecx,dword ptr [edi+30h]
    L_00446e16:
        lea eax,[ecx+edi]
    L_00446e19:
        mov dword ptr [esp+10h],ebx
    L_00446e1d:
        mov dword ptr [esp+14h],ebx
    L_00446e21:
        movsx edx,word ptr [eax+8]
    L_00446e25:
        mov dword ptr [esp+18h],edx
    L_00446e29:
        movsx ecx,word ptr [eax+0Ah]
    L_00446e2d:
        mov dword ptr [esp+1Ch],ecx
    L_00446e31:
        mov dword ptr [esp+20h],ebx
    L_00446e35:
        mov dword ptr [esp+24h],esi
    L_00446e39:
        movsx edx,word ptr [eax+8]
    L_00446e3d:
        mov dword ptr [esp+28h],edx
    L_00446e41:
        movsx ecx,word ptr [eax+0Ah]
    L_00446e45:
        push ebx
    L_00446e46:
        push 1
    L_00446e48:
        add ecx,esi
    L_00446e4a:
        mov dword ptr [esp+34h],ecx
    L_00446e4e:
        movsx ecx,word ptr [eax+6]
    L_00446e52:
        lea edx,[esp+18h]
    L_00446e56:
        push edx
    L_00446e57:
        movsx edx,word ptr [eax+8]
    L_00446e5b:
        shl ecx,2
    L_00446e5e:
        imul edx,dword ptr [ecx+46F2A0h]
    L_00446e65:
        mov ecx,dword ptr [ecx+46F288h]
    L_00446e6b:
        push ebx
    L_00446e6c:
        push edx
    L_00446e6d:
        push ecx
    L_00446e6e:
        add eax,10h
    L_00446e71:
        push eax
    L_00446e72:
        mov eax,dword ptr [esp+68h]
    L_00446e76:
        lea edx,[esp+3Ch]
    L_00446e7a:
        push edx
    L_00446e7b:
        push ebx
    L_00446e7c:
        push eax
    L_00446e7d:
        call asm_D3DXLoadSurfaceFromMemory_004521a6
    L_00446e82:
        mov eax,dword ptr [esp+4Ch]
    L_00446e86:
        mov ecx,dword ptr [eax]
    L_00446e88:
        push eax
    L_00446e89:
        call dword ptr [ecx+8]
    L_00446e8c:
        mov esi,dword ptr [esp+48h]
    L_00446e90:
        mov eax,esi
    L_00446e92:
        call asm_FUN_004465b0_004465b0
    L_00446e97:
        mov edx,dword ptr [esp+0Ch]
    L_00446e9b:
        mov eax,dword ptr [edx*4+46F2A0h]
    L_00446ea2:
        mov dword ptr [esi+0Ch],eax
    L_00446ea5:
        pop esi
    L_00446ea6:
        pop ebp
    L_00446ea7:
        xor eax,eax
    L_00446ea9:
        pop ebx
    L_00446eaa:
        add esp,34h
    L_00446ead:
        ret 10h
    }
}

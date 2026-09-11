#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446C70..0x00446D62: FUN_00446c70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00446c70_00446c70() {
    __asm {
    L_00446c70:
        sub esp,18h
    L_00446c73:
        test byte ptr [data_00491d78],1
    L_00446c7a:
        mov dword ptr [esp+4],eax
    L_00446c7e:
        je short L_00446ca7
    L_00446c80:
        mov eax,dword ptr [eax*4+46F288h]
    L_00446c87:
        cmp eax,15h
    L_00446c8a:
        je short L_00446c9f
    L_00446c8c:
        test eax,eax
    L_00446c8e:
        je short L_00446c9f
    L_00446c90:
        cmp eax,14h
    L_00446c93:
        jne short L_00446ca7
    L_00446c95:
        mov dword ptr [esp+4],3
    L_00446c9d:
        jmp short L_00446ca7
    L_00446c9f:
        mov dword ptr [esp+4],5
    L_00446ca7:
        mov eax,dword ptr [edi]
    L_00446ca9:
        lea edx,[esp]
    L_00446cac:
        push edx
    L_00446cad:
        push 0
    L_00446caf:
        mov dword ptr [edi+8],ebx
    L_00446cb2:
        mov dword ptr [esp+8],0
    L_00446cba:
        mov ecx,dword ptr [eax]
    L_00446cbc:
        push eax
    L_00446cbd:
        call dword ptr [ecx+48h]
    L_00446cc0:
        mov eax,dword ptr [esp+20h]
    L_00446cc4:
        test eax,eax
    L_00446cc6:
        push 0
    L_00446cc8:
        jne short L_00446ce2
    L_00446cca:
        mov eax,dword ptr [esp+4]
    L_00446cce:
        push 0
    L_00446cd0:
        push 1
    L_00446cd2:
        push 0
    L_00446cd4:
        push ebx
    L_00446cd5:
        push esi
    L_00446cd6:
        push 0
    L_00446cd8:
        push 0
    L_00446cda:
        push eax
    L_00446cdb:
        call asm_D3DXLoadSurfaceFromFileInMemory_004521d0
    L_00446ce0:
        jmp short L_00446d3d
    L_00446ce2:
        mov ecx,dword ptr [esi+30h]
    L_00446ce5:
        lea eax,[ecx+esi]
    L_00446ce8:
        mov dword ptr [esp+0Ch],0
    L_00446cf0:
        mov dword ptr [esp+10h],0
    L_00446cf8:
        movsx edx,word ptr [eax+8]
    L_00446cfc:
        mov dword ptr [esp+14h],edx
    L_00446d00:
        movsx ecx,word ptr [eax+0Ah]
    L_00446d04:
        push 1
    L_00446d06:
        mov dword ptr [esp+1Ch],ecx
    L_00446d0a:
        movsx ecx,word ptr [eax+6]
    L_00446d0e:
        lea edx,[esp+10h]
    L_00446d12:
        push edx
    L_00446d13:
        movsx edx,word ptr [eax+8]
    L_00446d17:
        shl ecx,2
    L_00446d1a:
        imul edx,dword ptr [ecx+46F2A0h]
    L_00446d21:
        mov ecx,dword ptr [ecx+46F288h]
    L_00446d27:
        push 0
    L_00446d29:
        push edx
    L_00446d2a:
        mov edx,dword ptr [esp+14h]
    L_00446d2e:
        push ecx
    L_00446d2f:
        add eax,10h
    L_00446d32:
        push eax
    L_00446d33:
        push 0
    L_00446d35:
        push 0
    L_00446d37:
        push edx
    L_00446d38:
        call asm_D3DXLoadSurfaceFromMemory_004521a6
    L_00446d3d:
        mov eax,dword ptr [esp]
    L_00446d40:
        mov ecx,dword ptr [eax]
    L_00446d42:
        push eax
    L_00446d43:
        call dword ptr [ecx+8]
    L_00446d46:
        mov eax,edi
    L_00446d48:
        call asm_FUN_004465b0_004465b0
    L_00446d4d:
        mov edx,dword ptr [esp+4]
    L_00446d51:
        mov eax,dword ptr [edx*4+46F2A0h]
    L_00446d58:
        mov dword ptr [edi+0Ch],eax
    L_00446d5b:
        xor eax,eax
    L_00446d5d:
        add esp,18h
    L_00446d60:
        ret 8
    }
}



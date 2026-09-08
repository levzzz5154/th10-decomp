#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446B70..0x00446C64: FUN_00446b70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00446b70_00446b70() {
    __asm {
    L_00446b70:
        sub esp,10Ch
    L_00446b76:
        mov eax,dword ptr [data_00473660]
    L_00446b7b:
        xor eax,esp
    L_00446b7d:
        push ebx
    L_00446b7e:
        mov dword ptr [esp+10Ch],eax
    L_00446b85:
        mov eax,dword ptr [esp+114h]
    L_00446b8c:
        mov ebx,ecx
    L_00446b8e:
        test byte ptr [data_00491d78],1
    L_00446b95:
        mov dword ptr [esp+4],eax
    L_00446b99:
        mov eax,dword ptr [esp+118h]
    L_00446ba0:
        push edi
    L_00446ba1:
        je short L_00446bc4
    L_00446ba3:
        mov ecx,dword ptr [ebx*4+46F288h]
    L_00446baa:
        cmp ecx,15h
    L_00446bad:
        je short L_00446bbf
    L_00446baf:
        test ecx,ecx
    L_00446bb1:
        je short L_00446bbf
    L_00446bb3:
        cmp ecx,14h
    L_00446bb6:
        jne short L_00446bc4
    L_00446bb8:
        mov ebx,3
    L_00446bbd:
        jmp short L_00446bc4
    L_00446bbf:
        mov ebx,5
    L_00446bc4:
        push eax
    L_00446bc5:
        lea ecx,[esp+10h]
    L_00446bc9:
        push 46E1C8h
    L_00446bce:
        push ecx
    L_00446bcf:
        call asm_sprintf_00452ae8
    L_00446bd4:
        add esp,0Ch
    L_00446bd7:
        push 1
    L_00446bd9:
        lea edx,[esp+0Ch]
    L_00446bdd:
        push edx
    L_00446bde:
        lea eax,[esp+14h]
    L_00446be2:
        call asm_FUN_0044b360_0044b360
    L_00446be7:
        mov edi,eax
    L_00446be9:
        test edi,edi
    L_00446beb:
        je short L_00446c31
    L_00446bed:
        mov ecx,dword ptr [esp+120h]
    L_00446bf4:
        mov eax,dword ptr [esp+8]
    L_00446bf8:
        push esi
    L_00446bf9:
        push 0
    L_00446bfb:
        push 0
    L_00446bfd:
        push ecx
    L_00446bfe:
        push 0FFFFFFFFh
    L_00446c00:
        push 3
    L_00446c02:
        push 1
    L_00446c04:
        mov dword ptr [esi+8],eax
    L_00446c07:
        mov edx,dword ptr [ebx*4+46F288h]
    L_00446c0e:
        push edx
    L_00446c0f:
        push 0
    L_00446c11:
        push 0
    L_00446c13:
        push 0
    L_00446c15:
        push 0
    L_00446c17:
        push eax
    L_00446c18:
        mov eax,dword ptr [data_00491c30]
    L_00446c1d:
        push edi
    L_00446c1e:
        push eax
    L_00446c1f:
        call asm_D3DXCreateTextureFromFileInMemoryEx_004521ca
    L_00446c24:
        test eax,eax
    L_00446c26:
        je short L_00446c36
    L_00446c28:
        push edi
    L_00446c29:
        call asm_free_00452422
    L_00446c2e:
        add esp,4
    L_00446c31:
        or eax,0FFFFFFFFh
    L_00446c34:
        jmp short L_00446c4c
    L_00446c36:
        mov eax,esi
    L_00446c38:
        call asm_FUN_004465b0_004465b0
    L_00446c3d:
        mov ecx,dword ptr [ebx*4+46F2A0h]
    L_00446c44:
        mov dword ptr [esi+0Ch],ecx
    L_00446c47:
        mov dword ptr [esi+4],edi
    L_00446c4a:
        xor eax,eax
    L_00446c4c:
        mov ecx,dword ptr [esp+110h]
    L_00446c53:
        pop edi
    L_00446c54:
        pop ebx
    L_00446c55:
        xor ecx,esp
    L_00446c57:
        call asm_security_check_cookie_00458ea5
    L_00446c5c:
        add esp,10Ch
    L_00446c62:
        ret 0Ch
    }
}

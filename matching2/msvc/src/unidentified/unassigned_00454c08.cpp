#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454C08..0x00454CF5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00454c08() {
    __asm {
    L_00454c08:
        push esi
    L_00454c09:
        inc ebx
    L_00454c0a:
        xor dh,byte ptr [eax]
    L_00454c0c:
        pop eax
    L_00454c0d:
        inc ebx
    L_00454c0e:
        xor byte ptr [eax],dh
    L_00454c10:
        push ebp
    L_00454c11:
        mov ebp,esp
    L_00454c13:
        sub esp,8
    L_00454c16:
        push ebx
    L_00454c17:
        push esi
    L_00454c18:
        push edi
    L_00454c19:
        push ebp
    L_00454c1a:
        cld
    L_00454c1b:
        mov ebx,dword ptr [ebp+0Ch]
    L_00454c1e:
        mov eax,dword ptr [ebp+8]
    L_00454c21:
        test dword ptr [eax+4],6
    L_00454c28:
        jne asm_target_00454cd9
    L_00454c2e:
        mov dword ptr [ebp-8],eax
    L_00454c31:
        mov eax,dword ptr [ebp+10h]
    L_00454c34:
        mov dword ptr [ebp-4],eax
    L_00454c37:
        lea eax,[ebp-8]
    L_00454c3a:
        mov dword ptr [ebx-4],eax
    L_00454c3d:
        mov esi,dword ptr [ebx+0Ch]
    L_00454c40:
        mov edi,dword ptr [ebx+8]
    L_00454c43:
        push ebx
    L_00454c44:
        call asm_ValidateEH3RN_0045998a
    L_00454c49:
        add esp,4
    L_00454c4c:
        or eax,eax
    L_00454c4e:
        je short L_00454ccb
    L_00454c50:
        cmp esi,0FFFFFFFFh
    L_00454c53:
        je short L_00454cd2
    L_00454c55:
        lea ecx,[esi+esi*2]
    L_00454c58:
        mov eax,dword ptr [edi+ecx*4+4]
    L_00454c5c:
        or eax,eax
    L_00454c5e:
        je short L_00454cb9
    L_00454c60:
        push esi
    L_00454c61:
        push ebp
    L_00454c62:
        lea ebp,[ebx+10h]
    L_00454c65:
        xor ebx,ebx
    L_00454c67:
        xor ecx,ecx
    L_00454c69:
        xor edx,edx
    L_00454c6b:
        xor esi,esi
    L_00454c6d:
        xor edi,edi
    L_00454c6f:
        call eax
    L_00454c71:
        pop ebp
    L_00454c72:
        pop esi
    L_00454c73:
        mov ebx,dword ptr [ebp+0Ch]
    L_00454c76:
        or eax,eax
    L_00454c78:
        je short L_00454cb9
    L_00454c7a:
        js short L_00454cc4
    L_00454c7c:
        mov edi,dword ptr [ebx+8]
    L_00454c7f:
        push ebx
    L_00454c80:
        call asm_global_unwind2_0045989c
    L_00454c85:
        add esp,4
    L_00454c88:
        lea ebp,[ebx+10h]
    L_00454c8b:
        push esi
    L_00454c8c:
        push ebx
    L_00454c8d:
        call asm_local_unwind2_004598de
    L_00454c92:
        add esp,8
    L_00454c95:
        lea ecx,[esi+esi*2]
    L_00454c98:
        push 1
    L_00454c9a:
        mov eax,dword ptr [edi+ecx*4+8]
    L_00454c9e:
        call asm_FUN_00459972_00459972
    L_00454ca3:
        mov eax,dword ptr [edi+ecx*4]
    L_00454ca6:
        mov dword ptr [ebx+0Ch],eax
    L_00454ca9:
        mov eax,dword ptr [edi+ecx*4+8]
    L_00454cad:
        xor ebx,ebx
    L_00454caf:
        xor ecx,ecx
    L_00454cb1:
        xor edx,edx
    L_00454cb3:
        xor esi,esi
    L_00454cb5:
        xor edi,edi
    L_00454cb7:
        call eax
    L_00454cb9:
        mov edi,dword ptr [ebx+8]
    L_00454cbc:
        lea ecx,[esi+esi*2]
    L_00454cbf:
        mov esi,dword ptr [edi+ecx*4]
    L_00454cc2:
        jmp short L_00454c50
    L_00454cc4:
        mov eax,0
    L_00454cc9:
        jmp short L_00454cee
    L_00454ccb:
        mov eax,dword ptr [ebp+8]
    L_00454cce:
        or dword ptr [eax+4],8
    L_00454cd2:
        mov eax,1
    L_00454cd7:
        jmp short L_00454cee
    L_00454cd9:
        push ebp
    L_00454cda:
        lea ebp,[ebx+10h]
    L_00454cdd:
        push 0FFFFFFFFh
    L_00454cdf:
        push ebx
    L_00454ce0:
        call asm_local_unwind2_004598de
    L_00454ce5:
        add esp,8
    L_00454ce8:
        pop ebp
    L_00454ce9:
        mov eax,1
    L_00454cee:
        pop ebp
    L_00454cef:
        pop edi
    L_00454cf0:
        pop esi
    L_00454cf1:
        pop ebx
    L_00454cf2:
        mov esp,ebp
    L_00454cf4:
        pop ebp
    L_00454cf5:
        ret
    }
}

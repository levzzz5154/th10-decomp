#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420DD0..0x00420E9C: VersionList_MatchRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_VersionList_MatchRetail_00420dd0() {
    __asm {
    L_00420dd0:
        sub esp,8
    L_00420dd3:
        push ebx
    L_00420dd4:
        mov ebx,dword ptr [eax+764h]
    L_00420dda:
        test ebx,ebx
    L_00420ddc:
        jne short L_00420de7
    L_00420dde:
        xor eax,eax
    L_00420de0:
        pop ebx
    L_00420de1:
        add esp,8
    L_00420de4:
        ret 0Ch
    L_00420de7:
        push ebp
    L_00420de8:
        mov ebp,dword ptr [eax+760h]
    L_00420dee:
        mov eax,dword ptr [esp+14h]
    L_00420df2:
        push 5
    L_00420df4:
        push 46DCA4h
    L_00420df9:
        push eax
    L_00420dfa:
        call asm_strncmp_00452f80
    L_00420dff:
        add esp,0Ch
    L_00420e02:
        test eax,eax
    L_00420e04:
        jne short L_00420e0e
    L_00420e06:
        pop ebp
    L_00420e07:
        pop ebx
    L_00420e08:
        add esp,8
    L_00420e0b:
        ret 0Ch
    L_00420e0e:
        push esi
    L_00420e0f:
        push edi
    L_00420e10:
        mov edi,46DCA4h
    L_00420e15:
        mov esi,46DC9Ch
    L_00420e1a:
        mov ecx,6
    L_00420e1f:
        xor edx,edx
    L_00420e21:
        repe cmpsb
    L_00420e23:
        jne short L_00420e31
    L_00420e25:
        pop edi
    L_00420e26:
        pop esi
    L_00420e27:
        pop ebp
    L_00420e28:
        xor eax,eax
    L_00420e2a:
        pop ebx
    L_00420e2b:
        add esp,8
    L_00420e2e:
        ret 0Ch
    L_00420e31:
        test ebp,ebp
    L_00420e33:
        jbe short L_00420e90
    L_00420e35:
        mov eax,dword ptr [esp+1Ch]
    L_00420e39:
        push 5
    L_00420e3b:
        push ebx
    L_00420e3c:
        push eax
    L_00420e3d:
        call asm_strncmp_00452f80
    L_00420e42:
        add esp,0Ch
    L_00420e45:
        test eax,eax
    L_00420e47:
        jne short L_00420e7a
    L_00420e49:
        lea ecx,[esp+14h]
    L_00420e4d:
        push ecx
    L_00420e4e:
        lea edx,[esp+14h]
    L_00420e52:
        push edx
    L_00420e53:
        add ebx,6
    L_00420e56:
        push 46DC94h
    L_00420e5b:
        push ebx
    L_00420e5c:
        call asm_sscanf_00452fb9
    L_00420e61:
        mov eax,dword ptr [esp+30h]
    L_00420e65:
        mov ecx,dword ptr [esp+20h]
    L_00420e69:
        add esp,10h
    L_00420e6c:
        cmp ecx,eax
    L_00420e6e:
        jne short L_00420e7a
    L_00420e70:
        mov ecx,dword ptr [esp+24h]
    L_00420e74:
        cmp dword ptr [esp+14h],ecx
    L_00420e78:
        je short L_00420e25
    L_00420e7a:
        push 0Ah
    L_00420e7c:
        push ebx
    L_00420e7d:
        mov esi,ebx
    L_00420e7f:
        call asm_FUN_00452730_00452730
    L_00420e84:
        add esp,8
    L_00420e87:
        inc eax
    L_00420e88:
        mov ebx,eax
    L_00420e8a:
        sub esi,ebx
    L_00420e8c:
        add ebp,esi
    L_00420e8e:
        jne short L_00420e35
    L_00420e90:
        pop edi
    L_00420e91:
        pop esi
    L_00420e92:
        pop ebp
    L_00420e93:
        or eax,0FFFFFFFFh
    L_00420e96:
        pop ebx
    L_00420e97:
        add esp,8
    L_00420e9a:
        ret 0Ch
    }
}

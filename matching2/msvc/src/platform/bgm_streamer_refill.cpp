#include "asm_encoding.hpp"
#include "asm_symbols.hpp"


// 0x0044D9F0..0x0044DACC: FUN_0044d850
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044d850_part_0044d9f0() {
    __asm {
    L_0044d9f0:
        mov esi,dword ptr [ebp+0Ch]
    L_0044d9f3:
        mov al,1
    L_0044d9f5:
        call asm_ArchiveCursor_SeekRetail_0044dd40
    L_0044d9fa:
        test eax,eax
    L_0044d9fc:
        jl asm_target_0044d8d7
    L_0044da02:
        mov ecx,dword ptr [esp+10h]
    L_0044da06:
        mov edx,dword ptr [esp+30h]
    L_0044da0a:
        lea eax,[esp+14h]
    L_0044da0e:
        push eax
    L_0044da0f:
        lea eax,[edi+ecx]
    L_0044da12:
        push eax
    L_0044da13:
        mov eax,dword ptr [ebp+0Ch]
    L_0044da16:
        sub edx,edi
    L_0044da18:
        call asm_ArchiveCursor_ReadRetail_0044de10
    L_0044da1d:
        test eax,eax
    L_0044da1f:
        jl asm_target_0044d8d7
    L_0044da25:
        mov ecx,dword ptr [esp+14h]
    L_0044da29:
        mov eax,dword ptr [esp+30h]
    L_0044da2d:
        add edi,ecx
    L_0044da2f:
        cmp edi,eax
    L_0044da31:
        jb short L_0044d9f0
    L_0044da33:
        mov ecx,dword ptr [ebp+4]
    L_0044da36:
        mov eax,dword ptr [ecx]
    L_0044da38:
        mov ecx,dword ptr [esp+30h]
    L_0044da3c:
        mov edx,dword ptr [eax]
    L_0044da3e:
        push 0
    L_0044da40:
        push 0
    L_0044da42:
        push ecx
    L_0044da43:
        mov ecx,dword ptr [esp+1Ch]
    L_0044da47:
        push ecx
    L_0044da48:
        push eax
    L_0044da49:
        call dword ptr [edx+4Ch]
    L_0044da4c:
        mov edx,dword ptr [ebp+4]
    L_0044da4f:
        mov eax,dword ptr [edx]
    L_0044da51:
        mov ecx,dword ptr [eax]
    L_0044da53:
        push 0
    L_0044da55:
        lea edx,[esp+24h]
    L_0044da59:
        push edx
    L_0044da5a:
        push eax
    L_0044da5b:
        call dword ptr [ecx+10h]
    L_0044da5e:
        test eax,eax
    L_0044da60:
        jl asm_target_0044d8d7
    L_0044da66:
        mov edx,dword ptr [ebp+5Ch]
    L_0044da69:
        mov ecx,dword ptr [esp+20h]
    L_0044da6d:
        cmp ecx,edx
    L_0044da6f:
        jae short L_0044da7a
    L_0044da71:
        mov eax,dword ptr [ebp+8]
    L_0044da74:
        sub eax,edx
    L_0044da76:
        add eax,ecx
    L_0044da78:
        jmp short L_0044da7e
    L_0044da7a:
        mov eax,ecx
    L_0044da7c:
        sub eax,edx
    L_0044da7e:
        mov edx,dword ptr [ebp+60h]
    L_0044da81:
        add edx,eax
    L_0044da83:
        mov dword ptr [ebp+5Ch],ecx
    L_0044da86:
        mov ecx,dword ptr [ebp+68h]
    L_0044da89:
        test ecx,ecx
    L_0044da8b:
        mov dword ptr [ebp+60h],edx
    L_0044da8e:
        mov eax,edx
    L_0044da90:
        je short L_0044daa5
    L_0044da92:
        mov ecx,dword ptr [ebp+0Ch]
    L_0044da95:
        cmp eax,dword ptr [ecx+2Ch]
    L_0044da98:
        jb short L_0044daa5
    L_0044da9a:
        mov edx,dword ptr [ebp+4]
    L_0044da9d:
        mov eax,dword ptr [edx]
    L_0044da9f:
        mov ecx,dword ptr [eax]
    L_0044daa1:
        push eax
    L_0044daa2:
        call dword ptr [ecx+48h]
    L_0044daa5:
        mov eax,dword ptr [ebp+64h]
    L_0044daa8:
        add eax,dword ptr [esp+30h]
    L_0044daac:
        xor edx,edx
    L_0044daae:
        div dword ptr [ebp+8]
    L_0044dab1:
        pop esi
    L_0044dab2:
        pop ebx
    L_0044dab3:
        pop edi
    L_0044dab4:
        xor eax,eax
    L_0044dab6:
        mov dword ptr [ebp+64h],edx
    L_0044dab9:
        pop ebp
    L_0044daba:
        add esp,1Ch
    L_0044dabd:
        ret 8
    L_0044dac0:
        pop edi
    L_0044dac1:
        mov eax,800401F0h
    L_0044dac6:
        pop ebp
    L_0044dac7:
        add esp,1Ch
    L_0044daca:
        ret 8
    }
}

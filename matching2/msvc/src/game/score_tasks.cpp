#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED: closest_byte_count=13/289; first_diff=0x00413A26;
// residual_class=private cached-resource/string-copy ABI (FUN_0044b360 consumes
// EAX/ESI/EDI) plus MSVC local-layout and stdcall tail scheduling;
// variants_tested=live Ghidra decompile/callers (0x00413A20, 0x00413980,
// 0x00417870) and MSVC 13.10 readable struct/resource-load/copy-loop candidate
// (300-byte extent, 13 matching bytes); next_lever=schema2 native-LTCG over
// the real callers with 0x00447280 and 0x0044B360 visible.

// 0x00413A20..0x00413B40: FUN_00413a20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413a20_00413a20() {
    __asm {
    L_00413a20:
        mov eax,dword ptr [data_00477848]
    L_00413a25:
        mov ecx,dword ptr [eax+20h]
    L_00413a28:
        mov edx,dword ptr [data_00491c10]
    L_00413a2e:
        push ebx
    L_00413a2f:
        push ebp
    L_00413a30:
        mov ebp,dword ptr [esp+0Ch]
    L_00413a34:
        push ecx
    L_00413a35:
        mov ecx,1Ch
    L_00413a3a:
        call asm_Recovery_LoadCachedResource_00447280
    L_00413a3f:
        xor ebx,ebx
    L_00413a41:
        cmp eax,ebx
    L_00413a43:
        mov dword ptr [ebp+9E80h],eax
    L_00413a49:
        je asm_target_00413b27
    L_00413a4f:
        mov eax,dword ptr [data_00491be8]
    L_00413a54:
        cmp eax,ebx
    L_00413a56:
        je short L_00413acb
    L_00413a58:
        mov dword ptr [ebp+9EBCh],eax
    L_00413a5e:
        mov dword ptr [data_00491be8],ebx
    L_00413a64:
        mov eax,dword ptr [ebp+9E70h]
    L_00413a6a:
        test al,1
    L_00413a6c:
        jne short L_00413a97
    L_00413a6e:
        or eax,1
    L_00413a71:
        mov dword ptr [ebp+9E64h],ebx
    L_00413a77:
        mov dword ptr [ebp+9E60h],0FFF0BDC1h
    L_00413a81:
        mov dword ptr [ebp+9E68h],ebx
    L_00413a87:
        mov dword ptr [ebp+9E6Ch],476F78h
    L_00413a91:
        mov dword ptr [ebp+9E70h],eax
    L_00413a97:
        mov dword ptr [ebp+9E64h],ebx
    L_00413a9d:
        mov dword ptr [ebp+9E68h],ebx
    L_00413aa3:
        or eax,0FFFFFFFFh
    L_00413aa6:
        mov dword ptr [ebp+9E60h],eax
    L_00413aac:
        mov ecx,dword ptr [data_00474c44]
    L_00413ab2:
        mov dword ptr [ebp+9EC0h],eax
    L_00413ab8:
        mov dword ptr [ebp+9EC4h],eax
    L_00413abe:
        mov dword ptr [ebp+9E78h],ecx
    L_00413ac4:
        pop ebp
    L_00413ac5:
        xor eax,eax
    L_00413ac7:
        pop ebx
    L_00413ac8:
        ret 4
    L_00413acb:
        mov edx,dword ptr [data_00477848]
    L_00413ad1:
        mov eax,dword ptr [data_00474c68]
    L_00413ad6:
        mov eax,dword ptr [edx+eax*4+18h]
    L_00413ada:
        mov byte ptr [data_00497c38],bl
    L_00413ae0:
        mov ecx,eax
    L_00413ae2:
        mov dl,byte ptr [eax]
    L_00413ae4:
        inc eax
    L_00413ae5:
        cmp dl,bl
    L_00413ae7:
        jne short L_00413ae2
    L_00413ae9:
        push esi
    L_00413aea:
        push edi
    L_00413aeb:
        mov edi,497C38h
    L_00413af0:
        sub eax,ecx
    L_00413af2:
        mov esi,ecx
    L_00413af4:
        dec edi
    L_00413af5:
        mov cl,byte ptr [edi+1]
    L_00413af8:
        inc edi
    L_00413af9:
        cmp cl,bl
    L_00413afb:
        jne short L_00413af5
    L_00413afd:
        mov ecx,eax
    L_00413aff:
        shr ecx,2
    L_00413b02:
        rep movsd
    L_00413b04:
        mov ecx,eax
    L_00413b06:
        push ebx
    L_00413b07:
        and ecx,3
    L_00413b0a:
        push ebx
    L_00413b0b:
        mov eax,497C38h
    L_00413b10:
        rep movsb
    L_00413b12:
        call asm_FUN_0044b360_0044b360
    L_00413b17:
        cmp eax,ebx
    L_00413b19:
        pop edi
    L_00413b1a:
        mov dword ptr [ebp+9EBCh],eax
    L_00413b20:
        pop esi
    L_00413b21:
        jne asm_target_00413a64
    L_00413b27:
        push 46CB68h
    L_00413b2c:
        mov ecx,474F70h
    L_00413b31:
        call asm_TextLog_Append_0044b810
    L_00413b36:
        add esp,4
    L_00413b39:
        pop ebp
    L_00413b3a:
        or eax,0FFFFFFFFh
    L_00413b3d:
        pop ebx
    L_00413b3e:
        ret 4
    }
}



#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043AAD0..0x0043AC8F: FUN_0043aad0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043aad0_0043aad0() {
    __asm {
    L_0043aad0:
        sub esp,18h
    L_0043aad3:
        mov eax,dword ptr [data_00473660]
    L_0043aad8:
        xor eax,esp
    L_0043aada:
        push ebp
    L_0043aadb:
        push esi
    L_0043aadc:
        mov esi,ebx
    L_0043aade:
        mov dword ptr [esp+1Ch],eax
    L_0043aae2:
        call asm_FUN_0043aa60_0043aa60
    L_0043aae7:
        mov eax,dword ptr [esp+24h]
    L_0043aaeb:
        mov ebp,dword ptr [ebx+eax*4+98h]
    L_0043aaf2:
        test ebp,ebp
    L_0043aaf4:
        jne short L_0043ab0c
    L_0043aaf6:
        pop esi
    L_0043aaf7:
        or eax,0FFFFFFFFh
    L_0043aafa:
        pop ebp
    L_0043aafb:
        mov ecx,dword ptr [esp+14h]
    L_0043aaff:
        xor ecx,esp
    L_0043ab01:
        call asm_security_check_cookie_00458ea5
    L_0043ab06:
        add esp,18h
    L_0043ab09:
        ret 4
    L_0043ab0c:
        mov eax,dword ptr [ebp+4]
    L_0043ab0f:
        mov ecx,dword ptr [ebp]
    L_0043ab12:
        mov dword ptr [esp+14h],ecx
    L_0043ab16:
        mov edx,eax
    L_0043ab18:
        mov ecx,eax
    L_0043ab1a:
        mov byte ptr [esp+0Ah],ah
    L_0043ab1e:
        mov byte ptr [esp+0Bh],al
    L_0043ab22:
        mov dword ptr [esp+18h],eax
    L_0043ab26:
        shr ecx,10h
    L_0043ab29:
        mov byte ptr [esp+9],cl
    L_0043ab2d:
        add ebp,8
    L_0043ab30:
        mov eax,ebp
    L_0043ab32:
        mov cx,word ptr [eax]
    L_0043ab35:
        shr edx,18h
    L_0043ab38:
        mov byte ptr [esp+8],dl
    L_0043ab3c:
        push edi
    L_0043ab3d:
        mov edi,dword ptr [esp+0Ch]
    L_0043ab41:
        mov byte ptr [esp+0Ch],ch
    L_0043ab45:
        mov byte ptr [esp+0Dh],cl
    L_0043ab49:
        movzx edx,word ptr [esp+0Ch]
    L_0043ab4e:
        mov dword ptr [ebx+11Ch],edx
    L_0043ab54:
        mov cx,word ptr [eax+4]
    L_0043ab58:
        mov byte ptr [esp+0Ch],ch
    L_0043ab5c:
        mov byte ptr [esp+0Dh],cl
    L_0043ab60:
        movzx ecx,word ptr [esp+0Ch]
    L_0043ab65:
        mov dword ptr [ebx+120h],ecx
    L_0043ab6b:
        mov ax,word ptr [eax+2]
    L_0043ab6f:
        mov byte ptr [esp+0Ch],ah
    L_0043ab73:
        mov byte ptr [esp+0Dh],al
    L_0043ab77:
        movzx eax,word ptr [esp+0Ch]
    L_0043ab7c:
        mov dword ptr [ebx+118h],eax
    L_0043ab82:
        shl eax,5
    L_0043ab85:
        push eax
    L_0043ab86:
        add ebp,edi
    L_0043ab88:
        call asm_malloc_00452706
    L_0043ab8d:
        mov ecx,dword ptr [ebx+118h]
    L_0043ab93:
        shl ecx,5
    L_0043ab96:
        mov edx,ecx
    L_0043ab98:
        mov edi,eax
    L_0043ab9a:
        shr ecx,2
    L_0043ab9d:
        xor eax,eax
    L_0043ab9f:
        mov dword ptr [ebx+138h],edi
    L_0043aba5:
        rep stosd
    L_0043aba7:
        mov ecx,edx
    L_0043aba9:
        and ecx,3
    L_0043abac:
        rep stosb
    L_0043abae:
        mov eax,dword ptr [ebx+118h]
    L_0043abb4:
        add esp,4
    L_0043abb7:
        test eax,eax
    L_0043abb9:
        mov dword ptr [esp+18h],0
    L_0043abc1:
        jle asm_target_0043ac69
    L_0043abc7:
        xor edi,edi
    L_0043abc9:
        mov dword ptr [esp+10h],edi
    L_0043abcd:
        jmp short L_0043abd3
    L_0043abcf:
        mov edi,dword ptr [esp+10h]
    L_0043abd3:
        mov eax,ebp
    L_0043abd5:
        mov eax,dword ptr [eax+4]
    L_0043abd8:
        mov ecx,eax
    L_0043abda:
        mov edx,eax
    L_0043abdc:
        shr ecx,18h
    L_0043abdf:
        shr edx,10h
    L_0043abe2:
        mov byte ptr [esp+0Eh],ah
    L_0043abe6:
        mov byte ptr [esp+0Fh],al
    L_0043abea:
        mov byte ptr [esp+0Ch],cl
    L_0043abee:
        mov byte ptr [esp+0Dh],dl
    L_0043abf2:
        mov esi,dword ptr [esp+0Ch]
    L_0043abf6:
        mov dword ptr [esp+14h],eax
    L_0043abfa:
        mov eax,dword ptr [ebx+138h]
    L_0043ac00:
        push esi
    L_0043ac01:
        add ebp,8
    L_0043ac04:
        mov dword ptr [edi+eax+8],esi
    L_0043ac08:
        call asm_malloc_00452706
    L_0043ac0d:
        mov ecx,dword ptr [ebx+138h]
    L_0043ac13:
        mov dword ptr [edi+ecx+10h],eax
    L_0043ac17:
        mov edx,dword ptr [ebx+138h]
    L_0043ac1d:
        mov dword ptr [edi+edx],1
    L_0043ac24:
        mov eax,dword ptr [ebx+138h]
    L_0043ac2a:
        mov edi,dword ptr [edi+eax+10h]
    L_0043ac2e:
        mov eax,dword ptr [esp+1Ch]
    L_0043ac32:
        mov ecx,esi
    L_0043ac34:
        mov edx,ecx
    L_0043ac36:
        shr ecx,2
    L_0043ac39:
        mov esi,ebp
    L_0043ac3b:
        rep movsd
    L_0043ac3d:
        mov ecx,edx
    L_0043ac3f:
        and ecx,3
    L_0043ac42:
        rep movsb
    L_0043ac44:
        mov ecx,dword ptr [ebx+118h]
    L_0043ac4a:
        mov edi,edx
    L_0043ac4c:
        mov edx,dword ptr [esp+14h]
    L_0043ac50:
        add esp,4
    L_0043ac53:
        add ebp,edi
    L_0043ac55:
        inc eax
    L_0043ac56:
        add edx,20h
    L_0043ac59:
        cmp eax,ecx
    L_0043ac5b:
        mov dword ptr [esp+18h],eax
    L_0043ac5f:
        mov dword ptr [esp+10h],edx
    L_0043ac63:
        jl asm_target_0043abcf
    L_0043ac69:
        mov eax,dword ptr [esp+28h]
    L_0043ac6d:
        mov ecx,dword ptr [esp+20h]
    L_0043ac71:
        pop edi
    L_0043ac72:
        pop esi
    L_0043ac73:
        pop ebp
    L_0043ac74:
        mov dword ptr [ebx+10h],eax
    L_0043ac77:
        xor ecx,esp
    L_0043ac79:
        mov dword ptr [ebx+124h],0F4240h
    L_0043ac83:
        xor eax,eax
    L_0043ac85:
        call asm_security_check_cookie_00458ea5
    L_0043ac8a:
        add esp,18h
    L_0043ac8d:
        ret 4
    }
}

// 0x0043AF30..0x0043B029: FUN_0043af30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043af30_0043af30() {
    __asm {
    L_0043af30:
        sub esp,0Ch
    L_0043af33:
        push ebx
    L_0043af34:
        push ebp
    L_0043af35:
        push esi
    L_0043af36:
        push edi
    L_0043af37:
        mov edi,ecx
    L_0043af39:
        mov ecx,dword ptr [edi+12Ch]
    L_0043af3f:
        mov eax,dword ptr [edi+120h]
    L_0043af45:
        push ecx
    L_0043af46:
        mov ecx,dword ptr [edi+128h]
    L_0043af4c:
        cdq
    L_0043af4d:
        push ecx
    L_0043af4e:
        push edx
    L_0043af4f:
        xor ebp,ebp
    L_0043af51:
        push eax
    L_0043af52:
        mov dword ptr [esp+24h],ebp
    L_0043af56:
        call asm_allmul_00456640
    L_0043af5b:
        push ebp
    L_0043af5c:
        push 3E8h
    L_0043af61:
        push edx
    L_0043af62:
        push eax
    L_0043af63:
        call asm_allmul_00456640
    L_0043af68:
        mov ecx,eax
    L_0043af6a:
        mov eax,dword ptr [edi+124h]
    L_0043af70:
        mov esi,edx
    L_0043af72:
        cdq
    L_0043af73:
        push edx
    L_0043af74:
        push eax
    L_0043af75:
        push esi
    L_0043af76:
        push ecx
    L_0043af77:
        call asm_aulldiv_00456b80
    L_0043af7c:
        mov ecx,dword ptr [edi+134h]
    L_0043af82:
        mov esi,edx
    L_0043af84:
        mov edx,dword ptr [edi+130h]
    L_0043af8a:
        mov ebx,eax
    L_0043af8c:
        mov eax,dword ptr [edi+2E0h]
    L_0043af92:
        add ebx,edx
    L_0043af94:
        adc esi,ecx
    L_0043af96:
        cmp eax,ebp
    L_0043af98:
        je short L_0043b000
    L_0043af9a:
        mov eax,dword ptr [edi+2E8h]
    L_0043afa0:
        mov ecx,dword ptr [edi+2E4h]
    L_0043afa6:
        cmp eax,ecx
    L_0043afa8:
        mov dword ptr [esp+10h],eax
    L_0043afac:
        mov dword ptr [esp+18h],ecx
    L_0043afb0:
        jge asm_target_0043b0fb
    L_0043afb6:
        fild dword ptr [esp+10h]
    L_0043afba:
        fidiv dword ptr [esp+18h]
    L_0043afbe:
        fsubr dword ptr [data_00470afc]
    L_0043afc4:
        fst dword ptr [edi+2C8h]
    L_0043afca:
        fmul dword ptr [data_00470bf4]
    L_0043afd0:
        call asm_FUN_00463b2c_00463b2c
    L_0043afd5:
        cmp eax,dword ptr [edi+2CCh]
    L_0043afdb:
        je short L_0043afe3
    L_0043afdd:
        push ebp
    L_0043afde:
        call asm_FUN_0043b7a0_0043b7a0
    L_0043afe3:
        fld dword ptr [edi+2C8h]
    L_0043afe9:
        fmul dword ptr [data_00470bf4]
    L_0043afef:
        call asm_FUN_00463b2c_00463b2c
    L_0043aff4:
        mov dword ptr [edi+2CCh],eax
    L_0043affa:
        inc dword ptr [edi+2E8h]
    L_0043b000:
        cmp dword ptr [edi+118h],ebp
    L_0043b006:
        mov dword ptr [esp+10h],ebp
    L_0043b00a:
        jle asm_target_0043b0c9
    L_0043b010:
        mov edx,dword ptr [edi+138h]
    L_0043b016:
        cmp dword ptr [edx+ebp],0
    L_0043b01a:
        je asm_target_0043b0ad
    L_0043b020:
        mov dword ptr [esp+14h],1
    L_0043b028:
        TH10_REL8(0xeb, 0x0043b028, VA_asm_FUN_0043af30_part_0043b030)
    }
}

// 0x0043B030..0x0043B108: FUN_0043af30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043af30_part_0043b030() {
    __asm {
    L_0043b030:
        mov eax,dword ptr [edi+138h]
    L_0043b036:
        lea ecx,[eax+ebp]
    L_0043b039:
        mov eax,dword ptr [ecx+4]
    L_0043b03c:
        cdq
    L_0043b03d:
        cmp edx,esi
    L_0043b03f:
        ja short L_0043b0ad
    L_0043b041:
        jb short L_0043b047
    L_0043b043:
        cmp eax,ebx
    L_0043b045:
        ja short L_0043b0ad
    L_0043b047:
        push ecx
    L_0043b048:
        push edi
    L_0043b049:
        call asm_FUN_0043b110_0043b110
    L_0043b04e:
        mov ecx,dword ptr [edi+12Ch]
    L_0043b054:
        mov eax,dword ptr [edi+120h]
    L_0043b05a:
        push ecx
    L_0043b05b:
        mov ecx,dword ptr [edi+128h]
    L_0043b061:
        cdq
    L_0043b062:
        push ecx
    L_0043b063:
        push edx
    L_0043b064:
        push eax
    L_0043b065:
        call asm_allmul_00456640
    L_0043b06a:
        push 0
    L_0043b06c:
        push 3E8h
    L_0043b071:
        push edx
    L_0043b072:
        push eax
    L_0043b073:
        call asm_allmul_00456640
    L_0043b078:
        mov ecx,eax
    L_0043b07a:
        mov eax,dword ptr [edi+124h]
    L_0043b080:
        mov esi,edx
    L_0043b082:
        cdq
    L_0043b083:
        push edx
    L_0043b084:
        push eax
    L_0043b085:
        push esi
    L_0043b086:
        push ecx
    L_0043b087:
        call asm_aulldiv_00456b80
    L_0043b08c:
        mov ecx,dword ptr [edi+134h]
    L_0043b092:
        mov esi,edx
    L_0043b094:
        mov edx,dword ptr [edi+130h]
    L_0043b09a:
        mov ebx,eax
    L_0043b09c:
        add ebx,edx
    L_0043b09e:
        mov edx,dword ptr [edi+138h]
    L_0043b0a4:
        mov eax,dword ptr [edx+ebp]
    L_0043b0a7:
        adc esi,ecx
    L_0043b0a9:
        test eax,eax
    L_0043b0ab:
        jne short L_0043b030
    L_0043b0ad:
        mov eax,dword ptr [esp+10h]
    L_0043b0b1:
        mov ecx,dword ptr [edi+118h]
    L_0043b0b7:
        inc eax
    L_0043b0b8:
        add ebp,20h
    L_0043b0bb:
        cmp eax,ecx
    L_0043b0bd:
        mov dword ptr [esp+10h],eax
    L_0043b0c1:
        jl asm_target_0043b010
    L_0043b0c7:
        xor ebp,ebp
    L_0043b0c9:
        mov edx,dword ptr [edi+128h]
    L_0043b0cf:
        mov ecx,dword ptr [edi+12Ch]
    L_0043b0d5:
        mov eax,dword ptr [esp+14h]
    L_0043b0d9:
        add edx,1
    L_0043b0dc:
        adc ecx,ebp
    L_0043b0de:
        cmp eax,ebp
    L_0043b0e0:
        mov dword ptr [edi+128h],edx
    L_0043b0e6:
        mov dword ptr [edi+12Ch],ecx
    L_0043b0ec:
        jne short L_0043b0f3
    L_0043b0ee:
        call asm_FUN_0043ace0_0043ace0
    L_0043b0f3:
        pop edi
    L_0043b0f4:
        pop esi
    L_0043b0f5:
        pop ebp
    L_0043b0f6:
        pop ebx
    L_0043b0f7:
        add esp,0Ch
    L_0043b0fa:
        ret
    L_0043b0fb:
        mov dword ptr [edi+2C8h],ebp
    L_0043b101:
        pop edi
    L_0043b102:
        pop esi
    L_0043b103:
        pop ebp
    L_0043b104:
        pop ebx
    L_0043b105:
        add esp,0Ch
    L_0043b108:
        ret
    }
}

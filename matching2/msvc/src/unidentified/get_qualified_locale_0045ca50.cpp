#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CA50..0x0045CC04: ___get_qualified_locale
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_get_qualified_locale_0045ca50() {
    __asm {
    L_0045ca50:
        push ebx
    L_0045ca51:
        xor ebx,ebx
    L_0045ca53:
        cmp dword ptr [data_00477648],ebx
    L_0045ca59:
        push esi
    L_0045ca5a:
        jne short L_0045ca7b
    L_0045ca5c:
        cmp dword ptr [data_00477470],2
    L_0045ca63:
        jne short L_0045ca71
    L_0045ca65:
        mov eax,dword ptr [data_0046605c]
    L_0045ca6a:
        mov dword ptr [data_00477648],eax
    L_0045ca6f:
        jmp short L_0045ca7b
    L_0045ca71:
        mov dword ptr [data_00477648],45C40Fh
    L_0045ca7b:
        mov esi,dword ptr [esp+0Ch]
    L_0045ca7f:
        cmp esi,ebx
    L_0045ca81:
        je asm_target_0045cb2a
    L_0045ca87:
        lea eax,[esi+40h]
    L_0045ca8a:
        cmp eax,ebx
    L_0045ca8c:
        mov ecx,esi
    L_0045ca8e:
        mov dword ptr [data_00477644],ecx
    L_0045ca94:
        mov dword ptr [data_0047763c],eax
    L_0045ca99:
        je short L_0045cabe
    L_0045ca9b:
        cmp byte ptr [eax],bl
    L_0045ca9d:
        je short L_0045cabe
    L_0045ca9f:
        push 47763Ch
    L_0045caa4:
        push 16h
    L_0045caa6:
        push 46BD50h
    L_0045caab:
        call asm_TranslateName_0045c2fd
    L_0045cab0:
        mov ecx,dword ptr [data_00477644]
    L_0045cab6:
        mov eax,dword ptr [data_0047763c]
    L_0045cabb:
        add esp,0Ch
    L_0045cabe:
        cmp ecx,ebx
    L_0045cac0:
        mov dword ptr [data_00477628],ebx
    L_0045cac6:
        je short L_0045cb1b
    L_0045cac8:
        cmp byte ptr [ecx],bl
    L_0045caca:
        je short L_0045cb1b
    L_0045cacc:
        cmp eax,ebx
    L_0045cace:
        je short L_0045cadb
    L_0045cad0:
        cmp byte ptr [eax],bl
    L_0045cad2:
        je short L_0045cadb
    L_0045cad4:
        call asm_GetLcidFromLangCountry_0045c975
    L_0045cad9:
        jmp short L_0045cae0
    L_0045cadb:
        call asm_GetLcidFromLanguage_0045c9fb
    L_0045cae0:
        cmp dword ptr [data_00477628],ebx
    L_0045cae6:
        jne short L_0045cb3e
    L_0045cae8:
        push 477644h
    L_0045caed:
        push 40h
    L_0045caef:
        push 46BF00h
    L_0045caf4:
        call asm_TranslateName_0045c2fd
    L_0045caf9:
        add esp,0Ch
    L_0045cafc:
        test eax,eax
    L_0045cafe:
        je short L_0045cb2f
    L_0045cb00:
        mov eax,dword ptr [data_0047763c]
    L_0045cb05:
        cmp eax,ebx
    L_0045cb07:
        je short L_0045cb14
    L_0045cb09:
        cmp byte ptr [eax],bl
    L_0045cb0b:
        je short L_0045cb14
    L_0045cb0d:
        call asm_GetLcidFromLangCountry_0045c975
    L_0045cb12:
        jmp short L_0045cb2f
    L_0045cb14:
        call asm_GetLcidFromLanguage_0045c9fb
    L_0045cb19:
        jmp short L_0045cb2f
    L_0045cb1b:
        cmp eax,ebx
    L_0045cb1d:
        je short L_0045cb2a
    L_0045cb1f:
        cmp byte ptr [eax],bl
    L_0045cb21:
        je short L_0045cb2a
    L_0045cb23:
        call asm_GetLcidFromCountry_0045c93e
    L_0045cb28:
        jmp short L_0045cb2f
    L_0045cb2a:
        call asm_GetLcidFromDefault_0045c35d
    L_0045cb2f:
        cmp dword ptr [data_00477628],ebx
    L_0045cb35:
        jne short L_0045cb3e
    L_0045cb37:
        xor eax,eax
    L_0045cb39:
        jmp asm_target_0045cc02
    L_0045cb3e:
        push edi
    L_0045cb3f:
        lea ecx,[esi+80h]
    L_0045cb45:
        call asm_FUN_0045c377_0045c377
    L_0045cb4a:
        mov edi,eax
    L_0045cb4c:
        cmp edi,ebx
    L_0045cb4e:
        je asm_target_0045cbff
    L_0045cb54:
        movzx eax,di
    L_0045cb57:
        push eax
    L_0045cb58:
        call dword ptr [data_00466050]
    L_0045cb5e:
        test eax,eax
    L_0045cb60:
        je asm_target_0045cbff
    L_0045cb66:
        push 1
    L_0045cb68:
        push dword ptr [data_0047762c]
    L_0045cb6e:
        call dword ptr [data_00466054]
    L_0045cb74:
        test eax,eax
    L_0045cb76:
        je asm_target_0045cbff
    L_0045cb7c:
        mov eax,dword ptr [esp+14h]
    L_0045cb80:
        cmp eax,ebx
    L_0045cb82:
        mov ecx,dword ptr [data_0047762c]
    L_0045cb88:
        je short L_0045cb9c
    L_0045cb8a:
        mov dx,word ptr [data_00477630]
    L_0045cb91:
        mov word ptr [eax],cx
    L_0045cb94:
        mov word ptr [eax+2],dx
    L_0045cb98:
        mov word ptr [eax+4],di
    L_0045cb9c:
        mov esi,dword ptr [esp+18h]
    L_0045cba0:
        cmp esi,ebx
    L_0045cba2:
        je short L_0045cbfa
    L_0045cba4:
        cmp word ptr [eax],814h
    L_0045cba9:
        jne short L_0045cbba
    L_0045cbab:
        push 46C524h
    L_0045cbb0:
        push esi
    L_0045cbb1:
        call asm_FUN_0045bd80_0045bd80
    L_0045cbb6:
        pop ecx
    L_0045cbb7:
        pop ecx
    L_0045cbb8:
        jmp short L_0045cbcd
    L_0045cbba:
        push 40h
    L_0045cbbc:
        push esi
    L_0045cbbd:
        push 1001h
    L_0045cbc2:
        push ecx
    L_0045cbc3:
        call dword ptr [data_00477648]
    L_0045cbc9:
        test eax,eax
    L_0045cbcb:
        je short L_0045cbff
    L_0045cbcd:
        push 40h
    L_0045cbcf:
        lea eax,[esi+40h]
    L_0045cbd2:
        push eax
    L_0045cbd3:
        push 1002h
    L_0045cbd8:
        push dword ptr [data_00477630]
    L_0045cbde:
        call dword ptr [data_00477648]
    L_0045cbe4:
        test eax,eax
    L_0045cbe6:
        je short L_0045cbff
    L_0045cbe8:
        push 0Ah
    L_0045cbea:
        add esi,80h
    L_0045cbf0:
        push esi
    L_0045cbf1:
        push edi
    L_0045cbf2:
        call asm_itoa_00460674
    L_0045cbf7:
        add esp,0Ch
    L_0045cbfa:
        xor eax,eax
    L_0045cbfc:
        inc eax
    L_0045cbfd:
        jmp short L_0045cc01
    L_0045cbff:
        xor eax,eax
    L_0045cc01:
        pop edi
    L_0045cc02:
        pop esi
    L_0045cc03:
        pop ebx
    L_0045cc04:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043CD30..0x0043CF56: FUN_0043cd30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043cd30_0043cd30() {
    __asm {
    L_0043cd30:
        sub esp,4Ch
    L_0043cd33:
        mov eax,dword ptr [data_00473660]
    L_0043cd38:
        xor eax,esp
    L_0043cd3a:
        mov dword ptr [esp+48h],eax
    L_0043cd3e:
        or eax,0FFFFFFFFh
    L_0043cd41:
        push ebp
    L_0043cd42:
        push esi
    L_0043cd43:
        mov esi,ecx
    L_0043cd45:
        mov ebp,dword ptr [esp+58h]
    L_0043cd49:
        push edi
    L_0043cd4a:
        lea edi,[esi+408h]
    L_0043cd50:
        mov ecx,80h
    L_0043cd55:
        rep stosd
    L_0043cd57:
        or eax,0FFFFFFFFh
    L_0043cd5a:
        mov dword ptr [esi+620h],eax
    L_0043cd60:
        mov dword ptr [esi+624h],eax
    L_0043cd66:
        mov dword ptr [esi+628h],eax
    L_0043cd6c:
        mov dword ptr [esi+62Ch],eax
    L_0043cd72:
        mov dword ptr [esi+630h],eax
    L_0043cd78:
        mov dword ptr [esi+634h],eax
    L_0043cd7e:
        mov dword ptr [esi+638h],eax
    L_0043cd84:
        mov dword ptr [esi+63Ch],eax
    L_0043cd8a:
        mov dword ptr [esi+640h],eax
    L_0043cd90:
        mov dword ptr [esi+644h],eax
    L_0043cd96:
        mov dword ptr [esi+648h],eax
    L_0043cd9c:
        push 4
    L_0043cd9e:
        mov dword ptr [esi+64Ch],eax
    L_0043cda4:
        call asm_operator_new_00452493
    L_0043cda9:
        add esp,4
    L_0043cdac:
        test eax,eax
    L_0043cdae:
        je short L_0043cdba
    L_0043cdb0:
        mov dword ptr [eax],0
    L_0043cdb6:
        mov edi,eax
    L_0043cdb8:
        jmp short L_0043cdbc
    L_0043cdba:
        xor edi,edi
    L_0043cdbc:
        mov dword ptr [esi+610h],edi
    L_0043cdc2:
        mov eax,dword ptr [edi]
    L_0043cdc4:
        test eax,eax
    L_0043cdc6:
        je short L_0043cdd4
    L_0043cdc8:
        mov ecx,dword ptr [eax]
    L_0043cdca:
        push eax
    L_0043cdcb:
        call dword ptr [ecx+8]
    L_0043cdce:
        mov dword ptr [edi],0
    L_0043cdd4:
        push 0
    L_0043cdd6:
        push edi
    L_0043cdd7:
        push 0
    L_0043cdd9:
        call asm_Ordinal_11_00452170
    L_0043cdde:
        test eax,eax
    L_0043cde0:
        jl asm_target_0043cfb8
    L_0043cde6:
        mov eax,dword ptr [edi]
    L_0043cde8:
        mov edx,dword ptr [eax]
    L_0043cdea:
        push 2
    L_0043cdec:
        push ebp
    L_0043cded:
        push eax
    L_0043cdee:
        call dword ptr [edx+18h]
    L_0043cdf1:
        test eax,eax
    L_0043cdf3:
        jl asm_target_0043cfb8
    L_0043cdf9:
        push ebx
    L_0043cdfa:
        push edi
    L_0043cdfb:
        mov ecx,10h
    L_0043ce00:
        mov edi,0AC44h
    L_0043ce05:
        mov ebx,2
    L_0043ce0a:
        call asm_Input_SetJoystickPropertyRetail_0044c7e0
    L_0043ce0f:
        mov edx,dword ptr [esi+610h]
    L_0043ce15:
        mov eax,dword ptr [edx]
    L_0043ce17:
        xor ecx,ecx
    L_0043ce19:
        mov dword ptr [esp+34h],ecx
    L_0043ce1d:
        mov dword ptr [esp+38h],ecx
    L_0043ce21:
        mov dword ptr [esp+3Ch],ecx
    L_0043ce25:
        xor edx,edx
    L_0043ce27:
        mov dword ptr [esp+14h],edx
    L_0043ce2b:
        mov dword ptr [esp+40h],ecx
    L_0043ce2f:
        mov dword ptr [esp+18h],edx
    L_0043ce33:
        mov dword ptr [esp+44h],ecx
    L_0043ce37:
        mov dword ptr [esp+1Ch],edx
    L_0043ce3b:
        mov dword ptr [esp+20h],edx
    L_0043ce3f:
        xor edi,edi
    L_0043ce41:
        mov dword ptr [esp+48h],ecx
    L_0043ce45:
        mov dword ptr [esi],eax
    L_0043ce47:
        mov word ptr [esp+16h],bx
    L_0043ce4c:
        push edi
    L_0043ce4d:
        mov word ptr [esp+28h],dx
    L_0043ce52:
        mov dword ptr [esp+50h],ecx
    L_0043ce56:
        lea eax,[esp+18h]
    L_0043ce5a:
        lea ebx,[esi+608h]
    L_0043ce60:
        push ebx
    L_0043ce61:
        mov dword ptr [esp+58h],ecx
    L_0043ce65:
        mov dword ptr [esp+4Ch],eax
    L_0043ce69:
        mov eax,dword ptr [esi]
    L_0043ce6b:
        lea edx,[esp+3Ch]
    L_0043ce6f:
        push edx
    L_0043ce70:
        mov dword ptr [esi+618h],edi
    L_0043ce76:
        mov dword ptr [esp+60h],ecx
    L_0043ce7a:
        mov dword ptr [esp+40h],24h
    L_0043ce82:
        mov dword ptr [esp+44h],8008h
    L_0043ce8a:
        mov dword ptr [esp+48h],8000h
    L_0043ce92:
        mov word ptr [esp+30h],di
    L_0043ce97:
        mov word ptr [esp+20h],1
    L_0043ce9e:
        mov dword ptr [esp+24h],0AC44h
    L_0043cea6:
        mov dword ptr [esp+28h],2B110h
    L_0043ceae:
        mov word ptr [esp+2Ch],4
    L_0043ceb5:
        mov word ptr [esp+2Eh],10h
    L_0043cebc:
        mov ecx,dword ptr [eax]
    L_0043cebe:
        push eax
    L_0043cebf:
        call dword ptr [ecx+0Ch]
    L_0043cec2:
        test eax,eax
    L_0043cec4:
        jl asm_target_0043d02a
    L_0043ceca:
        mov eax,dword ptr [ebx]
    L_0043cecc:
        mov ecx,dword ptr [eax]
    L_0043cece:
        push edi
    L_0043cecf:
        lea edx,[esp+30h]
    L_0043ced3:
        push edx
    L_0043ced4:
        lea edx,[esp+30h]
    L_0043ced8:
        push edx
    L_0043ced9:
        lea edx,[esp+3Ch]
    L_0043cedd:
        push edx
    L_0043cede:
        lea edx,[esp+20h]
    L_0043cee2:
        push edx
    L_0043cee3:
        push 8000h
    L_0043cee8:
        push edi
    L_0043cee9:
        push eax
    L_0043ceea:
        call dword ptr [ecx+2Ch]
    L_0043ceed:
        test eax,eax
    L_0043ceef:
        jl asm_target_0043d02a
    L_0043cef5:
        mov edi,dword ptr [esp+10h]
    L_0043cef9:
        xor eax,eax
    L_0043cefb:
        mov ecx,2000h
    L_0043cf00:
        rep stosd
    L_0043cf02:
        mov edx,dword ptr [esp+2Ch]
    L_0043cf06:
        mov eax,dword ptr [ebx]
    L_0043cf08:
        mov ecx,dword ptr [eax]
    L_0043cf0a:
        push edx
    L_0043cf0b:
        mov edx,dword ptr [esp+2Ch]
    L_0043cf0f:
        push edx
    L_0043cf10:
        mov edx,dword ptr [esp+38h]
    L_0043cf14:
        push edx
    L_0043cf15:
        mov edx,dword ptr [esp+1Ch]
    L_0043cf19:
        push edx
    L_0043cf1a:
        push eax
    L_0043cf1b:
        call dword ptr [ecx+4Ch]
    L_0043cf1e:
        mov ebx,dword ptr [ebx]
    L_0043cf20:
        mov eax,dword ptr [ebx]
    L_0043cf22:
        push 1
    L_0043cf24:
        push 0
    L_0043cf26:
        push 0
    L_0043cf28:
        push ebx
    L_0043cf29:
        call dword ptr [eax+30h]
    L_0043cf2c:
        push 0
    L_0043cf2e:
        push 0FAh
    L_0043cf33:
        mov eax,64h
    L_0043cf38:
        push 0
    L_0043cf3a:
        push ebp
    L_0043cf3b:
        mov dword ptr [esi+52C4h],eax
    L_0043cf41:
        mov dword ptr [esi+52C8h],eax
    L_0043cf47:
        call dword ptr [data_00466218]
    L_0043cf4d:
        mov dword ptr [esi+60Ch],ebp
    L_0043cf53:
        xor esi,esi
    L_0043cf55:
        TH10_REL8(0xeb, 0x0043cf55, VA_asm_FUN_0043cd30_part_0043cf60)
    }
}

// 0x0043CF60..0x0043D041: FUN_0043cd30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043cd30_part_0043cf60() {
    __asm {
    L_0043cf60:
        cmp dword ptr [data_004977b4],2
    L_0043cf67:
        je asm_target_0043d02a
    L_0043cf6d:
        mov ecx,dword ptr [esi*4+474B40h]
    L_0043cf74:
        push ecx
    L_0043cf75:
        mov ecx,esi
    L_0043cf77:
        mov edx,492590h
    L_0043cf7c:
        call asm_FUN_0043d390_0043d390
    L_0043cf81:
        test eax,eax
    L_0043cf83:
        jne asm_target_0043d010
    L_0043cf89:
        inc esi
    L_0043cf8a:
        cmp esi,25h
    L_0043cf8d:
        jl short L_0043cf60
    L_0043cf8f:
        push 46FDACh
    L_0043cf94:
        mov ecx,474F70h
    L_0043cf99:
        call asm_TextLog_Append_0044b810
    L_0043cf9e:
        add esp,4
    L_0043cfa1:
        pop ebx
    L_0043cfa2:
        pop edi
    L_0043cfa3:
        pop esi
    L_0043cfa4:
        xor eax,eax
    L_0043cfa6:
        pop ebp
    L_0043cfa7:
        mov ecx,dword ptr [esp+48h]
    L_0043cfab:
        xor ecx,esp
    L_0043cfad:
        call asm_security_check_cookie_00458ea5
    L_0043cfb2:
        add esp,4Ch
    L_0043cfb5:
        ret 4
    L_0043cfb8:
        push 46FE0Ch
    L_0043cfbd:
        mov ecx,474F70h
    L_0043cfc2:
        call asm_TextLog_Append_0044b810
    L_0043cfc7:
        mov edi,dword ptr [esi+610h]
    L_0043cfcd:
        add esp,4
    L_0043cfd0:
        test edi,edi
    L_0043cfd2:
        je short L_0043cff9
    L_0043cfd4:
        mov eax,dword ptr [edi]
    L_0043cfd6:
        test eax,eax
    L_0043cfd8:
        je short L_0043cfe6
    L_0043cfda:
        mov ecx,dword ptr [eax]
    L_0043cfdc:
        push eax
    L_0043cfdd:
        call dword ptr [ecx+8]
    L_0043cfe0:
        mov dword ptr [edi],0
    L_0043cfe6:
        push edi
    L_0043cfe7:
        call asm_free_004524a1
    L_0043cfec:
        add esp,4
    L_0043cfef:
        mov dword ptr [esi+610h],0
    L_0043cff9:
        pop edi
    L_0043cffa:
        pop esi
    L_0043cffb:
        or eax,0FFFFFFFFh
    L_0043cffe:
        pop ebp
    L_0043cfff:
        mov ecx,dword ptr [esp+48h]
    L_0043d003:
        xor ecx,esp
    L_0043d005:
        call asm_security_check_cookie_00458ea5
    L_0043d00a:
        add esp,4Ch
    L_0043d00d:
        ret 4
    L_0043d010:
        mov edx,dword ptr [esi*4+474B40h]
    L_0043d017:
        push edx
    L_0043d018:
        push 46FDD4h
    L_0043d01d:
        mov ecx,474F70h
    L_0043d022:
        call asm_TextLog_Append_0044b810
    L_0043d027:
        add esp,8
    L_0043d02a:
        mov ecx,dword ptr [esp+58h]
    L_0043d02e:
        pop ebx
    L_0043d02f:
        pop edi
    L_0043d030:
        pop esi
    L_0043d031:
        pop ebp
    L_0043d032:
        xor ecx,esp
    L_0043d034:
        or eax,0FFFFFFFFh
    L_0043d037:
        call asm_security_check_cookie_00458ea5
    L_0043d03c:
        add esp,4Ch
    L_0043d03f:
        ret 4
    }
}

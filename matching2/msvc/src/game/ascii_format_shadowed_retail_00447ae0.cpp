#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C2C0..0x0043C303: FUN_0043c2c0
// Naked body preserves the retail register/stack ABI.

// 0x00447AE0..0x00447BAB: AsciiOverlay_FormatShadowedRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Ascii_FormatShadowedRetail_00447ae0() {
    __asm {
    L_00447ae0:
        sub esp,88h
    L_00447ae6:
        mov eax,dword ptr [data_00473660]
    L_00447aeb:
        xor eax,esp
    L_00447aed:
        push ebx
    L_00447aee:
        mov dword ptr [esp+88h],eax
    L_00447af5:
        mov al,byte ptr [esi+3A0h]
    L_00447afb:
        test al,al
    L_00447afd:
        push ebp
    L_00447afe:
        push edi
    L_00447aff:
        mov ebp,11h
    L_00447b04:
        jbe short L_00447b09
    L_00447b06:
        movzx ebp,al
    L_00447b09:
        mov ecx,dword ptr [esp+0A0h]
    L_00447b10:
        lea eax,[esp+0A4h]
    L_00447b17:
        push eax
    L_00447b18:
        push ecx
    L_00447b19:
        lea edx,[esp+18h]
    L_00447b1d:
        push edx
    L_00447b1e:
        call asm_vsprintf_004524a6
    L_00447b23:
        lea eax,[esp+1Ch]
    L_00447b27:
        add esp,0Ch
    L_00447b2a:
        lea edx,[eax+1]
    L_00447b2d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00447b30:
        mov cl,byte ptr [eax]
    L_00447b32:
        inc eax
    L_00447b33:
        test cl,cl
    L_00447b35:
        jne short L_00447b30
    L_00447b37:
        mov ecx,dword ptr [esi+360h]
    L_00447b3d:
        mov edi,dword ptr [esi+394h]
    L_00447b43:
        shr ecx,1
    L_00447b45:
        and ecx,1
    L_00447b48:
        push ecx
    L_00447b49:
        sub eax,edx
    L_00447b4b:
        mov edx,dword ptr [esp+0A0h]
    L_00447b52:
        lea ecx,[ebp-1]
    L_00447b55:
        imul ecx,eax
    L_00447b58:
        shr ecx,1
    L_00447b5a:
        test ecx,ecx
    L_00447b5c:
        mov dword ptr [esp+10h],ecx
    L_00447b60:
        push edx
    L_00447b61:
        fild dword ptr [esp+14h]
    L_00447b65:
        jge short L_00447b6d
    L_00447b67:
        fadd dword ptr [data_00470b98]
    L_00447b6d:
        fsubr dword ptr [edi+34h]
    L_00447b70:
        call asm_FUN_00463b2c_00463b2c
    L_00447b75:
        mov edx,dword ptr [edi+4]
    L_00447b78:
        push eax
    L_00447b79:
        push edx
    L_00447b7a:
        lea ebx,[esp+20h]
    L_00447b7e:
        mov eax,ebp
    L_00447b80:
        call asm_Recovery_DispatchRandomText_004479d0
    L_00447b85:
        mov eax,dword ptr [esi+35Ch]
    L_00447b8b:
        mov ecx,dword ptr [esp+90h]
    L_00447b92:
        pop edi
    L_00447b93:
        pop ebp
    L_00447b94:
        or eax,1
    L_00447b97:
        pop ebx
    L_00447b98:
        xor ecx,esp
    L_00447b9a:
        mov dword ptr [esi+35Ch],eax
    L_00447ba0:
        call asm_security_check_cookie_00458ea5
    L_00447ba5:
        add esp,88h
    L_00447bab:
        ret
    }
}

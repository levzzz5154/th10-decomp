#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DE91..0x0045DEF7: FUN_0045de91
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045de91_0045de91() {
    __asm {
    L_0045de91:
        push ebp
    L_0045de92:
        mov ebp,esp
    L_0045de94:
        sub esp,2Ch
    L_0045de97:
        mov eax,dword ptr [data_00473660]
    L_0045de9c:
        push esi
    L_0045de9d:
        mov esi,dword ptr [ebp+0Ch]
    L_0045dea0:
        push edi
    L_0045dea1:
        lea ecx,[ebp-1Ch]
    L_0045dea4:
        push ecx
    L_0045dea5:
        xor eax,ebp
    L_0045dea7:
        mov dword ptr [ebp-4],eax
    L_0045deaa:
        mov eax,dword ptr [ebp+8]
    L_0045dead:
        lea ecx,[ebp-2Ch]
    L_0045deb0:
        push ecx
    L_0045deb1:
        push dword ptr [eax+4]
    L_0045deb4:
        push dword ptr [eax]
    L_0045deb6:
        call asm_FUN_00460e41_00460e41
    L_0045debb:
        mov edi,dword ptr [ebp+10h]
    L_0045debe:
        lea eax,[ebp-2Ch]
    L_0045dec1:
        push eax
    L_0045dec2:
        mov eax,dword ptr [ebp-28h]
    L_0045dec5:
        add eax,edi
    L_0045dec7:
        push eax
    L_0045dec8:
        xor eax,eax
    L_0045deca:
        cmp dword ptr [ebp-2Ch],2Dh
    L_0045dece:
        sete al
    L_0045ded1:
        add eax,esi
    L_0045ded3:
        push eax
    L_0045ded4:
        call asm_fptostr_00460d10
    L_0045ded9:
        push 0
    L_0045dedb:
        push edi
    L_0045dedc:
        push esi
    L_0045dedd:
        lea eax,[ebp-2Ch]
    L_0045dee0:
        call asm_cftof2_0045ddf5
    L_0045dee5:
        mov ecx,dword ptr [ebp-4]
    L_0045dee8:
        add esp,28h
    L_0045deeb:
        pop edi
    L_0045deec:
        mov eax,esi
    L_0045deee:
        xor ecx,ebp
    L_0045def0:
        pop esi
    L_0045def1:
        call asm_security_check_cookie_00458ea5
    L_0045def6:
        leave
    L_0045def7:
        ret
    }
}

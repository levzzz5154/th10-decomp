#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DD85..0x0045DDF4: FUN_0045dd85
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045dd85_0045dd85() {
    __asm {
    L_0045dd85:
        push ebp
    L_0045dd86:
        mov ebp,esp
    L_0045dd88:
        sub esp,2Ch
    L_0045dd8b:
        mov eax,dword ptr [data_00473660]
    L_0045dd90:
        push ebx
    L_0045dd91:
        mov ebx,dword ptr [ebp+0Ch]
    L_0045dd94:
        push esi
    L_0045dd95:
        lea ecx,[ebp-1Ch]
    L_0045dd98:
        push ecx
    L_0045dd99:
        xor eax,ebp
    L_0045dd9b:
        mov dword ptr [ebp-4],eax
    L_0045dd9e:
        mov eax,dword ptr [ebp+8]
    L_0045dda1:
        lea ecx,[ebp-2Ch]
    L_0045dda4:
        push ecx
    L_0045dda5:
        push dword ptr [eax+4]
    L_0045dda8:
        push dword ptr [eax]
    L_0045ddaa:
        call asm_FUN_00460e41_00460e41
    L_0045ddaf:
        mov esi,dword ptr [ebp+10h]
    L_0045ddb2:
        lea eax,[ebp-2Ch]
    L_0045ddb5:
        push eax
    L_0045ddb6:
        lea eax,[esi+1]
    L_0045ddb9:
        push eax
    L_0045ddba:
        xor eax,eax
    L_0045ddbc:
        cmp dword ptr [ebp-2Ch],2Dh
    L_0045ddc0:
        sete al
    L_0045ddc3:
        xor ecx,ecx
    L_0045ddc5:
        test esi,esi
    L_0045ddc7:
        setg cl
    L_0045ddca:
        add eax,ebx
    L_0045ddcc:
        add ecx,eax
    L_0045ddce:
        push ecx
    L_0045ddcf:
        call asm_fptostr_00460d10
    L_0045ddd4:
        push 0
    L_0045ddd6:
        push dword ptr [ebp+14h]
    L_0045ddd9:
        lea eax,[ebp-2Ch]
    L_0045dddc:
        push esi
    L_0045dddd:
        call asm_cftoe2_0045dcd7
    L_0045dde2:
        mov ecx,dword ptr [ebp-4]
    L_0045dde5:
        add esp,28h
    L_0045dde8:
        pop esi
    L_0045dde9:
        mov eax,ebx
    L_0045ddeb:
        xor ecx,ebp
    L_0045dded:
        pop ebx
    L_0045ddee:
        call asm_security_check_cookie_00458ea5
    L_0045ddf3:
        leave
    L_0045ddf4:
        ret
    }
}

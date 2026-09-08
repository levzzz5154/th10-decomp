#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460E41..0x00460EB8: FUN_00460e41
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00460e41_00460e41() {
    __asm {
    L_00460e41:
        push ebp
    L_00460e42:
        mov ebp,esp
    L_00460e44:
        sub esp,30h
    L_00460e47:
        mov eax,dword ptr [data_00473660]
    L_00460e4c:
        xor eax,ebp
    L_00460e4e:
        mov dword ptr [ebp-4],eax
    L_00460e51:
        mov eax,dword ptr [ebp+14h]
    L_00460e54:
        push ebx
    L_00460e55:
        mov ebx,dword ptr [ebp+10h]
    L_00460e58:
        push esi
    L_00460e59:
        mov dword ptr [ebp-30h],eax
    L_00460e5c:
        push edi
    L_00460e5d:
        lea eax,[ebp+8]
    L_00460e60:
        push eax
    L_00460e61:
        lea eax,[ebp-10h]
    L_00460e64:
        push eax
    L_00460e65:
        call asm_dtold_00460d87
    L_00460e6a:
        pop ecx
    L_00460e6b:
        pop ecx
    L_00460e6c:
        lea eax,[ebp-2Ch]
    L_00460e6f:
        push eax
    L_00460e70:
        push 0
    L_00460e72:
        push 11h
    L_00460e74:
        sub esp,0Ch
    L_00460e77:
        lea esi,[ebp-10h]
    L_00460e7a:
        mov edi,esp
    L_00460e7c:
        movsd
    L_00460e7d:
        movsd
    L_00460e7e:
        movsw
    L_00460e80:
        call asm_FUN_00461841_00461841
    L_00460e85:
        mov esi,dword ptr [ebp-30h]
    L_00460e88:
        mov dword ptr [ebx+8],eax
    L_00460e8b:
        movsx eax,byte ptr [ebp-2Ah]
    L_00460e8f:
        mov dword ptr [ebx],eax
    L_00460e91:
        movsx eax,word ptr [ebp-2Ch]
    L_00460e95:
        mov dword ptr [ebx+4],eax
    L_00460e98:
        lea eax,[ebp-28h]
    L_00460e9b:
        push eax
    L_00460e9c:
        push esi
    L_00460e9d:
        call asm_FUN_0045bd80_0045bd80
    L_00460ea2:
        mov ecx,dword ptr [ebp-4]
    L_00460ea5:
        add esp,20h
    L_00460ea8:
        pop edi
    L_00460ea9:
        mov dword ptr [ebx+0Ch],esi
    L_00460eac:
        pop esi
    L_00460ead:
        mov eax,ebx
    L_00460eaf:
        xor ecx,ebp
    L_00460eb1:
        pop ebx
    L_00460eb2:
        call asm_security_check_cookie_00458ea5
    L_00460eb7:
        leave
    L_00460eb8:
        ret
    }
}

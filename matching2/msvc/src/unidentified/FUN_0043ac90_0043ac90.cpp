#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043AC90..0x0043ACD7: FUN_0043ac90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043ac90_0043ac90() {
    __asm {
    L_0043ac90:
        push ebx
    L_0043ac91:
        push esi
    L_0043ac92:
        mov ebx,ecx
    L_0043ac94:
        push eax
    L_0043ac95:
        mov esi,1Fh
    L_0043ac9a:
        mov eax,ebx
    L_0043ac9c:
        call asm_FUN_0043a9b0_0043a9b0
    L_0043aca1:
        test eax,eax
    L_0043aca3:
        je short L_0043acab
    L_0043aca5:
        pop esi
    L_0043aca6:
        or eax,0FFFFFFFFh
    L_0043aca9:
        pop ebx
    L_0043acaa:
        ret
    L_0043acab:
        push 1Fh
    L_0043acad:
        call asm_FUN_0043aad0_0043aad0
    L_0043acb2:
        mov eax,dword ptr [ebx+114h]
    L_0043acb8:
        xor esi,esi
    L_0043acba:
        cmp eax,esi
    L_0043acbc:
        je short L_0043accd
    L_0043acbe:
        push eax
    L_0043acbf:
        call asm_free_00452422
    L_0043acc4:
        add esp,4
    L_0043acc7:
        mov dword ptr [ebx+114h],esi
    L_0043accd:
        mov dword ptr [ebx+114h],esi
    L_0043acd3:
        pop esi
    L_0043acd4:
        xor eax,eax
    L_0043acd6:
        pop ebx
    L_0043acd7:
        ret
    }
}

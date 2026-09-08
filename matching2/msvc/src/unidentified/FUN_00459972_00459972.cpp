#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459972..0x00459989: FUN_00459972
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00459972_00459972() {
    __asm {
    L_00459972:
        push ebx
    L_00459973:
        push ecx
    L_00459974:
        mov ebx,47372Ch
    L_00459979:
        mov ecx,dword ptr [ebp+8]
    L_0045997c:
        mov dword ptr [ebx+8],ecx
    L_0045997f:
        mov dword ptr [ebx+4],eax
    L_00459982:
        mov dword ptr [ebx+0Ch],ebp
    L_00459985:
        pop ecx
    L_00459986:
        pop ebx
    L_00459987:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F119..0x0045F128: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045f119() {
    __asm {
    L_0045f119:
        xor eax,eax
    L_0045f11b:
        inc eax
    L_0045f11c:
        ret
    L_0045f11d:
        mov esp,dword ptr [ebp-18h]
    L_0045f120:
        call asm_resetstkoflw_00458d91
    L_0045f125:
        xor ebx,ebx
    L_0045f127:
        xor edi,edi
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413B50..0x00413B81: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413b50() {
    __asm {
    L_00413b50:
        mov edx,dword ptr [data_00491c10]
    L_00413b56:
        push 46D254h
    L_00413b5b:
        mov ecx,6
    L_00413b60:
        call asm_Recovery_LoadCachedResource_00447280
    L_00413b65:
        test eax,eax
    L_00413b67:
        jne short L_00413b7f
    L_00413b69:
        push 46CB68h
    L_00413b6e:
        mov ecx,474F70h
    L_00413b73:
        call asm_TextLog_Append_0044b810
    L_00413b78:
        add esp,4
    L_00413b7b:
        or eax,0FFFFFFFFh
    L_00413b7e:
        ret
    L_00413b7f:
        xor eax,eax
    L_00413b81:
        ret
    }
}

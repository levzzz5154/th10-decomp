#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420B60..0x00420B73: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00420b60() {
    __asm {
    L_00420b60:
        mov al,byte ptr [data_00491d63]
    L_00420b65:
        cmp al,2
    L_00420b67:
        je short L_00420b6d
    L_00420b69:
        cmp al,1
    L_00420b6b:
        jne short L_00420b70
    L_00420b6d:
        xor eax,eax
    L_00420b6f:
        ret
    L_00420b70:
        or eax,0FFFFFFFFh
    L_00420b73:
        ret
    }
}

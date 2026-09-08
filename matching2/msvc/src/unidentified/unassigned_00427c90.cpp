#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427C90..0x00427CA2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427c90() {
    __asm {
    L_00427c90:
        sub word ptr [eax+8],cx
    L_00427c94:
        mov cx,word ptr [eax+8]
    L_00427c98:
        jns short L_00427ca0
    L_00427c9a:
        mov word ptr [eax+8],0
    L_00427ca0:
        xor eax,eax
    L_00427ca2:
        ret
    }
}

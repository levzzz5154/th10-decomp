#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457A24..0x00457A3B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00457a24() {
    __asm {
    L_00457a24:
        push esi
    L_00457a25:
        mov esi,eax
    L_00457a27:
        push esi
    L_00457a28:
        call asm_isdigit_0045685e
    L_00457a2d:
        test eax,eax
    L_00457a2f:
        pop ecx
    L_00457a30:
        jne short L_00457a38
    L_00457a32:
        and esi,0FFFFFFDFh
    L_00457a35:
        sub esi,7
    L_00457a38:
        mov eax,esi
    L_00457a3a:
        pop esi
    L_00457a3b:
        ret
    }
}

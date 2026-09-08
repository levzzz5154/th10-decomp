#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418170..0x0041818A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418170() {
    __asm {
    L_00418170:
        push esi
    L_00418171:
        call asm_FUN_00417c80_00417c80
    L_00418176:
        test byte ptr [esp+4],1
    L_0041817b:
        je short L_00418186
    L_0041817d:
        push esi
    L_0041817e:
        call asm_free_004524a1
    L_00418183:
        add esp,4
    L_00418186:
        mov eax,esi
    L_00418188:
        ret 4
    }
}

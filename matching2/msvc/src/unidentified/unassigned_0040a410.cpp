#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A410..0x0040A42A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040a410() {
    __asm {
    L_0040a410:
        push esi
    L_0040a411:
        call asm_FUN_0040a1a0_0040a1a0
    L_0040a416:
        test byte ptr [esp+4],1
    L_0040a41b:
        je short L_0040a426
    L_0040a41d:
        push esi
    L_0040a41e:
        call asm_free_004524a1
    L_0040a423:
        add esp,4
    L_0040a426:
        mov eax,esi
    L_0040a428:
        ret 4
    }
}

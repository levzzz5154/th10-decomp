#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463BF0..0x00463C03: FUN_00463bf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00463bf0_00463bf0() {
    __asm {
    L_00463bf0:
        sub esp,0Ch
    L_00463bf3:
        fst qword ptr [esp]
    L_00463bf6:
        call asm_FUN_00464f88_00464f88
    L_00463bfb:
        call asm_FUN_00463c0d_00463c0d
    L_00463c00:
        add esp,0Ch
    L_00463c03:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452E04..0x00452E09: FUN_00452e04
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00452e04_00452e04() {
    __asm {
    L_00452e04:
        call asm_FUN_00457580_00457580
    L_00452e09:
        ret
    }
}

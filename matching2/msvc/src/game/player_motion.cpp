#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040678E..0x00406797: ?Player_ForwardAxisWrap@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_ForwardAxisWrap_0040678e() {
    __asm {
    L_0040678e:
        push esi
    L_0040678f:
        mov esi,ecx
    L_00406791:
        call asm_FUN_004065c0_004065c0
    L_00406796:
        pop esi
    L_00406797:
        ret
    }
}





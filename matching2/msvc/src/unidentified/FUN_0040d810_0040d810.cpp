#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D810..0x0040D819: FUN_0040d810
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d810_0040d810() {
    __asm {
    L_0040d810:
        push edi
    L_0040d811:
        mov edi,ecx
    L_0040d813:
        call asm_Enemy_TimerSweepRetail_0040d750
    L_0040d818:
        pop edi
    L_0040d819:
        ret
    }
}

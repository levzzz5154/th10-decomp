#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D730..0x0040D742: FUN_0040d730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d730_0040d730() {
    __asm {
    L_0040d730:
        test esi,esi
    L_0040d732:
        je short L_0040d742
    L_0040d734:
        mov eax,esi
    L_0040d736:
        call asm_FUN_0040d530_0040d530
    L_0040d73b:
        push esi
    L_0040d73c:
        call asm_free_004524a1
    L_0040d741:
        pop ecx
    L_0040d742:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3705): closest_byte_count=0/19; first_diff=0x0040d730
// residual_class=private ESI receiver plus callee-private register ABI; the
// standalone readable pointer-parameter form emitted a 26-byte body instead
// of retail's 19-byte test/mov/call/push/call/pop sequence.
// variants_tested=typed explicit-pointer C++ cleanup calling the recovered
// 0040D530 and free helpers; the nonexact 26-byte output was restored.
// next_lever=caller-inclusive native-LTCG cluster over 0040D730, its 0040D530
// callee, and callers 0040A780/0040D710 so LTCG can select the ESI convention.

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

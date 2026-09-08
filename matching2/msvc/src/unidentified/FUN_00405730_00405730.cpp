#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405730..0x00405741: FUN_00405730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405730_00405730() {
    __asm {
    L_00405730:
        test esi,esi
    L_00405732:
        je short L_00405741
    L_00405734:
        push esi
    L_00405735:
        call asm_Recovery_ReleaseRawPairAndReset_00405620
    L_0040573a:
        push esi
    L_0040573b:
        call asm_free_004524a1
    L_00405740:
        pop ecx
    L_00405741:
        ret
    }
}

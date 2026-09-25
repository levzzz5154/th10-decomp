#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456AD4..0x00456AF1: __fpmath
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_fpmath_00456ad4(int set_default_precision) {
    __asm {
    L_00456ad4:
        call asm_FUN_00456a8c_00456a8c
    L_00456ad9:
        call asm_ms_p5_mp_test_fdiv_0045e03a
    L_00456ade:
        cmp dword ptr [esp+4],0
    L_00456ae3:
        mov dword ptr [data_00477388],eax
    L_00456ae8:
        je short L_00456aef
    L_00456aea:
        call asm_setdefaultprecision_0045dfe8
    L_00456aef:
        fnclex
    L_00456af1:
        ret
    }
}

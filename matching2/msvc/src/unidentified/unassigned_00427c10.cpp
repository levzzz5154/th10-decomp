#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427C10..0x00427C30: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2701): closest_byte_count=15/33; first_diff=0x00427C12;
// residual_class=toolkit/scheduler: the exact ESI source and EDI destination
// ABI is private, and the nearest readable scale/truncate candidate differed
// in 18 bytes because MSVC hoisted/reloaded the 0x00470B44 scale instead of
// retaining retail's `fld source; fmul [scale]` order.
// variants_tested=src*K, K*src, source local, scale local; an additional
// readable __fastcall ScalePair candidate emitted 51 bytes (vs 33), and all
// retained the private-register ABI but missed retail x87 spelling or extent.
// next_lever=compiler/toolkit mechanism that emits the retail x87 order inside
// a native-LTCG ESI/EDI context; retain this exact wrapper meanwhile.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427c10() {
    __asm {
    L_00427c10:
        fld dword ptr [esi]
    L_00427c12:
        fmul dword ptr [data_00470b44]
    L_00427c18:
        call asm_FUN_00463b2c_00463b2c
    L_00427c1d:
        mov dword ptr [edi],eax
    L_00427c1f:
        fld dword ptr [esi+4]
    L_00427c22:
        fmul dword ptr [data_00470b44]
    L_00427c28:
        call asm_FUN_00463b2c_00463b2c
    L_00427c2d:
        mov dword ptr [edi+4],eax
    L_00427c30:
        ret
    }
}

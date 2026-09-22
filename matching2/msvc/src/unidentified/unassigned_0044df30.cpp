#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED 0044DF30 (3 bytes): closest_byte_count=3, first_diff=none;
// residual_class=unreferenced register-only fragment (retail add eax,ecx; ret)
// with no Ghidra function boundary, callers, or xrefs. variants_tested=
// existing exact naked body and ordinary C++ cdecl/fastcall wrappers (the
// latter cannot express the live EAX/ECX entry state). next_lever=native LTCG
// probe from the owning function/context once its private ABI is identified.

// 0x0044DF30..0x0044DF32: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044df30() {
    __asm {
    L_0044df30:
        add eax,ecx
    L_0044df32:
        ret
    }
}

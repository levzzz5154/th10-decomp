// BLOCKED (M2704): closest_byte_count=8; first_diff=0x0040c590;
// residual_class=register-allocation/function-extent: readable thiscall
// candidates preserve the branchless bool tail and RET 4, but MSVC assigns
// the object load to ECX and stack argument to EDX, opposite retail's EDX/ECX
// schedule; the compiler contribution is 16 bytes while the claimed retail
// region includes a trailing RET at +0x10.
// variants_tested=direct member comparison and reversed comparison order;
// direct candidate measured 16 bytes, with 8 retail bytes matching.
// next_lever=an externally visible/public member boundary plus a context that
// prevents whole-program register reassignment and separately models the
// trailing one-byte RET extent.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C590..0x0040C5A0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c590() {
    __asm {
    L_0040c590:
        mov edx,dword ptr [ecx]
    L_0040c592:
        mov ecx,dword ptr [esp+4]
    L_0040c596:
        xor eax,eax
    L_0040c598:
        cmp edx,ecx
    L_0040c59a:
        sete al
    L_0040c59d:
        ret 4
    L_0040c5a0:
        ret
    }
}

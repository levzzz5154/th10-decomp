#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CE10..0x0040CE24: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2702): closest_byte_count=0/21; first_diff=0x0040CE10;
// residual_class=private ABI/register inputs: retail receives index in EAX,
// bits in EDX, and the float at [ESP+4], while a readable __thiscall setter
// receives all three declared arguments from the stack and emits 29 bytes.
// variants_tested=direct indexed setter with unsigned index/bits and float;
// candidate extent was 29 bytes and its first instruction loaded index from
// [ESP+4] instead of retail FLD [ESP+4].
// next_lever=native-LTCG context that anchors EAX/EDX live-ins and the
// caller-cleaned single float argument, or manifest semantic migration.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ce10() {
    __asm {
    L_0040ce10:
        fld dword ptr [esp+4]
    L_0040ce14:
        mov dword ptr [ecx+eax*8+9E98h],edx
    L_0040ce1b:
        fstp dword ptr [ecx+eax*8+9E94h]
    L_0040ce22:
        ret 4
    }
}

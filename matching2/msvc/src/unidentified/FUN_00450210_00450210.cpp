// BLOCKED (H3301): closest_byte_count=12/12; first_diff=none (authoritative
// retail wrapper remains exact). residual_class=private EAX receiver paired
// with a stack value and RET 4; native-LTCG remaps the explicit value into
// EDX when the readable member/constructor is linked with a caller.
// variants_tested=live Ghidra decompile/disassembly/xref audit, readable
// member-setter native-LTCG probe (6-byte body, first_diff=0x00450213), and a
// constructor/placement-new probe with the same private-ABI collapse; all
// nonexact variants were discarded. next_lever=schema-2 native-LTCG cluster
// containing the real EAX receiver caller while retaining the stack argument
// and callee RET 4 contract.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450210..0x0045021B: FUN_00450210
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00450210_00450210() {
    __asm {
    L_00450210:
        mov ecx,dword ptr [eax+4]
    L_00450213:
        mov edx,dword ptr [esp+4]
    L_00450217:
        mov dword ptr [ecx],edx
    L_00450219:
        ret 4
    }
}

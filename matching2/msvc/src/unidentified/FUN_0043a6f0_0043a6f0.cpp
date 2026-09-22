// BLOCKED (H3301): closest_byte_count=14/14; first_diff=none (authoritative
// retail wrapper remains exact). residual_class=private AX live-in/live-out,
// ECX preservation, and the compiler's two-byte temporary/aggregate schedule.
// variants_tested=live Ghidra decompile/xref audit (no function or references),
// exact 14-byte Ghidra disassembly, MSVC 13.10 short and byte-pair probes, and
// a native-LTCG aggregate candidate; the readable candidates changed the
// temporary schedule or extent and were not retained. next_lever=native-LTCG
// cluster with the real AX/ECX caller context and the original aggregate
// source shape, then compare the complete 14-byte contribution.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A6F0..0x0043A6FD: FUN_0043a6f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a6f0_0043a6f0() {
    __asm {
    L_0043a6f0:
        push ecx
    L_0043a6f1:
        mov byte ptr [esp],ah
    L_0043a6f4:
        mov byte ptr [esp+1],al
    L_0043a6f8:
        mov ax,word ptr [esp]
    L_0043a6fc:
        pop ecx
    L_0043a6fd:
        ret
    }
}

// BLOCKED (M3002): closest_byte_count=0/7; first_diff=0x004485E0;
// residual_class=private EAX receiver/trampoline ABI.  Live Ghidra confirms
// 004485E0 only receives a DATA xref from GameStateInit (00445B95), moves the
// incoming ECX into EAX, and jumps to the EAX/EDX-entry 00448900 worker.
// variants_tested=typed __fastcall direct-forwarder (6 bytes; a direct jump
// with no ECX-to-EAX move); no nonexact candidate retained.
// next_lever=native-LTCG cluster with GameStateInit's callback construction
// and 00448900's private EAX/EDX ABI, or a compiler lever for EAX entry.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004485E0..0x004485E6: FUN_004485e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004485e0_004485e0() {
    __asm {
    L_004485e0:
        mov eax,ecx
    L_004485e2:
        jmp asm_AnimationManager_UpdateSecondary_00448900
    }
}

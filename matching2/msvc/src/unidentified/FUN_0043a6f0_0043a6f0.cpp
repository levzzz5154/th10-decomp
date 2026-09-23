// BLOCKED (H3301): the exact 14-byte retail body remains authoritative.
// Live Ghidra has no Function at 0x0043A6F0; it classifies 0x0043A6F0..0x0043A6FF
// as undefined data with no xrefs, and a whole-program direct-call scan found
// no call site. The body round-trips AX and restores ECX, but no actual caller
// contract is available to ground an ordinary C++ signature. It calls no
// helpers. See matching2/reference/recovery_notes/fun_0043a6f0_private_abi_audit.md.
// closest_byte_count=14/14; first_diff=none; residual_class=unmodeled AX
// live-in/live-out and ECX preservation. Earlier MSVC and native-LTCG source
// candidates did not reproduce the complete 14-byte contribution.
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

// BLOCKED (M3001): closest_byte_count=0/7; first_diff=0x0042D2F0;
// residual_class=private ECX-to-EAX tail-call ABI.  Live Ghidra has exact
// boundaries 0x0042D2F0..0x0042D2F6, an ECX callback entry, and an
// unconditional tail jump to 0x0042D260, whose dispatcher consumes EAX.
// variants_tested=typed __fastcall no-argument tail candidate (native LTCG
// emitted only E9 rel32, 5 bytes), typed __cdecl pointer argument candidate
// (native LTCG emitted PUSH/CALL/ADD/RET, 10 bytes), and a synthetic native
// LTCG callback-loop context; all differed at the entry and none established
// the required ECX-to-EAX move without inline assembly.
// next_lever=compiler/toolkit mechanism or a coupled native-LTCG caller/callee
// context that exposes the private EAX receiver while retaining the exact
// seven-byte MOV EAX,ECX / JMP 0x0042D260 bridge.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042D2F0..0x0042D2F6: FUN_0042d2f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042d2f0_0042d2f0() {
    __asm {
    L_0042d2f0:
        mov eax,ecx
    L_0042d2f2:
        jmp asm_FUN_0042d260_0042d260
    }
}

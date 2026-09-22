// BLOCKED (H3101): closest_byte_count=6/29; first_diff=0x00442F31;
// residual_class=private EAX receiver ABI for the large state initializer.
// Live Ghidra boundary is 00442F30..00442F4C and the stores target
// +0x3ADAC8, +0x72DACC, and +0x72DAD0. Native-LTCG typed member probes
// with one and repeated calls emitted an ECX receiver (25 bytes); a free
// stdcall probe emitted stack-argument traffic and RET 4.
// variants_tested=S442F30::Init() with single/repeated native-LTCG calls,
// free H3101Init442(S442F30*) under /GL /LTCG, and corrected 0x380000
// intermediate padding to match the retail offsets.
// next_lever=real coupled caller context that forces EAX as the object
// register while retaining the LEA/store ordering, or private ABI anchor.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442F30..0x00442F4C: FUN_00442f30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00442f30_00442f30() {
    __asm {
    L_00442f30:
        lea ecx,[eax+3ADACCh]
    L_00442f36:
        mov dword ptr [eax+3ADAC8h],0
    L_00442f40:
        mov dword ptr [eax+72DACCh],ecx
    L_00442f46:
        mov dword ptr [eax+72DAD0h],ecx
    L_00442f4c:
        ret
    }
}

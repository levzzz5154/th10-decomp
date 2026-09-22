// BLOCKED (H3101): closest_byte_count=14/19; first_diff=0x0042A991;
// residual_class=private EAX receiver ABI. Live Ghidra boundary is
// 0042A990..0042A9A2 and the body copies fields 0->1, 2->3, then clears
// field 5. Native-LTCG member probes emitted an ECX receiver (19 bytes,
// five differing bytes); a dummy-argument member emitted stack value
// traffic and RET 4 (21 bytes).
// variants_tested=S2A990::Normalize(), S2A990::Normalize(int), repeated
// native-LTCG caller loops, and existing accessor-style array contexts.
// next_lever=real caller context that induces EAX as the object register,
// or a compiler/private-ABI anchor for this no-argument member.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A990..0x0042A9A2: FUN_0042a990
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a990_0042a990() {
    __asm {
    L_0042a990:
        mov ecx,dword ptr [eax]
    L_0042a992:
        mov edx,dword ptr [eax+8]
    L_0042a995:
        mov dword ptr [eax+4],ecx
    L_0042a998:
        mov dword ptr [eax+0Ch],edx
    L_0042a99b:
        mov dword ptr [eax+14h],0
    L_0042a9a2:
        ret
    }
}

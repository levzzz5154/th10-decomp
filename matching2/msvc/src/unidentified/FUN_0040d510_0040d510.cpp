// BLOCKED (D3605): closest_byte_count=1/28; first_diff=0x0040D511.
// residual_class=private EAX input ABI: live Ghidra shows the caller leaves
// the state object in EAX with no stack argument, while a readable cdecl
// candidate emitted a 32-byte body whose first four-byte load shifted every
// retail instruction (the remaining tail matched only after manual alignment).
// variants_tested=live Ghidra decompilation, real caller 0x0040A450, and MSVC
// 13.10 readable cdecl struct candidate (32-byte extent, 1/28 same-position
// bytes); exact naked baseline probe=28/28. next_lever=native-LTCG cluster
// preserving EAX state handoff and the caller's register context.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D510..0x0040D52B: FUN_0040d510
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d510_0040d510() {
    __asm {
    L_0040d510:
        mov ecx,dword ptr [eax+8]
    L_0040d513:
        test ecx,ecx
    L_0040d515:
        mov edx,2
    L_0040d51a:
        je short L_0040d51f
    L_0040d51c:
        or dword ptr [ecx+4],edx
    L_0040d51f:
        mov ecx,dword ptr [eax+0Ch]
    L_0040d522:
        test ecx,ecx
    L_0040d524:
        je short L_0040d52b
    L_0040d526:
        mov eax,ecx
    L_0040d528:
        or dword ptr [eax+4],edx
    L_0040d52b:
        ret
    }
}

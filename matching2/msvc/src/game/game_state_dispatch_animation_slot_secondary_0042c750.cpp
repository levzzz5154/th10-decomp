#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.

// 0x0042C750..0x0042C76A: ?GameState_DispatchAnimationSlotSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DispatchAnimationSlotSecondary_0042c750() {
    __asm {
    L_0042c750:
        mov edx,dword ptr [eax+ecx*4+2C4h]
    L_0042c757:
        push edi
    L_0042c758:
        push edx
    L_0042c759:
        mov edx,dword ptr [data_00491c10]
    L_0042c75f:
        mov edi,3
    L_0042c764:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042c769:
        pop edi
    L_0042c76a:
        ret
    }
}
// BLOCKED (D3303): closest_byte_count=0/27; first_diff=none;
// residual_class=private EAX owner/ECX slot inputs and EDX/EDI live values
// consumed by SetStopFrameAndRun, requiring caller-inclusive codegen.
// variants_tested=live Ghidra decompilation/topology and MSVC 13.10 readable
// stdcall translation (34/27 extent); next_lever=native-LTCG
// cluster/schema2 with callers 0042D420, 0042D920, 00430320, 004306A0,
// 00430A60 and callee 00449250.
// Current assembly overlay remains exact.


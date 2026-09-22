// BLOCKED (D3307): closest_byte_count=5/27; first_diff=0x0042C731;
// residual_class=private EAX state/ECX slot-index inputs, EDX manager receiver,
// EDI stop-frame live-in, and stack-slot lookup ABI at 0x00449250.
// variants_tested=live Ghidra complete decompilation with callers/xrefs and
// disassembly/variable audit; ordinary MSVC 13.10 readable cdecl candidate
// (31-byte extent, 5/27 prefix); no standalone readable body retained because
// the callee's DI/EDX agreement is compiler-context dependent.
// next_lever=schema-2 native-LTCG cluster joining the real callers, this body,
// and 0x00449250, preserving the slot table at +0x2c4 and stop-frame value 2;
// promote only after the complete 27-byte body and call relocation are exact.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.

// 0x0042C730..0x0042C74A: ?GameState_DispatchAnimationSlot@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DispatchAnimationSlot_0042c730() {
    __asm {
    L_0042c730:
        mov edx,dword ptr [eax+ecx*4+2C4h]
    L_0042c737:
        push edi
    L_0042c738:
        push edx
    L_0042c739:
        mov edx,dword ptr [data_00491c10]
    L_0042c73f:
        mov edi,2
    L_0042c744:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042c749:
        pop edi
    L_0042c74a:
        ret
    }
}

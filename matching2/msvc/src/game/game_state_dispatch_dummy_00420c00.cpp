#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3505): closest_byte_count=4/41; first_diff=0x00420c02;
// residual_class=private EAX/EDX helper inputs and ret-8 stack ownership,
// plus branch-local duplicate call shape. variants_tested=standalone typed
// register-resource candidate (38-byte extent, 4/41 equal, first diff at
// the global displacement); live-Ghidra decompile and helper 0x0043E460.
// next_lever=native-LTCG cluster with a caller that preserves the resource
// and string values in EAX/EDX while retaining the two helper call sites.

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DispatchDummy_00420c00() {
    __asm {
    L_00420c00:
        test byte ptr [data_00491d78],10h
    L_00420c07:
        mov edx,46DF98h
    L_00420c0c:
        push 0
    L_00420c0e:
        mov eax,492590h
    L_00420c13:
        je short L_00420c1f
    L_00420c15:
        push 4
    L_00420c17:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420c1c:
        xor eax,eax
    L_00420c1e:
        ret
    L_00420c1f:
        push 3
    L_00420c21:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420c26:
        xor eax,eax
    L_00420c28:
        ret
    }
}

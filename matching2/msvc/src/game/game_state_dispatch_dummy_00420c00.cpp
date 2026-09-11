#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.

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

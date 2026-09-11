#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00419090..0x004190D2: Recovery_CreateResourceState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateResourceState_00419090() {
    __asm {
    L_00419090:
        push ebx
    L_00419091:
        push 1A8h
    L_00419096:
        call asm_operator_new_00452493
    L_0041909b:
        add esp,4
    L_0041909e:
        test eax,eax
    L_004190a0:
        je short L_004190ad
    L_004190a2:
        mov edx,eax
    L_004190a4:
        call asm_StageTipManager_Construct_00418d40
    L_004190a9:
        mov ebx,eax
    L_004190ab:
        jmp short L_004190af
    L_004190ad:
        xor ebx,ebx
    L_004190af:
        call asm_StageTipRuntime_InitializeRetail_00418e30
    L_004190b4:
        test eax,eax
    L_004190b6:
        je short L_004190cf
    L_004190b8:
        test ebx,ebx
    L_004190ba:
        je short L_004190cb
    L_004190bc:
        push ebx
    L_004190bd:
        call asm_FUN_00418ee0_00418ee0
    L_004190c2:
        push ebx
    L_004190c3:
        call asm_free_004524a1
    L_004190c8:
        add esp,4
    L_004190cb:
        xor eax,eax
    L_004190cd:
        pop ebx
    L_004190ce:
        ret
    L_004190cf:
        mov eax,ebx
    L_004190d1:
        pop ebx
    L_004190d2:
        ret
    }
}

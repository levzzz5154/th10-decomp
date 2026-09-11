#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00422360..0x004223A2: Recovery_CreateTimerState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateTimerState_00422360() {
    __asm {
    L_00422360:
        push ebx
    L_00422361:
        push 2C8h
    L_00422366:
        call asm_operator_new_00452493
    L_0042236b:
        add esp,4
    L_0042236e:
        test eax,eax
    L_00422370:
        je short L_0042237d
    L_00422372:
        mov edx,eax
    L_00422374:
        call asm_RecoveryState_Initialize_004220e0
    L_00422379:
        mov ebx,eax
    L_0042237b:
        jmp short L_0042237f
    L_0042237d:
        xor ebx,ebx
    L_0042237f:
        call asm_MainMenu_RegisterTasksRetail_00422150
    L_00422384:
        test eax,eax
    L_00422386:
        je short L_0042239f
    L_00422388:
        test ebx,ebx
    L_0042238a:
        je short L_0042239b
    L_0042238c:
        push ebx
    L_0042238d:
        call asm_FUN_00422220_00422220
    L_00422392:
        push ebx
    L_00422393:
        call asm_free_004524a1
    L_00422398:
        add esp,4
    L_0042239b:
        xor eax,eax
    L_0042239d:
        pop ebx
    L_0042239e:
        ret
    L_0042239f:
        mov eax,ebx
    L_004223a1:
        pop ebx
    L_004223a2:
        ret
    }
}

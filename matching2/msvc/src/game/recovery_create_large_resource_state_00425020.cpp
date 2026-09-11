#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00425020..0x00425064: Recovery_CreateLargeResourceState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateLargeResourceState_00425020() {
    __asm {
    L_00425020:
        push ebx
    L_00425021:
        push 4478h
    L_00425026:
        call asm_operator_new_00452493
    L_0042502b:
        add esp,4
    L_0042502e:
        test eax,eax
    L_00425030:
        je short L_0042503f
    L_00425032:
        push esi
    L_00425033:
        mov esi,eax
    L_00425035:
        call asm_FUN_004246c0_004246c0
    L_0042503a:
        mov ebx,eax
    L_0042503c:
        pop esi
    L_0042503d:
        jmp short L_00425041
    L_0042503f:
        xor ebx,ebx
    L_00425041:
        call asm_FUN_004247f0_004247f0
    L_00425046:
        test eax,eax
    L_00425048:
        je short L_00425061
    L_0042504a:
        test ebx,ebx
    L_0042504c:
        je short L_0042505d
    L_0042504e:
        push ebx
    L_0042504f:
        call asm_FUN_00424ed0_00424ed0
    L_00425054:
        push ebx
    L_00425055:
        call asm_free_004524a1
    L_0042505a:
        add esp,4
    L_0042505d:
        xor eax,eax
    L_0042505f:
        pop ebx
    L_00425060:
        ret
    L_00425061:
        mov eax,ebx
    L_00425063:
        pop ebx
    L_00425064:
        ret
    }
}

#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00413450..0x004134A3: ?Platform_ReleaseOwnedHandle@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_ReleaseOwnedHandle_00413450() {
    __asm {
    L_00413450:
        test ebx,ebx
    L_00413452:
        je short L_004134a3
    L_00413454:
        push esi
    L_00413455:
        mov esi,dword ptr [ebx+0Ch]
    L_00413458:
        test esi,esi
    L_0041345a:
        push edi
    L_0041345b:
        mov edi,dword ptr [data_00491be4]
    L_00413461:
        je short L_0041348e
    L_00413463:
        push 492274h
    L_00413468:
        call dword ptr [data_004660b0]
    L_0041346e:
        inc byte ptr [data_0049231c]
    L_00413474:
        mov ecx,esi
    L_00413476:
        mov edx,edi
    L_00413478:
        call asm_Scheduler_Remove_00449f60
    L_0041347d:
        push 492274h
    L_00413482:
        call dword ptr [data_004660b4]
    L_00413488:
        dec byte ptr [data_0049231c]
    L_0041348e:
        push ebx
    L_0041348f:
        mov dword ptr [data_00477708],0
    L_00413499:
        call asm_free_004524a1
    L_0041349e:
        add esp,4
    L_004134a1:
        pop edi
    L_004134a2:
        pop esi
    L_004134a3:
        ret
    }
}

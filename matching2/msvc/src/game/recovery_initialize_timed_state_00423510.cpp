#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00423510..0x00423568: ?Recovery_InitializeTimedState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeTimedState_00423510() {
    __asm {
    L_00423510:
        mov dword ptr [esi+4],0Dh
    L_00423517:
        mov eax,dword ptr [esi+20h]
    L_0042351a:
        xor ecx,ecx
    L_0042351c:
        test al,1
    L_0042351e:
        jne short L_0042353a
    L_00423520:
        or eax,1
    L_00423523:
        mov dword ptr [esi+14h],ecx
    L_00423526:
        mov dword ptr [esi+10h],0FFF0BDC1h
    L_0042352d:
        mov dword ptr [esi+18h],ecx
    L_00423530:
        mov dword ptr [esi+1Ch],476F78h
    L_00423537:
        mov dword ptr [esi+20h],eax
    L_0042353a:
        lea eax,[esi+1D8h]
    L_00423540:
        mov dword ptr [esi+14h],ecx
    L_00423543:
        mov dword ptr [esi+18h],ecx
    L_00423546:
        mov dword ptr [esi+10h],0FFFFFFFFh
    L_0042354d:
        call asm_FUN_00409e50_00409e50
    L_00423552:
        lea eax,[esi+1D4h]
    L_00423558:
        call asm_FUN_00409e50_00409e50
    L_0042355d:
        mov eax,dword ptr [esi+2C0h]
    L_00423563:
        mov dword ptr [data_00476f78],eax
    L_00423568:
        ret
    }
}

#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0043D790..0x0043D7C6: ?Recovery_SelectArchiveEntry@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_SelectArchiveEntry_0043d790() {
    __asm {
    L_0043d790:
        push esi
    L_0043d791:
        mov esi,eax
    L_0043d793:
        mov eax,dword ptr [esi+5208h]
    L_0043d799:
        test eax,eax
    L_0043d79b:
        jne short L_0043d7a2
    L_0043d79d:
        or eax,0FFFFFFFFh
    L_0043d7a0:
        pop esi
    L_0043d7a1:
        ret
    L_0043d7a2:
        push esi
    L_0043d7a3:
        call asm_Path_FindBasenameSlot_0043d2a0
    L_0043d7a8:
        mov ecx,eax
    L_0043d7aa:
        mov eax,dword ptr [esi+1F84h]
    L_0043d7b0:
        imul ecx,34h
    L_0043d7b3:
        add ecx,eax
    L_0043d7b5:
        mov eax,dword ptr [esi+5208h]
    L_0043d7bb:
        mov esi,dword ptr [eax+0Ch]
    L_0043d7be:
        call asm_Platform_SelectStreamRecord_0044dca0
    L_0043d7c3:
        xor eax,eax
    L_0043d7c5:
        pop esi
    L_0043d7c6:
        ret
    }
}

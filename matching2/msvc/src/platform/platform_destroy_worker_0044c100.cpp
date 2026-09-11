#include <string.h>
#include "asm_encoding.hpp"
#include "th10/platform/windows_types.hpp"
#include "asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"

// 0x00436570..0x00436638: ?Platform_LaunchProcess@@
// Naked body preserves the retail register/stack ABI.

// 0x0044C100..0x0044C123: ?Platform_DestroyWorker@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_DestroyWorker_0044c100() {
    __asm {
    L_0044c100:
        push esi
    L_0044c101:
        mov esi,ecx
    L_0044c103:
        mov dword ptr [esi],4703E4h
    L_0044c109:
        call asm_Platform_StopWorker_0044c150
    L_0044c10e:
        test byte ptr [esp+8],1
    L_0044c113:
        je short L_0044c11e
    L_0044c115:
        push esi
    L_0044c116:
        call asm_free_004524a1
    L_0044c11b:
        add esp,4
    L_0044c11e:
        mov eax,esi
    L_0044c120:
        pop esi
    L_0044c121:
        ret 4
    }
}

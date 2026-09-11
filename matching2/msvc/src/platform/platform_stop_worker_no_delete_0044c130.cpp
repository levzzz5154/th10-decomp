#include <string.h>
#include "asm_encoding.hpp"
#include "th10/platform/windows_types.hpp"
#include "asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"

// 0x00436570..0x00436638: ?Platform_LaunchProcess@@
// Naked body preserves the retail register/stack ABI.

// 0x0044C130..0x0044C13F: ?Platform_StopWorkerNoDelete@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_StopWorkerNoDelete_0044c130() {
    __asm {
    L_0044c130:
        push esi
    L_0044c131:
        mov esi,ecx
    L_0044c133:
        mov dword ptr [ecx],4703E4h
    L_0044c139:
        call asm_Platform_StopWorker_0044c150
    L_0044c13e:
        pop esi
    L_0044c13f:
        ret
    }
}

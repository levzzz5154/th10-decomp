#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00401520..0x00401529: GameThread_RunQueueLeaf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_RunQueueLeaf_00401520() {
    __asm {
    L_00401520:
        push ebx
    L_00401521:
        mov ebx,ecx
    L_00401523:
        call asm_FUN_00401a50_00401a50
    L_00401528:
        pop ebx
    L_00401529:
        ret
    }
}

#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00412ED0..0x00412EDF: Score_SetMode
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Score_SetMode_00412ed0() {
    __asm {
    L_00412ed0:
        cmp dword ptr [eax+44h],ecx
    L_00412ed3:
        mov dword ptr [eax+44h],ecx
    L_00412ed6:
        je short L_00412edf
    L_00412ed8:
        mov dword ptr [eax+4Ch],0
    L_00412edf:
        ret
    }
}

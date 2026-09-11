#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x004297B0..0x004297C1: ?Platform_DeletingDestructorWithRelease@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_DeletingDestructorWithRelease_004297b0() {
    __asm {
    L_004297b0:
        test esi,esi
    L_004297b2:
        je short L_004297c1
    L_004297b4:
        push esi
    L_004297b5:
        call asm_FUN_004294a0_004294a0
    L_004297ba:
        push esi
    L_004297bb:
        call asm_free_004524a1
    L_004297c0:
        pop ecx
    L_004297c1:
        ret
    }
}

#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00412AA0..0x00412AB9: Ecl_ForwardFloat
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Ecl_ForwardFloat_00412aa0() {
    __asm {
    L_00412aa0:
        mov ecx,dword ptr [esp+8]
    L_00412aa4:
        mov eax,dword ptr [eax+14D8h]
    L_00412aaa:
        mov eax,dword ptr [eax+4]
    L_00412aad:
        push ecx
    L_00412aae:
        mov ecx,dword ptr [esp+8]
    L_00412ab2:
        call asm_ECL_ResolveFloatValue_0044ff80
    L_00412ab7:
        ret 8
    }
}

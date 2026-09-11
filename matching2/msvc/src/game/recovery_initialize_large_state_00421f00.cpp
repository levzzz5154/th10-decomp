#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00421F00..0x00421F46: ?Recovery_InitializeLargeState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeLargeState_00421f00() {
    __asm {
    L_00421f00:
        push edi
    L_00421f01:
        lea edx,[esi+120h]
    L_00421f07:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00421f0c:
        xor eax,eax
    L_00421f0e:
        mov dword ptr [esi+630h],eax
    L_00421f14:
        mov dword ptr [esi+634h],eax
    L_00421f1a:
        mov dword ptr [esi+638h],eax
    L_00421f20:
        mov dword ptr [esi+63Ch],eax
    L_00421f26:
        mov dword ptr [esi+62Ch],4703E4h
    L_00421f30:
        mov ecx,1E1h
    L_00421f35:
        mov edi,esi
    L_00421f37:
        rep stosd
    L_00421f39:
        or dword ptr [esi+3CCh],140h
    L_00421f43:
        mov eax,esi
    L_00421f45:
        pop edi
    L_00421f46:
        ret
    }
}

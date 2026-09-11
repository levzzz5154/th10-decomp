#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0040C9A0..0x0040C9CF: Recovery_ResetEmitter
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ResetEmitter_0040c9a0() {
    __asm {
    L_0040c9a0:
        push esi
    L_0040c9a1:
        mov esi,eax
    L_0040c9a3:
        mov eax,dword ptr [edi]
    L_0040c9a5:
        test eax,eax
    L_0040c9a7:
        jle short L_0040c9c2
    L_0040c9a9:
        push 400CCCCDh
    L_0040c9ae:
        push 0BFC90FDBh
    L_0040c9b3:
        push 0FFFFFFFFh
    L_0040c9b5:
        push eax
    L_0040c9b6:
        mov eax,dword ptr [data_00477818]
    L_0040c9bb:
        mov ecx,esi
    L_0040c9bd:
        call asm_FUN_0041bb00_0041bb00
    L_0040c9c2:
        push edi
    L_0040c9c3:
        call asm_FUN_0040c9d0_0040c9d0
    L_0040c9c8:
        mov dword ptr [edi],0
    L_0040c9ce:
        pop esi
    L_0040c9cf:
        ret
    }
}

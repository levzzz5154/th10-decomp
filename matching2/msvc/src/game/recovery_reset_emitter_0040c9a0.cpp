#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// BLOCKED (D3201): closest_byte_count=8/48; first_diff=0x0040C9A2
// (standalone readable member candidate, authoritative probe extent 55 bytes).
// residual_class=private EAX receiver plus EDI count pointer, and the
// 0041BB00 custom EAX/ECX/stack call ABI; 0040C9D0 is a stdcall callee.
// variants_tested=typed readable Reset(int*) member with stack helper
// declarations; the candidate was restored after 40 differing bytes in the
// measured 48-byte prefix.
// next_lever=schema2 native-LTCG cluster with the dispatch caller and anchors
// for 0040C9D0 and 0041BB00; preserve this exact body until 48 bytes match.
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

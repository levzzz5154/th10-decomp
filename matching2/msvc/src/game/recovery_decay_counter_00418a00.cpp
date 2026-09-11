#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00418A00..0x00418A40: Recovery_DecayCounter
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_DecayCounter_00418a00() {
    __asm {
    L_00418a00:
        mov ecx,dword ptr [eax+18h]
    L_00418a03:
        test ecx,ecx
    L_00418a05:
        push esi
    L_00418a06:
        jle short L_00418a17
    L_00418a08:
        push 0BF800000h
    L_00418a0d:
        lea esi,[eax+14h]
    L_00418a10:
        call asm_FrameTimer_Advance_0044bf40
    L_00418a15:
        pop esi
    L_00418a16:
        ret
    L_00418a17:
        mov ecx,dword ptr [eax+0Ch]
    L_00418a1a:
        mov esi,1388h
    L_00418a1f:
        cmp ecx,esi
    L_00418a21:
        jle short L_00418a3f
    L_00418a23:
        mov edx,dword ptr [eax+10h]
    L_00418a26:
        sub ecx,edx
    L_00418a28:
        cmp edx,12h
    L_00418a2b:
        mov dword ptr [eax+0Ch],ecx
    L_00418a2e:
        jge short L_00418a37
    L_00418a30:
        mov dword ptr [eax+10h],12h
    L_00418a37:
        cmp dword ptr [eax+0Ch],esi
    L_00418a3a:
        jge short L_00418a3f
    L_00418a3c:
        mov dword ptr [eax+0Ch],esi
    L_00418a3f:
        pop esi
    L_00418a40:
        ret
    }
}

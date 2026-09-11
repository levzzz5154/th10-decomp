#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0044D5D0..0x0044D5F8: Platform_InvokeConfigured
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_InvokeConfigured_0044d5d0() {
    __asm {
    L_0044d5d0:
        mov ecx,dword ptr [eax+4]
    L_0044d5d3:
        test ecx,ecx
    L_0044d5d5:
        jne short L_0044d5dd
    L_0044d5d7:
        mov eax,800401F0h
    L_0044d5dc:
        ret
    L_0044d5dd:
        mov ecx,dword ptr [ecx]
    L_0044d5df:
        push esi
    L_0044d5e0:
        mov esi,dword ptr [eax+24h]
    L_0044d5e3:
        mov dword ptr [eax+30h],1
    L_0044d5ea:
        mov eax,dword ptr [eax+20h]
    L_0044d5ed:
        mov edx,dword ptr [ecx]
    L_0044d5ef:
        push esi
    L_0044d5f0:
        push eax
    L_0044d5f1:
        push 0
    L_0044d5f3:
        push ecx
    L_0044d5f4:
        call dword ptr [edx+30h]
    L_0044d5f7:
        pop esi
    L_0044d5f8:
        ret
    }
}

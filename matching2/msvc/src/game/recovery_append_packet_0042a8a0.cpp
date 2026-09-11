#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0042A8A0..0x0042A8F4: Recovery_AppendPacket
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_AppendPacket_0042a8a0() {
    __asm {
    L_0042a8a0:
        mov ecx,dword ptr [eax+5460h]
    L_0042a8a6:
        mov word ptr [ecx],dx
    L_0042a8a9:
        mov ecx,dword ptr [eax+5460h]
    L_0042a8af:
        mov dx,word ptr [esp+4]
    L_0042a8b4:
        mov word ptr [ecx+2],dx
    L_0042a8b8:
        mov ecx,dword ptr [eax+5460h]
    L_0042a8be:
        mov dx,word ptr [esp+8]
    L_0042a8c3:
        mov word ptr [ecx+4],dx
    L_0042a8c7:
        mov ecx,dword ptr [eax+5460h]
    L_0042a8cd:
        add ecx,6
    L_0042a8d0:
        mov dword ptr [eax+5460h],ecx
    L_0042a8d6:
        sub ecx,eax
    L_0042a8d8:
        mov eax,2AAAAAABh
    L_0042a8dd:
        imul ecx
    L_0042a8df:
        mov eax,edx
    L_0042a8e1:
        shr eax,1Fh
    L_0042a8e4:
        add eax,edx
    L_0042a8e6:
        xor ecx,ecx
    L_0042a8e8:
        cmp eax,0E10h
    L_0042a8ed:
        setge cl
    L_0042a8f0:
        mov eax,ecx
    L_0042a8f2:
        ret 8
    }
}

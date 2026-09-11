#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0044D370..0x0044D3D6: ?Platform_FindAvailable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_FindAvailable_0044d370() {
    __asm {
    L_0044d370:
        push ecx
    L_0044d371:
        mov eax,dword ptr [edi+4]
    L_0044d374:
        test eax,eax
    L_0044d376:
        jne short L_0044d37c
    L_0044d378:
        xor eax,eax
    L_0044d37a:
        pop ecx
    L_0044d37b:
        ret
    L_0044d37c:
        mov eax,dword ptr [edi+10h]
    L_0044d37f:
        push esi
    L_0044d380:
        xor esi,esi
    L_0044d382:
        test eax,eax
    L_0044d384:
        jbe short L_0044d3b6
    L_0044d386:
        mov eax,dword ptr [edi+4]
    L_0044d389:
        cmp dword ptr [eax+esi*4],0
    L_0044d38d:
        je short L_0044d3ae
    L_0044d38f:
        mov ecx,eax
    L_0044d391:
        mov dword ptr [esp+4],0
    L_0044d399:
        mov eax,dword ptr [ecx+esi*4]
    L_0044d39c:
        mov edx,dword ptr [eax]
    L_0044d39e:
        lea ecx,[esp+4]
    L_0044d3a2:
        push ecx
    L_0044d3a3:
        push eax
    L_0044d3a4:
        call dword ptr [edx+24h]
    L_0044d3a7:
        test byte ptr [esp+4],1
    L_0044d3ac:
        je short L_0044d3b6
    L_0044d3ae:
        mov eax,dword ptr [edi+10h]
    L_0044d3b1:
        inc esi
    L_0044d3b2:
        cmp esi,eax
    L_0044d3b4:
        jb short L_0044d386
    L_0044d3b6:
        cmp esi,dword ptr [edi+10h]
    L_0044d3b9:
        je short L_0044d3c4
    L_0044d3bb:
        mov edx,dword ptr [edi+4]
    L_0044d3be:
        mov eax,dword ptr [edx+esi*4]
    L_0044d3c1:
        pop esi
    L_0044d3c2:
        pop ecx
    L_0044d3c3:
        ret
    L_0044d3c4:
        call asm_rand_0045371b
    L_0044d3c9:
        xor edx,edx
    L_0044d3cb:
        div dword ptr [edi+10h]
    L_0044d3ce:
        mov eax,dword ptr [edi+4]
    L_0044d3d1:
        pop esi
    L_0044d3d2:
        mov eax,dword ptr [eax+edx*4]
    L_0044d3d5:
        pop ecx
    L_0044d3d6:
        ret
    }
}

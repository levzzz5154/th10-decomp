#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0044D600..0x0044D63C: ?Platform_QueryInterfaces@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_QueryInterfaces_0044d600() {
    __asm {
    L_0044d600:
        mov eax,dword ptr [edi+4]
    L_0044d603:
        test eax,eax
    L_0044d605:
        jne short L_0044d60d
    L_0044d607:
        mov eax,800401F0h
    L_0044d60c:
        ret
    L_0044d60d:
        mov eax,dword ptr [edi+10h]
    L_0044d610:
        push ebx
    L_0044d611:
        push esi
    L_0044d612:
        xor ebx,ebx
    L_0044d614:
        xor esi,esi
    L_0044d616:
        test eax,eax
    L_0044d618:
        jbe short L_0044d638
    L_0044d61a:
        lea ebx,[ebx+force_disp32_zero]
    L_0044d620:
        mov eax,dword ptr [edi+4]
    L_0044d623:
        mov eax,dword ptr [eax+esi*4]
    L_0044d626:
        mov ecx,dword ptr [eax]
    L_0044d628:
        push 0
    L_0044d62a:
        push eax
    L_0044d62b:
        call dword ptr [ecx+34h]
    L_0044d62e:
        or ebx,eax
    L_0044d630:
        mov eax,dword ptr [edi+10h]
    L_0044d633:
        inc esi
    L_0044d634:
        cmp esi,eax
    L_0044d636:
        jb short L_0044d620
    L_0044d638:
        pop esi
    L_0044d639:
        mov eax,ebx
    L_0044d63b:
        pop ebx
    L_0044d63c:
        ret
    }
}

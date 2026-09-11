#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0044D6A0..0x0044D70C: Recovery_InitializeSingleInterface
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeSingleInterface_0044d6a0() {
    __asm {
    L_0044d6a0:
        push edi
    L_0044d6a1:
        push 4
    L_0044d6a3:
        mov dword ptr [esi],4705D8h
    L_0044d6a9:
        call asm_operator_new_00452493
    L_0044d6ae:
        mov ecx,dword ptr [esp+0Ch]
    L_0044d6b2:
        mov edx,dword ptr [esp+10h]
    L_0044d6b6:
        mov dword ptr [esi+4],eax
    L_0044d6b9:
        mov dword ptr [eax],ecx
    L_0044d6bb:
        mov eax,dword ptr [esp+14h]
    L_0044d6bf:
        mov ecx,dword ptr [esi+4]
    L_0044d6c2:
        add esp,4
    L_0044d6c5:
        mov dword ptr [esi+0Ch],eax
    L_0044d6c8:
        mov dword ptr [esi+8],edx
    L_0044d6cb:
        mov dword ptr [esi+10h],1
    L_0044d6d2:
        mov edx,dword ptr [ecx]
    L_0044d6d4:
        xor edi,edi
    L_0044d6d6:
        push edi
    L_0044d6d7:
        push edx
    L_0044d6d8:
        mov eax,esi
    L_0044d6da:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0044d6df:
        mov eax,dword ptr [esi+4]
    L_0044d6e2:
        mov eax,dword ptr [eax]
    L_0044d6e4:
        mov ecx,dword ptr [eax]
    L_0044d6e6:
        push edi
    L_0044d6e7:
        push eax
    L_0044d6e8:
        call dword ptr [ecx+34h]
    L_0044d6eb:
        mov edx,dword ptr [esp+14h]
    L_0044d6ef:
        mov dword ptr [esi+30h],edi
    L_0044d6f2:
        mov dword ptr [esi+5Ch],edi
    L_0044d6f5:
        mov dword ptr [esi+60h],edi
    L_0044d6f8:
        mov dword ptr [esi+64h],edi
    L_0044d6fb:
        mov dword ptr [esi+68h],edi
    L_0044d6fe:
        mov dword ptr [esi],4705D4h
    L_0044d704:
        mov dword ptr [esi+6Ch],edx
    L_0044d707:
        mov eax,esi
    L_0044d709:
        pop edi
    L_0044d70a:
        ret 10h
    }
}

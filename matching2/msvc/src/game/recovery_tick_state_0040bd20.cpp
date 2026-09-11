#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0040BD20..0x0040BD7C: ?Recovery_TickState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_TickState_0040bd20() {
    __asm {
    L_0040bd20:
        push esi
    L_0040bd21:
        call asm_FUN_0040bd80_0040bd80
    L_0040bd26:
        test eax,eax
    L_0040bd28:
        je short L_0040bd30
    L_0040bd2a:
        mov eax,1
    L_0040bd2f:
        ret
    L_0040bd30:
        mov edx,dword ptr [esi+8]
    L_0040bd33:
        mov ecx,dword ptr [esi+10h]
    L_0040bd36:
        mov dword ptr [esi+4],edx
    L_0040bd39:
        fld dword ptr [ecx]
    L_0040bd3b:
        fcomp dword ptr [data_00470b68]
    L_0040bd41:
        fnstsw ax
    L_0040bd43:
        test ah,41h
    L_0040bd46:
        jne short L_0040bd6a
    L_0040bd48:
        fld dword ptr [ecx]
    L_0040bd4a:
        fcomp dword ptr [data_00470b64]
    L_0040bd50:
        fnstsw ax
    L_0040bd52:
        test ah,5
    L_0040bd55:
        jp short L_0040bd6a
    L_0040bd57:
        fld dword ptr [esi+0Ch]
    L_0040bd5a:
        inc edx
    L_0040bd5b:
        fadd dword ptr [data_00470afc]
    L_0040bd61:
        mov dword ptr [esi+8],edx
    L_0040bd64:
        xor eax,eax
    L_0040bd66:
        fstp dword ptr [esi+0Ch]
    L_0040bd69:
        ret
    L_0040bd6a:
        fld dword ptr [esi+0Ch]
    L_0040bd6d:
        fadd dword ptr [ecx]
    L_0040bd6f:
        fst dword ptr [esi+0Ch]
    L_0040bd72:
        call asm_FUN_00463b2c_00463b2c
    L_0040bd77:
        mov dword ptr [esi+8],eax
    L_0040bd7a:
        xor eax,eax
    L_0040bd7c:
        ret
    }
}

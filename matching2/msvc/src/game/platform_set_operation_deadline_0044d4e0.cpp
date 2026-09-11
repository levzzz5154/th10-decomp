#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0044D4E0..0x0044D549: ?Platform_SetOperationDeadline@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_SetOperationDeadline_0044d4e0() {
    __asm {
    L_0044d4e0:
        mov ecx,dword ptr [data_00497854]
    L_0044d4e6:
        test ecx,ecx
    L_0044d4e8:
        je short L_0044d537
    L_0044d4ea:
        fild dword ptr [data_00497854]
    L_0044d4f0:
        mov ecx,dword ptr [esp+4]
    L_0044d4f4:
        mov eax,dword ptr [eax+4]
    L_0044d4f7:
        add ecx,1388h
    L_0044d4fd:
        fmul dword ptr [data_00470b00]
    L_0044d503:
        mov dword ptr [esp+4],ecx
    L_0044d507:
        push esi
    L_0044d508:
        mov esi,dword ptr [eax]
    L_0044d50a:
        fsubr dword ptr [data_00470afc]
    L_0044d510:
        push edi
    L_0044d511:
        mov edi,dword ptr [esi]
    L_0044d513:
        fld st(0)
    L_0044d515:
        fmul st,st(1)
    L_0044d517:
        fsubr dword ptr [data_00470afc]
    L_0044d51d:
        fimul dword ptr [esp+0Ch]
    L_0044d521:
        call asm_FUN_00463b2c_00463b2c
    L_0044d526:
        fstp st(0)
    L_0044d528:
        sub eax,1388h
    L_0044d52d:
        push eax
    L_0044d52e:
        push esi
    L_0044d52f:
        call dword ptr [edi+3Ch]
    L_0044d532:
        pop edi
    L_0044d533:
        pop esi
    L_0044d534:
        ret 4
    L_0044d537:
        mov edx,dword ptr [eax+4]
    L_0044d53a:
        mov eax,dword ptr [edx]
    L_0044d53c:
        mov ecx,dword ptr [eax]
    L_0044d53e:
        push 0FFFFD8F0h
    L_0044d543:
        push eax
    L_0044d544:
        call dword ptr [ecx+3Ch]
    L_0044d547:
        ret 4
    }
}

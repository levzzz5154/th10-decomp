#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00405040..0x0040509D: Recovery_InitializeWordColor
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeWordColor_00405040() {
    __asm {
    L_00405040:
        mov eax,dword ptr [esp+4]
    L_00405044:
        fld dword ptr [esp+0Ch]
    L_00405048:
        mov ecx,dword ptr [esp+8]
    L_0040504c:
        mov edx,dword ptr [esp+0Ch]
    L_00405050:
        mov dword ptr [esi],eax
    L_00405052:
        mov eax,dword ptr [esp+10h]
    L_00405056:
        mov dword ptr [esi+4],ecx
    L_00405059:
        mov ecx,dword ptr [esp+14h]
    L_0040505d:
        mov dword ptr [esi+8],edx
    L_00405060:
        mov edx,dword ptr [esp+18h]
    L_00405064:
        mov dword ptr [esi+0Ch],eax
    L_00405067:
        mov dword ptr [esi+10h],ecx
    L_0040506a:
        mov dword ptr [esi+14h],edx
    L_0040506d:
        call asm_FUN_00463b2c_00463b2c
    L_00405072:
        fld dword ptr [esp+10h]
    L_00405076:
        mov byte ptr [esi+18h],al
    L_00405079:
        call asm_FUN_00463b2c_00463b2c
    L_0040507e:
        fld dword ptr [esp+14h]
    L_00405082:
        mov byte ptr [esi+19h],al
    L_00405085:
        call asm_FUN_00463b2c_00463b2c
    L_0040508a:
        fld dword ptr [esp+18h]
    L_0040508e:
        mov byte ptr [esi+1Ah],al
    L_00405091:
        call asm_FUN_00463b2c_00463b2c
    L_00405096:
        mov byte ptr [esi+1Bh],al
    L_00405099:
        mov eax,esi
    L_0040509b:
        ret 18h
    }
}

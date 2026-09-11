#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00418810..0x0041884F: Recovery_OffsetPoint
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_OffsetPoint_00418810() {
    __asm {
    L_00418810:
        mov dl,byte ptr [data_00497d8c]
    L_00418816:
        mov ecx,1
    L_0041881b:
        test dl,cl
    L_0041881d:
        jne short L_00418825
    L_0041881f:
        or dword ptr [data_00497d8c],ecx
    L_00418825:
        fld dword ptr [eax]
    L_00418827:
        fadd dword ptr [data_00470b4c]
    L_0041882d:
        fstp dword ptr [data_00497d80]
    L_00418833:
        fld dword ptr [eax+4]
    L_00418836:
        fadd dword ptr [data_00470b48]
    L_0041883c:
        fstp dword ptr [data_00497d84]
    L_00418842:
        mov eax,dword ptr [eax+8]
    L_00418845:
        mov dword ptr [data_00497d88],eax
    L_0041884a:
        mov eax,497D80h
    L_0041884f:
        ret
    }
}

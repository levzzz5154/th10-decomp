#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00413790..0x004137CC: Animation_SetActiveCount
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Animation_SetActiveCount_00413790() {
    __asm {
    L_00413790:
        xor edx,edx
    L_00413792:
        test ecx,ecx
    L_00413794:
        push edi
    L_00413795:
        mov edi,eax
    L_00413797:
        jle short L_004137b5
    L_00413799:
        push esi
    L_0041379a:
        lea eax,[edi+4CDCh]
    L_004137a0:
        mov esi,ecx
    L_004137a2:
        mov edx,ecx
    L_004137a4:
        or dword ptr [eax],2
    L_004137a7:
        add eax,3ACh
    L_004137ac:
        dec esi
    L_004137ad:
        jne short L_004137a4
    L_004137af:
        cmp ecx,9
    L_004137b2:
        pop esi
    L_004137b3:
        TH10_REL8(0x7d, 0x004137b3, VA_asm_target_004137db)
    L_004137b5:
        mov eax,edx
    L_004137b7:
        imul eax,3ACh
    L_004137bd:
        mov ecx,9
    L_004137c2:
        lea eax,[eax+edi+4CDCh]
    L_004137c9:
        sub ecx,edx
    L_004137cb:
        TH10_REL8(0xeb, 0x004137cb, VA_asm_Animation_SetActiveCount_part_004137d0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004137d0:
        and dword ptr [eax],0FFFFFFFDh
    L_004137d3:
        add eax,3ACh
    L_004137d8:
        dec ecx
    L_004137d9:
        jne short L_004137d0
    L_004137db:
        pop edi
    L_004137dc:
        ret
    }
}

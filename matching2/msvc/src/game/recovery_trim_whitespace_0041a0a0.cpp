#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0041A0A0..0x0041A0DC: Recovery_TrimWhitespace
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_TrimWhitespace_0041a0a0() {
    __asm {
    L_0041a0a0:
        push esi
    L_0041a0a1:
        push edi
    L_0041a0a2:
        mov cl,byte ptr [eax]
    L_0041a0a4:
        cmp cl,20h
    L_0041a0a7:
        je short L_0041a0b8
    L_0041a0a9:
        cmp cl,9
    L_0041a0ac:
        je short L_0041a0b8
    L_0041a0ae:
        cmp cl,0Ah
    L_0041a0b1:
        je short L_0041a0b8
    L_0041a0b3:
        cmp cl,0Dh
    L_0041a0b6:
        jne short L_0041a0d6
    L_0041a0b8:
        mov ecx,eax
    L_0041a0ba:
        lea esi,[ecx+1]
    L_0041a0bd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041a0c0:
        mov dl,byte ptr [ecx]
    L_0041a0c2:
        inc ecx
    L_0041a0c3:
        test dl,dl
    L_0041a0c5:
        jne short L_0041a0c0
    L_0041a0c7:
        sub ecx,esi
    L_0041a0c9:
        test ecx,ecx
    L_0041a0cb:
        jle short L_0041a0a2
    L_0041a0cd:
        lea esi,[eax+1]
    L_0041a0d0:
        mov edi,eax
    L_0041a0d2:
        rep movsb
    L_0041a0d4:
        jmp short L_0041a0a2
    L_0041a0d6:
        mov ecx,eax
    L_0041a0d8:
        lea esi,[ecx+1]
    L_0041a0db:
        TH10_REL8(0xeb, 0x0041a0db, VA_asm_Recovery_TrimWhitespace_part_0041a0e0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0041a0e0:
        mov dl,byte ptr [ecx]
    L_0041a0e2:
        inc ecx
    L_0041a0e3:
        test dl,dl
    L_0041a0e5:
        jne short L_0041a0e0
    L_0041a0e7:
        sub ecx,esi
    L_0041a0e9:
        lea edx,[ecx-1]
    L_0041a0ec:
        test edx,edx
    L_0041a0ee:
        pop edi
    L_0041a0ef:
        pop esi
    L_0041a0f0:
        jl short L_0041a111
    L_0041a0f2:
        mov cl,byte ptr [edx+eax]
    L_0041a0f5:
        cmp cl,20h
    L_0041a0f8:
        je short L_0041a109
    L_0041a0fa:
        cmp cl,9
    L_0041a0fd:
        je short L_0041a109
    L_0041a0ff:
        cmp cl,0Ah
    L_0041a102:
        je short L_0041a109
    L_0041a104:
        cmp cl,0Dh
    L_0041a107:
        jne short L_0041a111
    L_0041a109:
        dec edx
    L_0041a10a:
        mov byte ptr [edx+eax+1],0
    L_0041a10f:
        jns short L_0041a0f2
    L_0041a111:
        ret
    }
}

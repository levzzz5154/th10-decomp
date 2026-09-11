#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0041A050..0x0041A09A: Recovery_SplitResourcePath
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_SplitResourcePath_0041a050() {
    __asm {
    L_0041a050:
        mov edx,edi
    L_0041a052:
        sub edx,eax
    L_0041a054:
        mov cl,byte ptr [eax]
    L_0041a056:
        mov byte ptr [edx+eax],cl
    L_0041a059:
        inc eax
    L_0041a05a:
        test cl,cl
    L_0041a05c:
        jne short L_0041a054
    L_0041a05e:
        push 3Ah
    L_0041a060:
        push edi
    L_0041a061:
        call asm_FUN_00452730_00452730
    L_0041a066:
        add esp,8
    L_0041a069:
        test eax,eax
    L_0041a06b:
        jne short L_0041a074
    L_0041a06d:
        mov eax,edi
    L_0041a06f:
        jmp asm_Recovery_TrimWhitespace_0041a0a0
    L_0041a074:
        push esi
    L_0041a075:
        lea ecx,[eax+1]
    L_0041a078:
        mov esi,ebx
    L_0041a07a:
        sub esi,ecx
    L_0041a07c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0041a080:
        mov dl,byte ptr [ecx]
    L_0041a082:
        mov byte ptr [esi+ecx],dl
    L_0041a085:
        inc ecx
    L_0041a086:
        test dl,dl
    L_0041a088:
        jne short L_0041a080
    L_0041a08a:
        mov byte ptr [eax],dl
    L_0041a08c:
        mov eax,edi
    L_0041a08e:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_0041a093:
        mov eax,ebx
    L_0041a095:
        pop esi
    L_0041a096:
        jmp asm_Recovery_TrimWhitespace_0041a0a0
    }
}

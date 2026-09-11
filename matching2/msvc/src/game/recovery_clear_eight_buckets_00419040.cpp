#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00419040..0x0041908E: Recovery_ClearEightBuckets
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ClearEightBuckets_00419040() {
    __asm {
    L_00419040:
        push ebx
    L_00419041:
        push esi
    L_00419042:
        push edi
    L_00419043:
        mov edi,eax
    L_00419045:
        add edi,7Ch
    L_00419048:
        mov ebx,8
    L_0041904d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00419050:
        mov eax,dword ptr [edi-60h]
    L_00419053:
        test eax,eax
    L_00419055:
        je short L_0041906b
    L_00419057:
        mov esi,dword ptr [eax+4]
    L_0041905a:
        mov eax,dword ptr [eax]
    L_0041905c:
        push eax
    L_0041905d:
        call asm_free_004524a1
    L_00419062:
        add esp,4
    L_00419065:
        test esi,esi
    L_00419067:
        mov eax,esi
    L_00419069:
        jne short L_00419057
    L_0041906b:
        mov eax,dword ptr [edi]
    L_0041906d:
        test eax,eax
    L_0041906f:
        je short L_00419085
    L_00419071:
        mov ecx,dword ptr [eax]
    L_00419073:
        mov esi,dword ptr [eax+4]
    L_00419076:
        push ecx
    L_00419077:
        call asm_free_004524a1
    L_0041907c:
        add esp,4
    L_0041907f:
        test esi,esi
    L_00419081:
        mov eax,esi
    L_00419083:
        jne short L_00419071
    L_00419085:
        add edi,0Ch
    L_00419088:
        dec ebx
    L_00419089:
        jne short L_00419050
    L_0041908b:
        pop edi
    L_0041908c:
        pop esi
    L_0041908d:
        pop ebx
    L_0041908e:
        ret
    }
}

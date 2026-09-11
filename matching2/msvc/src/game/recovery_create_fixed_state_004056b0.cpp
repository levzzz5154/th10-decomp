#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x004056B0..0x00405704: Recovery_CreateFixedState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateFixedState_004056b0() {
    __asm {
    L_004056b0:
        push ebx
    L_004056b1:
        push 48h
    L_004056b3:
        call asm_operator_new_00452493
    L_004056b8:
        mov edx,eax
    L_004056ba:
        add esp,4
    L_004056bd:
        test edx,edx
    L_004056bf:
        je short L_004056df
    L_004056c1:
        and dword ptr [edx+24h],0FFFFFFFEh
    L_004056c5:
        push edi
    L_004056c6:
        xor eax,eax
    L_004056c8:
        mov ecx,12h
    L_004056cd:
        mov edi,edx
    L_004056cf:
        rep stosd
    L_004056d1:
        or dword ptr [edx],2
    L_004056d4:
        mov dword ptr [data_004776ec],edx
    L_004056da:
        mov ebx,edx
    L_004056dc:
        pop edi
    L_004056dd:
        jmp short L_004056e1
    L_004056df:
        xor ebx,ebx
    L_004056e1:
        call asm_Recovery_InstallPairSetFlags_004055c0
    L_004056e6:
        test eax,eax
    L_004056e8:
        je short L_00405701
    L_004056ea:
        test ebx,ebx
    L_004056ec:
        je short L_004056fd
    L_004056ee:
        push ebx
    L_004056ef:
        call asm_Recovery_ReleaseRawPairAndReset_00405620
    L_004056f4:
        push ebx
    L_004056f5:
        call asm_free_004524a1
    L_004056fa:
        add esp,4
    L_004056fd:
        xor eax,eax
    L_004056ff:
        pop ebx
    L_00405700:
        ret
    L_00405701:
        mov eax,ebx
    L_00405703:
        pop ebx
    L_00405704:
        ret
    }
}

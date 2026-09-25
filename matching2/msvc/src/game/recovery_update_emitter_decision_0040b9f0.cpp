#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0040B9F0..0x0040BA5E: Recovery_UpdateEmitterDecision
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_UpdateEmitterDecision_0040b9f0() {
    __asm {
    L_0040b9f0:
        push esi
    L_0040b9f1:
        mov esi,dword ptr [edi+18h]
    L_0040b9f4:
        call asm_Recovery_TickState_0040bd20
    L_0040b9f9:
        test eax,eax
    L_0040b9fb:
        je short L_0040ba1d
    L_0040b9fd:
        mov eax,dword ptr [data_00491ff4]
    L_0040ba02:
        and eax,1000h
    L_0040ba07:
        neg eax
    L_0040ba09:
        sbb eax,eax
    L_0040ba0b:
        and eax,0FFFFFFF3h
    L_0040ba0e:
        add eax,0Fh
    L_0040ba11:
        mov dword ptr [data_00491fb8],eax
    L_0040ba16:
        mov eax,1
    L_0040ba1b:
        pop esi
    L_0040ba1c:
        ret
    L_0040ba1d:
        mov esi,dword ptr [edi+24h]
    L_0040ba20:
        mov ecx,dword ptr [edi+18h]
    L_0040ba23:
        inc esi
    L_0040ba24:
        mov dword ptr [edi+24h],esi
    L_0040ba27:
        mov ecx,dword ptr [ecx+74h]
    L_0040ba2a:
        test cl,4
    L_0040ba2d:
        mov eax,esi
    L_0040ba2f:
        jne short L_0040ba58
    L_0040ba31:
        test byte ptr [edi+20h],2
    L_0040ba35:
        jne short L_0040ba58
    L_0040ba37:
        test cl,2
    L_0040ba3a:
        je short L_0040ba58
    L_0040ba3c:
        mov ecx,dword ptr [data_00474e30]
    L_0040ba42:
        test ch,1
    L_0040ba45:
        je short L_0040ba58
    L_0040ba47:
        cdq
    L_0040ba48:
        mov ecx,0Ch
    L_0040ba4d:
        idiv ecx
    L_0040ba4f:
        mov eax,6
    L_0040ba54:
        test edx,edx
    L_0040ba56:
        jne short L_0040ba5d
    L_0040ba58:
        mov eax,1
    L_0040ba5d:
        pop esi
    L_0040ba5e:
        ret
    }
}

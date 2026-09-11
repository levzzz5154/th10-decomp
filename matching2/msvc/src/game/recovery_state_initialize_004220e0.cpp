#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x004220E0..0x00422144: RecoveryState_Initialize
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RecoveryState_Initialize_004220e0() {
    __asm {
    L_004220e0:
        mov ecx,dword ptr [edx+20h]
    L_004220e3:
        xor eax,eax
    L_004220e5:
        and ecx,0FFFFFFFEh
    L_004220e8:
        mov dword ptr [edx+20h],ecx
    L_004220eb:
        mov dword ptr [edx+0B0h],eax
    L_004220f1:
        mov dword ptr [edx+24h],eax
    L_004220f4:
        mov dword ptr [edx+0F8h],eax
    L_004220fa:
        mov dword ptr [edx+0F4h],1
    L_00422104:
        mov ecx,3E7h
    L_00422109:
        mov dword ptr [edx+2Ch],ecx
    L_0042210c:
        mov dword ptr [edx+104h],ecx
    L_00422112:
        push edi
    L_00422113:
        mov dword ptr [edx+188h],eax
    L_00422119:
        mov dword ptr [edx+0FCh],eax
    L_0042211f:
        mov dword ptr [edx+1D0h],eax
    L_00422125:
        mov dword ptr [edx+1CCh],1
    L_0042212f:
        mov ecx,0B2h
    L_00422134:
        mov edi,edx
    L_00422136:
        rep stosd
    L_00422138:
        or dword ptr [edx],2
    L_0042213b:
        mov dword ptr [data_00477830],edx
    L_00422141:
        mov eax,edx
    L_00422143:
        pop edi
    L_00422144:
        ret
    }
}

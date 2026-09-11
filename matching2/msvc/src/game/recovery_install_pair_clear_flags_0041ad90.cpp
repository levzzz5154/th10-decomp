#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0041AD90..0x0041ADE3: ?Recovery_InstallPairClearFlags@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InstallPairClearFlags_0041ad90() {
    __asm {
    L_0041ad90:
        push esi
    L_0041ad91:
        push edi
    L_0041ad92:
        push 41BA00h
    L_0041ad97:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041ad9c:
        mov esi,eax
    L_0041ad9e:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041ada2:
        mov eax,dword ptr [data_00491be4]
    L_0041ada7:
        push eax
    L_0041ada8:
        mov edi,15h
    L_0041adad:
        mov dword ptr [esi+20h],ebx
    L_0041adb0:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0041adb5:
        push 41BA30h
    L_0041adba:
        mov dword ptr [ebx+8],esi
    L_0041adbd:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041adc2:
        mov esi,eax
    L_0041adc4:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041adc8:
        mov ecx,dword ptr [data_00491be4]
    L_0041adce:
        push ecx
    L_0041adcf:
        mov edi,19h
    L_0041add4:
        mov dword ptr [esi+20h],ebx
    L_0041add7:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0041addc:
        pop edi
    L_0041addd:
        mov dword ptr [ebx+0Ch],esi
    L_0041ade0:
        xor eax,eax
    L_0041ade2:
        pop esi
    L_0041ade3:
        ret
    }
}

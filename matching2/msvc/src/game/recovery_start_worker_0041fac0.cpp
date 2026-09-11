#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0041FAC0..0x0041FB4B: Recovery_StartWorker
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_StartWorker_0041fac0() {
    __asm {
    L_0041fac0:
        push esi
    L_0041fac1:
        push edi
    L_0041fac2:
        push 41FEB0h
    L_0041fac7:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041facc:
        mov esi,eax
    L_0041face:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041fad2:
        mov eax,dword ptr [data_00491be4]
    L_0041fad7:
        push eax
    L_0041fad8:
        mov edi,3
    L_0041fadd:
        mov dword ptr [esi+20h],ebx
    L_0041fae0:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0041fae5:
        push 41FEF0h
    L_0041faea:
        mov dword ptr [ebx+8],esi
    L_0041faed:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041faf2:
        mov esi,eax
    L_0041faf4:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041faf8:
        mov ecx,dword ptr [data_00491be4]
    L_0041fafe:
        push ecx
    L_0041faff:
        mov edi,2
    L_0041fb04:
        mov dword ptr [esi+20h],ebx
    L_0041fb07:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0041fb0c:
        mov dword ptr [ebx+0Ch],esi
    L_0041fb0f:
        lea esi,[ebx+10h]
    L_0041fb12:
        call asm_Platform_StopWorker_0044c150
    L_0041fb17:
        lea edx,[esi+8]
    L_0041fb1a:
        push edx
    L_0041fb1b:
        push 0
    L_0041fb1d:
        push ebx
    L_0041fb1e:
        push 41F990h
    L_0041fb23:
        push 0
    L_0041fb25:
        push 0
    L_0041fb27:
        mov dword ptr [esi+18h],41F990h
    L_0041fb2e:
        mov dword ptr [esi+10h],1
    L_0041fb35:
        mov dword ptr [esi+0Ch],0
    L_0041fb3c:
        call asm_beginthreadex_00453683
    L_0041fb41:
        add esp,18h
    L_0041fb44:
        mov dword ptr [esi+4],eax
    L_0041fb47:
        pop edi
    L_0041fb48:
        xor eax,eax
    L_0041fb4a:
        pop esi
    L_0041fb4b:
        ret
    }
}

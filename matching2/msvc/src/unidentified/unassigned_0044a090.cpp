#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044A090..0x0044A0BA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044a090() {
    __asm {
    L_0044a090:
        push esi
    L_0044a091:
        push eax
    L_0044a092:
        call asm_SchedulerCallback_Create_00449ed0
    L_0044a097:
        mov ecx,dword ptr [esp+8]
    L_0044a09b:
        mov edx,dword ptr [data_00491be4]
    L_0044a0a1:
        mov esi,eax
    L_0044a0a3:
        mov dword ptr [esi+20h],ecx
    L_0044a0a6:
        mov ecx,dword ptr [esi+4]
    L_0044a0a9:
        and ecx,0FFFFFFFDh
    L_0044a0ac:
        push edx
    L_0044a0ad:
        mov dword ptr [esi+4],ecx
    L_0044a0b0:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0044a0b5:
        mov eax,esi
    L_0044a0b7:
        pop esi
    L_0044a0b8:
        ret 4
    }
}

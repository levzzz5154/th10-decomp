#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.

// 0x0044A000..0x0044A02A: ?Scheduler_CreateAndRegister@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Scheduler_CreateAndRegister_0044a000() {
    __asm {
    L_0044a000:
        push esi
    L_0044a001:
        push eax
    L_0044a002:
        call asm_SchedulerCallback_Create_00449ed0
    L_0044a007:
        mov ecx,dword ptr [esp+8]
    L_0044a00b:
        mov edx,dword ptr [data_00491be4]
    L_0044a011:
        mov esi,eax
    L_0044a013:
        mov dword ptr [esi+20h],ecx
    L_0044a016:
        mov ecx,dword ptr [esi+4]
    L_0044a019:
        or ecx,2
    L_0044a01c:
        push edx
    L_0044a01d:
        mov dword ptr [esi+4],ecx
    L_0044a020:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0044a025:
        mov eax,esi
    L_0044a027:
        pop esi
    L_0044a028:
        ret 4
    }
}

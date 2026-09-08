#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BBD0..0x0042BC23: FUN_0042bbd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042bbd0_0042bbd0() {
    __asm {
    L_0042bbd0:
        push esi
    L_0042bbd1:
        push edi
    L_0042bbd2:
        push 42C580h
    L_0042bbd7:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042bbdc:
        mov esi,eax
    L_0042bbde:
        or dword ptr [esi+4],2
    L_0042bbe2:
        mov eax,dword ptr [data_00491be4]
    L_0042bbe7:
        push eax
    L_0042bbe8:
        mov edi,5
    L_0042bbed:
        mov dword ptr [esi+20h],ebx
    L_0042bbf0:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0042bbf5:
        push 42C590h
    L_0042bbfa:
        mov dword ptr [ebx+8],esi
    L_0042bbfd:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042bc02:
        mov esi,eax
    L_0042bc04:
        or dword ptr [esi+4],2
    L_0042bc08:
        mov ecx,dword ptr [data_00491be4]
    L_0042bc0e:
        push ecx
    L_0042bc0f:
        mov edi,27h
    L_0042bc14:
        mov dword ptr [esi+20h],ebx
    L_0042bc17:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0042bc1c:
        pop edi
    L_0042bc1d:
        mov dword ptr [ebx+0Ch],esi
    L_0042bc20:
        xor eax,eax
    L_0042bc22:
        pop esi
    L_0042bc23:
        ret
    }
}

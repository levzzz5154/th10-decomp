#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404530..0x004045A6: FUN_00404530
// Naked body preserves the retail register/stack ABI.

// 0x004055C0..0x00405613: ?Recovery_InstallPairSetFlags@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InstallPairSetFlags_004055c0() {
    __asm {
    L_004055c0:
        push esi
    L_004055c1:
        push edi
    L_004055c2:
        push 405840h
    L_004055c7:
        call asm_SchedulerCallback_Create_00449ed0
    L_004055cc:
        mov esi,eax
    L_004055ce:
        or dword ptr [esi+4],2
    L_004055d2:
        mov eax,dword ptr [data_00491be4]
    L_004055d7:
        push eax
    L_004055d8:
        mov edi,11h
    L_004055dd:
        mov dword ptr [esi+20h],ebx
    L_004055e0:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_004055e5:
        push 405850h
    L_004055ea:
        mov dword ptr [ebx+8],esi
    L_004055ed:
        call asm_SchedulerCallback_Create_00449ed0
    L_004055f2:
        mov esi,eax
    L_004055f4:
        or dword ptr [esi+4],2
    L_004055f8:
        mov ecx,dword ptr [data_00491be4]
    L_004055fe:
        push ecx
    L_004055ff:
        mov edi,22h
    L_00405604:
        mov dword ptr [esi+20h],ebx
    L_00405607:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0040560c:
        pop edi
    L_0040560d:
        mov dword ptr [ebx+0Ch],esi
    L_00405610:
        xor eax,eax
    L_00405612:
        pop esi
    L_00405613:
        ret
    }
}

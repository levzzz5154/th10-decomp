#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FF80..0x0041FFF0: FUN_0041ff80
// Naked body preserves the retail register/stack ABI.

// 0x00420470..0x0042053B: FUN_00420470
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420470_00420470() {
    __asm {
    L_00420470:
        push ebx
    L_00420471:
        push ebp
    L_00420472:
        push esi
    L_00420473:
        push edi
    L_00420474:
        xor eax,eax
    L_00420476:
        push 41FF80h
    L_0042047b:
        mov dword ptr [data_00491fb4],0FFFFFFFEh
    L_00420485:
        mov dword ptr [data_00491fb8],eax
    L_0042048a:
        mov dword ptr [data_00491fc0],eax
    L_0042048f:
        call asm_SchedulerCallback_Create_00449ed0
    L_00420494:
        mov esi,dword ptr [eax+4]
    L_00420497:
        mov ecx,dword ptr [data_00491be4]
    L_0042049d:
        mov ebx,2
    L_004204a2:
        or esi,ebx
    L_004204a4:
        mov dword ptr [eax+4],esi
    L_004204a7:
        mov ebp,491C28h
    L_004204ac:
        push ecx
    L_004204ad:
        mov edi,1
    L_004204b2:
        mov esi,eax
    L_004204b4:
        mov dword ptr [eax+20h],ebp
    L_004204b7:
        mov dword ptr [eax+0Ch],4201B0h
    L_004204be:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_004204c3:
        test eax,eax
    L_004204c5:
        jne short L_00420537
    L_004204c7:
        push 420000h
    L_004204cc:
        call asm_SchedulerCallback_Create_00449ed0
    L_004204d1:
        mov edi,dword ptr [eax+4]
    L_004204d4:
        mov edx,dword ptr [data_00491be4]
    L_004204da:
        or edi,ebx
    L_004204dc:
        mov dword ptr [eax+4],edi
    L_004204df:
        push edx
    L_004204e0:
        mov edi,1
    L_004204e5:
        mov esi,eax
    L_004204e7:
        mov dword ptr [eax+20h],ebp
    L_004204ea:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004204ef:
        push 4200C0h
    L_004204f4:
        call asm_SchedulerCallback_Create_00449ed0
    L_004204f9:
        or dword ptr [eax+4],ebx
    L_004204fc:
        mov ecx,dword ptr [data_00491be4]
    L_00420502:
        push ecx
    L_00420503:
        mov edi,28h
    L_00420508:
        mov esi,eax
    L_0042050a:
        mov dword ptr [eax+20h],ebp
    L_0042050d:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00420512:
        push 4200D0h
    L_00420517:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042051c:
        or dword ptr [eax+4],ebx
    L_0042051f:
        mov edx,dword ptr [data_00491be4]
    L_00420525:
        push edx
    L_00420526:
        mov edi,32h
    L_0042052b:
        mov esi,eax
    L_0042052d:
        mov dword ptr [eax+20h],ebp
    L_00420530:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00420535:
        xor eax,eax
    L_00420537:
        pop edi
    L_00420538:
        pop esi
    L_00420539:
        pop ebp
    L_0042053a:
        pop ebx
    L_0042053b:
        ret
    }
}

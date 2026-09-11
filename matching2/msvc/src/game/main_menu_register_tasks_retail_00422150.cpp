#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422150..0x004221DD: MainMenu_RegisterTasksRetail
// Naked body preserves the retail register/stack ABI.

// 0x00422150..0x004221DD: MainMenu_RegisterTasksRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MainMenu_RegisterTasksRetail_00422150() {
    __asm {
    L_00422150:
        push esi
    L_00422151:
        push edi
    L_00422152:
        push 422A90h
    L_00422157:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042215c:
        mov esi,eax
    L_0042215e:
        mov edi,dword ptr [esi+4]
    L_00422161:
        mov eax,dword ptr [data_00491be4]
    L_00422166:
        and edi,0FFFFFFFDh
    L_00422169:
        mov dword ptr [esi+4],edi
    L_0042216c:
        push eax
    L_0042216d:
        mov edi,9
    L_00422172:
        mov dword ptr [esi+20h],ebx
    L_00422175:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0042217a:
        push 422AA0h
    L_0042217f:
        mov dword ptr [ebx+8],esi
    L_00422182:
        call asm_SchedulerCallback_Create_00449ed0
    L_00422187:
        mov ecx,dword ptr [data_00491be4]
    L_0042218d:
        mov esi,eax
    L_0042218f:
        mov eax,dword ptr [esi+4]
    L_00422192:
        and eax,0FFFFFFFDh
    L_00422195:
        push ecx
    L_00422196:
        mov edi,2Eh
    L_0042219b:
        mov dword ptr [esi+20h],ebx
    L_0042219e:
        mov dword ptr [esi+4],eax
    L_004221a1:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004221a6:
        mov dword ptr [ebx+0Ch],esi
    L_004221a9:
        mov eax,dword ptr [ebx+20h]
    L_004221ac:
        xor ecx,ecx
    L_004221ae:
        test al,1
    L_004221b0:
        pop edi
    L_004221b1:
        pop esi
    L_004221b2:
        jne short L_004221ce
    L_004221b4:
        or eax,1
    L_004221b7:
        mov dword ptr [ebx+14h],ecx
    L_004221ba:
        mov dword ptr [ebx+10h],0FFF0BDC1h
    L_004221c1:
        mov dword ptr [ebx+18h],ecx
    L_004221c4:
        mov dword ptr [ebx+1Ch],476F78h
    L_004221cb:
        mov dword ptr [ebx+20h],eax
    L_004221ce:
        mov dword ptr [ebx+14h],ecx
    L_004221d1:
        mov dword ptr [ebx+18h],ecx
    L_004221d4:
        mov dword ptr [ebx+10h],0FFFFFFFFh
    L_004221db:
        xor eax,eax
    L_004221dd:
        ret
    }
}

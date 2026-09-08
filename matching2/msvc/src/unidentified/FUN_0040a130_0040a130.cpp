#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A130..0x0040A199: FUN_0040a130
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040a130_0040a130() {
    __asm {
    L_0040a130:
        push esi
    L_0040a131:
        push edi
    L_0040a132:
        xor eax,eax
    L_0040a134:
        push 40ABE0h
    L_0040a139:
        mov dword ptr [data_00477848],474788h
    L_0040a143:
        mov dword ptr [data_00474c7c],eax
    L_0040a148:
        mov dword ptr [data_00474c80],eax
    L_0040a14d:
        call asm_SchedulerCallback_Create_00449ed0
    L_0040a152:
        mov esi,eax
    L_0040a154:
        or dword ptr [esi+4],2
    L_0040a158:
        mov eax,dword ptr [data_00491be4]
    L_0040a15d:
        push eax
    L_0040a15e:
        mov edi,5
    L_0040a163:
        mov dword ptr [esi+20h],ebx
    L_0040a166:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0040a16b:
        push 40ABF0h
    L_0040a170:
        mov dword ptr [ebx+8],esi
    L_0040a173:
        call asm_SchedulerCallback_Create_00449ed0
    L_0040a178:
        mov esi,eax
    L_0040a17a:
        or dword ptr [esi+4],2
    L_0040a17e:
        mov ecx,dword ptr [data_00491be4]
    L_0040a184:
        push ecx
    L_0040a185:
        mov edi,27h
    L_0040a18a:
        mov dword ptr [esi+20h],ebx
    L_0040a18d:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0040a192:
        pop edi
    L_0040a193:
        mov dword ptr [ebx+0Ch],esi
    L_0040a196:
        xor eax,eax
    L_0040a198:
        pop esi
    L_0040a199:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413350..0x004133E6: FUN_00413350
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413350_00413350() {
    __asm {
    L_00413350:
        push ebx
    L_00413351:
        push ebp
    L_00413352:
        push esi
    L_00413353:
        push edi
    L_00413354:
        push 8Ch
    L_00413359:
        call asm_operator_new_00452493
    L_0041335e:
        mov edx,eax
    L_00413360:
        xor ebp,ebp
    L_00413362:
        add esp,4
    L_00413365:
        cmp edx,ebp
    L_00413367:
        je short L_00413381
    L_00413369:
        xor eax,eax
    L_0041336b:
        mov ecx,23h
    L_00413370:
        mov edi,edx
    L_00413372:
        rep stosd
    L_00413374:
        or dword ptr [edx],2
    L_00413377:
        mov dword ptr [data_00477708],edx
    L_0041337d:
        mov ebx,edx
    L_0041337f:
        jmp short L_00413383
    L_00413381:
        xor ebx,ebx
    L_00413383:
        push 24h
    L_00413385:
        call asm_operator_new_00452493
    L_0041338a:
        add esp,4
    L_0041338d:
        cmp eax,ebp
    L_0041338f:
        je short L_004133b2
    L_00413391:
        mov ecx,dword ptr [eax+4]
    L_00413394:
        mov dword ptr [eax+8],ebp
    L_00413397:
        mov dword ptr [eax+0Ch],ebp
    L_0041339a:
        mov dword ptr [eax+10h],ebp
    L_0041339d:
        mov dword ptr [eax],ebp
    L_0041339f:
        and ecx,0FFFFFFFEh
    L_004133a2:
        mov dword ptr [eax+4],ecx
    L_004133a5:
        mov dword ptr [eax+14h],eax
    L_004133a8:
        mov dword ptr [eax+18h],ebp
    L_004133ab:
        mov dword ptr [eax+1Ch],ebp
    L_004133ae:
        mov esi,eax
    L_004133b0:
        jmp short L_004133b4
    L_004133b2:
        xor esi,esi
    L_004133b4:
        mov edx,dword ptr [esi+4]
    L_004133b7:
        mov eax,dword ptr [data_00491be4]
    L_004133bc:
        or edx,3
    L_004133bf:
        push eax
    L_004133c0:
        mov edi,2Fh
    L_004133c5:
        mov dword ptr [esi+8],413690h
    L_004133cc:
        mov dword ptr [esi+0Ch],ebp
    L_004133cf:
        mov dword ptr [esi+10h],ebp
    L_004133d2:
        mov dword ptr [esi+20h],ebx
    L_004133d5:
        mov dword ptr [esi+4],edx
    L_004133d8:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004133dd:
        pop edi
    L_004133de:
        mov dword ptr [ebx+0Ch],esi
    L_004133e1:
        pop esi
    L_004133e2:
        pop ebp
    L_004133e3:
        mov eax,ebx
    L_004133e5:
        pop ebx
    L_004133e6:
        ret
    }
}

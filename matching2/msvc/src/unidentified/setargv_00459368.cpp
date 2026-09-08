#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459368..0x00459409: __setargv
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_setargv_00459368() {
    __asm {
    L_00459368:
        push ebp
    L_00459369:
        mov ebp,esp
    L_0045936b:
        push ecx
    L_0045936c:
        push ecx
    L_0045936d:
        push ebx
    L_0045936e:
        push esi
    L_0045936f:
        push edi
    L_00459370:
        xor edi,edi
    L_00459372:
        cmp dword ptr [data_00499314],edi
    L_00459378:
        jne short L_0045937f
    L_0045937a:
        call asm_initmbctable_0045d2ac
    L_0045937f:
        push 104h
    L_00459384:
        mov esi,4774B8h
    L_00459389:
        push esi
    L_0045938a:
        push edi
    L_0045938b:
        mov byte ptr [data_004775bc],0
    L_00459392:
        call dword ptr [data_004660dc]
    L_00459398:
        mov eax,dword ptr [data_00499348]
    L_0045939d:
        cmp eax,edi
    L_0045939f:
        mov dword ptr [data_004774a0],esi
    L_004593a5:
        je short L_004593ae
    L_004593a7:
        cmp byte ptr [eax],0
    L_004593aa:
        mov ebx,eax
    L_004593ac:
        jne short L_004593b0
    L_004593ae:
        mov ebx,esi
    L_004593b0:
        lea eax,[ebp-4]
    L_004593b3:
        push eax
    L_004593b4:
        push edi
    L_004593b5:
        lea esi,[ebp-8]
    L_004593b8:
        xor ecx,ecx
    L_004593ba:
        mov eax,ebx
    L_004593bc:
        call asm_parse_cmdline_004591fc
    L_004593c1:
        mov esi,dword ptr [ebp-4]
    L_004593c4:
        mov eax,dword ptr [ebp-8]
    L_004593c7:
        shl esi,2
    L_004593ca:
        add eax,esi
    L_004593cc:
        push eax
    L_004593cd:
        call asm_malloc_00452706
    L_004593d2:
        mov edi,eax
    L_004593d4:
        add esp,0Ch
    L_004593d7:
        test edi,edi
    L_004593d9:
        jne short L_004593e0
    L_004593db:
        or eax,0FFFFFFFFh
    L_004593de:
        jmp short L_00459405
    L_004593e0:
        lea eax,[ebp-4]
    L_004593e3:
        push eax
    L_004593e4:
        lea ecx,[esi+edi]
    L_004593e7:
        push edi
    L_004593e8:
        lea esi,[ebp-8]
    L_004593eb:
        mov eax,ebx
    L_004593ed:
        call asm_parse_cmdline_004591fc
    L_004593f2:
        mov eax,dword ptr [ebp-4]
    L_004593f5:
        dec eax
    L_004593f6:
        pop ecx
    L_004593f7:
        mov dword ptr [data_00477484],eax
    L_004593fc:
        pop ecx
    L_004593fd:
        mov dword ptr [data_00477488],edi
    L_00459403:
        xor eax,eax
    L_00459405:
        pop edi
    L_00459406:
        pop esi
    L_00459407:
        pop ebx
    L_00459408:
        leave
    L_00459409:
        ret
    }
}

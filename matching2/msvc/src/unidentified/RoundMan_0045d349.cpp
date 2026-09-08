#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D349..0x0045D3BA: __RoundMan
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RoundMan_0045d349() {
    __asm {
    L_0045d349:
        push ebp
    L_0045d34a:
        mov ebp,esp
    L_0045d34c:
        push ecx
    L_0045d34d:
        and dword ptr [ebp-4],0
    L_0045d351:
        push ebx
    L_0045d352:
        push esi
    L_0045d353:
        push edi
    L_0045d354:
        mov edi,dword ptr [ebp+0Ch]
    L_0045d357:
        dec edi
    L_0045d358:
        push 20h
    L_0045d35a:
        lea eax,[edi+1]
    L_0045d35d:
        pop ecx
    L_0045d35e:
        cdq
    L_0045d35f:
        idiv ecx
    L_0045d361:
        push 1Fh
    L_0045d363:
        pop esi
    L_0045d364:
        sub esi,edx
    L_0045d366:
        xor edx,edx
    L_0045d368:
        inc edx
    L_0045d369:
        mov ecx,esi
    L_0045d36b:
        shl edx,cl
    L_0045d36d:
        mov ebx,eax
    L_0045d36f:
        mov eax,dword ptr [ebp+8]
    L_0045d372:
        test dword ptr [eax+ebx*4],edx
    L_0045d375:
        je short L_0045d398
    L_0045d377:
        lea ecx,[edi+1]
    L_0045d37a:
        push ecx
    L_0045d37b:
        push eax
    L_0045d37c:
        call asm_ZeroTail_0045d2ca
    L_0045d381:
        test eax,eax
    L_0045d383:
        pop ecx
    L_0045d384:
        pop ecx
    L_0045d385:
        jne short L_0045d395
    L_0045d387:
        push edi
    L_0045d388:
        push dword ptr [ebp+8]
    L_0045d38b:
        call asm_IncMan_0045d2fc
    L_0045d390:
        pop ecx
    L_0045d391:
        pop ecx
    L_0045d392:
        mov dword ptr [ebp-4],eax
    L_0045d395:
        mov eax,dword ptr [ebp+8]
    L_0045d398:
        or edx,0FFFFFFFFh
    L_0045d39b:
        mov ecx,esi
    L_0045d39d:
        shl edx,cl
    L_0045d39f:
        push 3
    L_0045d3a1:
        pop ecx
    L_0045d3a2:
        and dword ptr [eax+ebx*4],edx
    L_0045d3a5:
        inc ebx
    L_0045d3a6:
        cmp ebx,ecx
    L_0045d3a8:
        jge short L_0045d3b3
    L_0045d3aa:
        lea edi,[eax+ebx*4]
    L_0045d3ad:
        sub ecx,ebx
    L_0045d3af:
        xor eax,eax
    L_0045d3b1:
        rep stosd
    L_0045d3b3:
        mov eax,dword ptr [ebp-4]
    L_0045d3b6:
        pop edi
    L_0045d3b7:
        pop esi
    L_0045d3b8:
        pop ebx
    L_0045d3b9:
        leave
    L_0045d3ba:
        ret
    }
}

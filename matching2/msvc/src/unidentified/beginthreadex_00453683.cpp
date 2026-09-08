#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453683..0x0045370D: __beginthreadex
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_beginthreadex_00453683() {
    __asm {
    L_00453683:
        push ebp
    L_00453684:
        mov ebp,esp
    L_00453686:
        push ebx
    L_00453687:
        push edi
    L_00453688:
        mov edi,dword ptr [ebp+10h]
    L_0045368b:
        xor ebx,ebx
    L_0045368d:
        test edi,edi
    L_0045368f:
        jne short L_004536a0
    L_00453691:
        call asm_FUN_00456af2_00456af2
    L_00453696:
        mov dword ptr [eax],16h
    L_0045369c:
        xor eax,eax
    L_0045369e:
        jmp short L_0045370a
    L_004536a0:
        push esi
    L_004536a1:
        push 8Ch
    L_004536a6:
        push 1
    L_004536a8:
        call asm_FUN_0045794d_0045794d
    L_004536ad:
        mov esi,eax
    L_004536af:
        test esi,esi
    L_004536b1:
        pop ecx
    L_004536b2:
        pop ecx
    L_004536b3:
        je short L_004536f5
    L_004536b5:
        push esi
    L_004536b6:
        call asm_initptd_00456344
    L_004536bb:
        mov eax,dword ptr [ebp+14h]
    L_004536be:
        or dword ptr [esi+4],0FFFFFFFFh
    L_004536c2:
        mov dword ptr [esi+50h],eax
    L_004536c5:
        mov eax,dword ptr [ebp+1Ch]
    L_004536c8:
        test eax,eax
    L_004536ca:
        pop ecx
    L_004536cb:
        mov dword ptr [esi+4Ch],edi
    L_004536ce:
        jne short L_004536d3
    L_004536d0:
        lea eax,[ebp+10h]
    L_004536d3:
        push eax
    L_004536d4:
        push dword ptr [ebp+18h]
    L_004536d7:
        push esi
    L_004536d8:
        push 4535EEh
    L_004536dd:
        push dword ptr [ebp+0Ch]
    L_004536e0:
        push dword ptr [ebp+8]
    L_004536e3:
        call dword ptr [data_00466118]
    L_004536e9:
        test eax,eax
    L_004536eb:
        jne short L_00453709
    L_004536ed:
        call dword ptr [data_0046610c]
    L_004536f3:
        mov ebx,eax
    L_004536f5:
        push esi
    L_004536f6:
        call asm_free_00452422
    L_004536fb:
        test ebx,ebx
    L_004536fd:
        pop ecx
    L_004536fe:
        je short L_00453707
    L_00453700:
        push ebx
    L_00453701:
        call asm_dosmaperr_00456b04
    L_00453706:
        pop ecx
    L_00453707:
        xor eax,eax
    L_00453709:
        pop esi
    L_0045370a:
        pop edi
    L_0045370b:
        pop ebx
    L_0045370c:
        pop ebp
    L_0045370d:
        ret
    }
}

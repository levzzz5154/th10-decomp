#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B52A..0x0045B5BB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045b52a() {
    __asm {
    L_0045b52a:
        cmp dword ptr [data_00477660],0
    L_0045b531:
        push esi
    L_0045b532:
        je short L_0045b574
    L_0045b534:
        push 0B8h
    L_0045b539:
        push 1
    L_0045b53b:
        call asm_FUN_0045794d_0045794d
    L_0045b540:
        mov esi,eax
    L_0045b542:
        test esi,esi
    L_0045b544:
        pop ecx
    L_0045b545:
        pop ecx
    L_0045b546:
        jne short L_0045b54d
    L_0045b548:
        xor eax,eax
    L_0045b54a:
        inc eax
    L_0045b54b:
        pop esi
    L_0045b54c:
        ret
    L_0045b54d:
        call asm_get_lc_time_0045b033
    L_0045b552:
        test eax,eax
    L_0045b554:
        je short L_0045b566
    L_0045b556:
        push esi
    L_0045b557:
        call asm_free_lc_time_0045b39a
    L_0045b55c:
        push esi
    L_0045b55d:
        call asm_free_00452422
    L_0045b562:
        pop ecx
    L_0045b563:
        pop ecx
    L_0045b564:
        jmp short L_0045b548
    L_0045b566:
        mov dword ptr [data_004739e0],esi
    L_0045b56c:
        mov dword ptr [data_00477620],esi
    L_0045b572:
        jmp short L_0045b585
    L_0045b574:
        and dword ptr [data_00477620],0
    L_0045b57b:
        mov dword ptr [data_004739e0],4739E8h
    L_0045b585:
        xor eax,eax
    L_0045b587:
        pop esi
    L_0045b588:
        ret
    L_0045b589:
        xor dl,dl
    L_0045b58b:
        cmp byte ptr [ecx],dl
    L_0045b58d:
        je short L_0045b5a6
    L_0045b58f:
        push ebx
    L_0045b590:
        push esi
    L_0045b591:
        mov al,byte ptr [ecx]
    L_0045b593:
        cmp al,30h
    L_0045b595:
        jl short L_0045b5a7
    L_0045b597:
        cmp al,39h
    L_0045b599:
        jg short L_0045b5a7
    L_0045b59b:
        sub al,30h
    L_0045b59d:
        mov byte ptr [ecx],al
    L_0045b59f:
        inc ecx
    L_0045b5a0:
        cmp byte ptr [ecx],dl
    L_0045b5a2:
        jne short L_0045b591
    L_0045b5a4:
        pop esi
    L_0045b5a5:
        pop ebx
    L_0045b5a6:
        ret
    L_0045b5a7:
        cmp al,3Bh
    L_0045b5a9:
        jne short L_0045b59f
    L_0045b5ab:
        mov eax,ecx
    L_0045b5ad:
        lea esi,[eax+1]
    L_0045b5b0:
        mov bl,byte ptr [esi]
    L_0045b5b2:
        mov byte ptr [eax],bl
    L_0045b5b4:
        mov eax,esi
    L_0045b5b6:
        cmp byte ptr [eax],dl
    L_0045b5b8:
        jne short L_0045b5ad
    L_0045b5ba:
        jmp short L_0045b5a0
    }
}

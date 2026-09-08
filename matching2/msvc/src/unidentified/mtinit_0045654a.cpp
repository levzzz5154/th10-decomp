#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045654A..0x00456638: __mtinit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_mtinit_0045654a() {
    __asm {
    L_0045654a:
        call asm_mtinitlocks_00453aa1
    L_0045654f:
        test eax,eax
    L_00456551:
        jne short L_0045655b
    L_00456553:
        call asm_mtterm_00456327
    L_00456558:
        xor eax,eax
    L_0045655a:
        ret
    L_0045655b:
        push esi
    L_0045655c:
        push edi
    L_0045655d:
        push 46AA5Ch
    L_00456562:
        call dword ptr [data_00466198]
    L_00456568:
        mov edi,eax
    L_0045656a:
        test edi,edi
    L_0045656c:
        je short L_004565d9
    L_0045656e:
        mov esi,dword ptr [data_00466158]
    L_00456574:
        push 46AA50h
    L_00456579:
        push edi
    L_0045657a:
        call esi
    L_0045657c:
        push 46AA44h
    L_00456581:
        push edi
    L_00456582:
        mov dword ptr [data_00477374],eax
    L_00456587:
        call esi
    L_00456589:
        push 46AA38h
    L_0045658e:
        push edi
    L_0045658f:
        mov dword ptr [data_00477378],eax
    L_00456594:
        call esi
    L_00456596:
        push 46AA30h
    L_0045659b:
        push edi
    L_0045659c:
        mov dword ptr [data_0047737c],eax
    L_004565a1:
        call esi
    L_004565a3:
        cmp dword ptr [data_00477378],0
    L_004565aa:
        mov dword ptr [data_00477380],eax
    L_004565af:
        jne short L_004565d9
    L_004565b1:
        mov eax,dword ptr [data_0046615c]
    L_004565b6:
        mov dword ptr [data_00477378],eax
    L_004565bb:
        mov eax,dword ptr [data_00466160]
    L_004565c0:
        mov dword ptr [data_0047737c],eax
    L_004565c5:
        mov eax,dword ptr [data_00466164]
    L_004565ca:
        mov dword ptr [data_00477374],45631Eh
    L_004565d4:
        mov dword ptr [data_00477380],eax
    L_004565d9:
        push 4563C8h
    L_004565de:
        call dword ptr [data_00477374]
    L_004565e4:
        cmp eax,0FFFFFFFFh
    L_004565e7:
        mov dword ptr [data_00473390],eax
    L_004565ec:
        je short L_0045662f
    L_004565ee:
        xor edi,edi
    L_004565f0:
        push 8Ch
    L_004565f5:
        inc edi
    L_004565f6:
        push edi
    L_004565f7:
        call asm_FUN_0045794d_0045794d
    L_004565fc:
        mov esi,eax
    L_004565fe:
        test esi,esi
    L_00456600:
        pop ecx
    L_00456601:
        pop ecx
    L_00456602:
        je short L_0045662f
    L_00456604:
        push esi
    L_00456605:
        push dword ptr [data_00473390]
    L_0045660b:
        call dword ptr [data_0047737c]
    L_00456611:
        test eax,eax
    L_00456613:
        je short L_0045662f
    L_00456615:
        mov dword ptr [esi+54h],4735D0h
    L_0045661c:
        mov dword ptr [esi+14h],edi
    L_0045661f:
        call dword ptr [data_0046619c]
    L_00456625:
        or dword ptr [esi+4],0FFFFFFFFh
    L_00456629:
        mov dword ptr [esi],eax
    L_0045662b:
        mov eax,edi
    L_0045662d:
        jmp short L_00456636
    L_0045662f:
        call asm_mtterm_00456327
    L_00456634:
        xor eax,eax
    L_00456636:
        pop edi
    L_00456637:
        pop esi
    L_00456638:
        ret
    }
}

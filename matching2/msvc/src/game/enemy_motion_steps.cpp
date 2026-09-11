#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00407560..0x00407690: FUN_00407560
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407560_00407560() {
    __asm {
    L_00407560:
        mov eax,dword ptr [esi+64Ch]
    L_00407566:
        mov ecx,dword ptr [esi+670h]
    L_0040756c:
        sub esp,0Ch
    L_0040756f:
        cmp eax,ecx
    L_00407571:
        jl short L_0040757f
    L_00407573:
        and dword ptr [esi+43Ch],0FFFFFFEFh
    L_0040757a:
        jmp asm_target_00407627
    L_0040757f:
        fld dword ptr [data_00476f78]
    L_00407585:
        fmul dword ptr [esi+65Ch]
    L_0040758b:
        fadd dword ptr [esi+3D8h]
    L_00407591:
        fstp dword ptr [esi+3D8h]
    L_00407597:
        fld dword ptr [data_00476f78]
    L_0040759d:
        fmul dword ptr [esi+664h]
    L_004075a3:
        fld dword ptr [data_00476f78]
    L_004075a9:
        fmul dword ptr [esi+668h]
    L_004075af:
        fld dword ptr [data_00476f78]
    L_004075b5:
        fmul dword ptr [esi+66Ch]
    L_004075bb:
        fstp dword ptr [esp+8]
    L_004075bf:
        fxch
    L_004075c1:
        fadd dword ptr [esi+3C0h]
    L_004075c7:
        fstp dword ptr [esi+3C0h]
    L_004075cd:
        fadd dword ptr [esi+3C4h]
    L_004075d3:
        fstp dword ptr [esi+3C4h]
    L_004075d9:
        fld dword ptr [esp+8]
    L_004075dd:
        fadd dword ptr [esi+3C8h]
    L_004075e3:
        fstp dword ptr [esi+3C8h]
    L_004075e9:
        fld dword ptr [esi+3C0h]
    L_004075ef:
        fabs
    L_004075f1:
        fcomp dword ptr [data_00470c58]
    L_004075f7:
        fnstsw ax
    L_004075f9:
        test ah,41h
    L_004075fc:
        je short L_00407613
    L_004075fe:
        fld dword ptr [esi+3C4h]
    L_00407604:
        fabs
    L_00407606:
        fcomp dword ptr [data_00470c58]
    L_0040760c:
        fnstsw ax
    L_0040760e:
        test ah,41h
    L_00407611:
        jne short L_00407627
    L_00407613:
        fld dword ptr [esi+3C4h]
    L_00407619:
        fld dword ptr [esi+3C0h]
    L_0040761f:
        fpatan
    L_00407621:
        fstp dword ptr [esi+3E4h]
    L_00407627:
        mov edx,dword ptr [esi+64Ch]
    L_0040762d:
        mov ecx,dword ptr [esi+654h]
    L_00407633:
        mov dword ptr [esi+648h],edx
    L_00407639:
        fld dword ptr [ecx]
    L_0040763b:
        fcomp dword ptr [data_00470b68]
    L_00407641:
        fnstsw ax
    L_00407643:
        test ah,41h
    L_00407646:
        jne short L_00407674
    L_00407648:
        fld dword ptr [ecx]
    L_0040764a:
        fcomp dword ptr [data_00470b64]
    L_00407650:
        fnstsw ax
    L_00407652:
        test ah,5
    L_00407655:
        jp short L_00407674
    L_00407657:
        fld dword ptr [esi+650h]
    L_0040765d:
        inc edx
    L_0040765e:
        fadd dword ptr [data_00470afc]
    L_00407664:
        mov dword ptr [esi+64Ch],edx
    L_0040766a:
        fstp dword ptr [esi+650h]
    L_00407670:
        add esp,0Ch
    L_00407673:
        ret
    L_00407674:
        fld dword ptr [esi+650h]
    L_0040767a:
        fadd dword ptr [ecx]
    L_0040767c:
        fst dword ptr [esi+650h]
    L_00407682:
        call asm_FUN_00463b2c_00463b2c
    L_00407687:
        mov dword ptr [esi+64Ch],eax
    L_0040768d:
        add esp,0Ch
    L_00407690:
        ret
    }
}






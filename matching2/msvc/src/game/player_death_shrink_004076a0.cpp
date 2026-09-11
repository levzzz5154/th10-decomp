#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040678E..0x00406797: ?Player_ForwardAxisWrap@@
// Naked body preserves the retail register/stack ABI.

// 0x004076A0..0x00407770: Player_DeathShrink
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_DeathShrink_004076a0() {
    __asm {
    L_004076a0:
        push ecx
    L_004076a1:
        mov eax,dword ptr [esi+680h]
    L_004076a7:
        cmp eax,dword ptr [esi+6A4h]
    L_004076ad:
        jl short L_004076b8
    L_004076af:
        and dword ptr [esi+43Ch],0FFFFFFDFh
    L_004076b6:
        jmp short L_0040770b
    L_004076b8:
        fld dword ptr [data_00476f78]
    L_004076be:
        push ecx
    L_004076bf:
        fmul dword ptr [esi+694h]
    L_004076c5:
        mov ecx,dword ptr [esi+3E4h]
    L_004076cb:
        fstp dword ptr [esp]
    L_004076ce:
        push ecx
    L_004076cf:
        call asm_Angle_NormalizeSum_0044bc10
    L_004076d4:
        fstp dword ptr [esi+3E4h]
    L_004076da:
        fld dword ptr [data_00476f78]
    L_004076e0:
        mov eax,dword ptr [esi+3E4h]
    L_004076e6:
        fmul dword ptr [esi+690h]
    L_004076ec:
        lea ecx,[esi+3C0h]
    L_004076f2:
        fadd dword ptr [esi+3D8h]
    L_004076f8:
        fst dword ptr [esp]
    L_004076fb:
        mov edx,dword ptr [esp]
    L_004076fe:
        fstp dword ptr [esi+3D8h]
    L_00407704:
        push edx
    L_00407705:
        push eax
    L_00407706:
        call asm_Score_SetPolarVector_00408750
    L_0040770b:
        mov edx,dword ptr [esi+680h]
    L_00407711:
        mov ecx,dword ptr [esi+688h]
    L_00407717:
        mov dword ptr [esi+67Ch],edx
    L_0040771d:
        fld dword ptr [ecx]
    L_0040771f:
        fcomp dword ptr [data_00470b68]
    L_00407725:
        fnstsw ax
    L_00407727:
        test ah,41h
    L_0040772a:
        jne short L_00407756
    L_0040772c:
        fld dword ptr [ecx]
    L_0040772e:
        fcomp dword ptr [data_00470b64]
    L_00407734:
        fnstsw ax
    L_00407736:
        test ah,5
    L_00407739:
        jp short L_00407756
    L_0040773b:
        fld dword ptr [esi+684h]
    L_00407741:
        inc edx
    L_00407742:
        fadd dword ptr [data_00470afc]
    L_00407748:
        mov dword ptr [esi+680h],edx
    L_0040774e:
        fstp dword ptr [esi+684h]
    L_00407754:
        pop ecx
    L_00407755:
        ret
    L_00407756:
        fld dword ptr [ecx]
    L_00407758:
        fadd dword ptr [esi+684h]
    L_0040775e:
        fst dword ptr [esi+684h]
    L_00407764:
        call asm_FUN_00463b2c_00463b2c
    L_00407769:
        mov dword ptr [esi+680h],eax
    L_0040776f:
        pop ecx
    L_00407770:
        ret
    }
}

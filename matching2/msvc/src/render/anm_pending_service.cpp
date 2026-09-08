#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00447700..0x00447786: AnmPending_ServiceRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnmPending_ServiceRetail_00447700() {
    __asm {
    L_00447700:
        push ebx
    L_00447701:
        push esi
    L_00447702:
        mov esi,dword ptr [esp+0Ch]
    L_00447706:
        xor ebx,ebx
    L_00447708:
        push edi
    L_00447709:
        add esi,3AD06Ch
    L_0044770f:
        nop
    L_00447710:
        mov edi,dword ptr [esi]
    L_00447712:
        test edi,edi
    L_00447714:
        je short L_00447757
    L_00447716:
        mov eax,dword ptr [edi+128h]
    L_0044771c:
        test eax,eax
    L_0044771e:
        je short L_0044774d
    L_00447720:
        test ebx,ebx
    L_00447722:
        jl short L_0044773f
    L_00447724:
        cmp ebx,21h
    L_00447727:
        jae short L_0044773f
    L_00447729:
        call asm_FUN_00447810_00447810
    L_0044772e:
        mov eax,dword ptr [esi]
    L_00447730:
        push eax
    L_00447731:
        call asm_free_004524a1
    L_00447736:
        add esp,4
    L_00447739:
        mov dword ptr [esi],0
    L_0044773f:
        mov ecx,dword ptr [esi]
    L_00447741:
        mov dword ptr [ecx+128h],0
    L_0044774b:
        jmp short L_00447757
    L_0044774d:
        mov eax,dword ptr [edi+124h]
    L_00447753:
        test eax,eax
    L_00447755:
        jne short L_00447768
    L_00447757:
        inc ebx
    L_00447758:
        add esi,4
    L_0044775b:
        cmp ebx,21h
    L_0044775e:
        jb short L_00447710
    L_00447760:
        pop edi
    L_00447761:
        pop esi
    L_00447762:
        xor eax,eax
    L_00447764:
        pop ebx
    L_00447765:
        ret 4
    L_00447768:
        mov eax,dword ptr [esp+10h]
    L_0044776c:
        mov edx,dword ptr [eax+ebx*4+3AD06Ch]
    L_00447773:
        push edx
    L_00447774:
        push eax
    L_00447775:
        call asm_AnmArchive_AdvanceScriptCursorRetail_004473c0
    L_0044777a:
        neg eax
    L_0044777c:
        sbb eax,eax
    L_0044777e:
        pop edi
    L_0044777f:
        neg eax
    L_00447781:
        pop esi
    L_00447782:
        dec eax
    L_00447783:
        pop ebx
    L_00447784:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C710..0x0043C86C: FUN_0043c710
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c710_0043c710() {
    __asm {
    L_0043c710:
        push ecx
    L_0043c711:
        mov eax,dword ptr [data_004918a4]
    L_0043c716:
        test eax,eax
    L_0043c718:
        push edi
    L_0043c719:
        mov edi,ecx
    L_0043c71b:
        je short L_0043c725
    L_0043c71d:
        mov eax,7
    L_0043c722:
        pop edi
    L_0043c723:
        pop ecx
    L_0043c724:
        ret
    L_0043c725:
        mov ecx,dword ptr [data_00477810]
    L_0043c72b:
        test ecx,ecx
    L_0043c72d:
        je asm_target_0043c865
    L_0043c733:
        mov eax,dword ptr [ecx+58h]
    L_0043c736:
        mov edx,eax
    L_0043c738:
        shr edx,2
    L_0043c73b:
        or edx,eax
    L_0043c73d:
        test dl,1
    L_0043c740:
        jne asm_target_0043c865
    L_0043c746:
        test al,72h
    L_0043c748:
        jne asm_target_0043c865
    L_0043c74e:
        push esi
    L_0043c74f:
        lea esi,[edi+30h]
    L_0043c752:
        call asm_FrameTimer_Tick_00404ed0
    L_0043c757:
        mov eax,dword ptr [edi+20h]
    L_0043c75a:
        mov edx,dword ptr [edi+34h]
    L_0043c75d:
        cmp edx,eax
    L_0043c75f:
        mov dword ptr [esp+8],eax
    L_0043c763:
        jge short L_0043c76e
    L_0043c765:
        fild dword ptr [esp+8]
    L_0043c769:
        fdivr dword ptr [edi+38h]
    L_0043c76c:
        jmp short L_0043c7bf
    L_0043c76e:
        mov ecx,dword ptr [edi+24h]
    L_0043c771:
        lea esi,[ecx+eax]
    L_0043c774:
        cmp edx,esi
    L_0043c776:
        jge short L_0043c780
    L_0043c778:
        fld dword ptr [data_00470afc]
    L_0043c77e:
        jmp short L_0043c7bf
    L_0043c780:
        mov esi,dword ptr [edi+28h]
    L_0043c783:
        add esi,ecx
    L_0043c785:
        add esi,eax
    L_0043c787:
        cmp edx,esi
    L_0043c789:
        jge asm_target_0043c85c
    L_0043c78f:
        mov edx,dword ptr [edi+28h]
    L_0043c792:
        add ecx,edx
    L_0043c794:
        add ecx,eax
    L_0043c796:
        test ecx,ecx
    L_0043c798:
        mov dword ptr [esp+8],ecx
    L_0043c79c:
        fild dword ptr [esp+8]
    L_0043c7a0:
        jge short L_0043c7a8
    L_0043c7a2:
        fadd dword ptr [data_00470b98]
    L_0043c7a8:
        test edx,edx
    L_0043c7aa:
        fsub dword ptr [edi+38h]
    L_0043c7ad:
        mov dword ptr [esp+8],edx
    L_0043c7b1:
        fild dword ptr [esp+8]
    L_0043c7b5:
        jge short L_0043c7bd
    L_0043c7b7:
        fadd dword ptr [data_00470b98]
    L_0043c7bd:
        fdivp st(1),st
    L_0043c7bf:
        fild dword ptr [edi+1Ch]
    L_0043c7c2:
        mov edi,3
    L_0043c7c7:
        mov ecx,4918B0h
    L_0043c7cc:
        fmul st,st(1)
    L_0043c7ce:
        fstp dword ptr [esp+8]
    L_0043c7d2:
        fstp st(0)
    L_0043c7d4:
        call asm_EntityScript_NextRandomModulo_0043cb80
    L_0043c7d9:
        sub eax,0
    L_0043c7dc:
        je short L_0043c7fe
    L_0043c7de:
        dec eax
    L_0043c7df:
        je short L_0043c7f2
    L_0043c7e1:
        dec eax
    L_0043c7e2:
        jne short L_0043c808
    L_0043c7e4:
        fld dword ptr [esp+8]
    L_0043c7e8:
        fchs
    L_0043c7ea:
        fstp dword ptr [data_00491e64]
    L_0043c7f0:
        jmp short L_0043c808
    L_0043c7f2:
        mov edx,dword ptr [esp+8]
    L_0043c7f6:
        mov dword ptr [data_00491e64],edx
    L_0043c7fc:
        jmp short L_0043c808
    L_0043c7fe:
        mov dword ptr [data_00491e64],0
    L_0043c808:
        mov edi,3
    L_0043c80d:
        mov ecx,4918B0h
    L_0043c812:
        call asm_EntityScript_NextRandomModulo_0043cb80
    L_0043c817:
        sub eax,0
    L_0043c81a:
        je short L_0043c849
    L_0043c81c:
        dec eax
    L_0043c81d:
        je short L_0043c837
    L_0043c81f:
        dec eax
    L_0043c820:
        jne short L_0043c853
    L_0043c822:
        fld dword ptr [esp+8]
    L_0043c826:
        pop esi
    L_0043c827:
        fchs
    L_0043c829:
        mov eax,1
    L_0043c82e:
        fstp dword ptr [data_00491e68]
    L_0043c834:
        pop edi
    L_0043c835:
        pop ecx
    L_0043c836:
        ret
    L_0043c837:
        mov eax,dword ptr [esp+8]
    L_0043c83b:
        pop esi
    L_0043c83c:
        mov dword ptr [data_00491e68],eax
    L_0043c841:
        mov eax,1
    L_0043c846:
        pop edi
    L_0043c847:
        pop ecx
    L_0043c848:
        ret
    L_0043c849:
        mov dword ptr [data_00491e68],0
    L_0043c853:
        pop esi
    L_0043c854:
        mov eax,1
    L_0043c859:
        pop edi
    L_0043c85a:
        pop ecx
    L_0043c85b:
        ret
    L_0043c85c:
        pop esi
    L_0043c85d:
        mov eax,7
    L_0043c862:
        pop edi
    L_0043c863:
        pop ecx
    L_0043c864:
        ret
    L_0043c865:
        mov eax,1
    L_0043c86a:
        pop edi
    L_0043c86b:
        pop ecx
    L_0043c86c:
        ret
    }
}

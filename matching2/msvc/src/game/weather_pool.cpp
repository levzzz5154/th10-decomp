#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B6F0..0x0042B775: EffectPool_UpdateDrops
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EffectPool_UpdateDrops_0042b6f0() {
    __asm {
    L_0042b6f0:
        push esi
    L_0042b6f1:
        mov esi,eax
    L_0042b6f3:
        push edi
    L_0042b6f4:
        add esi,3E8h
    L_0042b6fa:
        mov edi,2D3h
    L_0042b6ff:
        nop
    L_0042b700:
        mov al,byte ptr [esi+14h]
    L_0042b703:
        test al,al
    L_0042b705:
        je short L_0042b768
    L_0042b707:
        fld dword ptr [data_00476f78]
    L_0042b70d:
        fmul dword ptr [data_00470b0c]
    L_0042b713:
        fsubr dword ptr [esi-14h]
    L_0042b716:
        fstp dword ptr [esi-14h]
    L_0042b719:
        mov edx,dword ptr [esi-4]
    L_0042b71c:
        mov ecx,dword ptr [esi+4]
    L_0042b71f:
        mov dword ptr [esi-8],edx
    L_0042b722:
        fld dword ptr [ecx]
    L_0042b724:
        fcomp dword ptr [data_00470b68]
    L_0042b72a:
        fnstsw ax
    L_0042b72c:
        test ah,41h
    L_0042b72f:
        jne short L_0042b750
    L_0042b731:
        fld dword ptr [ecx]
    L_0042b733:
        fcomp dword ptr [data_00470b64]
    L_0042b739:
        fnstsw ax
    L_0042b73b:
        test ah,5
    L_0042b73e:
        jp short L_0042b750
    L_0042b740:
        fld dword ptr [esi]
    L_0042b742:
        inc edx
    L_0042b743:
        fadd dword ptr [data_00470afc]
    L_0042b749:
        mov dword ptr [esi-4],edx
    L_0042b74c:
        fstp dword ptr [esi]
    L_0042b74e:
        jmp short L_0042b75e
    L_0042b750:
        fld dword ptr [esi]
    L_0042b752:
        fadd dword ptr [ecx]
    L_0042b754:
        fst dword ptr [esi]
    L_0042b756:
        call asm_FUN_00463b2c_00463b2c
    L_0042b75b:
        mov dword ptr [esi-4],eax
    L_0042b75e:
        cmp dword ptr [esi-4],3Ch
    L_0042b762:
        jle short L_0042b768
    L_0042b764:
        mov byte ptr [esi+14h],0
    L_0042b768:
        add esi,40h
    L_0042b76b:
        dec edi
    L_0042b76c:
        jne short L_0042b700
    L_0042b76e:
        pop edi
    L_0042b76f:
        mov eax,1
    L_0042b774:
        pop esi
    L_0042b775:
        ret
    }
}

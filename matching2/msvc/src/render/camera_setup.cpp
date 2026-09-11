#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421480..0x0042159E: Camera_ApplyRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Camera_ApplyRetail_00421480() {
    __asm {
    L_00421480:
        sub esp,2Ch
    L_00421483:
        push ebx
    L_00421484:
        push esi
    L_00421485:
        mov esi,dword ptr [data_00491c10]
    L_0042148b:
        test esi,esi
    L_0042148d:
        je short L_00421494
    L_0042148f:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00421494:
        mov eax,dword ptr [edi+0D4h]
    L_0042149a:
        fild dword ptr [edi+0D4h]
    L_004214a0:
        test eax,eax
    L_004214a2:
        jge short L_004214aa
    L_004214a4:
        fadd dword ptr [data_00470b98]
    L_004214aa:
        mov ecx,dword ptr [edi+0D8h]
    L_004214b0:
        fst dword ptr [esp+8]
    L_004214b4:
        test ecx,ecx
    L_004214b6:
        fmul dword ptr [data_00470b0c]
    L_004214bc:
        fild dword ptr [edi+0D8h]
    L_004214c2:
        jge short L_004214ca
    L_004214c4:
        fadd dword ptr [data_00470b98]
    L_004214ca:
        fst dword ptr [esp+0Ch]
    L_004214ce:
        lea edx,[esp+10h]
    L_004214d2:
        fmul dword ptr [data_00470b0c]
    L_004214d8:
        push edx
    L_004214d9:
        fld dword ptr [esp+0Ch]
    L_004214dd:
        lea eax,[esp+20h]
    L_004214e1:
        fdiv dword ptr [esp+10h]
    L_004214e5:
        push eax
    L_004214e6:
        lea ecx,[esp+30h]
    L_004214ea:
        push ecx
    L_004214eb:
        lea esi,[edi+4Ch]
    L_004214ee:
        push esi
    L_004214ef:
        mov dword ptr [esp+34h],0
    L_004214f7:
        mov dword ptr [esp+20h],0
    L_004214ff:
        mov dword ptr [esp+24h],0BF800000h
    L_00421507:
        mov dword ptr [esp+28h],0
    L_0042150f:
        fstp dword ptr [esp+1Ch]
    L_00421513:
        fld st(1)
    L_00421515:
        fstp dword ptr [esp+38h]
    L_00421519:
        fst dword ptr [esp+3Ch]
    L_0042151d:
        fld qword ptr [data_00470ba0]
    L_00421523:
        fptan
    L_00421525:
        fstp st(0)
    L_00421527:
        fdivr st,st(1)
    L_00421529:
        fstp dword ptr [esp+40h]
    L_0042152d:
        fxch
    L_0042152f:
        fstp dword ptr [esp+2Ch]
    L_00421533:
        fstp dword ptr [esp+30h]
    L_00421537:
        call asm_D3DXMatrixLookAtLH_00452194
    L_0042153c:
        mov edx,dword ptr [esp+0Ch]
    L_00421540:
        push 461C4000h
    L_00421545:
        push 3F800000h
    L_0042154a:
        push edx
    L_0042154b:
        push 3EA0D97Ch
    L_00421550:
        lea ebx,[edi+8Ch]
    L_00421556:
        push ebx
    L_00421557:
        call asm_D3DXMatrixPerspectiveFovLH_0045219a
    L_0042155c:
        mov eax,dword ptr [data_00491c30]
    L_00421561:
        mov ecx,dword ptr [eax]
    L_00421563:
        push esi
    L_00421564:
        push 2
    L_00421566:
        push eax
    L_00421567:
        call dword ptr [ecx+0B0h]
    L_0042156d:
        mov eax,dword ptr [data_00491c30]
    L_00421572:
        mov edx,dword ptr [eax]
    L_00421574:
        push ebx
    L_00421575:
        push 3
    L_00421577:
        push eax
    L_00421578:
        call dword ptr [edx+0B0h]
    L_0042157e:
        mov eax,dword ptr [data_00491c10]
    L_00421583:
        test eax,eax
    L_00421585:
        pop esi
    L_00421586:
        pop ebx
    L_00421587:
        je short L_0042159b
    L_00421589:
        mov ecx,dword ptr [edi+0E8h]
    L_0042158f:
        mov dword ptr [eax+5Ch],ecx
    L_00421592:
        mov edx,dword ptr [edi+0ECh]
    L_00421598:
        mov dword ptr [eax+60h],edx
    L_0042159b:
        add esp,2Ch
    L_0042159e:
        ret
    }
}




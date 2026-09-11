#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004134B0..0x004135C7: FrameRateCounter_UpdateRetail
// Naked body preserves the retail register/stack ABI.

// 0x004135D0..0x00413683: FUN_004135d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004135d0_004135d0() {
    __asm {
    L_004135d0:
        sub esp,0Ch
    L_004135d3:
        push esi
    L_004135d4:
        mov esi,edi
    L_004135d6:
        call asm_FrameRateCounter_UpdateRetail_004134b0
    L_004135db:
        cmp dword ptr [data_00491fb8],0Eh
    L_004135e2:
        je asm_target_0041366a
    L_004135e8:
        mov esi,dword ptr [data_004776e0]
    L_004135ee:
        fld dword ptr [edi+34h]
    L_004135f1:
        test esi,esi
    L_004135f3:
        je short L_00413668
    L_004135f5:
        fcom dword ptr [data_00470c30]
    L_004135fb:
        fnstsw ax
    L_004135fd:
        test ah,5
    L_00413600:
        jp short L_00413609
    L_00413602:
        mov eax,0FF5050FFh
    L_00413607:
        jmp short L_00413620
    L_00413609:
        fcom dword ptr [data_00470c64]
    L_0041360f:
        fnstsw ax
    L_00413611:
        test ah,5
    L_00413614:
        jp short L_0041361d
    L_00413616:
        mov eax,0FFA0A0FFh
    L_0041361b:
        jmp short L_00413620
    L_0041361d:
        or eax,0FFFFFFFFh
    L_00413620:
        push ebx
    L_00413621:
        sub esp,8
    L_00413624:
        fstp qword ptr [esp]
    L_00413627:
        push 46D198h
    L_0041362c:
        lea ebx,[esp+14h]
    L_00413630:
        mov dword ptr [esi+8974h],eax
    L_00413636:
        mov dword ptr [esp+14h],44138000h
    L_0041363e:
        mov dword ptr [esp+18h],43EB0000h
    L_00413646:
        mov dword ptr [esp+1Ch],0
    L_0041364e:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_00413653:
        mov eax,dword ptr [data_004776e0]
    L_00413658:
        add esp,0Ch
    L_0041365b:
        mov dword ptr [eax+8974h],0FFFFFFFFh
    L_00413665:
        pop ebx
    L_00413666:
        jmp short L_0041366a
    L_00413668:
        fstp st(0)
    L_0041366a:
        movzx ecx,byte ptr [data_00491d66]
    L_00413671:
        mov eax,dword ptr [edi+20h]
    L_00413674:
        inc ecx
    L_00413675:
        add eax,ecx
    L_00413677:
        mov dword ptr [edi+20h],eax
    L_0041367a:
        mov eax,1
    L_0041367f:
        pop esi
    L_00413680:
        add esp,0Ch
    L_00413683:
        ret
    }
}

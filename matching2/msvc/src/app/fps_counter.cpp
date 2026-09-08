#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004134B0..0x004135C7: FrameRateCounter_UpdateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FrameRateCounter_UpdateRetail_004134b0() {
    __asm {
    L_004134b0:
        push ebp
    L_004134b1:
        mov ebp,esp
    L_004134b3:
        and esp,0FFFFFFF8h
    L_004134b6:
        push ecx
    L_004134b7:
        push edi
    L_004134b8:
        call asm_FUN_00439540_00439540
    L_004134bd:
        fcom qword ptr [esi+14h]
    L_004134c0:
        fnstsw ax
    L_004134c2:
        test ah,5
    L_004134c5:
        jp short L_004134ca
    L_004134c7:
        fst qword ptr [esi+14h]
    L_004134ca:
        fsub qword ptr [esi+14h]
    L_004134cd:
        fcom qword ptr [data_00470bc0]
    L_004134d3:
        fnstsw ax
    L_004134d5:
        test ah,1
    L_004134d8:
        jne asm_target_004135bc
    L_004134de:
        mov eax,dword ptr [esi+20h]
    L_004134e1:
        fld st(0)
    L_004134e3:
        test eax,eax
    L_004134e5:
        fadd qword ptr [esi+14h]
    L_004134e8:
        fstp qword ptr [esi+14h]
    L_004134eb:
        fild dword ptr [esi+20h]
    L_004134ee:
        jge short L_004134f6
    L_004134f0:
        fadd qword ptr [data_00470b30]
    L_004134f6:
        fdivrp st(1),st
    L_004134f8:
        xor edi,edi
    L_004134fa:
        fst dword ptr [esi+34h]
    L_004134fd:
        fcomp dword ptr [data_00470bb8]
    L_00413503:
        fnstsw ax
    L_00413505:
        test ah,41h
    L_00413508:
        jne short L_00413565
    L_0041350a:
        mov edx,dword ptr [esi+1Ch]
    L_0041350d:
        inc edx
    L_0041350e:
        mov eax,edx
    L_00413510:
        cmp eax,2
    L_00413513:
        mov dword ptr [esi+1Ch],edx
    L_00413516:
        jne short L_00413537
    L_00413518:
        call asm_FUN_00439540_00439540
    L_0041351d:
        fst qword ptr [data_00492540]
    L_00413523:
        fst qword ptr [data_00492538]
    L_00413529:
        fst qword ptr [data_00492528]
    L_0041352f:
        fstp qword ptr [data_00492530]
    L_00413535:
        jmp short L_00413568
    L_00413537:
        cmp eax,4
    L_0041353a:
        jne short L_00413568
    L_0041353c:
        mov dword ptr [data_00492508],edi
    L_00413542:
        mov dword ptr [data_0049250c],edi
    L_00413548:
        call asm_FUN_00439540_00439540
    L_0041354d:
        fst qword ptr [data_00492540]
    L_00413553:
        fst qword ptr [data_00492538]
    L_00413559:
        fst qword ptr [data_00492528]
    L_0041355f:
        fstp qword ptr [data_00492530]
    L_00413565:
        mov dword ptr [esi+1Ch],edi
    L_00413568:
        mov ecx,dword ptr [data_00477810]
    L_0041356e:
        cmp ecx,edi
    L_00413570:
        je short L_004135af
    L_00413572:
        test byte ptr [ecx+58h],14h
    L_00413576:
        jne short L_004135a8
    L_00413578:
        fld qword ptr [esi+2Ch]
    L_0041357b:
        fadd qword ptr [data_00470bb0]
    L_00413581:
        fstp qword ptr [esi+2Ch]
    L_00413584:
        fld dword ptr [esi+34h]
    L_00413587:
        fcomp dword ptr [data_00470ba8]
    L_0041358d:
        fnstsw ax
    L_0041358f:
        test ah,41h
    L_00413592:
        jne short L_0041359f
    L_00413594:
        fld qword ptr [esi+24h]
    L_00413597:
        fadd qword ptr [data_00470bb0]
    L_0041359d:
        jmp short L_004135a5
    L_0041359f:
        fld dword ptr [esi+34h]
    L_004135a2:
        fadd qword ptr [esi+24h]
    L_004135a5:
        fstp qword ptr [esi+24h]
    L_004135a8:
        and dword ptr [ecx+58h],0FFFFFF7Fh
    L_004135af:
        mov dword ptr [esi+20h],edi
    L_004135b2:
        mov eax,1
    L_004135b7:
        pop edi
    L_004135b8:
        mov esp,ebp
    L_004135ba:
        pop ebp
    L_004135bb:
        ret
    L_004135bc:
        fstp st(0)
    L_004135be:
        mov eax,1
    L_004135c3:
        pop edi
    L_004135c4:
        mov esp,ebp
    L_004135c6:
        pop ebp
    L_004135c7:
        ret
    }
}

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

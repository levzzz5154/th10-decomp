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


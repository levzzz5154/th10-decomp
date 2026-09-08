#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046375F..0x00463962: FindHandler
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FindHandler_0046375f() {
    __asm {
    L_0046375f:
        push ebp
    L_00463760:
        mov ebp,esp
    L_00463762:
        sub esp,24h
    L_00463765:
        mov eax,dword ptr [ebp+0Ch]
    L_00463768:
        mov eax,dword ptr [eax+8]
    L_0046376b:
        cmp eax,0FFFFFFFFh
    L_0046376e:
        mov byte ptr [ebp-1],0
    L_00463772:
        mov dword ptr [ebp-1Ch],eax
    L_00463775:
        jl short L_0046377f
    L_00463777:
        mov ecx,dword ptr [ebp+18h]
    L_0046377a:
        cmp eax,dword ptr [ecx+4]
    L_0046377d:
        jl short L_00463784
    L_0046377f:
        call asm_inconsistency_004556e0
    L_00463784:
        push ebx
    L_00463785:
        mov ebx,dword ptr [ebp+8]
    L_00463788:
        cmp dword ptr [ebx],0E06D7363h
    L_0046378e:
        push esi
    L_0046378f:
        push edi
    L_00463790:
        jne asm_target_00463938
    L_00463796:
        cmp dword ptr [ebx+10h],3
    L_0046379a:
        mov edi,19930520h
    L_0046379f:
        jne asm_target_0046382c
    L_004637a5:
        mov eax,dword ptr [ebx+14h]
    L_004637a8:
        cmp eax,edi
    L_004637aa:
        je short L_004637b3
    L_004637ac:
        cmp eax,19930521h
    L_004637b1:
        jne short L_0046382c
    L_004637b3:
        cmp dword ptr [ebx+1Ch],0
    L_004637b7:
        jne short L_0046382c
    L_004637b9:
        call asm_getptd_00456357
    L_004637be:
        cmp dword ptr [eax+7Ch],0
    L_004637c2:
        je asm_target_00463930
    L_004637c8:
        call asm_getptd_00456357
    L_004637cd:
        mov esi,dword ptr [eax+7Ch]
    L_004637d0:
        mov dword ptr [ebp+8],esi
    L_004637d3:
        call asm_getptd_00456357
    L_004637d8:
        mov eax,dword ptr [eax+80h]
    L_004637de:
        push 1
    L_004637e0:
        push esi
    L_004637e1:
        mov dword ptr [ebp+10h],eax
    L_004637e4:
        mov byte ptr [ebp-1],1
    L_004637e8:
        call asm_ValidateRead_00463aca
    L_004637ed:
        test eax,eax
    L_004637ef:
        pop ecx
    L_004637f0:
        pop ecx
    L_004637f1:
        jne short L_004637f8
    L_004637f3:
        call asm_inconsistency_004556e0
    L_004637f8:
        cmp dword ptr [esi],0E06D7363h
    L_004637fe:
        jne asm_target_00463935
    L_00463804:
        mov eax,dword ptr [ebp+8]
    L_00463807:
        cmp dword ptr [eax+10h],3
    L_0046380b:
        jne short L_00463829
    L_0046380d:
        mov eax,dword ptr [eax+14h]
    L_00463810:
        cmp eax,edi
    L_00463812:
        je short L_0046381b
    L_00463814:
        cmp eax,19930521h
    L_00463819:
        jne short L_00463829
    L_0046381b:
        mov eax,dword ptr [ebp+8]
    L_0046381e:
        cmp dword ptr [eax+1Ch],0
    L_00463822:
        jne short L_00463829
    L_00463824:
        call asm_inconsistency_004556e0
    L_00463829:
        mov ebx,dword ptr [ebp+8]
    L_0046382c:
        cmp dword ptr [ebx],0E06D7363h
    L_00463832:
        jne asm_target_00463938
    L_00463838:
        cmp dword ptr [ebx+10h],3
    L_0046383c:
        jne asm_target_00463938
    L_00463842:
        mov eax,dword ptr [ebx+14h]
    L_00463845:
        cmp eax,edi
    L_00463847:
        je short L_00463854
    L_00463849:
        cmp eax,19930521h
    L_0046384e:
        jne asm_target_00463938
    L_00463854:
        mov esi,dword ptr [ebp-1Ch]
    L_00463857:
        lea eax,[ebp-20h]
    L_0046385a:
        push eax
    L_0046385b:
        lea eax,[ebp-0Ch]
    L_0046385e:
        push eax
    L_0046385f:
        push esi
    L_00463860:
        push dword ptr [ebp+20h]
    L_00463863:
        push dword ptr [ebp+18h]
    L_00463866:
        call asm_GetRangeOfTrysToCheck_00462971
    L_0046386b:
        mov ecx,dword ptr [ebp-0Ch]
    L_0046386e:
        add esp,14h
    L_00463871:
        cmp ecx,dword ptr [ebp-20h]
    L_00463874:
        mov dword ptr [ebp-8],eax
    L_00463877:
        jae asm_target_00463920
    L_0046387d:
        jmp short L_00463882
    L_0046387f:
        mov esi,dword ptr [ebp-1Ch]
    L_00463882:
        cmp dword ptr [eax],esi
    L_00463884:
        jg asm_target_0046390b
    L_0046388a:
        cmp esi,dword ptr [eax+4]
    L_0046388d:
        jg short L_0046390b
    L_0046388f:
        mov ecx,dword ptr [eax+0Ch]
    L_00463892:
        test ecx,ecx
    L_00463894:
        mov esi,dword ptr [eax+10h]
    L_00463897:
        mov dword ptr [ebp-18h],ecx
    L_0046389a:
        jle short L_0046390b
    L_0046389c:
        mov ecx,dword ptr [ebx+1Ch]
    L_0046389f:
        mov ecx,dword ptr [ecx+0Ch]
    L_004638a2:
        lea edx,[ecx+4]
    L_004638a5:
        mov ecx,dword ptr [ecx]
    L_004638a7:
        test ecx,ecx
    L_004638a9:
        mov dword ptr [ebp-10h],edx
    L_004638ac:
        mov dword ptr [ebp-14h],ecx
    L_004638af:
        jle short L_004638d5
    L_004638b1:
        mov eax,dword ptr [ebp-10h]
    L_004638b4:
        mov edi,dword ptr [eax]
    L_004638b6:
        push dword ptr [ebx+1Ch]
    L_004638b9:
        mov dword ptr [ebp-24h],edi
    L_004638bc:
        call asm_TypeMatch_00462e11
    L_004638c1:
        test eax,eax
    L_004638c3:
        pop ecx
    L_004638c4:
        jne short L_004638e3
    L_004638c6:
        dec dword ptr [ebp-14h]
    L_004638c9:
        add dword ptr [ebp-10h],4
    L_004638cd:
        cmp dword ptr [ebp-14h],eax
    L_004638d0:
        jg short L_004638b1
    L_004638d2:
        mov eax,dword ptr [ebp-8]
    L_004638d5:
        dec dword ptr [ebp-18h]
    L_004638d8:
        add esi,10h
    L_004638db:
        cmp dword ptr [ebp-18h],0
    L_004638df:
        jg short L_0046389c
    L_004638e1:
        jmp short L_0046390b
    L_004638e3:
        push dword ptr [ebp+24h]
    L_004638e6:
        mov edi,dword ptr [ebp-8]
    L_004638e9:
        push dword ptr [ebp+20h]
    L_004638ec:
        mov ecx,dword ptr [ebp-24h]
    L_004638ef:
        push dword ptr [ebp+18h]
    L_004638f2:
        push dword ptr [ebp+14h]
    L_004638f5:
        push dword ptr [ebp+10h]
    L_004638f8:
        push ebx
    L_004638f9:
        mov ebx,esi
    L_004638fb:
        mov esi,dword ptr [ebp+0Ch]
    L_004638fe:
        call asm_CatchIt_0046363a
    L_00463903:
        mov ebx,dword ptr [ebp+8]
    L_00463906:
        add esp,18h
    L_00463909:
        mov eax,edi
    L_0046390b:
        inc dword ptr [ebp-0Ch]
    L_0046390e:
        mov ecx,dword ptr [ebp-0Ch]
    L_00463911:
        add eax,14h
    L_00463914:
        cmp ecx,dword ptr [ebp-20h]
    L_00463917:
        mov dword ptr [ebp-8],eax
    L_0046391a:
        jb asm_target_0046387f
    L_00463920:
        cmp byte ptr [ebp+1Ch],0
    L_00463924:
        je short L_00463930
    L_00463926:
        push 1
    L_00463928:
        push ebx
    L_00463929:
        call asm_DestructExceptionObject_00462f7c
    L_0046392e:
        pop ecx
    L_0046392f:
        pop ecx
    L_00463930:
        pop edi
    L_00463931:
        pop esi
    L_00463932:
        pop ebx
    L_00463933:
        leave
    L_00463934:
        ret
    L_00463935:
        mov ebx,dword ptr [ebp+8]
    L_00463938:
        cmp byte ptr [ebp+1Ch],0
    L_0046393c:
        jne short L_0046395e
    L_0046393e:
        push dword ptr [ebp+24h]
    L_00463941:
        push dword ptr [ebp+20h]
    L_00463944:
        push dword ptr [ebp-1Ch]
    L_00463947:
        push dword ptr [ebp+18h]
    L_0046394a:
        push dword ptr [ebp+14h]
    L_0046394d:
        push dword ptr [ebp+10h]
    L_00463950:
        push dword ptr [ebp+0Ch]
    L_00463953:
        push ebx
    L_00463954:
        call asm_FindHandlerForForeignException_004636a1
    L_00463959:
        add esp,20h
    L_0046395c:
        jmp short L_00463930
    L_0046395e:
        jmp asm_terminate_00455693
    }
}

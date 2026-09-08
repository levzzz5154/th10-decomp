#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463963..0x00463A04: ___InternalCxxFrameHandler
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_InternalCxxFrameHandler_00463963() {
    __asm {
    L_00463963:
        push ebp
    L_00463964:
        mov ebp,esp
    L_00463966:
        push esi
    L_00463967:
        mov esi,dword ptr [ebp+18h]
    L_0046396a:
        mov eax,dword ptr [esi]
    L_0046396c:
        push edi
    L_0046396d:
        and eax,1FFFFFFFh
    L_00463972:
        mov edi,19930520h
    L_00463977:
        cmp eax,edi
    L_00463979:
        je short L_00463980
    L_0046397b:
        call asm_inconsistency_004556e0
    L_00463980:
        mov eax,dword ptr [ebp+8]
    L_00463983:
        test byte ptr [eax+4],66h
    L_00463987:
        je short L_004639a8
    L_00463989:
        cmp dword ptr [esi+4],0
    L_0046398d:
        je short L_004639fe
    L_0046398f:
        cmp dword ptr [ebp+1Ch],0
    L_00463993:
        jne short L_004639fe
    L_00463995:
        push 0FFFFFFFFh
    L_00463997:
        push esi
    L_00463998:
        push dword ptr [ebp+14h]
    L_0046399b:
        push dword ptr [ebp+0Ch]
    L_0046399e:
        call asm_FrameUnwindToState_00462e7e
    L_004639a3:
        add esp,10h
    L_004639a6:
        jmp short L_004639fe
    L_004639a8:
        cmp dword ptr [esi+0Ch],0
    L_004639ac:
        je short L_004639fe
    L_004639ae:
        cmp dword ptr [eax],0E06D7363h
    L_004639b4:
        jne short L_004639e2
    L_004639b6:
        cmp dword ptr [eax+14h],edi
    L_004639b9:
        jbe short L_004639e2
    L_004639bb:
        mov ecx,dword ptr [eax+1Ch]
    L_004639be:
        mov ecx,dword ptr [ecx+8]
    L_004639c1:
        test ecx,ecx
    L_004639c3:
        je short L_004639e2
    L_004639c5:
        movzx edx,byte ptr [ebp+24h]
    L_004639c9:
        push edx
    L_004639ca:
        push dword ptr [ebp+20h]
    L_004639cd:
        push dword ptr [ebp+1Ch]
    L_004639d0:
        push esi
    L_004639d1:
        push dword ptr [ebp+14h]
    L_004639d4:
        push dword ptr [ebp+10h]
    L_004639d7:
        push dword ptr [ebp+0Ch]
    L_004639da:
        push eax
    L_004639db:
        call ecx
    L_004639dd:
        add esp,20h
    L_004639e0:
        jmp short L_00463a01
    L_004639e2:
        push dword ptr [ebp+20h]
    L_004639e5:
        push dword ptr [ebp+1Ch]
    L_004639e8:
        push dword ptr [ebp+24h]
    L_004639eb:
        push esi
    L_004639ec:
        push dword ptr [ebp+14h]
    L_004639ef:
        push dword ptr [ebp+10h]
    L_004639f2:
        push dword ptr [ebp+0Ch]
    L_004639f5:
        push eax
    L_004639f6:
        call asm_FindHandler_0046375f
    L_004639fb:
        add esp,20h
    L_004639fe:
        xor eax,eax
    L_00463a00:
        inc eax
    L_00463a01:
        pop edi
    L_00463a02:
        pop esi
    L_00463a03:
        pop ebp
    L_00463a04:
        ret
    }
}

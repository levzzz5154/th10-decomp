#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462971..0x004629EA: _GetRangeOfTrysToCheck
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GetRangeOfTrysToCheck_00462971() {
    __asm {
    L_00462971:
        push ebp
    L_00462972:
        mov ebp,esp
    L_00462974:
        push ecx
    L_00462975:
        cmp dword ptr [ebp+0Ch],0
    L_00462979:
        push ebx
    L_0046297a:
        push esi
    L_0046297b:
        push edi
    L_0046297c:
        mov edi,dword ptr [ebp+8]
    L_0046297f:
        mov esi,dword ptr [edi+0Ch]
    L_00462982:
        mov ebx,dword ptr [edi+10h]
    L_00462985:
        mov eax,esi
    L_00462987:
        mov dword ptr [ebp-4],eax
    L_0046298a:
        mov dword ptr [ebp+8],esi
    L_0046298d:
        jl short L_004629c7
    L_0046298f:
        cmp esi,0FFFFFFFFh
    L_00462992:
        jne short L_00462999
    L_00462994:
        call asm_inconsistency_004556e0
    L_00462999:
        mov ecx,dword ptr [ebp+10h]
    L_0046299c:
        dec esi
    L_0046299d:
        lea eax,[esi+esi*4]
    L_004629a0:
        lea eax,[ebx+eax*4]
    L_004629a3:
        cmp dword ptr [eax+4],ecx
    L_004629a6:
        jge short L_004629ad
    L_004629a8:
        cmp ecx,dword ptr [eax+8]
    L_004629ab:
        jle short L_004629b2
    L_004629ad:
        cmp esi,0FFFFFFFFh
    L_004629b0:
        jne short L_004629be
    L_004629b2:
        mov eax,dword ptr [ebp+8]
    L_004629b5:
        dec dword ptr [ebp+0Ch]
    L_004629b8:
        mov dword ptr [ebp-4],eax
    L_004629bb:
        mov dword ptr [ebp+8],esi
    L_004629be:
        cmp dword ptr [ebp+0Ch],0
    L_004629c2:
        jge short L_0046298f
    L_004629c4:
        mov eax,dword ptr [ebp-4]
    L_004629c7:
        mov ecx,dword ptr [ebp+14h]
    L_004629ca:
        inc esi
    L_004629cb:
        mov dword ptr [ecx],esi
    L_004629cd:
        mov ecx,dword ptr [ebp+18h]
    L_004629d0:
        mov dword ptr [ecx],eax
    L_004629d2:
        cmp eax,dword ptr [edi+0Ch]
    L_004629d5:
        ja short L_004629db
    L_004629d7:
        cmp esi,eax
    L_004629d9:
        jbe short L_004629e0
    L_004629db:
        call asm_inconsistency_004556e0
    L_004629e0:
        pop edi
    L_004629e1:
        lea eax,[esi+esi*4]
    L_004629e4:
        pop esi
    L_004629e5:
        lea eax,[ebx+eax*4]
    L_004629e8:
        pop ebx
    L_004629e9:
        leave
    L_004629ea:
        ret
    }
}

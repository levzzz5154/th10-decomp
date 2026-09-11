#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403990..0x004039A9: FUN_00403990
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403990_00403990() {
    __asm {
    L_00403990:
        sub esp,8
    L_00403993:
        mov ecx,dword ptr [ebx+10h]
    L_00403996:
        xor eax,eax
    L_00403998:
        cmp word ptr [ecx],ax
    L_0040399b:
        mov dword ptr [esp+4],eax
    L_0040399f:
        jle asm_target_00403a24
    L_004039a5:
        push ebp
    L_004039a6:
        push esi
    L_004039a7:
        push edi
    L_004039a8:
        TH10_REL8(0xeb, 0x004039a8, VA_asm_FUN_00403990_part_004039b0)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_004039b0:
        mov edx,dword ptr [ebx+14h]
    L_004039b3:
        mov ebp,dword ptr [edx+eax*4]
    L_004039b6:
        test byte ptr [ebp+3],1
    L_004039ba:
        je short L_00403a0e
    L_004039bc:
        cmp word ptr [ebp+1Ch],0
    L_004039c1:
        lea edi,[ebp+1Ch]
    L_004039c4:
        mov dword ptr [esp+0Ch],0
    L_004039cc:
        jl short L_00403a0a
    L_004039ce:
        mov edi,edi
    L_004039d0:
        movsx esi,word ptr [edi+6]
    L_004039d4:
        mov edx,dword ptr [ebx+17Ch]
    L_004039da:
        imul esi,3ACh
    L_004039e0:
        add esi,edx
    L_004039e2:
        push esi
    L_004039e3:
        call asm_FUN_0043ee30_0043ee30
    L_004039e8:
        mov eax,dword ptr [esi+390h]
    L_004039ee:
        test eax,eax
    L_004039f0:
        je short L_004039f6
    L_004039f2:
        inc dword ptr [esp+0Ch]
    L_004039f6:
        movsx eax,word ptr [edi+2]
    L_004039fa:
        add edi,eax
    L_004039fc:
        cmp word ptr [edi],0
    L_00403a00:
        jge short L_004039d0
    L_00403a02:
        mov eax,dword ptr [esp+0Ch]
    L_00403a06:
        test eax,eax
    L_00403a08:
        jne short L_00403a0e
    L_00403a0a:
        and byte ptr [ebp+3],0FEh
    L_00403a0e:
        mov ecx,dword ptr [ebx+10h]
    L_00403a11:
        mov eax,dword ptr [esp+10h]
    L_00403a15:
        movsx edx,word ptr [ecx]
    L_00403a18:
        inc eax
    L_00403a19:
        cmp eax,edx
    L_00403a1b:
        mov dword ptr [esp+10h],eax
    L_00403a1f:
        jl short L_004039b0
    L_00403a21:
        pop edi
    L_00403a22:
        pop esi
    L_00403a23:
        pop ebp
    L_00403a24:
        xor eax,eax
    L_00403a26:
        add esp,8
    L_00403a29:
        ret
    }
}

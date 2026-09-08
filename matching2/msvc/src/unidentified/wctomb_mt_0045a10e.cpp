#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A10E..0x0045A16D: ___wctomb_mt
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_wctomb_mt_0045a10e() {
    __asm {
    L_0045a10e:
        push ebp
    L_0045a10f:
        mov ebp,esp
    L_0045a111:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045a114:
        push esi
    L_0045a115:
        xor esi,esi
    L_0045a117:
        cmp ecx,esi
    L_0045a119:
        jne short L_0045a11f
    L_0045a11b:
        xor eax,eax
    L_0045a11d:
        jmp short L_0045a16b
    L_0045a11f:
        mov eax,dword ptr [ebp+8]
    L_0045a122:
        cmp dword ptr [eax+14h],esi
    L_0045a125:
        jne short L_0045a138
    L_0045a127:
        mov ax,word ptr [ebp+10h]
    L_0045a12b:
        cmp ax,0FFh
    L_0045a12f:
        ja short L_0045a15d
    L_0045a131:
        mov byte ptr [ecx],al
    L_0045a133:
        xor eax,eax
    L_0045a135:
        inc eax
    L_0045a136:
        jmp short L_0045a16b
    L_0045a138:
        lea edx,[ebp+0Ch]
    L_0045a13b:
        push edx
    L_0045a13c:
        push esi
    L_0045a13d:
        push dword ptr [eax+28h]
    L_0045a140:
        mov dword ptr [ebp+0Ch],esi
    L_0045a143:
        push ecx
    L_0045a144:
        push 1
    L_0045a146:
        lea ecx,[ebp+10h]
    L_0045a149:
        push ecx
    L_0045a14a:
        push esi
    L_0045a14b:
        push dword ptr [eax+4]
    L_0045a14e:
        call dword ptr [data_00466154]
    L_0045a154:
        cmp eax,esi
    L_0045a156:
        je short L_0045a15d
    L_0045a158:
        cmp dword ptr [ebp+0Ch],esi
    L_0045a15b:
        je short L_0045a16b
    L_0045a15d:
        call asm_FUN_00456af2_00456af2
    L_0045a162:
        mov dword ptr [eax],2Ah
    L_0045a168:
        or eax,0FFFFFFFFh
    L_0045a16b:
        pop esi
    L_0045a16c:
        pop ebp
    L_0045a16d:
        ret
    }
}

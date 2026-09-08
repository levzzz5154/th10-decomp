#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004610A6..0x004610F3: __mbsnbicoll
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_mbsnbicoll_004610a6() {
    __asm {
    L_004610a6:
        push ebp
    L_004610a7:
        mov ebp,esp
    L_004610a9:
        call asm_getptd_00456357
    L_004610ae:
        mov eax,dword ptr [eax+60h]
    L_004610b1:
        cmp eax,dword ptr [data_00497f94]
    L_004610b7:
        je short L_004610be
    L_004610b9:
        call asm_updatetmbcinfo_0045cf49
    L_004610be:
        cmp dword ptr [ebp+10h],0
    L_004610c2:
        jne short L_004610c8
    L_004610c4:
        xor eax,eax
    L_004610c6:
        pop ebp
    L_004610c7:
        ret
    L_004610c8:
        push dword ptr [eax+4]
    L_004610cb:
        push dword ptr [ebp+10h]
    L_004610ce:
        push dword ptr [ebp+0Ch]
    L_004610d1:
        push dword ptr [ebp+10h]
    L_004610d4:
        push dword ptr [ebp+8]
    L_004610d7:
        push 1
    L_004610d9:
        push dword ptr [eax+0Ch]
    L_004610dc:
        call asm_FUN_00461af9_00461af9
    L_004610e1:
        add esp,1Ch
    L_004610e4:
        test eax,eax
    L_004610e6:
        jne short L_004610ef
    L_004610e8:
        mov eax,7FFFFFFFh
    L_004610ed:
        pop ebp
    L_004610ee:
        ret
    L_004610ef:
        add eax,0FFFFFFFEh
    L_004610f2:
        pop ebp
    L_004610f3:
        ret
    }
}

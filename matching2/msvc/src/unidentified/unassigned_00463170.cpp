#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463170..0x004631D4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00463170() {
    __asm {
    L_00463170:
        push 8
    L_00463172:
        push 46CAD0h
    L_00463177:
        call asm_SEH_prolog_00454bbc
    L_0046317c:
        and dword ptr [ebp-4],0
    L_00463180:
        mov ecx,dword ptr [ebp+0Ch]
    L_00463183:
        call dword ptr [ebp+8]
    L_00463186:
        jmp short L_00463194
    L_00463188:
        mov eax,dword ptr [ebp-14h]
    L_0046318b:
        call asm_unassigned_00462e60
    L_00463190:
        ret
    L_00463191:
        mov esp,dword ptr [ebp-18h]
    L_00463194:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00463198:
        call asm_SEH_epilog_00454bf7
    L_0046319d:
        ret
    L_0046319e:
        push 8
    L_004631a0:
        push 46CAE0h
    L_004631a5:
        call asm_SEH_prolog_00454bbc
    L_004631aa:
        and dword ptr [ebp-4],0
    L_004631ae:
        push dword ptr [ebp+18h]
    L_004631b1:
        push dword ptr [ebp+14h]
    L_004631b4:
        push dword ptr [ebp+10h]
    L_004631b7:
        push dword ptr [ebp+0Ch]
    L_004631ba:
        call dword ptr [ebp+8]
    L_004631bd:
        jmp short L_004631cb
    L_004631bf:
        mov eax,dword ptr [ebp-14h]
    L_004631c2:
        call asm_unassigned_00462e60
    L_004631c7:
        ret
    L_004631c8:
        mov esp,dword ptr [ebp-18h]
    L_004631cb:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004631cf:
        call asm_SEH_epilog_00454bf7
    L_004631d4:
        ret
    }
}

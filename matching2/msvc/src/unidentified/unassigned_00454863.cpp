#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454863..0x004548BD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00454863() {
    __asm {
    L_00454863:
        mov eax,dword ptr [data_00499344]
    L_00454868:
        cmp eax,3
    L_0045486b:
        jne short L_00454884
    L_0045486d:
        mov eax,dword ptr [esp+4]
    L_00454871:
        cmp eax,3F8h
    L_00454876:
        ja short L_00454881
    L_00454878:
        mov dword ptr [data_00499330],eax
    L_0045487d:
        xor eax,eax
    L_0045487f:
        inc eax
    L_00454880:
        ret
    L_00454881:
        xor eax,eax
    L_00454883:
        ret
    L_00454884:
        cmp eax,1
    L_00454887:
        push esi
    L_00454888:
        jne short L_004548ba
    L_0045488a:
        mov esi,dword ptr [esp+8]
    L_0045488e:
        test esi,esi
    L_00454890:
        jbe short L_004548ba
    L_00454892:
        cmp esi,3F8h
    L_00454898:
        ja short L_004548ba
    L_0045489a:
        push esi
    L_0045489b:
        call asm_sbh_heap_init_00453c52
    L_004548a0:
        test eax,eax
    L_004548a2:
        pop ecx
    L_004548a3:
        je short L_004548ba
    L_004548a5:
        xor eax,eax
    L_004548a7:
        mov dword ptr [data_00499330],esi
    L_004548ad:
        mov dword ptr [data_00499344],3
    L_004548b7:
        inc eax
    L_004548b8:
        pop esi
    L_004548b9:
        ret
    L_004548ba:
        xor eax,eax
    L_004548bc:
        pop esi
    L_004548bd:
        ret
    }
}

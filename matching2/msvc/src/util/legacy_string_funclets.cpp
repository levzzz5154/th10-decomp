#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438723..0x00438742: Catch@00438723
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Catch_00438723_00438723() {
    __asm {
    L_00438723:
        mov eax,dword ptr [ebp+8]
    L_00438726:
        mov dword ptr [ebp-18h],eax
    L_00438729:
        inc eax
    L_0043872a:
        mov dword ptr [ebp-10h],esp
    L_0043872d:
        push eax
    L_0043872e:
        mov byte ptr [ebp-4],2
    L_00438732:
        call asm_operator_new_00452493
    L_00438737:
        mov dword ptr [ebp+8],eax
    L_0043873a:
        add esp,4
    L_0043873d:
        mov eax,438743h
    L_00438742:
        ret
    }
}

// 0x004387C2..0x004387F1: Catch@004387c2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Catch_004387c2_004387c2() {
    __asm {
    L_004387c2:
        mov esi,dword ptr [ebp-14h]
    L_004387c5:
        cmp dword ptr [esi+18h],10h
    L_004387c9:
        jb short L_004387d7
    L_004387cb:
        mov edx,dword ptr [esi+4]
    L_004387ce:
        push edx
    L_004387cf:
        call asm_free_004524a1
    L_004387d4:
        add esp,4
    L_004387d7:
        push 0
    L_004387d9:
        mov dword ptr [esi+18h],0Fh
    L_004387e0:
        mov dword ptr [esi+14h],0
    L_004387e7:
        push 0
    L_004387e9:
        mov byte ptr [esi+4],0
    L_004387ed:
        call asm_CxxThrowException_8_00462afb
    }
}

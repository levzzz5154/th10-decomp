#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453AA1..0x00453AE9: __mtinitlocks
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_mtinitlocks_00453aa1() {
    __asm {
    L_00453aa1:
        push esi
    L_00453aa2:
        push edi
    L_00453aa3:
        xor esi,esi
    L_00453aa5:
        mov edi,477210h
    L_00453aaa:
        cmp dword ptr [esi*8+473084h],1
    L_00453ab2:
        jne short L_00453ad2
    L_00453ab4:
        lea eax,[esi*8+473080h]
    L_00453abb:
        mov dword ptr [eax],edi
    L_00453abd:
        push 0FA0h
    L_00453ac2:
        push dword ptr [eax]
    L_00453ac4:
        add edi,18h
    L_00453ac7:
        call asm_crtInitCritSecAndSpinCount_0045980e
    L_00453acc:
        test eax,eax
    L_00453ace:
        pop ecx
    L_00453acf:
        pop ecx
    L_00453ad0:
        je short L_00453ade
    L_00453ad2:
        inc esi
    L_00453ad3:
        cmp esi,24h
    L_00453ad6:
        jl short L_00453aaa
    L_00453ad8:
        xor eax,eax
    L_00453ada:
        inc eax
    L_00453adb:
        pop edi
    L_00453adc:
        pop esi
    L_00453add:
        ret
    L_00453ade:
        and dword ptr [esi*8+473080h],0
    L_00453ae6:
        xor eax,eax
    L_00453ae8:
        jmp short L_00453adb
    }
}

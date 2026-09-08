#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004575BF..0x00457628: __cinit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_cinit_004575bf() {
    __asm {
    L_004575bf:
        mov eax,dword ptr [data_004733a8]
    L_004575c4:
        test eax,eax
    L_004575c6:
        je short L_004575cf
    L_004575c8:
        push dword ptr [esp+4]
    L_004575cc:
        call eax
    L_004575ce:
        pop ecx
    L_004575cf:
        push esi
    L_004575d0:
        push edi
    L_004575d1:
        mov ecx,473034h
    L_004575d6:
        mov edi,47304Ch
    L_004575db:
        xor eax,eax
    L_004575dd:
        cmp ecx,edi
    L_004575df:
        mov esi,ecx
    L_004575e1:
        jae short L_004575fa
    L_004575e3:
        test eax,eax
    L_004575e5:
        jne short L_00457626
    L_004575e7:
        mov ecx,dword ptr [esi]
    L_004575e9:
        test ecx,ecx
    L_004575eb:
        je short L_004575ef
    L_004575ed:
        call ecx
    L_004575ef:
        add esi,4
    L_004575f2:
        cmp esi,edi
    L_004575f4:
        jb short L_004575e3
    L_004575f6:
        test eax,eax
    L_004575f8:
        jne short L_00457626
    L_004575fa:
        push 4597BAh
    L_004575ff:
        call asm_atexit_00452e0a
    L_00457604:
        mov esi,473000h
    L_00457609:
        mov eax,esi
    L_0045760b:
        mov edi,473030h
    L_00457610:
        cmp eax,edi
    L_00457612:
        pop ecx
    L_00457613:
        jae short L_00457624
    L_00457615:
        mov eax,dword ptr [esi]
    L_00457617:
        test eax,eax
    L_00457619:
        je short L_0045761d
    L_0045761b:
        call eax
    L_0045761d:
        add esi,4
    L_00457620:
        cmp esi,edi
    L_00457622:
        jb short L_00457615
    L_00457624:
        xor eax,eax
    L_00457626:
        pop edi
    L_00457627:
        pop esi
    L_00457628:
        ret
    }
}

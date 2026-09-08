#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044D400..0x0044D433: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044d400() {
    __asm {
    L_0044d400:
        push esi
    L_0044d401:
        mov esi,dword ptr [eax+4]
    L_0044d404:
        test esi,esi
    L_0044d406:
        jne short L_0044d40f
    L_0044d408:
        mov eax,800401F0h
    L_0044d40d:
        pop esi
    L_0044d40e:
        ret
    L_0044d40f:
        cmp edx,dword ptr [eax+10h]
    L_0044d412:
        jb short L_0044d41b
    L_0044d414:
        mov eax,80070057h
    L_0044d419:
        pop esi
    L_0044d41a:
        ret
    L_0044d41b:
        mov dword ptr [ecx],0
    L_0044d421:
        mov eax,dword ptr [eax+4]
    L_0044d424:
        mov eax,dword ptr [eax+edx*4]
    L_0044d427:
        mov edx,dword ptr [eax]
    L_0044d429:
        push ecx
    L_0044d42a:
        push 46747Ch
    L_0044d42f:
        push eax
    L_0044d430:
        call dword ptr [edx]
    L_0044d432:
        pop esi
    L_0044d433:
        ret
    }
}

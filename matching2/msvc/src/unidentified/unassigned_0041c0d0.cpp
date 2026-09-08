#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C0D0..0x0041C11D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041c0d0() {
    __asm {
    L_0041c0d0:
        dec dword ptr [ecx+438h]
    L_0041c0d6:
        mov edx,dword ptr [eax+4]
    L_0041c0d9:
        push esi
    L_0041c0da:
        mov esi,dword ptr [eax+8]
    L_0041c0dd:
        mov dword ptr [edx+8],esi
    L_0041c0e0:
        mov edx,dword ptr [eax+8]
    L_0041c0e3:
        test edx,edx
    L_0041c0e5:
        je short L_0041c0ed
    L_0041c0e7:
        mov esi,dword ptr [eax+4]
    L_0041c0ea:
        mov dword ptr [edx+4],esi
    L_0041c0ed:
        cmp dword ptr [ecx+434h],eax
    L_0041c0f3:
        pop esi
    L_0041c0f4:
        jne short L_0041c0ff
    L_0041c0f6:
        mov eax,dword ptr [eax+4]
    L_0041c0f9:
        mov dword ptr [ecx+434h],eax
    L_0041c0ff:
        ret
    L_0041c100:
        push edi
    L_0041c101:
        lea edx,[esi+10h]
    L_0041c104:
        call asm_ScoreObject_Initialize_0041c030
    L_0041c109:
        xor eax,eax
    L_0041c10b:
        mov ecx,117h
    L_0041c110:
        mov edi,esi
    L_0041c112:
        rep stosd
    L_0041c114:
        mov dword ptr [data_0047781c],esi
    L_0041c11a:
        mov eax,esi
    L_0041c11c:
        pop edi
    L_0041c11d:
        ret
    }
}

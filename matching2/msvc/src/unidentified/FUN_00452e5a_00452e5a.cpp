#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452E5A..0x00452EDF: FUN_00452e5a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00452e5a_00452e5a() {
    __asm {
    L_00452e5a:
        push 0Ch
    L_00452e5c:
        push 46A6F0h
    L_00452e61:
        call asm_SEH_prolog_00454bbc
    L_00452e66:
        push dword ptr [data_00473390]
    L_00452e6c:
        call dword ptr [data_00477378]
    L_00452e72:
        mov esi,eax
    L_00452e74:
        test esi,esi
    L_00452e76:
        jne short L_00452e95
    L_00452e78:
        mov esi,dword ptr [ebp+8]
    L_00452e7b:
        push esi
    L_00452e7c:
        push dword ptr [data_00473390]
    L_00452e82:
        call dword ptr [data_0047737c]
    L_00452e88:
        test eax,eax
    L_00452e8a:
        jne short L_00452eb1
    L_00452e8c:
        push 10h
    L_00452e8e:
        call asm_amsg_exit_0045373d
    L_00452e93:
        jmp short L_00452eb0
    L_00452e95:
        mov eax,dword ptr [ebp+8]
    L_00452e98:
        mov ecx,dword ptr [eax+4Ch]
    L_00452e9b:
        mov dword ptr [esi+4Ch],ecx
    L_00452e9e:
        mov ecx,dword ptr [eax+50h]
    L_00452ea1:
        mov dword ptr [esi+50h],ecx
    L_00452ea4:
        mov ecx,dword ptr [eax+4]
    L_00452ea7:
        mov dword ptr [esi+4],ecx
    L_00452eaa:
        push eax
    L_00452eab:
        call asm_free_00452422
    L_00452eb0:
        pop ecx
    L_00452eb1:
        mov eax,dword ptr [data_004733ac]
    L_00452eb6:
        test eax,eax
    L_00452eb8:
        je short L_00452ebc
    L_00452eba:
        call eax
    L_00452ebc:
        and dword ptr [ebp-4],0
    L_00452ec0:
        push dword ptr [esi+50h]
    L_00452ec3:
        call dword ptr [esi+4Ch]
    L_00452ec6:
        pop ecx
    L_00452ec7:
        call asm_endthread_00452e1c
    L_00452ecc:
        mov eax,dword ptr [ebp-14h]
    L_00452ecf:
        mov ecx,dword ptr [eax]
    L_00452ed1:
        mov ecx,dword ptr [ecx]
    L_00452ed3:
        mov dword ptr [ebp-1Ch],ecx
    L_00452ed6:
        push eax
    L_00452ed7:
        push ecx
    L_00452ed8:
        call asm_XcptFilter_004577ce
    L_00452edd:
        pop ecx
    L_00452ede:
        pop ecx
    L_00452edf:
        ret
    }
}

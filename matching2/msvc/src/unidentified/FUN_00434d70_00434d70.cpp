#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434D70..0x00434DCC: FUN_00434d70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00434d70_00434d70() {
    __asm {
    L_00434d70:
        push ebx
    L_00434d71:
        mov bl,byte ptr [esp+8]
    L_00434d75:
        test bl,2
    L_00434d78:
        je short L_00434da4
    L_00434d7a:
        mov eax,dword ptr [esi-4]
    L_00434d7d:
        push edi
    L_00434d7e:
        push 435250h
    L_00434d83:
        lea edi,[esi-4]
    L_00434d86:
        push eax
    L_00434d87:
        push 10h
    L_00434d89:
        push esi
    L_00434d8a:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00434d8f:
        test bl,1
    L_00434d92:
        je short L_00434d9d
    L_00434d94:
        push edi
    L_00434d95:
        call asm_free_004524a1
    L_00434d9a:
        add esp,4
    L_00434d9d:
        mov eax,edi
    L_00434d9f:
        pop edi
    L_00434da0:
        pop ebx
    L_00434da1:
        ret 4
    L_00434da4:
        mov eax,dword ptr [esi]
    L_00434da6:
        test eax,eax
    L_00434da8:
        je short L_00434db9
    L_00434daa:
        push eax
    L_00434dab:
        call asm_free_00452422
    L_00434db0:
        add esp,4
    L_00434db3:
        mov dword ptr [esi],0
    L_00434db9:
        test bl,1
    L_00434dbc:
        je short L_00434dc7
    L_00434dbe:
        push esi
    L_00434dbf:
        call asm_free_004524a1
    L_00434dc4:
        add esp,4
    L_00434dc7:
        mov eax,esi
    L_00434dc9:
        pop ebx
    L_00434dca:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462CC2..0x00462CFF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462cc2() {
    __asm {
    L_00462cc2:
        mov eax,dword ptr [ecx+4]
    L_00462cc5:
        test eax,eax
    L_00462cc7:
        jne short L_00462cce
    L_00462cc9:
        mov eax,46CA70h
    L_00462cce:
        ret
    L_00462ccf:
        push esi
    L_00462cd0:
        lea eax,[esp+8]
    L_00462cd4:
        push eax
    L_00462cd5:
        mov esi,ecx
    L_00462cd7:
        call asm_FUN_00462c12_00462c12
    L_00462cdc:
        mov dword ptr [esi],46CA88h
    L_00462ce2:
        mov eax,esi
    L_00462ce4:
        pop esi
    L_00462ce5:
        ret 4
    L_00462ce8:
        push esi
    L_00462ce9:
        push dword ptr [esp+8]
    L_00462ced:
        mov esi,ecx
    L_00462cef:
        call asm_FUN_00462c5a_00462c5a
    L_00462cf4:
        mov dword ptr [esi],46CA88h
    L_00462cfa:
        mov eax,esi
    L_00462cfc:
        pop esi
    L_00462cfd:
        ret 4
    }
}

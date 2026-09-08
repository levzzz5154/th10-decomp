#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043CBF0..0x0043CC2A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043cbf0() {
    __asm {
    L_0043cbf0:
        push edi
    L_0043cbf1:
        xor eax,eax
    L_0043cbf3:
        mov ecx,14B4h
    L_0043cbf8:
        mov edi,esi
    L_0043cbfa:
        rep stosd
    L_0043cbfc:
        mov eax,dword ptr [esp+8]
    L_0043cc00:
        lea ecx,[esi+5220h]
    L_0043cc06:
        push ecx
    L_0043cc07:
        push 0
    L_0043cc09:
        push esi
    L_0043cc0a:
        push 43CCF0h
    L_0043cc0f:
        push 0
    L_0043cc11:
        push 0
    L_0043cc13:
        mov dword ptr [esi+5228h],eax
    L_0043cc19:
        call dword ptr [data_00466118]
    L_0043cc1f:
        mov dword ptr [esi+5218h],eax
    L_0043cc25:
        xor eax,eax
    L_0043cc27:
        pop edi
    L_0043cc28:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AC60..0x0042AC84: FUN_0042ac60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042ac60_0042ac60() {
    __asm {
    L_0042ac60:
        mov eax,dword ptr [ecx+1Ch]
    L_0042ac63:
        xor edx,edx
    L_0042ac65:
        cmp eax,edx
    L_0042ac67:
        push esi
    L_0042ac68:
        je short L_0042ac70
    L_0042ac6a:
        mov esi,dword ptr [ecx+20h]
    L_0042ac6d:
        mov dword ptr [eax+8],esi
    L_0042ac70:
        mov eax,dword ptr [ecx+20h]
    L_0042ac73:
        cmp eax,edx
    L_0042ac75:
        je short L_0042ac7d
    L_0042ac77:
        mov esi,dword ptr [ecx+1Ch]
    L_0042ac7a:
        mov dword ptr [eax+4],esi
    L_0042ac7d:
        mov dword ptr [ecx+1Ch],edx
    L_0042ac80:
        mov dword ptr [ecx+20h],edx
    L_0042ac83:
        pop esi
    L_0042ac84:
        ret
    }
}

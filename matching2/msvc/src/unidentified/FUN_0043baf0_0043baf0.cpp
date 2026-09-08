#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BAF0..0x0043BB23: FUN_0043baf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043baf0_0043baf0() {
    __asm {
    L_0043baf0:
        mov eax,dword ptr [data_00491c3c]
    L_0043baf5:
        test eax,eax
    L_0043baf7:
        jne short L_0043bb1f
    L_0043baf9:
        mov edx,dword ptr [esp+4]
    L_0043bafd:
        mov eax,dword ptr [data_00491c34]
    L_0043bb02:
        mov ecx,dword ptr [eax]
    L_0043bb04:
        push 0
    L_0043bb06:
        push 491C3Ch
    L_0043bb0b:
        add edx,4
    L_0043bb0e:
        push edx
    L_0043bb0f:
        push eax
    L_0043bb10:
        call dword ptr [ecx+0Ch]
    L_0043bb13:
        test eax,eax
    L_0043bb15:
        jge short L_0043bb1f
    L_0043bb17:
        mov eax,1
    L_0043bb1c:
        ret 8
    L_0043bb1f:
        xor eax,eax
    L_0043bb21:
        ret 8
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046077D..0x00460797: __ui64toa
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ui64toa_0046077d() {
    __asm {
    L_0046077d:
        push ebp
    L_0046077e:
        mov ebp,esp
    L_00460780:
        mov eax,dword ptr [ebp+10h]
    L_00460783:
        push 0
    L_00460785:
        push dword ptr [ebp+14h]
    L_00460788:
        push dword ptr [ebp+0Ch]
    L_0046078b:
        push dword ptr [ebp+8]
    L_0046078e:
        call asm_FID_conflict_x64toa_20_004606df
    L_00460793:
        mov eax,dword ptr [ebp+10h]
    L_00460796:
        pop ebp
    L_00460797:
        ret
    }
}

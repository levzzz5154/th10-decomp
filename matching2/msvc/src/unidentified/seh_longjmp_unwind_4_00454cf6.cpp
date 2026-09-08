#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454CF6..0x00454D10: __seh_longjmp_unwind@4
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_seh_longjmp_unwind_4_00454cf6() {
    __asm {
    L_00454cf6:
        push ebp
    L_00454cf7:
        mov ecx,dword ptr [esp+8]
    L_00454cfb:
        mov ebp,dword ptr [ecx]
    L_00454cfd:
        mov eax,dword ptr [ecx+1Ch]
    L_00454d00:
        push eax
    L_00454d01:
        mov eax,dword ptr [ecx+18h]
    L_00454d04:
        push eax
    L_00454d05:
        call asm_local_unwind2_004598de
    L_00454d0a:
        add esp,8
    L_00454d0d:
        pop ebp
    L_00454d0e:
        ret 4
    }
}

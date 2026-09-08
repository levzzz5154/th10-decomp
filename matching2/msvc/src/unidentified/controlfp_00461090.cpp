#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461090..0x004610A5: __controlfp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_controlfp_00461090() {
    __asm {
    L_00461090:
        mov eax,dword ptr [esp+8]
    L_00461094:
        and eax,0FFF7FFFFh
    L_00461099:
        push eax
    L_0046109a:
        push dword ptr [esp+8]
    L_0046109e:
        call asm_control87_0046105e
    L_004610a3:
        pop ecx
    L_004610a4:
        pop ecx
    L_004610a5:
        ret
    }
}

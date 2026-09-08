#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046015B..0x00460162: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046015b() {
    __asm {
    L_0046015b:
        mov edi,dword ptr [ebp-20h]
    L_0046015e:
        mov ebx,dword ptr [ebp-24h]
    L_00460161:
        xor ecx,ecx
    }
}

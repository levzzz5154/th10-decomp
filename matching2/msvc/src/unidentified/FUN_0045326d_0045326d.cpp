#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045326D..0x0045327C: FUN_0045326d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045326d_0045326d() {
    __asm {
    L_0045326d:
        mov ecx,dword ptr [esp+4]
    L_00453271:
        mov eax,dword ptr [data_00477200]
    L_00453276:
        mov dword ptr [data_00477200],ecx
    L_0045327c:
        ret
    }
}

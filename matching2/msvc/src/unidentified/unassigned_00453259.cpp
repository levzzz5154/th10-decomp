#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453259..0x0045326C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00453259() {
    __asm {
    L_00453259:
        mov eax,dword ptr [data_00477200]
    L_0045325e:
        test eax,eax
    L_00453260:
        je short L_00453264
    L_00453262:
        call eax
    L_00453264:
        push 19h
    L_00453266:
        call asm_amsg_exit_0045373d
    L_0045326b:
        pop ecx
    L_0045326c:
        ret
    }
}

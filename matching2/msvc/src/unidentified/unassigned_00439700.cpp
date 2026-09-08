#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00439700..0x0043972C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00439700() {
    __asm {
    L_00439700:
        push 20h
    L_00439702:
        call asm_Direct3DCreate9_00452176
    L_00439707:
        test eax,eax
    L_00439709:
        mov dword ptr [data_00491c2c],eax
    L_0043970e:
        jne short L_0043972a
    L_00439710:
        push edi
    L_00439711:
        push 46F6A0h
    L_00439716:
        mov edi,474F70h
    L_0043971b:
        call asm_TextLog_AppendLine_0044b8e0
    L_00439720:
        add esp,4
    L_00439723:
        mov eax,1
    L_00439728:
        pop edi
    L_00439729:
        ret
    L_0043972a:
        xor eax,eax
    L_0043972c:
        ret
    }
}

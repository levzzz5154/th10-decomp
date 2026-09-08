#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004654F9..0x00465513: Unwind@004654f9
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004654f9_004654f9() {
    __asm {
    L_004654f9:
        push 401FF0h
    L_004654fe:
        push 8
    L_00465500:
        push 3ACh
    L_00465505:
        mov eax,dword ptr [ebp+4]
    L_00465508:
        add eax,778h
    L_0046550d:
        push eax
    L_0046550e:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00465513:
        ret
    }
}

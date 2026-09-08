#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465400..0x0046541B: Unwind@00465400
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465400_00465400() {
    __asm {
    L_00465400:
        push 41AD60h
    L_00465405:
        push 896h
    L_0046540a:
        push 3F0h
    L_0046540f:
        mov eax,dword ptr [ebp+4]
    L_00465412:
        add eax,14h
    L_00465415:
        push eax
    L_00465416:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0046541b:
        ret
    }
}

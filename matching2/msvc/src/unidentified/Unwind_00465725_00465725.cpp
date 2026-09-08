#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465725..0x0046573F: Unwind@00465725
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465725_00465725() {
    __asm {
    L_00465725:
        push 401FF0h
    L_0046572a:
        push 7
    L_0046572c:
        push 3ACh
    L_00465731:
        mov eax,dword ptr [ebp+4]
    L_00465734:
        add eax,8094h
    L_00465739:
        push eax
    L_0046573a:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0046573f:
        ret
    }
}

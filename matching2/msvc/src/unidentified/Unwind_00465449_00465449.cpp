#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465449..0x00465463: Unwind@00465449
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465449_00465449() {
    __asm {
    L_00465449:
        push 401FF0h
    L_0046544e:
        push 0Ah
    L_00465450:
        push 3ACh
    L_00465455:
        mov eax,dword ptr [ebp+4]
    L_00465458:
        add eax,24C8h
    L_0046545d:
        push eax
    L_0046545e:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00465463:
        ret
    }
}

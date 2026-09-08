#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004652A0..0x004652BA: Unwind@004652a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004652a0_004652a0() {
    __asm {
    L_004652a0:
        push 401FF0h
    L_004652a5:
        push 8
    L_004652a7:
        push 3ACh
    L_004652ac:
        mov eax,dword ptr [ebp+4]
    L_004652af:
        add eax,180h
    L_004652b4:
        push eax
    L_004652b5:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004652ba:
        ret
    }
}

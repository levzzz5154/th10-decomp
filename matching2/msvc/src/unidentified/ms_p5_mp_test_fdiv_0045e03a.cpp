#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E03A..0x0045E062: __ms_p5_mp_test_fdiv
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ms_p5_mp_test_fdiv_0045e03a() {
    __asm {
    L_0045e03a:
        push 46C58Ch
    L_0045e03f:
        call dword ptr [data_00466198]
    L_0045e045:
        test eax,eax
    L_0045e047:
        je short L_0045e05e
    L_0045e049:
        push 46C570h
    L_0045e04e:
        push eax
    L_0045e04f:
        call dword ptr [data_00466158]
    L_0045e055:
        test eax,eax
    L_0045e057:
        je short L_0045e05e
    L_0045e059:
        push 0
    L_0045e05b:
        call eax
    L_0045e05d:
        ret
    L_0045e05e:
        jmp asm_ms_p5_test_fdiv_0045dffa
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453C52..0x00453C99: ___sbh_heap_init
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sbh_heap_init_00453c52() {
    __asm {
    L_00453c52:
        push 140h
    L_00453c57:
        push 0
    L_00453c59:
        push dword ptr [data_00499340]
    L_00453c5f:
        call dword ptr [data_004661e4]
    L_00453c65:
        test eax,eax
    L_00453c67:
        mov dword ptr [data_0049932c],eax
    L_00453c6c:
        jne short L_00453c6f
    L_00453c6e:
        ret
    L_00453c6f:
        mov ecx,dword ptr [esp+4]
    L_00453c73:
        and dword ptr [data_00499324],0
    L_00453c7a:
        and dword ptr [data_00499328],0
    L_00453c81:
        mov dword ptr [data_00499334],eax
    L_00453c86:
        xor eax,eax
    L_00453c88:
        mov dword ptr [data_00499330],ecx
    L_00453c8e:
        mov dword ptr [data_00499338],10h
    L_00453c98:
        inc eax
    L_00453c99:
        ret
    }
}

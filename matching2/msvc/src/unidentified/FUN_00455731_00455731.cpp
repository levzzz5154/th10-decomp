#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455731..0x00455736: FUN_00455731
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00455731_00455731() {
    __asm {
    L_00455731:
        mov eax,dword ptr [data_00477360]
    L_00455736:
        ret
    }
}

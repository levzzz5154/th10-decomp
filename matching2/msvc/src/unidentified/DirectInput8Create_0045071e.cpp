#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045071E..0x00450723: DirectInput8Create
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DirectInput8Create_0045071e() {
    __asm {
    L_0045071e:
        jmp dword ptr [data_00466000]
    }
}

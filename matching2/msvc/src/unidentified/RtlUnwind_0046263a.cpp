#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046263A..0x0046263F: RtlUnwind
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RtlUnwind_0046263a() {
    __asm {
    L_0046263a:
        jmp dword ptr [data_0046607c]
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452176..0x0045217B: Direct3DCreate9
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Direct3DCreate9_00452176() {
    __asm {
    L_00452176:
        jmp dword ptr [data_004662b4]
    }
}

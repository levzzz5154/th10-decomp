#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521D0..0x004521D5: D3DXLoadSurfaceFromFileInMemory
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXLoadSurfaceFromFileInMemory_004521d0() {
    __asm {
    L_004521d0:
        jmp dword ptr [data_004662c4]
    }
}

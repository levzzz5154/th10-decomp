#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004176F0..0x004176F7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004176f0() {
    __asm {
    L_004176f0:
        and dword ptr [eax+35Ch],0FFFFFFFDh
    L_004176f7:
        ret
    }
}

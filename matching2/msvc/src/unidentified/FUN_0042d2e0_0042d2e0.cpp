#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042D2E0..0x0042D2E6: FUN_0042d2e0
// Ghidra byte disassembly confirms this is an ECX-to-EAX adapter before the
// private-EAX dispatcher at 0x0042CDF0. Keep the thunk naked until that
// callback ABI and dispatcher are recovered as one typed cluster; see
// recovery_notes/menu_dispatch_callback_thunks_0042d2e0_0042d2f0.md.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042d2e0_0042d2e0() {
    __asm {
    L_0042d2e0:
        mov eax,ecx
    L_0042d2e2:
        jmp asm_FUN_0042cdf0_0042cdf0
    }
}

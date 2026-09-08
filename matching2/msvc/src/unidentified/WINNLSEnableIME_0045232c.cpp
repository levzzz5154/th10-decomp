#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045232C..0x00452331: WINNLSEnableIME
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_WINNLSEnableIME_0045232c() {
    __asm {
    L_0045232c:
        jmp dword ptr [data_004661fc]
    }
}

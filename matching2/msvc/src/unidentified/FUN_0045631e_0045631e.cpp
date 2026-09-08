#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045631E..0x00456326: FUN_0045631e
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045631e_0045631e() {
    __asm {
    L_0045631e:
        call dword ptr [data_00466170]
    L_00456324:
        ret 4
    }
}

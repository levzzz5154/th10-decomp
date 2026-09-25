#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458EA5..0x00458EB2: __security_check_cookie
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_security_check_cookie_00458ea5() {
    __asm {
    L_00458ea5:
        cmp ecx,dword ptr [data_00473660]
    L_00458eab:
        jne short L_00458eae
    L_00458ead:
        ret
    L_00458eae:
        jmp asm_report_failure_00458e74
    }
}

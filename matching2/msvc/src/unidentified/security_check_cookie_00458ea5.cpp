#include "asm_symbols.hpp"

// 0x00458EA5..0x00458EB2: __security_check_cookie
// Ghidra identifies one fastcall cookie argument in ECX.
extern "C" __declspec(noinline) void __fastcall
asm_security_check_cookie_00458ea5(unsigned int stack_cookie) {
    if (stack_cookie != data_00473660) {
        asm_report_failure_00458e74();
    }
}

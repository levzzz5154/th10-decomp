#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465580..0x0046558A: Unwind@00465580
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465580_00465580() {
    __asm {
    L_00465580:
        mov ecx,dword ptr [ebp+4]
    L_00465583:
        add ecx,0Ch
    L_00465586:
        jmp asm_LegacyString_Clear_004381f0
    }
}

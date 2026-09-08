#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004657DB..0x004657E8: Unwind@004657db
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004657db_004657db() {
    __asm {
    L_004657db:
        mov ecx,dword ptr [ebp+4]
    L_004657de:
        add ecx,2C8h
    L_004657e4:
        jmp asm_Entity_Destructor_00401ff0
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004624C3..0x004624E4: FUN_004624c3
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004624c3_004624c3() {
    __asm {
    L_004624c3:
        push esi
    L_004624c4:
        mov esi,ecx
    L_004624c6:
        push 0
    L_004624c8:
        mov dword ptr [esi+18h],0Fh
    L_004624cf:
        call asm_SetLength_LegacyString_00438590
    L_004624d4:
        push dword ptr [esp+8]
    L_004624d8:
        mov ecx,esi
    L_004624da:
        call asm_Assign_LegacyString_00438350
    L_004624df:
        mov eax,esi
    L_004624e1:
        pop esi
    L_004624e2:
        ret 4
    }
}

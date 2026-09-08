#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413070..0x00413090: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413070() {
    __asm {
    L_00413070:
        fild dword ptr [esp+4]
    L_00413074:
        push ecx
    L_00413075:
        fstp dword ptr [esp]
    L_00413078:
        call asm_FrameTimer_Advance_0044bf40
    L_0041307d:
        ret 4
    L_00413080:
        mov edx,dword ptr [ecx+4]
    L_00413083:
        mov ecx,dword ptr [esp+4]
    L_00413087:
        xor eax,eax
    L_00413089:
        cmp edx,ecx
    L_0041308b:
        setg al
    L_0041308e:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438220..0x0043823D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438220() {
    __asm {
    L_00438220:
        mov eax,edx
    L_00438222:
        push esi
    L_00438223:
        lea esi,[eax+1]
    L_00438226:
        mov cl,byte ptr [eax]
    L_00438228:
        inc eax
    L_00438229:
        test cl,cl
    L_0043822b:
        jne short L_00438226
    L_0043822d:
        mov ecx,dword ptr [esp+8]
    L_00438231:
        sub eax,esi
    L_00438233:
        push eax
    L_00438234:
        push edx
    L_00438235:
        call asm_AssignRange_LegacyString_00438420
    L_0043823a:
        pop esi
    L_0043823b:
        ret 4
    }
}

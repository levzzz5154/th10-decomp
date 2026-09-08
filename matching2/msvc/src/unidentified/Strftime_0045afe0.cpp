#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045AFE0..0x0045B011: __Strftime
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Strftime_0045afe0() {
    __asm {
    L_0045afe0:
        push ebp
    L_0045afe1:
        mov ebp,esp
    L_0045afe3:
        call asm_getptd_00456357
    L_0045afe8:
        mov eax,dword ptr [eax+64h]
    L_0045afeb:
        cmp eax,dword ptr [data_0047320c]
    L_0045aff1:
        je short L_0045aff8
    L_0045aff3:
        call asm_updatetlocinfo_00455ade
    L_0045aff8:
        push dword ptr [ebp+18h]
    L_0045affb:
        push dword ptr [ebp+14h]
    L_0045affe:
        push dword ptr [ebp+10h]
    L_0045b001:
        push dword ptr [ebp+0Ch]
    L_0045b004:
        push dword ptr [ebp+8]
    L_0045b007:
        push eax
    L_0045b008:
        call asm_FUN_0045af1d_0045af1d
    L_0045b00d:
        add esp,18h
    L_0045b010:
        pop ebp
    L_0045b011:
        ret
    }
}

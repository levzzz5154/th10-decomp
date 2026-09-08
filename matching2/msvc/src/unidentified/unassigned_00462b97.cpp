#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462B97..0x00462BEC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462b97() {
    __asm {
    L_00462b97:
        mov eax,dword ptr [esp+4]
    L_00462b9b:
        add ecx,9
    L_00462b9e:
        push ecx
    L_00462b9f:
        add eax,9
    L_00462ba2:
        push eax
    L_00462ba3:
        call asm_strcmp_0045bf30
    L_00462ba8:
        neg eax
    L_00462baa:
        pop ecx
    L_00462bab:
        sbb eax,eax
    L_00462bad:
        pop ecx
    L_00462bae:
        inc eax
    L_00462baf:
        ret 4
    L_00462bb2:
        mov eax,dword ptr [esp+4]
    L_00462bb6:
        add ecx,9
    L_00462bb9:
        push ecx
    L_00462bba:
        add eax,9
    L_00462bbd:
        push eax
    L_00462bbe:
        call asm_strcmp_0045bf30
    L_00462bc3:
        neg eax
    L_00462bc5:
        pop ecx
    L_00462bc6:
        sbb eax,eax
    L_00462bc8:
        pop ecx
    L_00462bc9:
        neg eax
    L_00462bcb:
        ret 4
    L_00462bce:
        mov eax,dword ptr [esp+4]
    L_00462bd2:
        add ecx,9
    L_00462bd5:
        push ecx
    L_00462bd6:
        add eax,9
    L_00462bd9:
        push eax
    L_00462bda:
        call asm_strcmp_0045bf30
    L_00462bdf:
        pop ecx
    L_00462be0:
        pop ecx
    L_00462be1:
        xor ecx,ecx
    L_00462be3:
        test eax,eax
    L_00462be5:
        setg cl
    L_00462be8:
        mov eax,ecx
    L_00462bea:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EBF5..0x0045EC33: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045ebf5() {
    __asm {
    L_0045ebf5:
        mov eax,dword ptr [esp+0Ah]
    L_0045ebf9:
        shr eax,4
    L_0045ebfc:
        and eax,0FFFF07FFh
    L_0045ec01:
        sub eax,3FEh
    L_0045ec06:
        movsx eax,ax
    L_0045ec09:
        ret
    L_0045ec0a:
        mov eax,dword ptr [esp+0Ah]
    L_0045ec0e:
        fld qword ptr [esp+4]
    L_0045ec12:
        mov ecx,dword ptr [esp+0Ch]
    L_0045ec16:
        shr eax,4
    L_0045ec19:
        and eax,7FFh
    L_0045ec1e:
        lea eax,[eax+ecx-3FEh]
    L_0045ec25:
        push eax
    L_0045ec26:
        push ecx
    L_0045ec27:
        push ecx
    L_0045ec28:
        fstp qword ptr [esp]
    L_0045ec2b:
        call asm_set_exp_0045ebcb
    L_0045ec30:
        add esp,0Ch
    L_0045ec33:
        ret
    }
}

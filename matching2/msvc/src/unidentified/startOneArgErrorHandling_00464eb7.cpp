#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464EB7..0x00464EF2: __startOneArgErrorHandling
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_startOneArgErrorHandling_00464eb7() {
    __asm {
    L_00464eb7:
        push ebp
    L_00464eb8:
        mov ebp,esp
    L_00464eba:
        add esp,0FFFFFFE0h
    L_00464ebd:
        mov dword ptr [ebp-20h],eax
    L_00464ec0:
        fstp qword ptr [ebp-8]
    L_00464ec3:
        mov dword ptr [ebp-1Ch],ecx
    L_00464ec6:
        mov eax,dword ptr [ebp+10h]
    L_00464ec9:
        mov ecx,dword ptr [ebp+14h]
    L_00464ecc:
        mov dword ptr [ebp-18h],eax
    L_00464ecf:
        mov dword ptr [ebp-14h],ecx
    L_00464ed2:
        lea eax,[ebp+8]
    L_00464ed5:
        lea ecx,[ebp-20h]
    L_00464ed8:
        push eax
    L_00464ed9:
        push ecx
    L_00464eda:
        push edx
    L_00464edb:
        call asm_FUN_0046508c_0046508c
    L_00464ee0:
        add esp,0Ch
    L_00464ee3:
        fld qword ptr [ebp-8]
    L_00464ee6:
        cmp word ptr [ebp+8],27Fh
    L_00464eec:
        je short L_00464ef1
    L_00464eee:
        fldcw word ptr [ebp+8]
    L_00464ef1:
        leave
    L_00464ef2:
        ret
    }
}

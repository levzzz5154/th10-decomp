#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401DC0..0x00401DDC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401dc0() {
    __asm {
    L_00401dc0:
        mov edx,esi
    L_00401dc2:
        call asm_InitializeEntity_00401de0
    L_00401dc7:
        mov edx,dword ptr [esp+4]
    L_00401dcb:
        mov eax,esi
    L_00401dcd:
        mov ecx,edi
    L_00401dcf:
        mov dword ptr [esi+308h],edi
    L_00401dd5:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00401dda:
        ret 4
    }
}

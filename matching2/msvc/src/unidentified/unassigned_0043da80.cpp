#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043DA80..0x0043DAAB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043da80() {
    __asm {
    L_0043da80:
        mov eax,dword ptr [esi+5208h]
    L_0043da86:
        test eax,eax
    L_0043da88:
        je short L_0043da97
    L_0043da8a:
        push 1
    L_0043da8c:
        push 0
    L_0043da8e:
        call asm_SoundStream_Start_0044d440
    L_0043da93:
        test eax,eax
    L_0043da95:
        jge short L_0043da9d
    L_0043da97:
        or eax,0FFFFFFFFh
    L_0043da9a:
        ret 4
    L_0043da9d:
        mov eax,dword ptr [esp+4]
    L_0043daa1:
        mov dword ptr [esi+5210h],eax
    L_0043daa7:
        xor eax,eax
    L_0043daa9:
        ret 4
    }
}

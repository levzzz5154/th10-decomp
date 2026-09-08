#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453C3D..0x00453C51: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00453c3d() {
    __asm {
    L_00453c3d:
        mov eax,dword ptr [data_00499344]
    L_00453c42:
        sub eax,3
    L_00453c45:
        neg eax
    L_00453c47:
        sbb eax,eax
    L_00453c49:
        not eax
    L_00453c4b:
        and eax,dword ptr [data_00499330]
    L_00453c51:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403077..0x0040308F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00403077() {
    __asm {
    L_00403077:
        int 3
    L_00403078:
        int 3
    L_00403079:
        int 3
    L_0040307a:
        int 3
    L_0040307b:
        int 3
    L_0040307c:
        int 3
    L_0040307d:
        int 3
    L_0040307e:
        int 3
    L_0040307f:
        int 3
    L_00403080:
        push eax
    L_00403081:
        call asm_FUN_00403850_00403850
    L_00403086:
        neg eax
    L_00403088:
        sbb eax,eax
    L_0040308a:
        ret
    L_0040308b:
        int 3
    L_0040308c:
        int 3
    L_0040308d:
        int 3
    L_0040308e:
        int 3
    L_0040308f:
        int 3
    }
}

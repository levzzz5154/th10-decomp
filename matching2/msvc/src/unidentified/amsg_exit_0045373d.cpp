#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045373D..0x0045375E: __amsg_exit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_amsg_exit_0045373d() {
    __asm {
    L_0045373d:
        cmp dword ptr [data_0047720c],1
    L_00453744:
        jne short L_0045374b
    L_00453746:
        call asm_FF_MSGBANNER_0045909f
    L_0045374b:
        push dword ptr [esp+4]
    L_0045374f:
        call asm_FUN_00458efd_00458efd
    L_00453754:
        push 0FFh
    L_00453759:
        call dword ptr [data_00473070]
    }
}

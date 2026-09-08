#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453762..0x00453782: fast_error_exit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_fast_error_exit_00453762() {
    __asm {
    L_00453762:
        cmp dword ptr [data_0047720c],1
    L_00453769:
        jne short L_00453770
    L_0045376b:
        call asm_FF_MSGBANNER_0045909f
    L_00453770:
        push dword ptr [esp+4]
    L_00453774:
        call asm_FUN_00458efd_00458efd
    L_00453779:
        push 0FFh
    L_0045377e:
        call asm_crtExitProcess_00457547
    }
}

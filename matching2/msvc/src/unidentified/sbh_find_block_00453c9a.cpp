#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453C9A..0x00453CC4: ___sbh_find_block
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sbh_find_block_00453c9a() {
    __asm {
    L_00453c9a:
        mov eax,dword ptr [data_00499328]
    L_00453c9f:
        lea ecx,[eax+eax*4]
    L_00453ca2:
        mov eax,dword ptr [data_0049932c]
    L_00453ca7:
        lea ecx,[eax+ecx*4]
    L_00453caa:
        jmp short L_00453cbe
    L_00453cac:
        mov edx,dword ptr [esp+4]
    L_00453cb0:
        sub edx,dword ptr [eax+0Ch]
    L_00453cb3:
        cmp edx,100000h
    L_00453cb9:
        jb short L_00453cc4
    L_00453cbb:
        add eax,14h
    L_00453cbe:
        cmp eax,ecx
    L_00453cc0:
        jb short L_00453cac
    L_00453cc2:
        xor eax,eax
    L_00453cc4:
        ret
    }
}

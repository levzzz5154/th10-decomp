#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462D9E..0x00462DBC: operator=
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_operator_00462d9e() {
    __asm {
    L_00462d9e:
        push esi
    L_00462d9f:
        mov esi,ecx
    L_00462da1:
        cmp esi,dword ptr [esp+8]
    L_00462da5:
        je short L_00462db7
    L_00462da7:
        call asm_exception_00462cac
    L_00462dac:
        push dword ptr [esp+8]
    L_00462db0:
        mov ecx,esi
    L_00462db2:
        call asm_FUN_00462c5a_00462c5a
    L_00462db7:
        mov eax,esi
    L_00462db9:
        pop esi
    L_00462dba:
        ret 4
    }
}

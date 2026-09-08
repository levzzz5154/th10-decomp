#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453C0C..0x00453C3C: __lock
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_lock_00453c0c() {
    __asm {
    L_00453c0c:
        push ebp
    L_00453c0d:
        mov ebp,esp
    L_00453c0f:
        mov eax,dword ptr [ebp+8]
    L_00453c12:
        push esi
    L_00453c13:
        lea esi,[eax*8+473080h]
    L_00453c1a:
        cmp dword ptr [esi],0
    L_00453c1d:
        jne short L_00453c32
    L_00453c1f:
        push eax
    L_00453c20:
        call asm_mtinitlocknum_00453b6c
    L_00453c25:
        test eax,eax
    L_00453c27:
        pop ecx
    L_00453c28:
        jne short L_00453c32
    L_00453c2a:
        push 11h
    L_00453c2c:
        call asm_amsg_exit_0045373d
    L_00453c31:
        pop ecx
    L_00453c32:
        push dword ptr [esi]
    L_00453c34:
        call dword ptr [data_004660b0]
    L_00453c3a:
        pop esi
    L_00453c3b:
        pop ebp
    L_00453c3c:
        ret
    }
}

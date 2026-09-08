#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462225..0x0046224F: __freebuf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_freebuf_00462225() {
    __asm {
    L_00462225:
        push esi
    L_00462226:
        mov esi,dword ptr [esp+8]
    L_0046222a:
        mov eax,dword ptr [esi+0Ch]
    L_0046222d:
        test al,83h
    L_0046222f:
        je short L_0046224e
    L_00462231:
        test al,8
    L_00462233:
        je short L_0046224e
    L_00462235:
        push dword ptr [esi+8]
    L_00462238:
        call asm_free_00452422
    L_0046223d:
        and word ptr [esi+0Ch],0FBF7h
    L_00462243:
        xor eax,eax
    L_00462245:
        pop ecx
    L_00462246:
        mov dword ptr [esi],eax
    L_00462248:
        mov dword ptr [esi+8],eax
    L_0046224b:
        mov dword ptr [esi+4],eax
    L_0046224e:
        pop esi
    L_0046224f:
        ret
    }
}

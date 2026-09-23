#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457589..0x004575A0: __initterm
// Semantic action: visit [begin, end) in four-byte steps and call each
// non-null entry as a no-argument initializer. The retail private ABI supplies
// begin in EAX and end as the sole stack argument; MSVC has no ordinary C++
// declaration for that EAX/stack combination, so keep the exact entry body
// until the caller and callee can be modeled together.
extern "C" __declspec(naked) void __cdecl asm_initterm_00457589() {
    __asm {
    L_00457589:
        push esi
    L_0045758a:
        mov esi,eax
    L_0045758c:
        jmp short L_00457599
    L_0045758e:
        mov eax,dword ptr [esi]
    L_00457590:
        test eax,eax
    L_00457592:
        je short L_00457596
    L_00457594:
        call eax
    L_00457596:
        add esi,4
    L_00457599:
        cmp esi,dword ptr [esp+8]
    L_0045759d:
        jb short L_0045758e
    L_0045759f:
        pop esi
    L_004575a0:
        ret
    }
}

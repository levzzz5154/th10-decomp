#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F4FC..0x0045F58F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045f4fc() {
    __asm {
    L_0045f4fc:
        push 1
    L_0045f4fe:
        push 0
    L_0045f500:
        push dword ptr [esp+0Ch]
    L_0045f504:
        call asm_x_ismbbtype_0045f4c9
    L_0045f509:
        add esp,0Ch
    L_0045f50c:
        ret
    L_0045f50d:
        push 3
    L_0045f50f:
        push 0
    L_0045f511:
        push dword ptr [esp+0Ch]
    L_0045f515:
        call asm_x_ismbbtype_0045f4c9
    L_0045f51a:
        add esp,0Ch
    L_0045f51d:
        ret
    L_0045f51e:
        push 2
    L_0045f520:
        push 0
    L_0045f522:
        push dword ptr [esp+0Ch]
    L_0045f526:
        call asm_x_ismbbtype_0045f4c9
    L_0045f52b:
        add esp,0Ch
    L_0045f52e:
        ret
    L_0045f52f:
        push 1
    L_0045f531:
        push 107h
    L_0045f536:
        push dword ptr [esp+0Ch]
    L_0045f53a:
        call asm_x_ismbbtype_0045f4c9
    L_0045f53f:
        add esp,0Ch
    L_0045f542:
        ret
    L_0045f543:
        push 1
    L_0045f545:
        push 103h
    L_0045f54a:
        push dword ptr [esp+0Ch]
    L_0045f54e:
        call asm_x_ismbbtype_0045f4c9
    L_0045f553:
        add esp,0Ch
    L_0045f556:
        ret
    L_0045f557:
        push 3
    L_0045f559:
        push 117h
    L_0045f55e:
        push dword ptr [esp+0Ch]
    L_0045f562:
        call asm_x_ismbbtype_0045f4c9
    L_0045f567:
        add esp,0Ch
    L_0045f56a:
        ret
    L_0045f56b:
        push 3
    L_0045f56d:
        push 157h
    L_0045f572:
        push dword ptr [esp+0Ch]
    L_0045f576:
        call asm_x_ismbbtype_0045f4c9
    L_0045f57b:
        add esp,0Ch
    L_0045f57e:
        ret
    L_0045f57f:
        push 2
    L_0045f581:
        push 10h
    L_0045f583:
        push dword ptr [esp+0Ch]
    L_0045f587:
        call asm_x_ismbbtype_0045f4c9
    L_0045f58c:
        add esp,0Ch
    L_0045f58f:
        ret
    }
}

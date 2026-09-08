#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BBA0..0x0043BBEC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043bba0() {
    __asm {
    L_0043bba0:
        push esi
    L_0043bba1:
        mov esi,474DD4h
    L_0043bba6:
        call asm_Platform_StopWorker_0044c150
    L_0043bbab:
        push 474DDCh
    L_0043bbb0:
        push 0
    L_0043bbb2:
        push 491C28h
    L_0043bbb7:
        push 43BA90h
    L_0043bbbc:
        push 0
    L_0043bbbe:
        push 0
    L_0043bbc0:
        mov dword ptr [data_00474dec],43BA90h
    L_0043bbca:
        mov dword ptr [data_00474de4],1
    L_0043bbd4:
        mov dword ptr [data_00474de0],0
    L_0043bbde:
        call asm_beginthreadex_00453683
    L_0043bbe3:
        add esp,18h
    L_0043bbe6:
        mov dword ptr [data_00474dd8],eax
    L_0043bbeb:
        pop esi
    L_0043bbec:
        ret
    }
}

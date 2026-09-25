#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457547..0x00457575: ___crtExitProcess
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtExitProcess_00457547() {
    __asm {
    L_00457547:
        push 46AB0Ch
    L_0045754c:
        call dword ptr [data_00466198]
    L_00457552:
        test eax,eax
    L_00457554:
        je short L_0045756c
    L_00457556:
        push 46AAFCh
    L_0045755b:
        push eax
    L_0045755c:
        call dword ptr [data_00466158]
    L_00457562:
        test eax,eax
    L_00457564:
        je short L_0045756c
    L_00457566:
        push dword ptr [esp+4]
    L_0045756a:
        call eax
    L_0045756c:
        push dword ptr [esp+4]
    L_00457570:
        call dword ptr [data_0046614c]
    }
}

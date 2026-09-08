#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045650F..0x0045653D: __freeptd
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_freeptd_0045650f() {
    __asm {
    L_0045650f:
        mov ecx,dword ptr [data_00473390]
    L_00456515:
        cmp ecx,0FFFFFFFFh
    L_00456518:
        je short L_0045653d
    L_0045651a:
        mov eax,dword ptr [esp+4]
    L_0045651e:
        test eax,eax
    L_00456520:
        jne short L_00456529
    L_00456522:
        push ecx
    L_00456523:
        call dword ptr [data_00477378]
    L_00456529:
        push eax
    L_0045652a:
        call asm_freefls_4_004563c8
    L_0045652f:
        push 0
    L_00456531:
        push dword ptr [data_00473390]
    L_00456537:
        call dword ptr [data_0047737c]
    L_0045653d:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456357..0x004563C7: __getptd
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_getptd_00456357() {
    __asm {
    L_00456357:
        push ebx
    L_00456358:
        push esi
    L_00456359:
        call dword ptr [data_0046610c]
    L_0045635f:
        push dword ptr [data_00473390]
    L_00456365:
        mov ebx,eax
    L_00456367:
        call dword ptr [data_00477378]
    L_0045636d:
        mov esi,eax
    L_0045636f:
        test esi,esi
    L_00456371:
        jne short L_004563bc
    L_00456373:
        push 8Ch
    L_00456378:
        push 1
    L_0045637a:
        call asm_FUN_0045794d_0045794d
    L_0045637f:
        mov esi,eax
    L_00456381:
        test esi,esi
    L_00456383:
        pop ecx
    L_00456384:
        pop ecx
    L_00456385:
        je short L_004563b4
    L_00456387:
        push esi
    L_00456388:
        push dword ptr [data_00473390]
    L_0045638e:
        call dword ptr [data_0047737c]
    L_00456394:
        test eax,eax
    L_00456396:
        je short L_004563b4
    L_00456398:
        mov dword ptr [esi+54h],4735D0h
    L_0045639f:
        mov dword ptr [esi+14h],1
    L_004563a6:
        call dword ptr [data_0046619c]
    L_004563ac:
        or dword ptr [esi+4],0FFFFFFFFh
    L_004563b0:
        mov dword ptr [esi],eax
    L_004563b2:
        jmp short L_004563bc
    L_004563b4:
        push 10h
    L_004563b6:
        call asm_amsg_exit_0045373d
    L_004563bb:
        pop ecx
    L_004563bc:
        push ebx
    L_004563bd:
        call dword ptr [data_0046616c]
    L_004563c3:
        mov eax,esi
    L_004563c5:
        pop esi
    L_004563c6:
        pop ebx
    L_004563c7:
        ret
    }
}

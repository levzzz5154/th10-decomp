#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004203C0..0x004203EF: ?TimerWin32_Release@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_TimerWin32_Release_004203c0() {
    __asm {
    L_004203c0:
        mov eax,dword ptr [esi+4]
    L_004203c3:
        test eax,eax
    L_004203c5:
        mov dword ptr [esi],46F810h
    L_004203cb:
        je short L_004203d4
    L_004203cd:
        push eax
    L_004203ce:
        call dword ptr [data_00466288]
    L_004203d4:
        mov eax,dword ptr [esi+8]
    L_004203d7:
        push edi
    L_004203d8:
        mov edi,dword ptr [data_00466274]
    L_004203de:
        push eax
    L_004203df:
        call edi
    L_004203e1:
        mov ecx,dword ptr [esi+8]
    L_004203e4:
        push ecx
    L_004203e5:
        mov dword ptr [esi+4],0
    L_004203ec:
        call edi
    L_004203ee:
        pop edi
    L_004203ef:
        ret
    }
}

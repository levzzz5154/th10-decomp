#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004627A3..0x004627F7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004627a3() {
    __asm {
    L_004627a3:
        mov eax,dword ptr [esp+4]
    L_004627a7:
        push dword ptr [eax+1Ch]
    L_004627aa:
        push dword ptr [eax+28h]
    L_004627ad:
        push 0
    L_004627af:
        push dword ptr [eax+18h]
    L_004627b2:
        call asm_FrameUnwindToState_00462e7e
    L_004627b7:
        add esp,10h
    L_004627ba:
        ret 4
    L_004627bd:
        cld
    L_004627be:
        mov eax,dword ptr [esp+8]
    L_004627c2:
        mov ecx,dword ptr [eax+8]
    L_004627c5:
        cmp ecx,dword ptr [data_00473660]
    L_004627cb:
        je short L_004627d9
    L_004627cd:
        mov eax,dword ptr [esp+4]
    L_004627d1:
        or dword ptr [eax+4],8
    L_004627d5:
        xor eax,eax
    L_004627d7:
        inc eax
    L_004627d8:
        ret
    L_004627d9:
        push 0
    L_004627db:
        push eax
    L_004627dc:
        push dword ptr [eax+14h]
    L_004627df:
        push dword ptr [eax+0Ch]
    L_004627e2:
        push 0
    L_004627e4:
        push dword ptr [esp+20h]
    L_004627e8:
        push dword ptr [eax+10h]
    L_004627eb:
        push dword ptr [esp+20h]
    L_004627ef:
        call asm_InternalCxxFrameHandler_00463963
    L_004627f4:
        add esp,20h
    L_004627f7:
        ret
    }
}

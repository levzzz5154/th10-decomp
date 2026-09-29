#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043D080..0x0043D0EA: publish 37 archived WAVE buffers, then await shutdown.
// Tested C++: reference/semantic_candidates/sound_preload_worker.cpp.
// See reference/recovery_notes/sound_preload_worker_0043d080.md.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d080_0043d080() {
    __asm {
    L_0043d080:
        push esi
    L_0043d081:
        xor esi,esi
    L_0043d083:
        cmp dword ptr [data_004977b4],2
    L_0043d08a:
        je short L_0043d0cd
    L_0043d08c:
        mov eax,dword ptr [esi*4+474B40h]
    L_0043d093:
        push 0
    L_0043d095:
        push 0
    L_0043d097:
        call asm_FUN_0044b360_0044b360
    L_0043d09c:
        test eax,eax
    L_0043d09e:
        mov dword ptr [esi*4+4977C0h],eax
    L_0043d0a5:
        je short L_0043d0cf
    L_0043d0a7:
        inc esi
    L_0043d0a8:
        cmp esi,25h
    L_0043d0ab:
        jl short L_0043d083
    L_0043d0ad:
        mov eax,dword ptr [data_004977b4]
    L_0043d0b2:
        test eax,eax
    L_0043d0b4:
        jne short L_0043d0cd
    L_0043d0b6:
        mov esi,dword ptr [data_004660ac]
    L_0043d0bc:
        TH10_NOP_LEA_ESP_DISP8()
    L_0043d0c0:
        push 1
    L_0043d0c2:
        call esi
    L_0043d0c4:
        mov eax,dword ptr [data_004977b4]
    L_0043d0c9:
        test eax,eax
    L_0043d0cb:
        je short L_0043d0c0
    L_0043d0cd:
        pop esi
    L_0043d0ce:
        ret
    L_0043d0cf:
        mov eax,dword ptr [esi*4+474B40h]
    L_0043d0d6:
        push eax
    L_0043d0d7:
        push 46FDD4h
    L_0043d0dc:
        mov ecx,474F70h
    L_0043d0e1:
        call asm_TextLog_Append_0044b810
    L_0043d0e6:
        add esp,8
    L_0043d0e9:
        pop esi
    L_0043d0ea:
        ret
    }
}

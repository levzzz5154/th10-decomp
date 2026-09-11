#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043B7A0..0x0043B82B: FUN_0043b7a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043b7a0_0043b7a0() {
    __asm {
    L_0043b7a0:
        mov eax,dword ptr [edi+2D4h]
    L_0043b7a6:
        sub esp,8
    L_0043b7a9:
        test eax,eax
    L_0043b7ab:
        push ebp
    L_0043b7ac:
        mov ebp,dword ptr [esp+10h]
    L_0043b7b0:
        jne short L_0043b825
    L_0043b7b2:
        push ebx
    L_0043b7b3:
        push esi
    L_0043b7b4:
        xor ebx,ebx
    L_0043b7b6:
        lea esi,[edi+169h]
    L_0043b7bc:
        TH10_NOP_LEA_ESP_DISP8()
    L_0043b7c0:
        movzx edx,byte ptr [esi]
    L_0043b7c3:
        mov dword ptr [esp+0Ch],edx
    L_0043b7c7:
        mov al,bl
    L_0043b7c9:
        sub al,50h
    L_0043b7cb:
        fild dword ptr [esp+0Ch]
    L_0043b7cf:
        movzx ecx,al
    L_0043b7d2:
        fmul dword ptr [edi+2C8h]
    L_0043b7d8:
        mov dword ptr [esp+10h],ecx
    L_0043b7dc:
        call asm_FUN_00463b2c_00463b2c
    L_0043b7e1:
        add eax,ebp
    L_0043b7e3:
        jns short L_0043b7e9
    L_0043b7e5:
        xor eax,eax
    L_0043b7e7:
        jmp short L_0043b7f3
    L_0043b7e9:
        cmp eax,7Fh
    L_0043b7ec:
        jle short L_0043b7f3
    L_0043b7ee:
        mov eax,7Fh
    L_0043b7f3:
        mov ecx,dword ptr [edi+13Ch]
    L_0043b7f9:
        test ecx,ecx
    L_0043b7fb:
        je short L_0043b81a
    L_0043b7fd:
        mov dl,byte ptr [esp+10h]
    L_0043b801:
        mov byte ptr [esp+18h],dl
    L_0043b805:
        mov byte ptr [esp+1Ah],al
    L_0043b809:
        mov byte ptr [esp+19h],7
    L_0043b80e:
        mov eax,dword ptr [esp+18h]
    L_0043b812:
        push eax
    L_0043b813:
        push ecx
    L_0043b814:
        call dword ptr [data_00466298]
    L_0043b81a:
        inc ebx
    L_0043b81b:
        add esi,17h
    L_0043b81e:
        cmp ebx,10h
    L_0043b821:
        jl short L_0043b7c0
    L_0043b823:
        pop esi
    L_0043b824:
        pop ebx
    L_0043b825:
        pop ebp
    L_0043b826:
        add esp,8
    L_0043b829:
        ret 4
    }
}

// 0x0043E3A0..0x0043E45C: MidiWorker_MessageLoopRetail
// MIDI worker thread loop: wait for the stop event or a window message, drain
// the message queue when one arrives, and stop the running stream when the
// wait reported the event. The wait handle and the worker state are both
// reached through their global slots, exactly as the retail loop does.
struct MidiWorkerState {
    unsigned char pad_00[0x30];
    unsigned int stream;
    unsigned char pad_34[0x40];
    unsigned int stopping;
};

struct TagMsg {
    unsigned int window;
    unsigned int message;
    unsigned int wparam;
    unsigned int lparam;
    unsigned int time;
    unsigned int point_x;
    unsigned int point_y;
};

extern "C" unsigned char data_00497798;
extern "C" unsigned char data_0049779c;
extern "C" void __cdecl asm_FUN_0044d850_0044d850();

extern "C" __declspec(dllimport) unsigned int __stdcall MsgWaitForMultipleObjects(
    unsigned int count, void* handles, unsigned int wake_mask, unsigned int timeout,
    unsigned int wake_flags);
extern "C" __declspec(dllimport) int __stdcall PeekMessageA(
    TagMsg* message, void* window, unsigned int min, unsigned int max, unsigned int remove);

typedef void (__stdcall* StreamStopFn)(void* state, int mode);

extern "C" unsigned int __stdcall asm_MidiWorker_MessageLoopRetail_0043e3a0(void* thread_parameter) {
    int finished = 0;
    TagMsg message;
    do {
        unsigned int wait = MsgWaitForMultipleObjects(1, &data_0049779c, 0, 0xFFFFFFFF, 0xBF);
        MidiWorkerState* state = (MidiWorkerState*)*(void**)&data_00497798;
        if (state == 0)
            finished = 1;
        switch (wait) {
        case 0:
            if (state != 0 && state->stream != 0) {
                state->stopping = 1;
                ((StreamStopFn)asm_FUN_0044d850_0044d850)(*(void**)&data_00497798, 1);
                ((MidiWorkerState*)*(void**)&data_00497798)->stopping = 0;
            }
            break;
        case 1:
            if (PeekMessageA(&message, 0, 0, 0, 1) != 0) {
                do {
                    if (message.message == 18)
                        finished = 1;
                } while (PeekMessageA(&message, 0, 0, 0, 1) != 0);
            }
            break;
        }
    } while (finished == 0);
    return 0;
}

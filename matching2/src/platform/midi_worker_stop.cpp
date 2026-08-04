#include "th10/platform/midi_worker_stop.hpp"

#ifdef _MSC_VER
extern "C" void sub_44D550(void*);
extern "C" void* __imp_PostThreadMessageA;
extern "C" void* __imp_WaitForSingleObject;
extern "C" void* __imp_CloseHandle;
#endif

// 0x0043DAB0 - Stop the MIDI worker. Retail guards on the device slot
// (context+0x5208): when it is set, it flushes playback (0x0044D550),
// and if the worker handle at +0x618 is live it posts message 0x12 to
// the worker thread id at +0x614 and waits 0x100 ms on the handle,
// re-posting while the wait result is non-zero; both the worker handle
// and the companion handle at +0x520C are then closed and the worker
// slot cleared. Finally the device object is destroyed through its
// first vtable entry with argument 1 and its slot cleared. The Win32
// edges are injected so host tests can drive the polling loop.
#ifdef _MSC_VER
__declspec(naked) void MidiWorker_StopRetail() {
    __asm {
        push edi
        mov edi, [esi+5208h]
        test edi, edi
        jz loc_43DB5E
        call sub_44D550
        mov eax, [esi+618h]
        test eax, eax
        jz loc_43DB44
        mov eax, [esi+614h]
        mov edi, dword ptr [__imp_PostThreadMessageA]
        push ebx
        push 0
        push 0
        push 12h
        push eax
        call edi
        mov ecx, [esi+618h]
        mov ebx, dword ptr [__imp_WaitForSingleObject]
        push 100h
        push ecx
        call ebx
        test eax, eax
        jz loc_43DB21
        _emit 8Dh
        _emit 64h
        _emit 24h
        _emit 00h
loc_43DB00:
        mov edx, [esi+614h]
        push 0
        push 0
        push 12h
        push edx
        call edi
        mov eax, [esi+618h]
        push 100h
        push eax
        call ebx
        test eax, eax
        jnz loc_43DB00
loc_43DB21:
        mov ecx, [esi+618h]
        mov edi, dword ptr [__imp_CloseHandle]
        push ecx
        call edi
        mov edx, [esi+520Ch]
        push edx
        call edi
        mov dword ptr [esi+618h], 0
        pop ebx
loc_43DB44:
        mov ecx, [esi+5208h]
        test ecx, ecx
        jz loc_43DB5E
        mov eax, [ecx]
        push 1
        call dword ptr [eax]
        mov dword ptr [esi+5208h], 0
loc_43DB5E:
        pop edi
        ret
    }
}
#endif

void MidiWorker_Stop(MidiWorkerState* state, void (*flush)(),
                     int (*post_thread_message)(uint32_t thread_id,
                                                uint32_t message,
                                                uint32_t wparam,
                                                uint32_t lparam),
                     uint32_t (*wait)(void* handle, uint32_t milliseconds),
                     void (*close)(void* handle)) {
    if (state->device == 0) {
        return;
    }
    if (flush != 0) {
        flush();
    }
    if (state->worker_thread != 0) {
        uint32_t result;
        do {
            if (post_thread_message != 0) {
                post_thread_message(state->worker_thread_id, 0x12, 0, 0);
            }
            result = wait != 0 ? wait(state->worker_thread, 0x100) : 0;
        } while (result != 0);
        if (close != 0) {
            close(state->worker_thread);
            close(state->companion_handle);
        }
        state->worker_thread = 0;
    }
    if (state->device != 0) {
        state->device->vtbl->destroy(1);
        state->device = 0;
    }
}

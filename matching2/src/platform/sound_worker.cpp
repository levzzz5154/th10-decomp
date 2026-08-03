#include "th10/platform/sound_worker.hpp"

#ifdef _MSC_VER
extern "C" void* __imp_WaitForSingleObject;
extern "C" void* __imp_Sleep;
extern "C" void* __imp_CloseHandle;
#endif

// 0x0043CC40 - Stop the sound/music worker pair. The retail function
// guards on the primary handle at context+0x5218, raises the stop flag
// at +0x5224 when it is still clear, polls each handle with
// WaitForSingleObject(handle, 100) and Sleep(1) while the wait times
// out (0x102), then closes both handles and clears their slots. The
// readable form injects the three Win32 edges; a null hook is treated
// as an immediately signaled wait / no-op, following the shared
// Platform_StopWorker (0x0044C130) convention.
#ifdef _MSC_VER
__declspec(naked) unsigned int Platform_StopSoundWorkersRetail() {
    __asm {
        mov eax, [esi+5218h]
        test eax, eax
        jz loc_43CCEC
        mov ecx, [esi+5224h]
        test ecx, ecx
        jnz loc_43CC62
        mov dword ptr [esi+5224h], 1
loc_43CC62:
        push ebx
        push edi
        mov edi, dword ptr [__imp_WaitForSingleObject]
        push 64h
        push eax
        call edi
        cmp eax, 102h
        mov ebx, dword ptr [__imp_Sleep]
        jnz loc_43CC96
        _emit 8Dh
        _emit 64h
        _emit 24h
        _emit 00h
loc_43CC80:
        push 1
        call ebx
        mov eax, [esi+5218h]
        push 64h
        push eax
        call edi
        cmp eax, 102h
        jz loc_43CC80
loc_43CC96:
        mov ecx, [esi+521Ch]
        push 64h
        push ecx
        call edi
        cmp eax, 102h
        jnz loc_43CCBE
loc_43CCA8:
        push 1
        call ebx
        mov edx, [esi+521Ch]
        push 64h
        push edx
        call edi
        cmp eax, 102h
        jz loc_43CCA8
loc_43CCBE:
        mov eax, [esi+5218h]
        mov edi, dword ptr [__imp_CloseHandle]
        push eax
        call edi
        mov ecx, [esi+521Ch]
        push ecx
        call edi
        pop edi
        mov dword ptr [esi+5218h], 0
        mov dword ptr [esi+521Ch], 0
        pop ebx
loc_43CCEC:
        xor eax, eax
        ret
    }
}
#endif

unsigned int Platform_StopSoundWorkers(
        SoundWorkerState* state, unsigned int (*wait)(void*, unsigned int),
        void (*sleep)(unsigned int), void (*close)(void*)) {
    if (state->worker_thread == 0) {
        return 0;
    }
    if (state->stop_requested == 0) {
        state->stop_requested = 1;
    }
    while (wait != 0 && wait(state->worker_thread, 100) == 0x102u) {
        if (sleep != 0) {
            sleep(1);
        }
    }
    while (wait != 0 && wait(state->companion_thread, 100) == 0x102u) {
        if (sleep != 0) {
            sleep(1);
        }
    }
    if (close != 0) {
        close(state->worker_thread);
        close(state->companion_thread);
    }
    state->worker_thread = 0;
    state->companion_thread = 0;
    return 0;
}

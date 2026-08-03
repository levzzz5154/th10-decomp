#include "th10/game/progress_worker.hpp"

#include "th10/game/pool_constructors.hpp"

#ifdef _MSC_VER
extern "C" void* operator_new(unsigned int);
extern "C" void sub_42C920(void*);
extern "C" void sub_44C150(void*);
extern "C" void sub_42C9F0(void*);
extern "C" unsigned long beginthread_ex(void*, unsigned int, void*, void*,
                                        unsigned int, unsigned int*);
#endif

// 0x0042CD50 - Create the progress manager and start its worker thread.
// Retail calls the statically linked operator new with size 0x5ACC
// (host callers must return at least kProgressManagerDwords words),
// constructs and publishes the manager, stops the current worker, and
// then fills the embedded worker control block exactly like the generic
// worker start at 0x0044C1C0: entry point at word 0x16B2, running flag
// at 0x16B0, stop request cleared at 0x16AF, and the _beginthreadex
// handle at word 0x16AD with the thread id at 0x16AE.
#ifdef _MSC_VER
__declspec(naked) uint32_t* ProgressManager_CreateAndStartWorker(
        void* (*allocate)(uint32_t size),
        void (*stop_current)(uint32_t* manager),
        uintptr_t (*begin_thread)(void* security, unsigned stack_size,
                                  void* start, void* argument, unsigned flags,
                                  uint32_t* thread_id),
        void* thread_proc) {
    __asm {
        push esi
        push edi
        push 5ACCh
        call operator_new
        add esp, 4
        test eax, eax
        jz loc_42CD6E
        mov edx, eax
        call sub_42C920
        mov edi, eax
        jmp loc_42CD70
loc_42CD6E:
        xor edi, edi
loc_42CD70:
        lea esi, [edi+5AB0h]
        call sub_44C150
        lea eax, [esi+8]
        push eax
        push 0
        push edi
        push offset sub_42C9F0
        push 0
        push 0
        mov dword ptr [esi+18h], offset sub_42C9F0
        mov dword ptr [esi+10h], 1
        mov dword ptr [esi+0Ch], 0
        call beginthread_ex
        add esp, 18h
        mov [esi+4], eax
        mov eax, edi
        pop edi
        pop esi
        ret
    }
}
#else
uint32_t* ProgressManager_CreateAndStartWorker(
        void* (*allocate)(uint32_t size),
        void (*stop_current)(uint32_t* manager),
        uintptr_t (*begin_thread)(void* security, unsigned stack_size,
                                  void* start, void* argument, unsigned flags,
                                  uint32_t* thread_id),
        void* thread_proc) {
    uint32_t* state =
        allocate != 0 ? (uint32_t*)allocate(0x5ACC) : (uint32_t*)0;
    if (state == 0) {
        return 0;
    }
    ProgressManager_ConstructAndPublish(state);
    if (stop_current != 0) {
        stop_current(state);
    }
    // Retail keeps 32-bit slots; the host image truncates like the
    // release path at 0x0042AB20.
    state[0x16B2] = (uint32_t)(uintptr_t)thread_proc;
    state[0x16B0] = 1;
    state[0x16AF] = 0;
    const uintptr_t handle =
        begin_thread != 0
            ? begin_thread(0, 0, thread_proc, state, 0, &state[0x16AE])
            : 0;
    state[0x16AD] = (uint32_t)handle;
    return state;
}
#endif

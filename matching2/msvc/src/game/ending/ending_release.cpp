// 0x0040B7B0: detach the ending's tasks, release its animation banks and
// script storage, then clear the published ending (g_ending).
#include "../../../layout/ltcg/message_teardown_dependencies.hpp"
extern "C" void* data_00491be4;
extern "C" void* g_ending;
extern "C" int data_004918a4;
inline void ReleaseEndingBank(int index) {
    AnimationResource_00447810*& bank = reinterpret_cast<AnimationResource_00447810*&>(data_00491c10->banks[index]);
    if (bank) {
        bank->Release();
        entry_free_004524a1(bank);
        bank = 0;
    }
}

struct EndingState {
    unsigned int flags; // +0x00
    unsigned int reserved_004;
    SchedulerTask* update_task; // +0x08
    SchedulerTask* draw_task; // +0x0C
    unsigned int reserved_010;
    void* script; // +0x14
    BulletAnimOwner* animations; // +0x18
};

#pragma code_seg(".text$03message")
extern "C" __declspec(noinline) void __stdcall Ending_Release(EndingState* state) {
    SchedulerTask* task = state->update_task;
    Scheduler* scheduler = (Scheduler*)data_00491be4;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = state->draw_task;
    scheduler = (Scheduler*)data_00491be4;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    data_00491c10->Clear(0);
    BulletAnimOwner* animations = state->animations;
    if (animations) {
        animations->Destroy();
        entry_free_004524a1(animations);
    }
    state->animations = 0;
    ReleaseEndingBank(29);
    ReleaseEndingBank(30);
    ReleaseEndingBank(31);
    ReleaseEndingBank(32);
    if (state->script) {
        entry_free_00452422(state->script);
        state->script = 0;
    }
    state->script = 0;
    g_ending = 0;
    data_004918a4 = 0;
}
#pragma code_seg()

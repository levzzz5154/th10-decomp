#include "../../../layout/ltcg/title_teardown_0041fb50/title_teardown_dependencies.hpp"

inline void ReleaseLoadingBank(int index) {
    AnimationResource_00447810*& bank = reinterpret_cast<AnimationResource_00447810*&>(data_00491c10->banks[index]);
    if (bank) {
        bank->Release();
        entry_free_004524a1(bank);
        bank = 0;
    }
}

#pragma code_seg(".text$03title")
TitleState_0041FB50::~TitleState_0041FB50() {
    worker.Stop();
    SchedulerTask* task = update_task;
    Scheduler* scheduler = static_cast<Scheduler*>(data_00491be4);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = draw_task;
    scheduler = static_cast<Scheduler*>(data_00491be4);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    ReleasePair_0041f930();
    ReleaseLoadingBank(1);
    GameThread* thread = static_cast<GameThread*>(g_ascii_manager);
    g_loading = 0;
    if (thread) {
        DestroyGameThread_00401260(thread);
        entry_free_004524a1(thread);
    }
    ReleaseLoadingBank(0);
    static_cast<ScoreArchive_0042B1E0*>(data_0047783c)->Save();
    ScoreArchive_0042B1E0* archive = static_cast<ScoreArchive_0042B1E0*>(data_0047783c);
    if (archive) {
        if (archive->file) {
            entry_free_00452422(archive->file);
            archive->file = 0;
        }
        if (archive->sections) {
            entry_free_00452422(archive->sections);
            archive->sections = 0;
        }
        entry_free_004524a1(archive);
    }
    data_0047783c = 0;
}
#pragma code_seg()

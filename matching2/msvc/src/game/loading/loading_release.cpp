#include "../../../build_support/layout/ltcg/title_teardown_0041fb50/title_teardown_dependencies.hpp"

inline void ReleaseLoadingBank(int index) {
    AnimationResource_00447810*& bank = reinterpret_cast<AnimationResource_00447810*&>(g_sprt_ctrl->banks[index]);
    if (bank) {
        bank->Release();
        crt_free_startup(bank);
        bank = 0;
    }
}

#pragma code_seg(".text$03title")
TitleState::~TitleState() {
    worker.Stop();
    SchedulerTask* task = update_task;
    FuncCtrl* scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        FuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = draw_task;
    scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        FuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    ReleasePair_0041f930();
    ReleaseLoadingBank(1);
    GameThread* thread = static_cast<GameThread*>(g_ascii_manager);
    g_loading = 0;
    if (thread) {
        DestroyGameThread(thread);
        crt_free_startup(thread);
    }
    ReleaseLoadingBank(0);
    static_cast<ScoreArchive*>(g_score)->Save();
    ScoreArchive* archive = static_cast<ScoreArchive*>(g_score);
    if (archive) {
        if (archive->file) {
            crt_free(archive->file);
            archive->file = 0;
        }
        if (archive->sections) {
            crt_free(archive->sections);
            archive->sections = 0;
        }
        crt_free_startup(archive);
    }
    g_score = 0;
}
#pragma code_seg()

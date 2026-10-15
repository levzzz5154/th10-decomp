// 0x00401260: GameThread destructor. Unregisters its three scheduler tasks
// and unloads the text and capture script banks; the two slots then free
// their own blocks.
#include "th10/game/game_thread.hpp"
#include "th10/game/manager_teardown_helpers.hpp"

extern "C" {
extern AnimationBanks_00402440* data_00491c10;
extern GameThread* g_ascii_manager;
}

#pragma code_seg(".text$01dtor")
GameThread::~GameThread() {
    RemoveSchedulerTask(update_task);
    RemoveSchedulerTask(draw_task);
    RemoveSchedulerTask(late_draw_task);
    ReleaseAnimationBank(data_00491c10, 2);
    ReleaseAnimationBank(data_00491c10, 0);
    ReleaseAnimationBank(data_00491c10, 3);
    g_ascii_manager = 0;
}
#pragma code_seg()

// 0x00429610: create the replay manager and start it recording or playing
// back. A manager that fails to start is destroyed again and the factory
// returns null. The compiler-generated cleanup at 0x00465660 frees the block
// if a node constructor throws.
#include "th10/game/replay_manager_create.hpp"

#pragma code_seg(".text$04create")
ReplayManager* __stdcall ReplayManager_Create2(int start_mode, const char* replay_path) {
    ReplayManager* manager = new ReplayManager;
    if (manager->Start(start_mode, replay_path)) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()

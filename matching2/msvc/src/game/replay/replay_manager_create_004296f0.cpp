// 0x004296F0: create the replay manager for a replay file. The inlined
// constructor builds the eight list nodes and clears the block; a manager
// that fails to initialize is destroyed again and the factory returns null.
// The compiler-generated cleanup at 0x00465640 frees the block if a node
// constructor throws.
#include "th10/game/replay_manager_create_004296f0.hpp"

#pragma code_seg(".text$04create")
ReplayManager_004296f0* __stdcall ReplayManager_Create_004296f0(const char* replay_path) {
    ReplayManager_004296f0* manager = new ReplayManager_004296f0;
    manager->mode = 2;
    if (manager->Initialize(replay_path)) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()

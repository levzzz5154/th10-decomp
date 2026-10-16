// 0x004296F0: create the replay manager for a replay file. The inlined
// constructor builds the eight list nodes and clears the block; a manager
// that fails to initialize is destroyed again and the factory returns null.
// The compiler-generated cleanup at 0x00465640 frees the block if a node
// constructor throws.
#include "th10/game/replay_manager_create.hpp"

#pragma code_seg(".text$04create")
ReplayManager* __stdcall ReplayManager_Create3(const char* replay_path) {
    ReplayManager* manager = new ReplayManager;
    manager->mode = 2;
    if (manager->Initialize(replay_path)) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()

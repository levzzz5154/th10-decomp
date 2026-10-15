#include "th10/game/item_manager_destructor.hpp"

// 0x0041BA00..0x0041BA2F: the item manager's update task. Report 1 while the active scene's flag word has bit 0
// or bit 2 set (the frame-phased flags), or bit 10 (the busy flag), otherwise
// hand the manager that arrived in ECX to the item update at 0x0041AFD0 (the
// argument is taken on the stack and cleaned by the callee). Only the bytes this
// routine reads are described.
struct SceneFlags_0041ba00 {
    unsigned char unknown_00[0x58];
    unsigned int flags_58;               // +0x58
};


extern "C" unsigned char data_00477810;  // 0x00477810  active scene
extern "C" int __stdcall asm_FUN_0041afd0_0041afd0(void* self);

int ItemManager::OnUpdate() {
    SceneFlags_0041ba00* scene = *(SceneFlags_0041ba00**)&data_00477810;
    if (scene != 0 && ((((scene->flags_58 >> 2) | scene->flags_58) & 1) != 0 ||
                       (scene->flags_58 & 0x400) != 0))
        return 1;
    return asm_FUN_0041afd0_0041afd0(this);
}

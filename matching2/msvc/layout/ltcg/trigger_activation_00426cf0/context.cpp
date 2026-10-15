// Compiler context only; the selected stdcall activation keeps its public ABI.
#include "../../../src/game/player/trigger_activation.cpp"
#include "../result_open_00423370/find.cpp"
#include "../result_open_00423370/allocate.cpp"
#include "../result_open_00423370/dispatcher_animation_helpers.cpp"
#include "set_position.cpp"
#include "../result_open_00423370/animation_manager_queue_resource_0043dc90.cpp"
#define data_00491c10 g_trigger_load_manager
#define code_seg(name) code_seg(".text$0043e710_fn")
#include "../../../src/core/sprtanim/animation_object_load_script_0043e710.cpp"
#undef code_seg
#undef data_00491c10
#pragma code_seg()

#pragma code_seg(".text$0044ba00_context")
extern "C" int __stdcall TriggerActivationContext(Player* player) {
    Player_Hit(player);
    return 1;
}
#pragma code_seg()

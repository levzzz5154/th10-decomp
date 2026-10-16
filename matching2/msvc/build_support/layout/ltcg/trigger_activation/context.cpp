// Compiler context only; the selected stdcall activation keeps its public ABI.
#include "../../../../src/game/player/trigger_activation.cpp"
#include "../result_open/find.cpp"
#include "../result_open/allocate.cpp"
#include "../result_open/dispatcher_animation_helpers.cpp"
#include "set_position.cpp"
#include "../result_open/animation_manager_queue_resource.cpp"
#define g_sprt_ctrl g_trigger_load_manager
#define code_seg(name) code_seg(".text$0043e710_fn")
#include "../../../../src/core/sprtanim/animation_object_load_script.cpp"
#undef code_seg
#undef g_sprt_ctrl
#pragma code_seg()

#pragma code_seg(".text$0044ba00_context")
extern "C" int __stdcall TriggerActivationContext(Player* player) {
    Player_Hit(player);
    return 1;
}
#pragma code_seg()

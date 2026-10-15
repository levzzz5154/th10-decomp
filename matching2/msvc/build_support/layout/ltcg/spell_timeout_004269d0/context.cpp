// Complete helper bodies let native LTCG derive their private register ABIs.
#include "../../../../src/game/player/player_die.cpp"
#include "set_active_count.cpp"
#define g_sprt_ctrl g_timeout_load_manager
#define code_seg(name) code_seg(".text$0043e710_fn")
#include "../../../../src/core/sprtanim/animation_object_load_script_0043e710.cpp"
#undef code_seg
#undef g_sprt_ctrl
#pragma code_seg()
#define code_seg(name) code_seg(".text$0041a120_fn")
#include "../../../../src/game/hint/hint_data_create.cpp"
#undef code_seg
#pragma code_seg()
#define code_seg(name) code_seg(".text$00424650_fn")
#include "../../../../src/game/pause/stage_tip_create_urgent_00424650.cpp"
#undef code_seg
#pragma code_seg()

#pragma code_seg(".text$0044ba00_context")
extern "C" int __stdcall TimeoutContext(Player* field) {
    Player_Die(field);
    return 1;
}
#pragma code_seg()

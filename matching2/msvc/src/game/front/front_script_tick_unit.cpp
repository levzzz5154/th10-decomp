// Equivalent-recovery unit for 0x00415E90: the walker model followed by the
// helper graph of build_support/contexts/legacy/game/front_script_tick_00415e90.cpp, in its order.
#include "../../../build_support/contexts/equivalent/game/front_script_tick_00415e90.cpp"
#include "../pause/result_menu_open.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/dispatcher_handle_helpers.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/dispatcher_animation_helpers.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/dispatcher_input_mode.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/frame_timer.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/path_decode_xor_00417010.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/score_bookkeeping.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/animation_manager_queue_resource_0043dc90.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/animation_object_configure_from_resource_0043e5a0.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/recovery_mark_text_and_dispatcher_004479d0.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/ascii_manager_create_retail_0043c8b0.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/fun_0043c970_0043c970.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/runtime_selector_0043c970_scheduler_create.cpp"
#include "../../../build_support/layout/ltcg/result_open_00423370/scheduler_tasks.cpp"

// 0x00415AE0 - the scheduler trampoline: the task loop holds the front
// runtime in ECX and the callback hands it to the update as its single stack
// argument while preserving the register.
#pragma code_seg(".text$00415ae0_fn")
struct FrontUpdateView;
__declspec(noinline) int __stdcall FrontHudUpdate_00414900(FrontUpdateView* front);
extern "C" __declspec(noinline) int __fastcall FrontHudCallback_00415ae0(void* state) {
    return FrontHudUpdate_00414900((FrontUpdateView*)state);
}
#pragma code_seg()

// 0x00448D00 in the out-record form the walker calls.
#pragma code_seg(".text$00448d00_at")
int* __stdcall DispatcherCreateAt(
        AnimationResource_00449870* resource, int* out, int script_index, int render_bucket) {
    Entity* object = reinterpret_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = render_bucket;
    object->flags_35C = flags | 0x40000000;
    resource->InitializeObject(object, script_index);
    *out = reinterpret_cast<DispatcherPrimaryLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object).value;
    return out;
}
#pragma code_seg()

// The game counters around 0x00474C68 are address-taken elsewhere in the
// program, so stores through pointers force their reloads.
#pragma code_seg(".text$02entry")
extern "C" void* __stdcall FrontScriptTickEscape(int which) {
    switch (which) {
    case 0: return &g_globals_character;
    case 1: return &g_globals_shot_type;
    case 2: return &g_globals_difficulty;
    case 3: return &g_globals_stage;
    case 4: return &g_globals_lives;
    case 5: return &g_globals_gauge;
    case 6: return &g_globals_power;
    default: return &data_00474c84;
    }
}
#pragma code_seg()

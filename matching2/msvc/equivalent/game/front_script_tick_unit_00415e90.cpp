// Equivalent-recovery unit for 0x00415E90: the walker model followed by the
// helper graph of src/game/front_script_tick_00415e90.cpp, in its order.
#include "front_script_tick_00415e90.cpp"
#include "../../src/game/result_menu_open.cpp"
#include "../../layout/ltcg/result_open_00423370/dispatcher_handle_helpers.cpp"
#include "../../layout/ltcg/result_open_00423370/dispatcher_animation_helpers.cpp"
#include "../../layout/ltcg/result_open_00423370/dispatcher_input_mode.cpp"
#include "../../layout/ltcg/result_open_00423370/frame_timer.cpp"
#include "../../layout/ltcg/result_open_00423370/path_decode_xor_00417010.cpp"
#include "../../layout/ltcg/result_open_00423370/score_bookkeeping.cpp"
#include "../../layout/ltcg/result_open_00423370/animation_manager_queue_resource_0043dc90.cpp"
#include "../../layout/ltcg/result_open_00423370/animation_object_configure_from_resource_0043e5a0.cpp"
#include "../../layout/ltcg/result_open_00423370/recovery_mark_text_and_dispatcher_004479d0.cpp"
#include "../../layout/ltcg/result_open_00423370/ascii_manager_create_retail_0043c8b0.cpp"
#include "../../layout/ltcg/result_open_00423370/fun_0043c970_0043c970.cpp"
#include "../../layout/ltcg/result_open_00423370/runtime_selector_0043c970_scheduler_create.cpp"
#include "../../layout/ltcg/result_open_00423370/scheduler_tasks.cpp"

// 0x00415AE0 - the scheduler trampoline: the task loop holds the front
// runtime in ECX and the callback hands it to the update as its single stack
// argument while preserving the register.
#pragma code_seg(".text$00415ae0_fn")
struct FrontHudRuntime;
__declspec(noinline) int __stdcall FrontHudUpdate_00414900(FrontHudRuntime* front);
extern "C" __declspec(noinline) int __fastcall FrontHudCallback_00415ae0(void* state) {
    return FrontHudUpdate_00414900((FrontHudRuntime*)state);
}
#pragma code_seg()

// 0x00448D00 in the out-record form the walker calls.
#pragma code_seg(".text$00448d00_at")
int* __stdcall DispatcherCreateAt(
        AnimationResource_00449870* resource, int* out, int script_index, int render_bucket) {
    Entity* object = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = render_bucket;
    object->flags_35C = flags | 0x40000000;
    resource->InitializeObject(object, script_index);
    *out = reinterpret_cast<DispatcherPrimaryLists*>(data_00491c10)->RegisterPrimaryBack(object).value;
    return out;
}
#pragma code_seg()

// The game counters around 0x00474C68 are address-taken elsewhere in the
// program, so stores through pointers force their reloads.
#pragma code_seg(".text$02entry")
extern "C" void* __stdcall FrontScriptTickEscape(int which) {
    switch (which) {
    case 0: return &data_00474c68;
    case 1: return &data_00474c6c;
    case 2: return &data_00474c74;
    case 3: return &data_00474c7c;
    case 4: return &data_00474c70;
    case 5: return &data_00474c4c;
    case 6: return &data_00474c48;
    default: return &data_00474c84;
    }
}
#pragma code_seg()

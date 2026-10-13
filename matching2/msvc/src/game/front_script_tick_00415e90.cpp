// 0x00415E90 - the stage-front script walker, recovered as
// ResultDispatcher_00415e90 (see the dispatcher contract header). This
// translation unit compiles the walker as the selected region and carries the
// complete helper graph the native /LTCG link needs for its private register
// edges: the dispatcher handle/animation helpers, the frame timers, the sound
// queue, the text VM, the screen-effect factory and the result overlay, plus
// the 0x00415AE0 scheduler trampoline that forwards the front runtime into
// the 0x00414900 update.

#include "../../layout/ltcg/front_hud_pair/result_dispatcher.cpp"
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

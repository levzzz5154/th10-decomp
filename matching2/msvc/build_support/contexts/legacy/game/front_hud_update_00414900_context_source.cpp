// Compiler context only for the 0x00414900 promotion cluster: the same helper
// graph as build_support/contexts/legacy/game/front_script_tick.cpp (which the
// 0x00415E90 cluster owns), with the 0x00415AE0 scheduler trampoline under a
// C++ mangled name. LINK decorates a C /ENTRY name with a leading underscore,
// so an extern "C" __fastcall entry cannot be named directly; the body is
// unchanged.

#include "../../../layout/ltcg/front_hud_pair/result_dispatcher.cpp"
#include "../../../../src/game/pause/result_menu_open.cpp"
#include "../../../layout/ltcg/result_open/dispatcher_handle_helpers.cpp"
#include "../../../layout/ltcg/result_open/dispatcher_animation_helpers.cpp"
#include "../../../layout/ltcg/result_open/dispatcher_input_mode.cpp"
#include "../../../layout/ltcg/result_open/frame_timer.cpp"
#include "../../../layout/ltcg/result_open/path_decode_xor.cpp"
#include "../../../layout/ltcg/result_open/score_bookkeeping.cpp"
#include "../../../layout/ltcg/result_open/animation_manager_queue_resource.cpp"
#include "../../../layout/ltcg/result_open/animation_object_configure_from_resource.cpp"
#include "../../../layout/ltcg/result_open/recovery_mark_text_and_dispatcher.cpp"
#include "../../../layout/ltcg/result_open/ascii_manager_create_retail.cpp"
#include "../../../layout/ltcg/result_open/fun.cpp"
#include "../../../layout/ltcg/result_open/runtime_selector_0043c970_scheduler_create.cpp"
#include "../../../layout/ltcg/result_open/scheduler_tasks.cpp"

// 0x00415AE0 - the scheduler trampoline: the task loop holds the front
// runtime in ECX and the callback hands it to the update as its single stack
// argument while preserving the register.
#pragma code_seg(".text$00415ae0_fn")
struct FrontUpdateView;
__declspec(noinline) int __stdcall FrontHudUpdate(FrontUpdateView* front);
namespace front_hud_context {
__declspec(noinline) int __fastcall Callback(void* state) {
    return FrontHudUpdate((FrontUpdateView*)state);
}
}
#pragma code_seg()

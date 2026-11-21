// Compiler context only; never selected as recovered game code.
// The packed-command dispatcher model at 0x00415E90 compiles with its real
// callee graph so the native /LTCG link derives the conventions retail has;
// the stage-front tick 0x00414900 (compiled beside it) is the link entry.
#include "../../../src/game/front/front_script_tick_unit.cpp"
#include "../../../src/game/pause/result_menu_open.cpp"
#include "result_open/allocate.cpp"
#include "result_open/descriptor.cpp"
#include "result_open/entity_init.cpp"
#include "result_open/find.cpp"
#include "result_open/music.cpp"
#include "result_open/registrar.cpp"
#include "result_open/secondary_back.cpp"
#include "result_open/dispatcher_handle_helpers.cpp"
#include "result_open/dispatcher_animation_helpers.cpp"
#include "result_open/dispatcher_input_mode.cpp"

// 0x004492F0 in the parameter order the walker calls it with.
#pragma code_seg(".text$004492f0_at")
void __stdcall SetAnimationPosition(
        AnimationLookupContext* context, AnimationScriptId id, const DispatcherVec3* position) {
    DispatcherPositionObject* object = reinterpret_cast<DispatcherPositionObject*>(
        AnimationManager_Find(context, id));
    if (object) {
        object->position = *position;
        if (!object->children_flagged)
            for (DispatcherPositionLink* child = object->children; child; child = child->next)
                child->object->position = *position;
    }
}
#pragma code_seg()
#include "result_open/frame_timer.cpp"
#include "result_open/path_decode_xor.cpp"
#include "result_open/animation_manager_queue_resource.cpp"
#include "result_open/animation_object_configure_from_resource.cpp"
#include "result_open/recovery_mark_text_and_dispatcher.cpp"
#include "result_open/ascii_manager_create_retail.cpp"
#include "result_open/fun.cpp"
#include "result_open/runtime_selector_0043c970_scheduler_create.cpp"
#include "result_open/scheduler_tasks.cpp"

// 0x00415AE0 - the scheduler trampoline: the task loop holds the front
// runtime in ECX and the callback hands it to the update as its single stack
// argument while preserving the register.
#pragma code_seg(".text$00415ae0_fn")
struct FrontUpdateView;
__declspec(noinline) int __stdcall FrontHudUpdate(FrontUpdateView* front);
extern "C" __declspec(noinline) int __fastcall FrontHudCallback(void* state) {
    return FrontHudUpdate((FrontUpdateView*)state);
}
#pragma code_seg()

// 0x00448D00 in the out-record form the walker calls.
#pragma code_seg(".text$00448d00_at")
int* __stdcall DispatcherCreateAt(
        AnimationBank* resource, int* out, int script_index, int render_bucket) {
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
    case 5: return &g_globals_faith;
    case 6: return &g_globals_power;
    default: return &g_stage_progress;
    }
}
#pragma code_seg()

// Compiler context only; never selected as recovered game code.
#include "../../src/game/ascii_manager_load_resources_00401110.cpp"

#pragma code_seg(".text$00_0thread")
#include "../../src/game/game_thread.cpp"
#pragma code_seg()
#pragma code_seg(".text$00_d_init")
#include "../../src/game/entity_initialize_00401de0.cpp"
#pragma code_seg()
#include "../../src/game/animation_object_configure_from_resource_0043e5a0.cpp"
#include "scheduler_register_anchors.cpp"
#include "../../src/platform/text_log.cpp"

extern "C" GameThread *__stdcall GameThread_Create_00401440();

#pragma code_seg(".text$90context")
int __stdcall GameThreadCreateContext_00401110(SchedulerTask* task, int count) {
    // Keeps the full registration anchors in the link.
    int result = Scheduler_RegisterPrimary(data_00491be4, task, count);
    while (count--)
        result += GameThread_Create_00401440() != 0;
    return result;
}
#pragma code_seg()

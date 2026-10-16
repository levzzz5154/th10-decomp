// Compiler context only; never selected as recovered game code.
#include "../../../src/game/ascii/create.cpp"

#pragma code_seg(".text$00_0thread")
#include "../../../src/game/ascii/construct.cpp"
#pragma code_seg()
#pragma code_seg(".text$00_d_init")
#include "../../contexts/legacy/game/entity_initialize.cpp"
#pragma code_seg()
#include "../../../src/core/sprtanim/animation_object_configure_from_resource.cpp"
#include "scheduler_register_anchors.cpp"
#include "../../../src/core/zunlib/text_log.cpp"

extern "C" GameThread *__stdcall AsciiManager_Create();

#pragma code_seg(".text$90context")
int __stdcall GameThreadCreateContext_00401110(SchedulerTask* task, int count) {
    // Keeps the full registration anchors in the link.
    int result = FuncCtrl_RegisterPrimary(g_func_ctrl, task, count);
    while (count--)
        result += AsciiManager_Create() != 0;
    return result;
}
#pragma code_seg()

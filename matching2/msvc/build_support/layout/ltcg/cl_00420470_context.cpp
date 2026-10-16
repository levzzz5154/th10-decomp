// Compiler context only; never selected as recovered game code.
#include "../../../src/game/mother/app_register_tasks.cpp"
#include "scheduler_register_anchors.cpp"

#pragma code_seg(".text$30context")
int __stdcall AppRegisterTasksContext_00420470(int count) {
    int result = 0;
    while (count--)
        result += App_RegisterTasks();
    return result;
}
#pragma code_seg()

// 0x00449A50 and 0x00449A70: construct a scheduler task with no tick routine
// or with the supplied routine. Both preserve the other flag bits and leave
// the callback context untouched. Native LTCG derives the EAX receiver and
// the routine constructor's ECX callback argument.
#include "th10/core/func_ctrl.hpp"

struct EmptyTask : SchedulerTask {
    __declspec(noinline) EmptyTask();
};
struct RoutineTask : SchedulerTask {
    __declspec(noinline) RoutineTask(TaskRoutine);
};

static inline void InitializeTaskLink(TaskLink& node, SchedulerTask* task) {
    node.task = task;
    node.next = 0;
    node.previous = 0;
}

#pragma code_seg(".text$01empty")
EmptyTask::EmptyTask() {
    on_tick = 0;
    on_register = 0;
    on_remove = 0;
    priority = 0;
    heap_owned = 0;
    InitializeTaskLink(link, this);
}

#pragma code_seg(".text$02routine")
RoutineTask::RoutineTask(TaskRoutine routine) {
    on_tick = routine;
    on_register = 0;
    on_remove = 0;
    priority = 0;
    heap_owned = 0;
    InitializeTaskLink(link, this);
}
#pragma code_seg()

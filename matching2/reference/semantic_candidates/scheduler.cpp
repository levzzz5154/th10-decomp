// Readable models removed from matching2/msvc/src/game/scheduler.cpp: they compiled but did
// not reproduce the retail bytes, so that file keeps the exact assembly.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(
    void* callback) {
    SchedulerTask* result = (SchedulerTask*)::operator new(0x24);
    volatile SchedulerTask* task = result;
    volatile unsigned int* flags =
        (volatile unsigned int*)((unsigned long)result + 4);

    if (result) {
        unsigned int initial_flags = *flags;
        task->on_tick = 0;
        task->on_register = 0;
        task->on_remove = 0;
        task->priority = 0;
        *flags = initial_flags & ~1u;
        task->link.task = result;
        task->link.next = 0;
        task->link.previous = 0;
        task->context = 0;
    } else {
        result = 0;
    }

    TaskRoutine callback_routine = reinterpret_cast<TaskRoutine>(callback);
    task->on_register = 0;
    task->on_remove = 0;
    unsigned int final_flags = *flags | 1u;
    task->on_tick = callback_routine;
    *flags = final_flags;
    return result;
}

#include "th10/game/effect_manager_destroy.hpp"

extern "C" void __stdcall EnterCriticalSection(void* critical_section);
extern "C" void __stdcall LeaveCriticalSection(void* critical_section);
extern "C" void _free(void* memory);

extern uint32_t DAT_00492274;   // scheduler critical section
extern uint8_t DAT_0049231c;    // scheduler reentrancy counter
extern uint32_t DAT_00491be4;   // scheduler device token
extern uint32_t* DAT_00477840;  // published effect manager instance

namespace {

// One guarded task release, matching the retail lock/counter bracket.
void ReleaseGuarded(void* task,
                    void (*release_task)(void* task, uint32_t token)) {
    if (task == 0) {
        return;
    }
    EnterCriticalSection(&DAT_00492274);
    ++DAT_0049231c;
    if (release_task != 0) {
        release_task(task, DAT_00491be4);
    }
    LeaveCriticalSection(&DAT_00492274);
    --DAT_0049231c;
}

}  // namespace

// 0x0042B570 - Tear down the effect manager. Retail releases the update
// task at +0x08 and the render task at +0x0C (each under the scheduler
// critical section), zeroes the published global at 0x00477840, and
// frees the buffer at +0x370, clearing the slot on both branches.
void EffectManager_ReleaseTasks(EffectManagerTasks* state,
                                void (*release_task)(void* task,
                                                     uint32_t token)) {
    ReleaseGuarded(state->update_task, release_task);
    ReleaseGuarded(state->render_task, release_task);
    DAT_00477840 = 0;
    if (state->buffer != 0) {
        _free(state->buffer);
    }
    state->buffer = 0;
}

// Complete 174-byte sequence update. The genuine outer player state body
// supplies the private EAX receiver naturally in this graph.
#include "runtime.hpp"
#include "movement_input.hpp"
#include "scheduler_store.cpp"

// True on the first update of a new frame.
static inline bool TimerChanged(const FrameTimer& stage_timer) {
    return stage_timer.current != stage_timer.previous;
}

#pragma code_seg(".text$b30sequence")
int PlayerState::UpdateSequence() {
    if (phase == 1) {
        if (stage_timer.current < 0) {
            if (!data_00474e5c.repeat)
                return 0;
            reinterpret_cast<PlayerSchedulerRecord*>(&stage_timer)->SetSchedulerValue(0);
        }
        if (TimerChanged(stage_timer))
            Dispatch(stage_timer.current);
        if (stage_timer.current >= 15) {
            if (data_00474e5c.repeat)
                stage_timer.Advance(-15.0f);
            else
                reinterpret_cast<PlayerSchedulerRecord*>(&stage_timer)->SetSchedulerValue(-1);
            return 0;
        }
        stage_timer.Tick();
        return 0;
    }
    pending_3504 = 0;
    pending_name_3508 = 0;
    return 0;
}
#pragma code_seg()

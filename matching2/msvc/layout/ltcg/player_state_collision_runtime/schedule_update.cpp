// The complete 174-byte shot cycle. The player state update supplies the
// private EAX receiver naturally in this graph. data_00474e5c.repeat is the
// fire button.
#include "runtime.hpp"
#include "scheduler_store.cpp"
#include "movement_input.hpp"
// True on the first update of a new frame.
static inline bool TimerChanged(const FrameTimer& timer) {
    return timer.current != timer.previous;
}

#pragma code_seg(".text$f004281d0F")
int Player::UpdateShooting() {
    if (state == PLAYER_ALIVE) {
        if (shot_timer.current < 0) {
            if (!data_00474e5c.repeat)
                return 0;
            reinterpret_cast<PlayerSchedulerRecord*>(&shot_timer)->SetSchedulerValue(0);
        }
        if (TimerChanged(shot_timer))
            FireShots(shot_timer.current);
        if (shot_timer.current >= 15) {
            if (data_00474e5c.repeat)
                shot_timer.Advance(-15.0f);
            else
                reinterpret_cast<PlayerSchedulerRecord*>(&shot_timer)->SetSchedulerValue(-1);
            return 0;
        }
        shot_timer.Tick();
        return 0;
    }
    homing_target = 0;
    has_homing_target = 0;
    return 0;
}
#pragma code_seg()

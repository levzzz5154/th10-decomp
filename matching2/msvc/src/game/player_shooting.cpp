// 0x00428160 and 0x004281D0: the player's shot cycle. While the player is
// alive and the fire button is held, a 15-frame timer runs and each frame
// fires the shots of the current power level that are due on it.
//
// Two source shapes are load-bearing for the retail bytes: the fire button is
// a bitfield (that keeps the constant 1 in EBX), and the frame-changed test is
// an inline helper (so the fired frame is read again from the timer).
#include "../../layout/ltcg/player_state_collision_runtime/runtime.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/player_state.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/movement_input.hpp"
extern "C" {
extern unsigned short data_00474c48;
__declspec(noinline) int __stdcall Player_FireShot(
    Player* player, ShotDefinition* shot, int frame);
}

// The complete 105-byte shot walker. Its only native caller is
// UpdateShooting; LTCG derives retail's EDI receiver and EBX frame.
#pragma code_seg(".text$f00428160F")
int Player::FireShots(int frame) {
    int level = data_00474c48 / 20;  // whole units of power
    if (level >= 5) level = 4;
    if (focused) level += 5;
    for (ShotDefinition* shot = shot_type->lists[level].shots; shot->period >= 0; ++shot) {
        if (frame % shot->period == shot->phase)
            Player_FireShot(this, shot, frame);
    }
    return 0;
}

// True on the first update of a new frame.
static inline bool TimerChanged(const FrameTimer& timer) {
    return timer.current != timer.previous;
}

#pragma code_seg(".text$f004281d0F")
int Player::UpdateShooting() {
    if (state == PLAYER_ALIVE) {
        if (shot_timer.current < 0) {
            if (!g_input.repeat)
                return 0;
            reinterpret_cast<PlayerSchedulerRecord*>(&shot_timer)->SetSchedulerValue(0);
        }
        if (TimerChanged(shot_timer))
            FireShots(shot_timer.current);
        if (shot_timer.current >= 15) {
            if (g_input.repeat)
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

// Copies of the sound queue and gauge timer bodies an enemy's death calls, so
// that this link gives them the registers the retail callers load.
#include "th10/game/score.hpp"
#include "th10/platform/sound_queue.hpp"

extern "C" const float data_00470b20;
extern "C" short g_sound_priority[];
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;
extern float g_score_default_speed;

#pragma code_seg(".text$099p_pan")
void SoundQueue::QueuePan(int sound_id, float pan) {
    int priority = g_sound_priority[sound_id * 4];
    int request = int(pan * data_00470b20);
    int slot;
    for (slot = 0; slot < 12; ++slot) {
        if (sound_ids[slot] < 0)
            break;
        if (sound_ids[slot] == sound_id) {
            int count = counts[slot];
            if (count < 128) {
                requests[slot][count] = request;
                ++counts[slot];
            }
            return;
        }
    }
    if (slot < 12) {
        sound_ids[slot] = sound_id;
        priorities[sound_id] = priority;
        requests[slot][0] = request;
        ++counts[slot];
    }
}

#pragma code_seg(".text$079n_advance")
void FrameTimer::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        elapsed += delta;
    } else {
        elapsed += delta * *speed;
    }
    current = int(elapsed);
}

#pragma code_seg(".text$079m_gauge")
void ScoreState::AdvanceGaugeTimer(int frames) {
    if (gauge_timer.current < 130) {
        FrameTimer& timer = gauge_timer;
        timer.Advance(float(frames));
        if (gauge_timer.current > 130) {
            if ((timer.flags & 1) == 0) {
                timer.current = 0;
                timer.previous = -999999;
                timer.elapsed = 0.0f;
                timer.speed = &g_score_default_speed;
                timer.flags |= 1;
            }
            timer.current = 130;
            timer.elapsed = 130.0f;
            timer.previous = 129;
        }
    }
}
#pragma code_seg()

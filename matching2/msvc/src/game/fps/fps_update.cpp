#include "th10/source_views/fps_update_7bb61f_0.hpp"
int FPS::Update() {
    double now = FrameTimer_GetDelta();
    if (now < time_last)
        time_last = now;                 // the clock went backwards: resync
    double delta = now - time_last;
    if (delta >= 0.5) {
        time_last = delta + time_last;
        __declspec(align(8)) float rate = (float)((double)frame_count / delta);
        fps = rate;
        if (rate > 65.0f) {
            if (++frame_events == 2) {
                data_00492530 = data_00492528 = data_00492538 = data_00492540 =
                    FrameTimer_GetDelta();
            } else if (frame_events == 4) {
                data_00492508 = 0;       // give up on the performance counter
                data_00492530 = data_00492528 = data_00492538 = data_00492540 =
                    FrameTimer_GetDelta();
                frame_events = 0;
            }
        } else {
            frame_events = 0;
        }
        if (g_game != 0) {
            if ((g_game->field_58 & 0x14) == 0) {
                budget = budget + 60.0;
                if (fps > 57.0f)
                    measured = measured + 60.0;
                else
                    measured = fps + measured;
            }
            g_game->field_58 &= ~0x80u;
        }
        frame_count = 0;
        return 1;
    }
    return 1;
}

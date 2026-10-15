// 0x0042B6F0: raise every active score popup and retire it after 60 frames.
#include "th10/game/smoll_score_view.hpp"

extern "C" float g_game_speed;
extern "C" float data_00470b0c;
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;

__forceinline void SmollScoreTimer::Tick() {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        current++;
        elapsed += 1.0f;
    } else {
        float sum = elapsed;
        sum += *speed;
        elapsed = sum;
        current = int(sum);
    }
}

#pragma code_seg(".text$01drops")
int SmollScoreView::UpdatePopups() {
    for (int index = 0; index < 0x2D3; index++) {
        SmollScorePopup* popup = &popups[index];
        if (!popup->active) continue;
        popup->position -= data_00470b0c * g_game_speed;
        popup->timer.Tick();
        if (popup->timer.current > 60) popup->active = 0;
    }
    return 1;
}
#pragma code_seg()

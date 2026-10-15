#include "types.hpp"
#pragma code_seg(".text$00scheduler")
void LaserScheduler::Set(int frame) {
    if (!(flags&1u)) {
        current=0;previous=-999999;elapsed=0.0f;speed=&g_game_speed;flags|=1u;
    }
    current=frame;previous=frame-1;elapsed=static_cast<float>(frame);
}
#pragma code_seg()

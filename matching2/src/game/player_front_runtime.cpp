#include "th10/game/player_front_runtime.hpp"
#include <algorithm>
namespace th10::player_front {
namespace {

// The clamp retail applies to the hundredths accumulators: +-18400 across
// (the playfield is 368 wide, centred), 3200..43200 down.
const int kMinX = -18400;
const int kMaxX = 18400;
const int kMinY = 3200;
const int kMaxY = 43200;

int Clamp(int value, int low, int high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

}  // namespace

// 0x004250B0 - one frame of player motion (the player object arrives in EDI).
//
// The direction code, the speed pick and the clamp are retail's; the axis
// assignment follows retail's own key word, in which 0x10 is up and 0x20 is
// down (both vertical) while 0x40/0x80 are left/right.
void UpdatePlayer(Player& p, std::uint32_t in, bool enabled, int shot_index,
                  const PlayerSpeeds& speeds, const PlayerEdges& e) {
    // Direction code, tested in retail's order: the four diagonals first.
    if ((in & 0x50) == 0x50) p.direction = 5;        // up + left
    else if ((in & 0x60) == 0x60) p.direction = 7;   // down + left
    else if ((in & 0x90) == 0x90) p.direction = 6;   // up + right
    else if ((in & 0xA0) == 0xA0) p.direction = 8;   // down + right
    else if (in & 0x20) p.direction = 2;             // down
    else if (in & 0x10) p.direction = 1;             // up
    else if (in & 0x40) p.direction = 3;             // left
    else if (!(in & 0x80)) p.direction = 0;
    else p.direction = 4;                            // right

    if (enabled) {
        p.slow = (in >> 2) & 1;
        // Retail only ages the focus counter for one shot type, the
        // character/weapon pair whose 3 * character + weapon is 5.
        if (shot_index == 5) {
            if (in & 4) p.slow_age = 0;
            else if (p.slow_age < 30) p.slow_age += 1;
        }
    } else {
        p.slow = 0;
        p.slow_age = 30;
    }

    const int straight = p.slow ? speeds.focus_straight : speeds.straight;
    const int diagonal = p.slow ? speeds.focus_diagonal : speeds.diagonal;
    int step_x = 0;
    int step_y = 0;
    switch (p.direction) {
    case 1: step_y = -straight; break;
    case 2: step_y = straight; break;
    case 3: step_x = -straight; break;
    case 4: step_x = straight; break;
    case 5: step_x = -diagonal; step_y = step_x; break;
    case 6: step_x = diagonal; step_y = -step_x; break;
    case 7: step_y = diagonal; step_x = -step_y; break;
    case 8: step_x = diagonal; step_y = step_x; break;
    default: break;
    }

    // The horizontal step drives the lean animation: 1 on starting to move
    // left, 3 on starting to move right, 2 and 4 on stopping either.
    if (e.direction_changed) {
        if (step_x < 0 && p.prev_vx >= 0) e.direction_changed(e.context, 1);
        else if (step_x > 0 && p.prev_vx <= 0) e.direction_changed(e.context, 3);
        else if (step_x == 0 && p.prev_vx < 0) e.direction_changed(e.context, 2);
        else if (step_x == 0 && p.prev_vx > 0) e.direction_changed(e.context, 4);
    }
    p.prev_vx = step_x;
    p.prev_vy = step_y;

    p.vx = static_cast<int>(static_cast<double>(step_x) * speeds.frame_scale);
    p.vy = static_cast<int>(static_cast<double>(step_y) * speeds.frame_scale);
    p.x = Clamp(p.x + p.vx, kMinX, kMaxX);
    p.y = Clamp(p.y + p.vy, kMinY, kMaxY);

    if (!p.slow && (p.vx || p.vy)) {
        for (int i = 31; i > 0; --i) p.trail[i] = p.trail[i - 1];
    }
    p.trail[0] = {p.x, p.y};
}
// Semantic reconstruction of retail 0x00413BC0.
void InitializeFront(Front&f,const FrontInput&i){f.update_task=f.draw_task=true;for(int n=0;n<9;++n)f.lives[n]=n<i.lives;int q=((i.counter%20)*100)/20;f.digits={i.counter/20+8,q/10+8,q%10+8};f.animations.clear();if(i.mode!=8){if(!i.special){f.animations.push_back(0);f.animations.push_back(1);}f.animations.push_back(0x71);}if(i.stage_one_clear)f.animations.push_back(0x4f);if(i.extra_overlay)f.animations.push_back(i.difficulty+0x66);f.animations.push_back(i.difficulty+0x6b);f.linked_a=f.animations.size()>1?f.animations[f.animations.size()-2]:0;f.linked_b=f.animations.back();}
}

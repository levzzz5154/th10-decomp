#include "th10/game/player_update_collision.hpp"
#include "th10/game/entity.hpp"

__declspec(noinline) void** __stdcall ItemAnimation_CreateOffset(
    void* resource, void** out, int index, const Vector3* position);

#pragma code_seg(".text$050activate")
int CollisionRecord::Activate() {
    if (state != 2 && state != 1) return 0;
    int outside = reinterpret_cast<const PlayfieldPoint*>(&position)->OutsideBounds(8.0f, 8.0f);
    animation_state = 1;
    state = 3;
    if (outside) {
        flags |= 8;
        return 1;
    }
    if (animation_index >= 0) {
        void* output;
        ItemAnimation_CreateOffset(g_bullet_manager->item_animation, &output,
            animation_index, reinterpret_cast<const Vector3*>(&position));
    }
    if (!(timer_flags & 1u)) {
        timer_current = 0;
        timer_previous = -999999;
        timer_elapsed = 0.0f;
        timer_speed = &g_game_speed;
        timer_flags |= 1u;
    }
    timer_current = 0;
    timer_elapsed = 0.0f;
    timer_previous = -1;
    return 1;
}
#pragma code_seg()

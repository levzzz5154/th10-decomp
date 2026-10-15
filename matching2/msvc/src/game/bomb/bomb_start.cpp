#include "th10/source_views/bomb_start_bf1de1_0.hpp"
#include "th10/source_views/bomb_start_bf1de1_1.hpp"
#include "th10/source_views/bomb_start_bf1de1_2.hpp"
int __stdcall Bomb_Start(Bomb* bomb) {
    if (bomb->active) return -1;
    bomb->active = 1;
    bomb->timer.Reset();
    bomb->radius = 32.0f;
    bomb->unknown_40 = 4.0f;
    bomb->position = g_player->position;
    int index;
    if ((!(g_card->flags & 1) ||
         g_card->animation_state < 0x5D ||
         g_card->animation_state > 0x60) &&
        g_card->animation_state != 0x6D)
        index = data_00474c68 ? 0x197 : 0x190;
    else
        index = 0x1B9;
    int handle;
    bomb->animation = *CreateScreenPositionedPrimary_00448db0(
        data_004776f0->resource, &handle, index, &bomb->position);
    g_sound_manager.QueuePan(0x26, bomb->position.x);
    int power = data_00474c48;
    g_front->SetPowerDigits(power / 20, (power % 20) * 100 / 20);
    PlayerInitializeGlobal* state = g_card;
    state->ClearExpiredFlags();
    data_00474c98 -= 0x80;
    if (data_00474c98 > 0x400) data_00474c98 = 0x400;
    else if (data_00474c98 < -0x400) data_00474c98 = -0x400;
    if ((state->flags & 1) && state->elapsed_frames >= 60) bomb->mode = 1;
    else bomb->mode = 0;
    return 0;
}

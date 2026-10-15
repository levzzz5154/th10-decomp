// 0x00427960: PlayerOption::FollowTrail, and 0x00427950, the option update
// callback that runs it and returns zero.
//
// The history copies go through FixedPoint's member-wise assignment; that
// ordinary inline body keeps the option in ESI.
#include "th10/game/player.hpp"

#pragma code_seg(".text$03worker")
void PlayerOption::FollowTrail() {
    Player* player = g_player;
    int focused = player->focused;
    target = player->position_history[index * 8 + 8];
    if (focused == 0) {
        unfocused_offset = FixedPoint(target.x - player->fixed_position.x, target.y - player->fixed_position.y);
    } else {
        player->position_history[index * 8 + 8] = FixedPoint(player->fixed_position.x + unfocused_offset.x,
                                                             player->fixed_position.y + unfocused_offset.y);
        float fraction = 0.125f;
        for (int point = index * 8 + 1; point <= index * 8 + 7; ++point) {
            player->position_history[point].x = int((player->position_history[index * 8 + 8].x -
                                                     player->position_history[index * 8].x) * fraction +
                                                    player->position_history[index * 8].x);
            player->position_history[point].y = int((player->position_history[index * 8 + 8].y -
                                                     player->position_history[index * 8].y) * fraction +
                                                    player->position_history[index * 8].y);
            fraction += 0.125f;
        }
    }
    target = player->fixed_position + unfocused_offset;
    was_focused = focused;
}
#pragma code_seg()
#pragma code_seg(".text$01callback")
__declspec(noinline) int __fastcall PlayerOption_FollowTrail(PlayerOption* option) {
    option->FollowTrail();
    return 0;
}
#pragma code_seg()

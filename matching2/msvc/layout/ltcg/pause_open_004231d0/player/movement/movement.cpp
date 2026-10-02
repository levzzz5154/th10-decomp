// Complete movement update at 0x004250B0. One actual receiver; its retail
// EDI home is derived by the real PlayerUpdate caller in the native graph.
#include "th10/game/pause_result_open_004231d0/player/movement/movement.hpp"

#pragma code_seg(".text$004250b0_fn")
int PlayerMovement_004250b0(MovementState* player) {
    int move_x = 0;
    int move_y = 0;
    unsigned char input = static_cast<unsigned char>(g_movement_input);
    if ((input & 0x50) == 0x50) player->direction = 5;
    else if ((input & 0x60) == 0x60) player->direction = 7;
    else if ((input & 0x90) == 0x90) player->direction = 6;
    else if ((input & 0xA0) == 0xA0) player->direction = 8;
    else if (input & 0x20) player->direction = 2;
    else if (input & 0x10) player->direction = 1;
    else if (input & 0x40) player->direction = 3;
    else if (input & 0x80) player->direction = 4;
    else player->direction = 0;

    if (g_movement_gate != 0 && g_movement_gate->playable != 0 &&
        player->playable_state >= 4) {
        player->slow = (g_movement_input >> 2) & 1;
        if (g_movement_character * 3 + g_movement_shot_type == 5) {
            if (g_movement_input & 4)
                player->slow_transition_age = 0;
            else if (player->slow_transition_age < 30)
                ++player->slow_transition_age;
        }
    } else {
        player->slow = 0;
        player->slow_transition_age = 30;
    }

    if (player->slow) {
        if (player->slow_animation.value == 0) {
            AnimationResource_00449870* resource = g_movement_resources->player_resource;
            Entity* object = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
            object->render_bucket = 9;
            object->flags_35C |= 0x40000000u;
            resource->InitializeObject(object, 0x160);
            player->slow_animation =
                reinterpret_cast<MovementPrimaryLists*>(data_00491c10)->RegisterPrimaryBack(object);
        }
        switch (player->direction) {
        case 1: move_y = -player->slow_speed; break;
        case 2: move_y = player->slow_speed; break;
        case 3: move_x = -player->slow_speed; break;
        case 4: move_x = player->slow_speed; break;
        case 5: move_x = move_y = -player->slow_diagonal_speed; break;
        case 6: move_x = player->slow_diagonal_speed; move_y = -move_x; break;
        case 7: move_y = player->slow_diagonal_speed; move_x = -move_y; break;
        case 8: move_x = move_y = player->slow_diagonal_speed; break;
        }
    } else {
        AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(data_00491c10);
        if (AnimationManager_Find_004491c0(context, player->slow_animation) != 0)
            MovementStopFrame_00449210(1, context, player->slow_animation);
        player->slow_animation.value = 0;
        switch (player->direction) {
        case 1: move_y = -player->normal_speed; break;
        case 2: move_y = player->normal_speed; break;
        case 3: move_x = -player->normal_speed; break;
        case 4: move_x = player->normal_speed; break;
        case 5: move_x = move_y = -player->normal_diagonal_speed; break;
        case 6: move_x = player->normal_diagonal_speed; move_y = -move_x; break;
        case 7: move_y = player->normal_diagonal_speed; move_x = -move_y; break;
        case 8: move_x = move_y = player->normal_diagonal_speed; break;
        }
    }

    if (move_x < 0 && player->previous_movement.x >= 0)
        MovementLoadScript_0043e710(player->resource, &player->animation, 1);
    if (move_x > 0 && player->previous_movement.x <= 0)
        MovementLoadScript_0043e710(player->resource, &player->animation, 3);
    if (move_x == 0) {
        if (player->previous_movement.x < 0)
            MovementLoadScript_0043e710(player->resource, &player->animation, 2);
        if (player->previous_movement.x > 0)
            MovementLoadScript_0043e710(player->resource, &player->animation, 4);
    }
    player->previous_movement.x = move_x;
    player->previous_movement.y = move_y;
    player->velocity.x = static_cast<int>(static_cast<float>(move_x) * data_00476f78);
    player->velocity.y = static_cast<int>(static_cast<float>(move_y) * data_00476f78);
    player->integer_position.x += player->velocity.x;
    player->integer_position.y += player->velocity.y;
    if (player->integer_position.x < -18400) player->integer_position.x = -18400;
    else if (player->integer_position.x > 18400) player->integer_position.x = 18400;
    if (player->integer_position.y < 3200) player->integer_position.y = 3200;
    else if (player->integer_position.y > 43200) player->integer_position.y = 43200;
    player->position.x = static_cast<float>(player->integer_position.x) * g_movement_position_scale;
    player->position.y = static_cast<float>(player->integer_position.y) * g_movement_position_scale;
    AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(data_00491c10);
    if (AnimationManager_Find_004491c0(context, player->slow_animation) == 0) {
        player->slow_animation.value = 0;
    } else {
        Vector3 position = { player->position.x + g_movement_render_x,
                             player->position.y + g_movement_render_y,
                             player->position.z };
        MovementSetPosition_004492f0(&position, context, player->slow_animation);
    }

    if (player->slow == 0 && (move_x != 0 || move_y != 0)) {
        int entry = 32;
        while (entry > player->trail_sections * 8) {
            player->trail[entry] = player->trail[player->trail_sections * 8];
            --entry;
        }
        while (entry > 0) {
            player->trail[entry] = player->trail[entry - 1];
            --entry;
        }
    }
    player->trail[0] = player->integer_position;

    for (int index = 0; index < 4; ++index) {
        MovementOrbit* orbit = &player->orbits[index];
        if (orbit->active != 0) {
            const MovementPoint* offset = player->slow ? &orbit->slow_offset : &orbit->normal_offset;
            orbit->desired.x = player->integer_position.x + offset->x;
            orbit->desired.y = player->integer_position.y + offset->y;
            if (orbit->update != 0)
                orbit->update(orbit);
            if (orbit->reset_position != 0) {
                orbit->reset_position = 0;
                orbit->current = orbit->desired;
            } else if (player->slow_transition_age >= 30) {
                int dx = (orbit->desired.x - orbit->current.x) * player->slow_transition_age / 100;
                int dy = (orbit->desired.y - orbit->current.y) * player->slow_transition_age / 100;
                if (dx != 0 || dy != 0) {
                    orbit->current.x += dx;
                    orbit->current.y += dy;
                } else {
                    orbit->current = orbit->desired;
                }
            }
            Vector3 position = {
                static_cast<float>(orbit->current.x) * g_movement_position_scale,
                static_cast<float>(orbit->current.y) * g_movement_position_scale, 0.0f };
            context = reinterpret_cast<AnimationLookupContext*>(data_00491c10);
            MovementSetTranslatedPosition_00449350(&position, context, orbit->first_animation);
            MovementSetTranslatedPosition_00449350(&position, context, orbit->second_animation);
        }
    }
    return 0;
}
#pragma code_seg()

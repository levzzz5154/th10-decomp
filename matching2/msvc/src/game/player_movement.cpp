// 0x004250B0: the player's per-frame movement: the held direction, focus and
// its marker animation, the lean scripts, the clamped position, the trail and
// the four option orbits.
#include "../../layout/ltcg/player_state_collision_runtime/runtime.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/item_spawn.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/animation_public_callers.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/movement.hpp"

#pragma code_seg(".text$f004250b0F")
int PlayerState::Move() {
    MovementState* player = reinterpret_cast<MovementState*>(this);
    volatile MovementInput& movement_input = data_00474e5c;
    long move_x = 0;
    long move_y = 0;
    unsigned char input = movement_input.bytes[0];
    if ((input & 0x50) == 0x50) player->direction = MovementUpLeft;
    else if ((input & 0x60) == 0x60) player->direction = MovementDownLeft;
    else if ((input & 0x90) == 0x90) player->direction = MovementUpRight;
    else if ((input & 0xA0) == 0xA0) player->direction = MovementDownRight;
    else if (input & 0x20) player->direction = MovementDown;
    else if (input & 0x10) player->direction = MovementUp;
    else if (input & 0x40) player->direction = MovementLeft;
    else if (input & 0x80) player->direction = MovementRight;
    else player->direction = MovementNone;

    if (data_00477704 != 0 && data_00477704->enabled != 0 &&
        player->auxiliary_timer.current >= 4) {
        player->slow = (movement_input.word >> 2) & 1;
        if (data_00474c40.character * 3 + data_00474c40.shot_type == 5) {
            if (movement_input.bytes[0] & 4)
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
            AnimationResource_00449870* resource = reinterpret_cast<AnimationResource_00449870*>(data_004776f0->item_animation);
            Entity* object = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
            object->render_bucket = 9;
            object->flags_35C |= 0x40000000u;
            resource->InitializeObject(object, 0x160);
            AnimationRef assigned = reinterpret_cast<AnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
            player->slow_animation = assigned;
        }
        switch (player->direction) {
        case MovementRight: move_x = player->slow_speed; break;
        case MovementLeft: move_x = -player->slow_speed; break;
        case MovementUp: move_y = -player->slow_speed; break;
        case MovementDown: move_y = player->slow_speed; break;
        case MovementUpLeft: move_y = move_x = -player->slow_diagonal_speed; break;
        case MovementDownLeft: move_y = player->slow_diagonal_speed; move_x = -move_y; break;
        case MovementUpRight: move_x = player->slow_diagonal_speed; move_y = -move_x; break;
        case MovementDownRight: move_y = move_x = player->slow_diagonal_speed; break;
        }
    } else {
        PickupAnimationLists* context = reinterpret_cast<PickupAnimationLists*>(data_00491c10);
        if (context->Find(player->slow_animation) != 0)
            MovementStopFrame_00449210(1, context, player->slow_animation);
        AnimationRef* handle = &player->slow_animation;
        handle->value = 0;
        switch (player->direction) {
        case MovementRight: move_x = player->normal_speed; break;
        case MovementLeft: move_x = -player->normal_speed; break;
        case MovementUp: move_y = -player->normal_speed; break;
        case MovementDown: move_y = player->normal_speed; break;
        case MovementUpLeft: move_y = move_x = -player->normal_diagonal_speed; break;
        case MovementDownLeft: move_y = player->normal_diagonal_speed; move_x = -move_y; break;
        case MovementUpRight: move_x = player->normal_diagonal_speed; move_y = -move_x; break;
        case MovementDownRight: move_y = move_x = player->normal_diagonal_speed; break;
        }
    }

    // Lean into a turn and straighten out of it.
    // Lean into a turn and straighten out of it.
    if (move_x < 0 && player->previous_movement.x >= 0) player->resource->LoadScript(&player->animation, 1);
    else if (move_x == 0 && player->previous_movement.x < 0) player->resource->LoadScript(&player->animation, 2);
    if (move_x > 0 && player->previous_movement.x <= 0) player->resource->LoadScript(&player->animation, 3);
    else if (move_x == 0 && player->previous_movement.x > 0) player->resource->LoadScript(&player->animation, 4);
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
    Vector3* world = &player->position;
    world->x = static_cast<float>(player->integer_position.x) * 0.01f;
    world->y = static_cast<float>(player->integer_position.y) * 0.01f;
    PickupAnimationLists* context = reinterpret_cast<PickupAnimationLists*>(data_00491c10);
    if (context->Find(player->slow_animation) == 0) {
        player->slow_animation = AnimationRef(0);
    } else {
        Vector3 position;
        position.x = player->position.x + 224.0f;
        position.z = player->position.z;
        position.y = player->position.y + 16.0f;
        MovementSetPosition_004492f0(&position, context, player->slow_animation);
    }

    if (player->slow == 0 && (move_y != 0 || move_x != 0)) {
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
            orbit->desired = *(player->slow ? &orbit->slow_offset : &orbit->normal_offset) + player->integer_position;
            if (orbit->update != 0)
                orbit->update(orbit);
            if (orbit->reset_position == 0) {
                if (player->slow_transition_age >= 30) {
                    MovementPoint delta = (orbit->desired - orbit->current) * player->slow_transition_age / 100;
                    if (delta != MovementPoint(0,0))
                        orbit->current += delta;
                    else
                        orbit->current = orbit->desired;
                }
            } else {
                orbit->reset_position = 0;
                orbit->current = orbit->desired;
            }
            Vector3 position = {
                static_cast<float>(orbit->current.x) * 0.01f,
                static_cast<float>(orbit->current.y) * 0.01f, 0.0f };
            context = reinterpret_cast<PickupAnimationLists*>(data_00491c10);
            MovementSetTranslatedPosition_00449350(context, &position, orbit->first_animation);
            MovementSetTranslatedPosition_00449350(context, &position, orbit->second_animation);
        }
    }
    return 0;
}
#pragma code_seg()

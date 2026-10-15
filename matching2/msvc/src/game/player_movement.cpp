// 0x004250B0: the player's per-frame movement: the held direction, focus and
// its marker animation, the lean scripts, the clamped position, the trail and
// the four option orbits.
#include "../../layout/ltcg/player_state_collision_runtime/runtime.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/item_spawn.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/animation_public_callers.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/movement.hpp"

// Start one of the sprite's lean scripts (1/2 into and out of a left turn,
// 3/4 for the right).
static __forceinline void Lean(Player* player, int script) {
    static_cast<AnimationResource_0043e710*>(player->animation_file)->LoadScript(&player->sprite, script);
}

// The player keeps animation handles as plain words; the animation calls take
// them as AnimationRef copies of the stored value.
static __forceinline AnimationRef& AsRef(unsigned int& handle) {
    return *reinterpret_cast<AnimationRef*>(&handle);
}

#pragma code_seg(".text$f004250b0F")
int Player::Move() {
    volatile MovementInput& movement_input = data_00474e5c;
    long move_x = 0;
    long move_y = 0;
    unsigned char input = movement_input.bytes[0];
    if ((input & 0x50) == 0x50) direction = PLAYER_DIRECTION_UP_LEFT;
    else if ((input & 0x60) == 0x60) direction = PLAYER_DIRECTION_DOWN_LEFT;
    else if ((input & 0x90) == 0x90) direction = PLAYER_DIRECTION_UP_RIGHT;
    else if ((input & 0xA0) == 0xA0) direction = PLAYER_DIRECTION_DOWN_RIGHT;
    else if (input & 0x20) direction = PLAYER_DIRECTION_DOWN;
    else if (input & 0x10) direction = PLAYER_DIRECTION_UP;
    else if (input & 0x40) direction = PLAYER_DIRECTION_LEFT;
    else if (input & 0x80) direction = PLAYER_DIRECTION_RIGHT;
    else direction = PLAYER_DIRECTION_NONE;

    if (data_00477704 != 0 && data_00477704->enabled != 0 &&
        focus_timer.current >= 4) {
        focused = (movement_input.word >> 2) & 1;
        if (data_00474c40.character * 3 + data_00474c40.shot_type == 5) {
            if (movement_input.bytes[0] & 4)
                focus_transition_age = 0;
            else if (focus_transition_age < 30)
                ++focus_transition_age;
        }
    } else {
        focused = 0;
        focus_transition_age = 30;
    }

    if (focused) {
        if (focus_marker == 0) {
            AnimationResource_00449870* marker_resource = reinterpret_cast<AnimationResource_00449870*>(data_004776f0->item_animation);
            Entity* object = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
            object->render_bucket = 9;
            object->flags_35C |= 0x40000000u;
            marker_resource->InitializeObject(object, 0x160);
            AnimationRef assigned = reinterpret_cast<AnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
            AsRef(focus_marker) = assigned;
        }
        switch (direction) {
        case PLAYER_DIRECTION_RIGHT: move_x = focused_speed; break;
        case PLAYER_DIRECTION_LEFT: move_x = -focused_speed; break;
        case PLAYER_DIRECTION_UP: move_y = -focused_speed; break;
        case PLAYER_DIRECTION_DOWN: move_y = focused_speed; break;
        case PLAYER_DIRECTION_UP_LEFT: move_y = move_x = -focused_diagonal_speed; break;
        case PLAYER_DIRECTION_DOWN_LEFT: move_y = focused_diagonal_speed; move_x = -move_y; break;
        case PLAYER_DIRECTION_UP_RIGHT: move_x = focused_diagonal_speed; move_y = -move_x; break;
        case PLAYER_DIRECTION_DOWN_RIGHT: move_y = move_x = focused_diagonal_speed; break;
        }
    } else {
        PickupAnimationLists* context = reinterpret_cast<PickupAnimationLists*>(data_00491c10);
        if (context->Find(AsRef(focus_marker)) != 0)
            Animation_SetStopFrame(1, context, AsRef(focus_marker));
        AnimationRef* marker = &AsRef(focus_marker);
        marker->value = 0;
        switch (direction) {
        case PLAYER_DIRECTION_RIGHT: move_x = speed; break;
        case PLAYER_DIRECTION_LEFT: move_x = -speed; break;
        case PLAYER_DIRECTION_UP: move_y = -speed; break;
        case PLAYER_DIRECTION_DOWN: move_y = speed; break;
        case PLAYER_DIRECTION_UP_LEFT: move_y = move_x = -diagonal_speed; break;
        case PLAYER_DIRECTION_DOWN_LEFT: move_y = diagonal_speed; move_x = -move_y; break;
        case PLAYER_DIRECTION_UP_RIGHT: move_x = diagonal_speed; move_y = -move_x; break;
        case PLAYER_DIRECTION_DOWN_RIGHT: move_y = move_x = diagonal_speed; break;
        }
    }

    // Lean into a turn and straighten out of it.
    if (move_x < 0 && previous_velocity.x >= 0) Lean(this, 1);
    else if (move_x == 0 && previous_velocity.x < 0) Lean(this, 2);
    if (move_x > 0 && previous_velocity.x <= 0) Lean(this, 3);
    else if (move_x == 0 && previous_velocity.x > 0) Lean(this, 4);
    previous_velocity.x = move_x;
    previous_velocity.y = move_y;
    velocity.x = static_cast<int>(static_cast<float>(move_x) * data_00476f78);
    velocity.y = static_cast<int>(static_cast<float>(move_y) * data_00476f78);
    fixed_position.x += velocity.x;
    fixed_position.y += velocity.y;
    if (fixed_position.x < -18400) fixed_position.x = -18400;
    else if (fixed_position.x > 18400) fixed_position.x = 18400;
    if (fixed_position.y < 3200) fixed_position.y = 3200;
    else if (fixed_position.y > 43200) fixed_position.y = 43200;
    Vector3* world = &position;
    world->x = static_cast<float>(fixed_position.x) * 0.01f;
    world->y = static_cast<float>(fixed_position.y) * 0.01f;
    PickupAnimationLists* context = reinterpret_cast<PickupAnimationLists*>(data_00491c10);
    if (context->Find(AsRef(focus_marker)) == 0) {
        AsRef(focus_marker) = AnimationRef(0);
    } else {
        Vector3 marker_position;
        marker_position.x = position.x + 224.0f;
        marker_position.z = position.z;
        marker_position.y = position.y + 16.0f;
        Animation_SetPosition(&marker_position, context, AsRef(focus_marker));
    }

    if (focused == 0 && (move_y != 0 || move_x != 0)) {
        int entry = 32;
        while (entry > option_count * 8) {
            position_history[entry] = position_history[option_count * 8];
            --entry;
        }
        while (entry > 0) {
            position_history[entry] = position_history[entry - 1];
            --entry;
        }
    }
    position_history[0] = fixed_position;

    for (int index = 0; index < 4; ++index) {
        PlayerOption* option = &options[index];
        if (option->active != 0) {
            option->target = fixed_position + *(focused ? &option->focused_offset : &option->unfocused_offset);
            if (option->update != 0)
                option->update(option);
            if (option->reset_position == 0) {
                if (focus_transition_age >= 30) {
                    FixedPoint delta = (option->target - option->position) * focus_transition_age / 100;
                    if (delta != FixedPoint(0,0))
                        option->position += delta;
                    else
                        option->position = option->target;
                }
            } else {
                option->reset_position = 0;
                option->position = option->target;
            }
            Vector3 option_position = {
                static_cast<float>(option->position.x) * 0.01f,
                static_cast<float>(option->position.y) * 0.01f, 0.0f };
            context = reinterpret_cast<PickupAnimationLists*>(data_00491c10);
            Animation_SetTranslatedPosition(context, &option_position, AsRef(option->animation));
            Animation_SetTranslatedPosition(context, &option_position, AsRef(option->second_animation));
        }
    }
    return 0;
}
#pragma code_seg()

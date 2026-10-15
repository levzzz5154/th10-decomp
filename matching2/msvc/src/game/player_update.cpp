// 0x00425730: the per-frame update of the player's state machine: respawn
// entry, the live state, death and its item fan, then the collision regions,
// timers and bounding boxes shared by every state.
#include "../../layout/ltcg/player_state_collision_runtime/runtime.hpp"
#include "../../layout/ltcg/player_state_collision_runtime/player_state.hpp"

// These are inline expansions of the real embedded timer operations.
static inline void ResetPlayerTimer(FrameTimer& timer, int frame) {
    if (!(timer.flags & 1)) {
        timer.current = 0;
        timer.previous = -999999;
        timer.elapsed = 0.0f;
        timer.speed = &g_score_default_speed;
        timer.flags |= 1;
    }
    timer.current = frame;
    timer.elapsed = float(frame);
    timer.previous = frame - 1;
}
// Inline expansions of the timer's Advance and Decrement.
template <class Timer>
static __forceinline void AdvancePlayerTimer(Timer* timer, float delta) {
    timer->previous = timer->current;
    if (*timer->speed > g_frame_timer_normal_lower && *timer->speed < g_frame_timer_normal_upper)
        timer->elapsed += delta;
    else
        timer->elapsed += *timer->speed * delta;
    timer->current = int(timer->elapsed);
}
template <class Timer>
static __forceinline void DecrementPlayerTimer(Timer* timer, int count) {
    AdvancePlayerTimer(timer, float(-count));
}
static __forceinline Vec3 operator-(const Vec3& a, const Vec3& b) {
    Vec3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r;
}
struct ScaledVec3 : Vec3 {
    ScaledVec3(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
};
static __forceinline ScaledVec3 operator*(const Vec3& a, float f) {
    return ScaledVec3(a.x * f, a.y * f, a.z * f);
}
static inline void ActivatePlayerCollisions(bool idle_only) {
    PlayerCollisionRecord* record = data_004776f0->records;
    for (int remaining = 2000; remaining; --remaining, ++record)
        if (record->state != 0 && record->state != 3 &&
                (!idle_only || record->countdown == 0))
            record->Activate();
}

#pragma code_seg(".text$f00425730F")
extern "C" __declspec(noinline) int __stdcall Player_Update(Player* player) {
    switch (player->state) {
    case PLAYER_RESPAWNING: {
        player->fixed_position.y = 48000 - player->state_timer.current * 8000 / 60;
        player->position.y = float(player->fixed_position.y) * 0.01f;
        PlayerOption* option = player->options;
        option[0].reset_position = 1;
        option[1].reset_position = 1;
        option[2].reset_position = 1;
        option[3].reset_position = 1;
        int history_index;
        for (history_index = 32; history_index > player->option_count * 8; --history_index)
            player->position_history[history_index] = player->position_history[player->option_count * 8];
        for (; history_index > 0; --history_index)
            player->position_history[history_index] = player->position_history[history_index - 1];
        FixedPoint* head = player->position_history;
        head->x = player->fixed_position.x;
        head->y = player->fixed_position.y;
        if (player->state_timer.current >= 30) {
            ActivatePlayerCollisions(true);
            for (Laser* laser = data_0047781c->first; laser;) {
                Laser* next = laser->next;
                if (laser->state != 1) laser->Retire(0);
                laser = next;
            }
        } else {
            float radius = float(player->state_timer.current) * (512.0f / 30.0f) + 64.0f;
            data_004776f0->Check(&player->death_position, radius, 0, 1);
            data_004776f0->Check(&player->death_position, radius * 0.25f, 0, 0);
            data_0047781c->Evaluate(&player->death_position, radius, 0);
        }
        if (player->state_timer.current < 60) break;
        player->state = PLAYER_ALIVE;
        ResetPlayerTimer(player->state_timer, 0);
        // The actual entry transition continues directly into the live state.
    }
    case PLAYER_ALIVE:
        if (data_0047770c && !data_0047770c->script && data_004776ec &&
                !data_004776ec->active && static_cast<short>(data_00474c40.power / 20) != 0 &&
                data_00474e5c.revive) {
            reinterpret_cast<PlayerSchedulerRecord*>(&player->invulnerability_timer)->SetSchedulerValue(270);
            Bomb_Start(data_004776ec);
            data_00474c40.power -= 20;
            Player_RefreshOptions(player);
            {
                int power = data_00474c40.power;
                reinterpret_cast<PowerDisplayOwner_004054b0*>(data_0047770c)->SetPowerDigits(power / 20, (power % 20) * 100 / 20);
            }
            data_00474c40.AddWithMinimum(3000);
        }
        if (player->state_timer.current < 30) {
            ActivatePlayerCollisions(true);
            for (Laser* laser = data_0047781c->first; laser;) {
                Laser* next = laser->next;
                if (laser->state != 1) laser->Retire(0);
                laser = next;
            }
        }
        player->Move();
        break;
    case PLAYER_HIT:
        if (player->state_timer.current >= 8) {
            Player_Die(player);
            // Once contact has been updated, state 4 shares the full death path.
        } else {
            if (data_004776ec && !data_004776ec->active &&
                    static_cast<short>(data_00474c40.power / 20) != 0 && data_00474e5c.revive) {
                reinterpret_cast<PlayerSchedulerRecord*>(&player->state_timer)->SetSchedulerValue(60);
                reinterpret_cast<PlayerSchedulerRecord*>(&player->invulnerability_timer)->SetSchedulerValue(200);
                Bomb_Start(data_004776ec);
                data_00474c40.power -= 20;
                Player_RefreshOptions(player);
                {
                int power = data_00474c40.power;
                reinterpret_cast<PowerDisplayOwner_004054b0*>(data_0047770c)->SetPowerDigits(power / 20, (power % 20) * 100 / 20);
            }
                player->state = PLAYER_ALIVE;
            }
            break;
        }
    case PLAYER_DYING:
        if (player->state_timer.current == 3) {
            data_00474c40.power -= 64;
            if (data_00474c40.power < 0) data_00474c40.power = 0;
            {
                int power = data_00474c40.power;
                reinterpret_cast<PowerDisplayOwner_004054b0*>(data_0047770c)->SetPowerDigits(power / 20, (power % 20) * 100 / 20);
            }
            Vec3 target = {0.0f, player->position.y - 224.0f, 0.0f};
            float angle = float(Player_AngleToPoint(player, &target));
            for (int fan_index = 0; fan_index < 7; ++fan_index) {
                float direction = (float(fan_index) * 0.11219974f + angle) - 0.39269909f;
                int kind = fan_index == 1 || fan_index == 3 || fan_index == 5 ? 4 : 1;
                data_00477818->Spawn(reinterpret_cast<const Vector3*>(&player->position), kind, 0xffffff, direction, 3.0f);
            }
            Player_RefreshOptions(player);
        }
        if (player->state_timer.current >= 30) {
            if (data_00474c40.lives < 0) {
                if (data_00477838->mode != 1) data_00477830->Open();
                else data_00491c28.Set(4);
            } else {
                player->state = PLAYER_RESPAWNING;
                g_score_default_speed = 1.0f;
                Player_AddDamageSource(0, player, &player->position, 0x42000000, 0x41800000, 30, 150);
                player->death_position = player->position;
                player->fixed_position.x = 0;
                player->fixed_position.y = 48000;
                player->position.x = 0.0f;
                player->position.y = 480.0f;
                reinterpret_cast<PlayerSchedulerRecord*>(&player->invulnerability_timer)->SetSchedulerValue(280);
                reinterpret_cast<PlayerSchedulerRecord*>(&player->state_timer)->SetSchedulerValue(0);
            }
        }
        break;
    case PLAYER_STATE_3:
        if (player->state_timer.current != 4 && player->state_timer.current == 15) {
            ActivatePlayerCollisions(false);
            data_0047781c->Reset(1);
        }
        break;
    }

    PlayerDamageSource* circle = player->damage_sources;
    PlayerDamageSource* table = circle;
    for (int region_index = 0; region_index < 32; ++circle, ++region_index) {
        PlayerDamageSource& region = table[region_index];
        if (region.flags & 1) {
            region.motion.Update();
            region.motion.Advance();
            circle->radius += region.radius_growth;
            region.angle += region.angle_step;
            DecrementPlayerTimer(&region.lifetime, 1);
            if (region.lifetime.current <= 0) region.flags &= ~1u;
        }
    }
    if (player->invulnerability_timer.current > 0) {
        DecrementPlayerTimer(&player->invulnerability_timer, 1);
        if (player->state_timer.current != player->state_timer.previous && player->state_timer.current % 3 == 0) {
            player->sprite.secondary_color = 0xff0000ff;
            player->sprite.flags_35C |= 0x8000;
        } else player->sprite.flags_35C &= ~0x8000u;
    } else player->sprite.flags_35C &= ~0x8000u;
    asm_FUN_0043ee30_0043ee30(&player->sprite);

    player->hitbox.min = player->position - player->hitbox_half_size;
    player->hitbox.max = player->position + player->hitbox_half_size;
    player->item_collect_box.min = player->position - player->item_box_size * 0.5f;
    player->item_collect_box.max = player->item_box_size * 0.5f + player->position;
    player->focused_item_attract_box.min = player->position - player->item_attract_half_size;
    player->focused_item_attract_box.max = player->position + player->item_attract_half_size;
    player->item_attract_box.min = player->position - player->item_box_size;
    player->item_attract_box.max = player->position + player->item_box_size;
    player->state_timer.TickInline();
    player->focus_timer.TickInline();

    if (!data_0047770c->script && data_00477704 && data_00477704->enabled &&
            player->state_timer.current % 60 == 0) {
        ++data_00474c40.field_58;
        if (data_00474c40.field_58 > 1024) data_00474c40.field_58 = 1024;
        else if (data_00474c40.field_58 < -1024) data_00474c40.field_58 = -1024;
    }
    if (!data_0047770c->script && data_00477704 && data_00477704->enabled)
        player->UpdateShooting();
    else {
        ResetPlayerTimer(player->shot_timer, -1);
        player->homing_target = 0;
        player->has_homing_target = 0;
    }
    Player_UpdateBullets(player);
    return 1;
}
#pragma code_seg()

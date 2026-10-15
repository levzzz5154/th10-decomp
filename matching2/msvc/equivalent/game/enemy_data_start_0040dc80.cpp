// 0x0040DC80..0x0040E5EB: one frame of an enemy. The enemy arrives on the
// stack.
//
// A draft, transcribed block by block from the retail instructions (see
// reference/recovery_notes/enemy_data_start_0040dc80_decode_2026_10_12.md).
// It is measured with `equivalence.py --layout` and is not registered as an
// equivalent recovery.
#include "enemy_data_start_0040dc80_context.hpp"

#pragma code_seg(".text$0040dc80_fn")
extern "C" __declspec(noinline) int __stdcall EnemyDataStart_0040dc80(EnemyTick_0040dc80* enemy) {
    if (enemy->flags & ENEMY_TICKED)
        return 0;
    enemy->flags |= ENEMY_TICKED;
    enemy->previous = enemy->final;

    // 0x0040DCA9: the heading and orbit interpolators feed the two motions.
    if (enemy->relative_heading.duration) {
        TrajectoryVec2 heading = enemy->relative_heading.Step();
        enemy->relative.angle = Angle_Normalize_0044bc70(heading.x);
        enemy->relative.speed = heading.y;
    }
    if (enemy->relative_orbit.duration) {
        TrajectoryVec2 orbit = enemy->relative_orbit.Step();
        enemy->relative.radius = orbit.x;
        enemy->relative.radius_step = orbit.y;
    }
    if (enemy->absolute_heading.duration) {
        TrajectoryVec2 heading = enemy->absolute_heading.Step();
        enemy->absolute.angle = Angle_Normalize_0044bc70(heading.x);
        enemy->absolute.speed = heading.y;
    }
    if (enemy->absolute_orbit.duration) {
        TrajectoryVec2 orbit = enemy->absolute_orbit.Step();
        enemy->absolute.radius = orbit.x;
        enemy->absolute.radius_step = orbit.y;
    }

    // 0x0040DD69: each motion follows its path when one runs, else its heading.
    if (enemy->relative_path.duration)
        enemy->relative.velocity = enemy->relative_path.Step() - enemy->relative.position;
    else
        enemy->relative.Update();
    if (enemy->absolute_path.duration)
        enemy->absolute.velocity = enemy->absolute_path.Step() - enemy->absolute.position;
    else
        enemy->absolute.Update();

    // 0x0040DE87: move both, and the drawn position by what they add up to.
    enemy->relative.Advance();
    if (enemy->flags & ENEMY_UNSCROLLED)
        enemy->absolute.position += data_00491e6c;
    enemy->absolute.Advance();
    *reinterpret_cast<Vec3*>(&enemy->final.velocity) =
        *reinterpret_cast<Vec3*>(&enemy->relative.position) + *reinterpret_cast<Vec3*>(&enemy->absolute.position)
        - *reinterpret_cast<Vec3*>(&enemy->final.position);
    enemy->final.Advance();

    // 0x0040DF13: keep a limited enemy inside its box.
    if (enemy->flags & ENEMY_LIMITED) {
        float reach = enemy->limit_size.x * 0.5f;
        float edge = enemy->limit_center.x - reach;
        if (edge > enemy->final.position.x) {
            enemy->final.position.x = edge;
        } else {
            edge = reach + enemy->limit_center.x;
            if (edge < enemy->final.position.x)
                enemy->final.position.x = edge;
        }
        reach = enemy->limit_size.y * 0.5f;
        edge = enemy->limit_center.y - reach;
        if (edge > enemy->final.position.y) {
            enemy->final.position.y = edge;
        } else {
            edge = reach + enemy->limit_center.y;
            if (edge < enemy->final.position.y)
                enemy->final.position.y = edge;
        }
        enemy->relative.position = enemy->final.position - enemy->absolute.position;
    }

    // 0x0040DFDA: an enemy that was seen and has left the field is removed.
    {
        float half_width = enemy->visible_size.x * 0.5f;
        float half_height;
        if (half_width + enemy->final.position.x < -192.0f
            || enemy->final.position.x - half_width > 192.0f
            || (half_height = enemy->visible_size.y * 0.5f,
                half_height + enemy->final.position.y < 0.0f)
            || enemy->final.position.y - half_height > 448.0f) {
            if ((enemy->flags & ENEMY_SEEN) && !(enemy->flags & ENEMY_KEEP_OFFSCREEN))
                return -1;
        } else {
            enemy->flags |= ENEMY_SEEN;
        }
    }

    // 0x0040E050: swap the animation while the stage covers the enemy.
    if (enemy->flags & ENEMY_SWAPS_SCRIPT) {
        if (g_bomb->Covered() && !(enemy->flags & ENEMY_SCRIPT_SWAPPED)) {
            enemy->animation_script = enemy->covered_script;
            enemy->animations[0].ChangeScript(enemy->covered_script);
            enemy->flags |= ENEMY_SCRIPT_SWAPPED | ENEMY_NO_HIT;
        } else if (!g_bomb->Covered() && (enemy->flags & ENEMY_SCRIPT_SWAPPED)) {
            enemy->animation_script = enemy->uncovered_script;
            enemy->animations[0].ChangeScript(enemy->uncovered_script);
            enemy->flags &= ~(ENEMY_SCRIPT_SWAPPED | ENEMY_NO_HIT);
        }
    }

    // 0x0040E0E9: the script.
    {
        float delta = *enemy->clock.speed;
        if (EclVm_TickChildren(reinterpret_cast<EclChildOwner*>(enemy->record), delta))
            return -1;
    }

    // 0x0040E107: damage from the player's shots.
    enemy->flags &= ~ENEMY_HIT;
    if (!(enemy->flags & (ENEMY_NO_HIT | ENEMY_INTANGIBLE))) {
        int damage = static_cast<Player_0040dc80*>(0)->Sweep(
            g_player, &enemy->final.position, &enemy->hit_size);
        if (g_player->shot_mode == 2 || g_player->shot_mode == 0)
            damage /= 5;
        if (damage != 0) {
            if ((data_004776f4->flags & 1) && (enemy->flags & ENEMY_BOSS)) {
                damage /= 5;
                if (damage <= 0)
                    damage = 1;
            }
            if (!(enemy->flags & ENEMY_NO_DAMAGE) && enemy->invulnerable_timer.current <= 0)
                enemy->health -= damage;
            // A spell slot that came due restarts the script at once.
            const char* entry = enemy->record->AdvanceSlots();
            if (entry) {
                enemy->record->ClearResourceList();
                enemy->record->ResetScript();
                BindName_00450700(entry, enemy->record);
                float delta = *enemy->clock.speed;
                if (EclVm_TickChildren(reinterpret_cast<EclChildOwner*>(enemy->record), delta))
                    return -1;
            }
            if (((enemy->health <= 0) & ~(enemy->flags >> 6)) & 1) {
                data_00474c40.AddScore(enemy->bonus);
                if (Enemy_ReleaseOnDeath_0040e5f0(enemy->record))
                    return 1;
            }
            enemy->flags |= ENEMY_HIT;
        }
        data_00474c50 = 1;
    }

    // 0x0040E275: a spell slot that came due without a hit.
    {
        const char* entry = enemy->record->AdvanceSlots();
        if (entry) {
            enemy->record->ClearResourceList();
            enemy->record->ResetScript();
            EnemyRecord_0040dc80* record = enemy->record;
            record->current->instruction = record->table->Resolve(entry);
            record->current->time = 0;
        }
    }

    // 0x0040E2BD: contact with the player.
    if (!(enemy->flags & (ENEMY_NO_CONTACT | ENEMY_INTANGIBLE)) && enemy->contact_timer.current <= 0)
        FieldContact_004266b0(&enemy->final.position, g_player, &enemy->contact_size);

    // 0x0040E2E4: the turning animations.
    if (enemy->flags & ENEMY_FACES) {
        int step = 0;
        int facing;
        if (enemy->final.velocity.x < -0.1f)
            facing = -1;
        else if (enemy->final.velocity.x > 0.1f)
            facing = 1;
        else
            facing = 0;
        if (enemy->facing != facing) {
            switch (enemy->facing) {
            case -1:
                step = facing != 0 ? 2 : 3;
                break;
            case 0:
                step = facing != -1 ? 2 : 1;
                break;
            case 1:
                step = facing != 0 ? 1 : 4;
                break;
            }
            enemy->facing = facing;
            enemy->animations[0].ChangeScript(enemy->animation_script + step);
        }
    }

    // 0x0040E379: the animations follow the enemy.
    if (!(enemy->flags & ENEMY_UNSCROLLED)) {
        for (int index = 0; index < 8; ++index)
            SetAnimationTranslatedPosition_00449350(
                data_00491c10, &enemy->final.position, enemy->animations[index]);
    } else {
        for (int index = 0; index < 8; ++index)
            Animation_SetPosition(
                data_00491c10, &enemy->final.position, enemy->animations[index]);
    }

    // 0x0040E3DB: offer the enemy to the player's homing shots.
    if (!(enemy->flags & (ENEMY_NO_HIT | ENEMY_INTANGIBLE))
        && !(enemy->flags & (ENEMY_UNSCROLLED | ENEMY_UNTARGETED))) {
        Player_0040dc80* player = g_player;
        if (player->target == 0
            || fabsf(player->target->data.final.position.x - player->x)
                   < fabsf(enemy->final.position.x - player->x)) {
            if (!player->target_chosen)
                player->target = enemy->record;
            player->target_chosen = 1;
        }
    }

    // 0x0040E43E: the hit flash and its sound.
    {
        Animation_0040dc80* animation = AnimationManager_Find_004491c0(data_00491c10, enemy->animations[0]);
        if (animation == 0)
            enemy->animations[0].id = 0;
        if (enemy->flash_frames == 0) {
            if (enemy->flags & ENEMY_HIT) {
                animation->color = 0xFF0000FF;
                animation->flags |= 0x8000;
                enemy->flash_frames = 4;
                unsigned int mode = 0;
                if ((enemy->flags & ENEMY_BOSS)
                    && (mode = data_004776f4->flags, !((mode & 1) && (mode & 8)))
                    && (((mode & 1) && enemy->record->data.spell_delta < 300)
                        || (!(mode & 1) && enemy->record->data.spell_delta < 900)))
                    data_00492590.QueuePan(0x23, enemy->final.position.x);
                else
                    data_00492590.QueuePan(0x13, enemy->final.position.x);
            }
        } else {
            animation->flags &= ~0x8000u;
            if (enemy->flags & ENEMY_BOSS)
                data_0047770c->boss_bar_flags &= ~0x8000u;
            --enemy->flash_frames;
        }
    }

    // 0x0040E53E: the timers.
    if (enemy->invulnerable_timer.current > 0)
        enemy->invulnerable_timer.Advance(-1.0f);
    if (enemy->contact_timer.current > 0)
        enemy->contact_timer.Advance(-1.0f);
    enemy->clock.TickInline();
    return 0;
}
#pragma code_seg()

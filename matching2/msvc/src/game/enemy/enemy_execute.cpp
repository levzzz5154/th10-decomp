// Equivalent recovery of the enemy ECL instruction handler at 0x0040E770. The
// default build compiles this into the executable once
// tools/matching/equivalence.py has checked that it differs from the exact
// bytes only as recorded in layout/equivalent/enemy_execute2.json. The
// assembly in src/game/enemy/ecl_vm.cpp supplies those exact bytes and `make EXACT=1`.
// This is the loosest of the equivalent recoveries: see the note the layout names.
#include "th10/runtime/game/enemy/enemy_execute.hpp"

#define IOP(n) Int(n)
#define FOP(n) Float(n)
#define IVAL(n, v) IntValue(n, v)
#define UNSET -999999.0

static __forceinline Float3 operator-(const Float3& a, const Float3& b) {
    return Float3(a.x - b.x, a.y - b.y, a.z - b.z);
}

static __forceinline float SquaredLength(float x, float y) { return x * x + y * y; }
static __forceinline float DistanceSquared(const Float3& a, const Float3& b) { return SquaredLength(a.x - b.x, a.y - b.y); }
__declspec(noinline) int __stdcall ShooterShoot(BulletManager* manager, Shooter* shooter);

int Enemy::Execute2() {
    AnmHandle h3[3];
    EclInstr* ins = (*(EclVm* const volatile*)&ecl->active)->instr;
    switch (ins->id) {
    case 0x109:
        if (g_enemy_ctrl->boss[0] != 0) break;
    case 0x100: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        if (!(flags & 0x40000)) {
            float x = position.x;
            spawn.position.x = x + FloatValue2(1, ins->f[n]);
            float y = position.y;
            spawn.position.y = y + FloatValue2(2, ins->f[n + 1]);
        } else {
            Float3 world;
            float x = position.x;
            world.x = x + FloatValue2(1, ins->f[n]);
            float y = position.y;
            world.y = y + FloatValue2(2, ins->f[n + 1]);
            world.z = position.z;
            g_application.SelectStage2(0);
            D3DXVec3Project2(&spawn.position, &world, g_projection_matrix, g_projection_view_matrix, g_projection_world_matrix, g_enemy_project_viewport);
            spawn.position.x -= 224.0f;
            spawn.position.z = 0.0f;
            spawn.position.y -= 16.0f;
        }
        spawn.life = IVAL(3, ins->i[n + 2]);
        spawn.score = IVAL(4, ins->i[n + 3]);
        spawn.item = IVAL(5, ins->i[n + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &ins->s[4]);
        return 0;
    }
    case 0x10a:
        if (g_enemy_ctrl->boss[0] != 0) break;
    case 0x101: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.position.x = FloatValue2(1, ins->f[n]);
        spawn.position.y = FloatValue2(2, ins->f[n + 1]);
        spawn.life = IVAL(3, ins->i[n + 2]);
        spawn.score = IVAL(4, ins->i[n + 3]);
        spawn.item = IVAL(5, ins->i[n + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &ins->s[4]);
        return 0;
    }
    case 0x10f:
        if (g_enemy_ctrl->boss[0] != 0) break;
    case 0x10e: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.position.x = FloatValue2(1, ins->f[n]) + g_camera_offset.x;
        spawn.position.y = FloatValue2(2, ins->f[n + 1]) + g_camera_offset.y;
        spawn.position.z = FloatValue2(3, ins->f[n + 2]);
        spawn.life = IVAL(4, ins->i[n + 3]);
        spawn.score = IVAL(5, ins->i[n + 4]);
        spawn.item = IVAL(6, ins->i[n + 5]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        spawn.flags |= 1;
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &ins->s[4]);
        return 0;
    }
    case 0x10b:
        if (g_enemy_ctrl->boss[0] != 0) break;
    case 0x104: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        float x = position.x;
        spawn.position.x = x + FloatValue2(1, ins->f[n]);
        float y = position.y;
        spawn.position.y = y + FloatValue2(2, ins->f[n + 1]);
        spawn.life = IVAL(3, ins->i[n + 2]);
        spawn.score = IVAL(4, ins->i[n + 3]);
        spawn.item = IVAL(5, ins->i[n + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        spawn.mirrored = 1;
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &ins->s[4]);
        return 0;
    }
    case 0x10c:
        if (g_enemy_ctrl->boss[0] != 0) break;
    case 0x105: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.position.x = FloatValue2(1, ins->f[n]);
        spawn.position.y = FloatValue2(2, ins->f[n + 1]);
        spawn.life = IVAL(3, ins->i[n + 2]);
        spawn.score = IVAL(4, ins->i[n + 3]);
        spawn.item = IVAL(5, ins->i[n + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        spawn.mirrored = 1;
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &ins->s[4]);
        return 0;
    }
    case 0x102:
        anm_file = IOP(0);
        return 0;
    case 0x103: {
        int slot = IOP(0);
        int script = IOP(1);
        anm[slot].Release2();
        if (script < 0) break;
        anm[slot] = *Anm_CreateFront(g_enemy_ctrl->anm[anm_file], &h3[0], IOP(1), 5);
        if (slot == 0) {
            anm_main_script = IOP(1);
            anm_main_file = anm_file;
        }
        AnmVm* vm = Anm_Resolve2(&anm[slot]);
        if (slot == 0) {
            hitbox_width = vm->sprite_width * vm->scale.y;
            hitbox_height = vm->sprite_height * vm->scale.x;
        }
        if (flags & 0x10) anm[slot].Show2();
        return 0;
    }
    case 0x107: {
        int file = IOP(0);
        AnmHandle handle;
        Anm_CreateFront(g_enemy_ctrl->anm[file], &handle, IOP(1), 6);
        AnmVm* vm = Anm_Resolve2(&handle);
        if (!(flags & 0x40000)) vm->offset = *OffsetPoint2(&position);
        else vm->offset = position;
        goto done2;
    }
    case 0x110: {
        int file = IOP(0);
        AnmHandle handle;
        Anm_CreateBack(g_enemy_ctrl->anm[file], &handle, IOP(1), 6);
        AnmVm* vm = Anm_Resolve2(&handle);
        if (!(flags & 0x40000)) vm->offset = *OffsetPoint2(&position);
        else vm->offset = position;
        goto done;
    }
    case 0x108: {
        int file = IOP(0);
        AnmHandle handle;
        Anm_CreateFront(g_enemy_ctrl->anm[file], &handle, IOP(1), 6);
        return 0;
    }
    case 0x111: {
        int file = IOP(0);
        AnmHandle handle;
        Anm_CreateFront(g_enemy_ctrl->anm[file], &handle, IOP(1), 6);
        AnmVm* vm = Anm_Resolve2(&handle);
        if (!(flags & 0x40000)) vm->offset = *OffsetPoint2(&position);
        else vm->offset = position;
        vm->rotation.z = FOP(2);
        vm->flags |= 4;
        return 0;
    }
    case 0x106: {
        int slot = IOP(0);
        int script = IOP(1);
        anm[slot].Release2();
        anm[slot] = *Anm_CreateFront(g_enemy_ctrl->anm[anm_file], &h3[2], script, 5);
        AnmVm* vm = Anm_Resolve2(&anm[slot]);
        if (slot == 0) {
            hitbox_width = vm->sprite_width * vm->scale.y;
            hitbox_height = vm->sprite_height * vm->scale.x;
        }
        if (flags & 0x10) anm[slot].Show2();
        if (slot == 0) {
            (volatile unsigned int&)flags |= 0x1000;
            anm_base_script = script;
            anm_main_script = script;
            anm_f8 = 0;
            anm_main_file = anm_file;
        }
        return 0;
    }
    case 0x10d: {
        int slot = IOP(0);
        anm[slot].Release2();
        anm[slot] = *Anm_CreateFront(g_enemy_ctrl->anm[anm_file], &h3[1], anm_base_script + 5, 5);
        AnmVm* vm = Anm_Resolve2(&anm[slot]);
        if (slot == 0) {
            hitbox_width = vm->sprite_width * vm->scale.y;
            hitbox_height = vm->sprite_height * vm->scale.x;
        }
        if (flags & 0x10) anm[slot].Show2();
        return 0;
    }
    case 0x118:
    case 0x11a: {
        EnemyMotion* motion = ins->id == 0x118 ? &absolute : &relative;
        float x = FOP(0);
        float y = FOP(1);
        if (x > UNSET) motion->position.x = x;
        if (y > UNSET) motion->position.y = y;
        motion->flags &= ~1u;
        position = relative.position + absolute.position;
        return 0;
    }
    case 0x128:
    case 0x129: {
        EnemyMotion* motion = ins->id == 0x128 ? &absolute : &relative;
        float x = FOP(0);
        float y = FOP(1);
        float z = FOP(2);
        motion->position.x += x;
        motion->position.y += y;
        motion->position.z += z;
        return 0;
    }
    case 0x119:
    case 0x11b: {
        EnemyMotion* motion = ins->id == 0x119 ? &absolute : &relative;
        Float3Interp* interp = ins->id == 0x119 ? &absolute_position_interp : &relative_position_interp;
        float x = FOP(2);
        float y = FOP(3);
        interp->end_time = IOP(0);
        interp->control_1 = g_zero_vector3f;
        interp->control_2 = g_zero_vector3f;
        interp->mode = IOP(1);
        interp->initial = motion->position;
        interp->goal = Float3(x > UNSET ? x : motion->position.x, y > UNSET ? y : motion->position.y, 0.0f);
        interp->Restart2();
        motion->flags &= ~1u;
        return 0;
    }
    case 0x11c:
    case 0x11e: {
        EnemyMotion* motion = ins->id == 0x11c ? &absolute : &relative;
        float px;
        float py;
        px = FOP(0);
        py = FOP(1);
        if (px > UNSET) {
            if (flags & 0x800) px = Angle_Normalize(1.5707964f - Angle_Normalize(px - 1.5707964f));
            Motion_SetAngle(motion, px);
        }
        if (py > UNSET) motion->speed = py;
        motion->flags &= ~1u;
        return 0;
    }
    case 0x11d:
    case 0x11f: {
        EnemyMotion* motion = ins->id == 0x11d ? &absolute : &relative;
        Float2Interp* interp = ins->id == 0x11d ? &absolute_direction_interp : &relative_direction_interp;
        float angle = FOP(2);
        float speed = FOP(3);
        interp->mode = IOP(1);
        Float2 goal;
        if (interp->mode != 7) {
            {
                float gx;
                gx = angle > UNSET ? ((flags & 0x800) ? Angle_Normalize(1.5707964f - Angle_Normalize(angle - 1.5707964f)) : angle) : motion->angle;
                goal.x = gx;
            }
            {
                float gy;
                gy = speed > UNSET ? speed : motion->speed;
                goal.y = gy;
            }
        } else {
            if (angle > UNSET) goal.x = angle;
            else goal.x = 0.0f;
            if (speed > UNSET) goal.y = speed;
            else goal.y = 0.0f;
        }
        Float2 initial(motion->angle, motion->speed);
        if (fabs(initial.x - goal.x) >= 3.1415927f) {
            if (initial.x < goal.x) initial.x += 6.2831855f;
            else goal.x += 6.2831855f;
        }
        interp->end_time = IOP(0);
        interp->control_1 = g_zero_vector22;
        interp->control_2 = g_zero_vector22;
        interp->initial = initial;
        interp->goal = goal;
        interp->Restart3();
        motion->flags &= ~1u;
        return 0;
    }
    case 0x120:
    case 0x122: {
        EnemyMotion* motion = ins->id == 0x120 ? &absolute : &relative;
        float angle = FOP(0);
        float speed = FOP(1);
        float radial = FOP(2);
        float angular = FOP(3);
        if (!(motion->flags & 1)) motion->origin = motion->position;
        if (angle > UNSET) Motion_SetAngle(motion, angle);
        if (speed > UNSET) motion->speed = speed;
        if (radial > UNSET) motion->radial_speed = radial;
        if (angular > UNSET) motion->angular_speed = angular;
        motion->flags |= 1;
        return 0;
    }
    case 0x121:
    case 0x123: {
        EnemyMotion* motion = ins->id == 0x121 ? &absolute : &relative;
        Float2Interp* direction = ins->id == 0x121 ? &absolute_direction_interp : &relative_direction_interp;
        Float2Interp* orbit = ins->id == 0x121 ? &absolute_orbit_interp : &relative_orbit_interp;
        float angle = FOP(2);
        float speed = FOP(3);
        float radial = FOP(4);
        float angular = FOP(5);
        Float2 goal(angle > UNSET ? angle : motion->angle, speed > UNSET ? speed : motion->speed);
        Float2 initial(motion->angle, motion->speed);
        Float2 orbit_goal(radial > UNSET ? radial : motion->radial_speed, angular > UNSET ? angular : motion->angular_speed);
        Float2 orbit_initial(motion->radial_speed, motion->angular_speed);
        int end_time = IOP(0);
        int mode = IOP(1);
        direction->end_time = end_time;
        direction->control_1 = g_zero_vector22;
        direction->control_2 = g_zero_vector22;
        direction->mode = mode;
        direction->initial = initial;
        direction->goal = goal;
        direction->Restart3();
        orbit->end_time = end_time;
        orbit->control_1 = g_zero_vector22;
        orbit->control_2 = g_zero_vector22;
        orbit->mode = mode;
        orbit->initial = orbit_initial;
        orbit->goal = orbit_goal;
        orbit->Restart3();
        motion->origin = motion->position;
        motion->flags |= 1;
        return 0;
    }
    case 0x12a:
    case 0x12b: {
        EnemyMotion* motion = ins->id == 0x12a ? &absolute : &relative;
        float x = FOP(0);
        float y = FOP(1);
        if (x > UNSET) motion->origin.x = x;
        if (y > UNSET) motion->origin.y = y;
    }
    case 0x126:
        absolute.position = g_enemy_ctrl->boss[0]->body.position;
        return 0;
    case 0x127:
        relative.position = g_enemy_ctrl->boss[0]->body.position;
        return 0;
    case 0x144:
        flags |= 0x200;
        bounds_x = FOP(0);
        bounds_y = FOP(1);
        bounds_width = FOP(2);
        bounds_height = FOP(3);
        return 0;
    case 0x145:
        flags &= ~0x200u;
        return 0;
    case 0x15a: {
        float range = FOP(0);
        shoot_range_squared = range * range;
        break;
    }
    case 0x124:
    case 0x125: {
        EnemyMotion* motion = ins->id == 0x124 ? &absolute : &relative;
        Float2Interp* interp = ins->id == 0x124 ? &absolute_direction_interp : &relative_direction_interp;
        float angle;
        if (bounds_x - bounds_width * 0.25f > position.x) {
            angle = g_effect_rng2.NextFloatSigned() * (3.1415927f / 3.0f);
        } else if (bounds_width * 0.25f + bounds_x < position.x) {
            angle = Angle_Normalize(g_effect_rng2.NextAngle() * 0.33333334f + 3.1415927f);
        } else if (position.x < g_player->position.x) {
            angle = g_effect_rng2.NextFloatSigned() * (3.1415927f / 2.0f);
        } else {
            angle = Angle_Normalize(g_effect_rng2.NextAngle() * 0.5f + 3.1415927f);
        }
        if (bounds_y - bounds_height * 0.25f > position.y) angle = fabs(angle);
        else if (bounds_height * 0.25f + bounds_y < position.y) angle = -fabs(angle);
        interp->mode = IOP(1);
        Float2 goal;
        if (interp->mode != 7) {
            goal.x = angle;
            goal.y = 0.0f;
        } else {
            goal.x = angle;
            goal.y = 0.0f;
        }
        Float2 initial;
        initial.x = angle;
        initial.y = FOP(2);
        interp->end_time = IOP(0);
        interp->control_1 = g_zero_vector22;
        interp->control_2 = g_zero_vector22;
        interp->initial = initial;
        interp->goal = goal;
        interp->Restart3();
        motion->flags &= ~1u;
        return 0;
    }
    case 0x15b:
        g_front->SetMarker(IOP(0), max_life, FOP(1), IOP(2));
        return 0;
    case 0x140:
        fb0 = FOP(0);
        fb4 = FOP(1);
        return 0;
    case 0x141:
        fb8 = FOP(0);
        fbc = FOP(1);
        return 0;
    case 0x142:
        flags |= IOP(0);
        if (flags & 0x10) {
            for (int i = 0; i < 10; ++i) anm[i].Show2();
        }
        return 0;
    case 0x143:
        flags &= ~IOP(0);
        if (!(flags & 0x10)) {
            for (int i = 0; i < 10; ++i) anm[i].Hide2();
        }
        return 0;
    case 0x146:
        memset(&drops.items[1], 0, 12 * sizeof(int));
        return 0;
    case 0x147: {
        int kind = IOP(0);
        if (flags & 0x8000) {
            if (kind == 1) kind = 10;
            else if (kind == 4) kind = 11;
        }
        drops.items[kind] = IOP(1);
        return 0;
    }
    case 0x148:
        SetSpread(FOP(0), FOP(1));
        return 0;
    case 0x149:
        Drops_Flush(&drops, &position);
        return 0;
    case 0x14a: {
        int kind = IOP(0);
        if (flags & 0x8000) {
            if (kind == 1) kind = 10;
            else if (kind == 4) kind = 11;
        }
        drops.items[0] = kind;
        return 0;
    }
    case 0x14b: {
        life = IOP(0);
        max_life = life;
        for (int i = 0; i < 4; ++i) {
            g_front->markers[i].ratio = 0.0f;
            g_front->markers[i].value = 0;
        }
        f13c8 = life;
        return 0;
    }
    case 0x14c: {
        int index = IOP(0);
        if (index < 0) {
            if (flags & 0x8000) g_enemy_ctrl->boss[boss_index] = 0;
            flags &= ~0x8000u;
        } else {
            flags |= 0x8000;
            g_enemy_ctrl->boss[index] = ecl;
            boss_index = index;
        }
        return 0;
    }
    case 0x14f:
        timer_141c.Set2(IOP(0));
        return 0;
    case 0x169:
        timer_1430.Set2(IOP(0));
        return 0;
    case 0x159:
        EnemyCtrl_SweepDeaths(g_enemy_ctrl);
        return 0;
    case 0x163:
        switch (g_difficulty) {
        case 0: *IntDest2(0) = IOP(1); goto done2;
        case 1: *IntDest2(0) = IOP(2); goto done2;
        case 2: *IntDest2(0) = IOP(3); goto done2;
        case 3:
        case 4: *IntDest2(0) = IOP(4); goto done2;
        }
        break;
    case 0x164:
        switch (g_difficulty) {
        case 0: *FloatDest(0) = FOP(1); goto done2;
        case 1: *FloatDest(0) = FOP(2); goto done2;
        case 2: *FloatDest(0) = FOP(3); goto done2;
        case 3: *FloatDest(0) = FOP(4); goto done2;
        case 4: *FloatDest(0) = FOP(4); goto done2;
        }
        break;
    case 0x190: {
        int index = IOP(0);
        memset(&shooters[index], 0, sizeof(Shooter));
        shooters[index].count_1 = 1;
        shooters[index].count_2 = 1;
        shooters[index].angle_1 = 0.0f;
        shooters[index].speed_1 = 2.0f;
        shooters[index].sound = 7;
        shooters[index].sound_2 = 0x18;
        shooters[index].flags = 0x203;
        shoot_offset[index].x = 0.0f;
        shoot_offset[index].y = 0.0f;
        return 0;
    }
    case 0x19b:
        shooters[IOP(0)] = shooters[IOP(1)];
        return 0;
    case 0x191: {
        int index = IOP(0);
        shooters[index].position = shoot_offset[index] + position;
        if (shoot_range_squared != 0.0f) {
            if (!(shoot_range_squared <= DistanceSquared(shooters[index].position, g_player->position))) break;
        }
        ShooterShoot(g_bullet_manager, &shooters[index]);
        return 0;
    }
    case 0x192: {
        int index = IOP(0);
        shooters[index].type = IOP(1);
        shooters[index].color = IOP(2);
        return 0;
    }
    case 0x193: {
        int index = IOP(0);
        shoot_offset[index].x = FOP(1);
        shoot_offset[index].y = FOP(2);
        return 0;
    }
    case 0x194: {
        int index = IOP(0);
        shooters[index].angle_1 = FOP(1);
        shooters[index].angle_2 = FOP(2);
        return 0;
    }
    case 0x195: {
        int index = IOP(0);
        shooters[index].speed_1 = FOP(1);
        shooters[index].speed_2 = FOP(2);
        return 0;
    }
    case 0x196: {
        int index = IOP(0);
        shooters[index].count_1 = IOP(1);
        shooters[index].count_2 = IOP(2);
        return 0;
    }
    case 0x1b3: {
        int index = IOP(0);
        float value;
        if (g_difficulty == 0) value = FOP(1);
        else if (g_difficulty == 1) value = FOP(2);
        else if (g_difficulty == 2) value = FOP(3);
        else value = FOP(4);
        shooters[index].speed_1 = value;
        if (g_difficulty == 0) value = FOP(5);
        else if (g_difficulty == 1) value = FOP(6);
        else if (g_difficulty == 2) value = FOP(7);
        else value = FOP(8);
        shooters[index].speed_2 = value;
        return 0;
    }
    case 0x1b4: {
        int index = IOP(0);
        int value;
        if (g_difficulty == 0) value = IOP(1);
        else if (g_difficulty == 1) value = IOP(2);
        else if (g_difficulty == 2) value = IOP(3);
        else value = IOP(4);
        shooters[index].count_1 = value;
        if (g_difficulty == 0) value = IOP(5);
        else if (g_difficulty == 1) value = IOP(6);
        else if (g_difficulty == 2) value = IOP(7);
        else value = IOP(8);
        shooters[index].count_2 = value;
        goto done;
    }
    case 0x1a7: {
        int index = IOP(0);
        if (g_rank >= 600) {
            shooters[index].speed_1 = FOP(9);
            shooters[index].speed_2 = FOP(10);
            return 0;
        }
        if (g_rank >= 200) {
            shooters[index].speed_1 = FOP(7);
            shooters[index].speed_2 = FOP(8);
            return 0;
        }
        if (g_rank >= -200) {
            shooters[index].speed_1 = FOP(5);
            shooters[index].speed_2 = FOP(6);
            return 0;
        }
        if (g_rank >= -600) {
            shooters[index].speed_1 = FOP(3);
            shooters[index].speed_2 = FOP(4);
        } else {
            shooters[index].speed_1 = FOP(1);
            shooters[index].speed_2 = FOP(2);
        }
        return 0;
    }
    case 0x1a6: {
        int index = IOP(0);
        if (g_rank >= 0x200) {
            shooters[index].speed_1 = FOP(5);
            shooters[index].speed_2 = FOP(6);
            goto done2;
        }
        if (g_rank >= -0x200) {
            shooters[index].speed_1 = FOP(3);
            shooters[index].speed_2 = FOP(4);
        } else {
            shooters[index].speed_1 = FOP(1);
            shooters[index].speed_2 = FOP(2);
        }
        return 0;
    }
    case 0x1a8: {
        int index = IOP(0);
        float low_1 = FOP(1);
        float low_2 = FOP(2);
        float high_1 = FOP(3);
        float high_2 = FOP(4);
        shooters[index].speed_1 = ((float)g_rank + 1024.0f) * (high_1 - low_1) / 2048.0f + low_1;
        shooters[index].speed_2 = ((float)g_rank + 1024.0f) * (high_2 - low_2) / 2048.0f + low_2;
        return 0;
    }
    case 0x1a9: {
        int index = IOP(0);
        if (g_rank >= 0x200) {
            shooters[index].count_1 = IOP(5);
            shooters[index].count_2 = IOP(6);
            goto done2;
        }
        if (g_rank >= -0x200) {
            shooters[index].count_1 = IOP(3);
            shooters[index].count_2 = IOP(4);
        } else {
            shooters[index].count_1 = IOP(1);
            shooters[index].count_2 = IOP(2);
        }
        goto done2;
    }
    case 0x1aa: {
        int index = IOP(0);
        if (g_rank >= 600) {
            shooters[index].count_1 = IOP(9);
            shooters[index].count_2 = IOP(10);
            goto done;
        }
        if (g_rank >= 200) {
            shooters[index].count_1 = IOP(7);
            shooters[index].count_2 = IOP(8);
            goto done;
        }
        if (g_rank >= -200) {
            shooters[index].count_1 = IOP(5);
            shooters[index].count_2 = IOP(6);
            goto done;
        }
        if (g_rank >= -600) {
            shooters[index].count_1 = IOP(3);
            shooters[index].count_2 = IOP(4);
        } else {
            shooters[index].count_1 = IOP(1);
            shooters[index].count_2 = IOP(2);
        }
        goto done;
    }
    case 0x1ab: {
        int index = IOP(0);
        int low_1 = IOP(1);
        int low_2 = IOP(2);
        int high_1 = IOP(3);
        int high_2 = IOP(4);
        shooters[index].count_1 = (high_1 - low_1) * (g_rank + 1024) / 2048 + low_1;
        shooters[index].count_2 = (high_2 - low_2) * (g_rank + 1024) / 2048 + low_2;
        goto done;
    }
    case 0x197: {
        int index = IOP(0);
        shooters[index].aim_mode = IOP(1);
        return 0;
    }
    case 0x198: {
        int index = IOP(0);
        shooters[index].sound = IOP(1);
        shooters[index].sound_2 = IOP(2);
        return 0;
    }
    case 0x199: {
        int index = IOP(0);
        int entry = IOP(1);
        shooters[index].ex[entry].f = IOP(2);
        shooters[index].ex[entry].e = IOP(3);
        shooters[index].ex[entry].c = IOP(4);
        shooters[index].ex[entry].d = IOP(5);
        shooters[index].ex[entry].a = FOP(6);
        shooters[index].ex[entry].b = FOP(7);
        return 0;
    }
    case 0x14d:
        timer_11c.Set2(0);
        return 0;
    case 0x14e:
        Enemy_BindSlot(ecl, IOP(0), IOP(1), IOP(2), &ins->s[0x10]);
        return 0;
    case 0x155:
        ecl->body.slots[IOP(0)].cursor = &ins->s[8];
        return 0;
    case 0x19a:
        g_bullet_manager->Sweep2(1);
        g_laser_manager->Cleanup2(1);
        return 0;
    case 0x150:
        g_sound_manager.QueuePan2(IOP(0), position.x);
        return 0;
    case 0x151:
        Screen_Create(0x31, 1, IOP(0), IOP(1), IOP(2), 0);
        return 0;
    case 0x152:
        g_front->CreateScoreDisplay2(IOP(0));
        g_bullet_manager->Sweep2(0);
        g_laser_manager->Cleanup2(0);
        EnemyCtrl_SweepDeaths(g_enemy_ctrl);
        return 0;
    case 0x153:
        if (g_front->message != 0 && g_front->message->f78 == 0) return -1;
        break;
    case 0x154:
        if (g_enemy_ctrl->boss[0] != 0) return -1;
        break;
    case 0x156:
    case 0x15c:
    case 0x165:
    case 0x166:
    case 0x167: {
        char name[128];
        const char* text = &ins->s[0x10];
        unsigned char key = 0x77;
        unsigned char step = 7;
        int length = ins->i[3];
        for (int i = 0; i < length; ++i) {
            name[i] = text[i] ^ key;
            key += step;
            step += 0x10;
        }
        int id = IOP(0);
        switch (ins->id) {
        case 0x165: id += g_difficulty; break;
        case 0x166: id += g_difficulty - 1; break;
        case 0x167: id += g_difficulty - 2; break;
        }
        Card_Start(g_card, id, name, IOP(1), IOP(2));
        return 0;
    }
    case 0x157:
        g_card->End2();
        return 0;
    case 0x16a:
        g_card->flags |= 8;
        return 0;
    case 0x16b:
        g_card->StopAnimation();
        return 0;
    case 0x16c:
        f19 = IOP(0);
        return 0;
    case 0x19c:
    case 0x1af: {
        LineLaserParams params;
        memset(&params, 0, sizeof(params));
        if (ins->id == 0x1af) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = IOP(0);
        params.color = IOP(1);
        params.f0c = FOP(2);
        params.f20 = FOP(3);
        params.f14 = FOP(4);
        params.f10 = FOP(5);
        params.f18 = FOP(6);
        params.f1c = FOP(7);
        params.flags |= 1;
        g_laser_manager->Spawn2(&params, 0);
        return 0;
    }
    case 0x19d:
    case 0x1b0: {
        BeamLaserParams params;
        int* result = IntDest2(0);
        if (ins->id == 0x1b0) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = IOP(1);
        params.color = IOP(2);
        params.f18 = FOP(3);
        params.f24 = FOP(4);
        params.f20 = FOP(5);
        params.f30 = IOP(6);
        params.f34 = IOP(7);
        params.f38 = IOP(8);
        params.f3c = IOP(9);
        params.f28 = FOP(10);
        params.flags = IOP(11) | 2;
        int id = g_laser_manager->Spawn2(&params, 1);
        if (result) *result = id;
        return 0;
    }
    case 0x1ac:
    case 0x1b1: {
        LineLaserParams params;
        memset(&params, 0, sizeof(params));
        if (ins->id == 0x1b1) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = IntArg(0);
        params.color = IntArg(1);
        params.f0c = FOP(2);
        params.f20 = FOP(3);
        params.f14 = FOP(4);
        params.f10 = FOP(5);
        params.f18 = FOP(6);
        params.f1c = FOP(7);
        params.flags &= ~1u;
        g_laser_manager->Spawn2(&params, 0);
        return 0;
    }
    case 0x1ad:
    case 0x1b2: {
        BeamLaserParams params((BeamLaserParams::Raw()));
        params.Construct2();
        int* result = IntDest2(0);
        if (ins->id == 0x1b2) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = IntArg(1);
        params.color = IntArg(2);
        params.f18 = FOP(3);
        params.f24 = FOP(4);
        params.f20 = FOP(5);
        params.f30 = IntArg(6);
        params.f34 = IntArg(7);
        params.f38 = IntArg(8);
        params.f3c = IntArg(9);
        params.f28 = FOP(10);
        params.flags = IntArg(11) & ~2u;
        int id = g_laser_manager->Spawn2(&params, 1);
        if (result) *result = id;
        return 0;
    }
    case 0x19e: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f24 = Float3(FOP(1), FOP(2), 0.0f);
        return 0;
    }
    case 0x19f: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->SetVector(Float3(FOP(1), FOP(2), 0.0f));
        return 0;
    }
    case 0x1a0: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f48 = FOP(1);
        return 0;
    }
    case 0x1a1: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f44 = FOP(1);
        return 0;
    }
    case 0x1a2: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f3c = FOP(1);
        return 0;
    }
    case 0x1a3: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f440 = FOP(1);
        return 0;
    }
    case 0x1a4: {
        float radius = FOP(0);
        g_bullet_manager->Check2(&position, radius, 1, 0);
        g_laser_manager->Evaluate2(&position, radius, 1);
        return 0;
    }
    case 0x1a5: {
        float radius = FOP(0);
        g_bullet_manager->Check2(&position, radius, 0, 0);
        g_laser_manager->Evaluate2(&position, radius, 0);
        return 0;
    }
    case 0x158:
        Score_SetMode2(&g_globals, IntArg(0));
        return 0;
    case 0x15d:
        if (g_rank >= 0x200) *FloatDest(0) = FOP(2);
        else if (g_rank > -0x200) *FloatDest(0) = FOP(0);
        else *FloatDest(0) = FOP(0);
        goto done;
    case 0x15e:
        if (g_rank >= 600) {
            *FloatDest(0) = FOP(4);
            goto done2;
        }
        if (g_rank >= 200) {
            *FloatDest(0) = FOP(3);
            goto done2;
        }
        if (g_rank >= -200) {
            *FloatDest(0) = FOP(2);
            goto done2;
        }
        if (g_rank >= -400) {
            *FloatDest(0) = FOP(1);
        } else {
            *FloatDest(0) = FOP(0);
        }
        goto done2;
    case 0x15f: {
        float low = FOP(1);
        float high = FOP(2);
        *FloatDest(0) = ((float)g_rank + 1024.0f) * (high - low) / 2048.0f + low;
        return 0;
    }
    case 0x160:
        if (g_rank >= 0x200) *IntDest2(0) = IntArg(2);
        else if (g_rank > -0x200) *IntDest2(0) = IntArg(0);
        else *IntDest2(0) = IntArg(0);
        goto done;
    case 0x161:
        if (g_rank >= 600) {
            *IntDest2(0) = IntArg(4);
            goto done;
        }
        if (g_rank >= 200) {
            *IntDest2(0) = IntArg(3);
            goto done;
        }
        if (g_rank >= -200) {
            *IntDest2(0) = IntArg(2);
            goto done;
        }
        if (g_rank >= -400) {
            *IntDest2(0) = IntArg(1);
        } else {
            *IntDest2(0) = IntArg(0);
        }
        goto done;
    case 0x162: {
        int low = IntArg(1);
        int high = IntArg(2);
        *IntDest2(0) = (high - low) * (g_rank + 1024) / 2048 + low;
        return 0;
    }
    case 0x168:
        g_front->f9e90 = IntArg(0);
        return 0;
    case 0x16d:
        g_laser_manager->MarkEligible2();
        return 0;
    case 0x16e:
        f20 = IntArg(0);
        f1448 = IntArg(1);
        f21 = 0;
        f144c = anm_base_script;
        return 0;
    case 0x16f:
        g_game_speed = FOP(0);
        return 0;
    case 0x1ae: {
        const Float3* p1 = &g_player->position;
        float t1 = FOP(1);
        const Float3* p2 = &g_player->position;
        *FloatDest(0) = (float)atan2(p2->y - FOP(2), p1->x - t1);
        goto done2;
    }
    case 0x170: {
        float wait;
        if (g_difficulty == 0) wait = (float)IntArg(0);
        else if (g_difficulty == 1) wait = (float)IntArg(1);
        else if (g_difficulty == 2) wait = (float)IntArg(2);
        else wait = (float)IntArg(3);
        ecl->active->time -= wait;
        break;
    }
    }
// done2 keeps its own (first) label: the tail merge picks its survivor per label,
// which is what puts 0x1ab's copy where retail keeps it.
done2:
done:
    return 0;
}

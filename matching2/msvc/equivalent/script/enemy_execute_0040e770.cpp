// Equivalent recovery of the enemy ECL instruction handler at 0x0040E770. The
// default build compiles this into the executable once
// tools/matching/equivalence.py has checked that it differs from the exact
// bytes only as recorded in layout/equivalent/enemy_execute_0040e770.json. The
// assembly in src/game/enemy/ecl_vm.cpp supplies those exact bytes and `make EXACT=1`.
// This is the loosest of the equivalent recoveries: see the note the layout names.
#include "enemy_execute_0040e770.hpp"

#define IOP(n) Int(n)
#define FOP(n) Float(n)
#define IVAL(n, v) IntValue(n, v)
#define UNSET -999999.0

static __forceinline Float3 operator-(const Float3& a, const Float3& b) {
    return Float3(a.x - b.x, a.y - b.y, a.z - b.z);
}

static __forceinline float SquaredLength(float x, float y) { return x * x + y * y; }
static __forceinline float DistanceSquared(const Float3& a, const Float3& b) { return SquaredLength(a.x - b.x, a.y - b.y); }

int Enemy::Execute_0040e770() {
    EclInstr* ins = (*(EclVm* const volatile*)&ecl->active)->instr;
    switch (ins->id) {
    case 0x109:
        if (data_00477704->boss[0] != 0) break;
    case 0x100: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        if (!(flags & 0x40000)) {
            float x = position.x;
            spawn.position.x = x + FloatValue_00412aa0(1, ins->f[n]);
            float y = position.y;
            spawn.position.y = y + FloatValue_00412aa0(2, ins->f[n + 1]);
        } else {
            Float3 world;
            float x = position.x;
            world.x = x + FloatValue_00412aa0(1, ins->f[n]);
            float y = position.y;
            world.y = y + FloatValue_00412aa0(2, ins->f[n + 1]);
            world.z = position.z;
            data_00491c28.SelectStage_00401d20(0);
            D3DXVec3Project_0045218e(&spawn.position, &world, data_00491e48, data_00491e08, data_00491dc8, data_00474df0);
            spawn.position.x -= 224.0f;
            spawn.position.z = 0.0f;
            spawn.position.y -= 16.0f;
        }
        spawn.life = IVAL(3, ins->i[n + 2]);
        spawn.score = IVAL(4, ins->i[n + 3]);
        spawn.item = IVAL(5, ins->i[n + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        EnemyManager_Spawn_0040cfb0(&spawn, data_00477704, &ins->s[4]);
        return 0;
    }
    case 0x10a:
        if (data_00477704->boss[0] != 0) break;
    case 0x101: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.position.x = FloatValue_00412aa0(1, ins->f[n]);
        spawn.position.y = FloatValue_00412aa0(2, ins->f[n + 1]);
        spawn.life = IVAL(3, ins->i[n + 2]);
        spawn.score = IVAL(4, ins->i[n + 3]);
        spawn.item = IVAL(5, ins->i[n + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        EnemyManager_Spawn_0040cfb0(&spawn, data_00477704, &ins->s[4]);
        return 0;
    }
    case 0x10f:
        if (data_00477704->boss[0] != 0) break;
    case 0x10e: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.position.x = FloatValue_00412aa0(1, ins->f[n]) + g_camera_offset_00491d7c.x;
        spawn.position.y = FloatValue_00412aa0(2, ins->f[n + 1]) + g_camera_offset_00491d7c.y;
        spawn.position.z = FloatValue_00412aa0(3, ins->f[n + 2]);
        spawn.life = IVAL(4, ins->i[n + 3]);
        spawn.score = IVAL(5, ins->i[n + 4]);
        spawn.item = IVAL(6, ins->i[n + 5]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        spawn.flags |= 1;
        EnemyManager_Spawn_0040cfb0(&spawn, data_00477704, &ins->s[4]);
        return 0;
    }
    case 0x10b:
        if (data_00477704->boss[0] != 0) break;
    case 0x104: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        float x = position.x;
        spawn.position.x = x + FloatValue_00412aa0(1, ins->f[n]);
        float y = position.y;
        spawn.position.y = y + FloatValue_00412aa0(2, ins->f[n + 1]);
        spawn.life = IVAL(3, ins->i[n + 2]);
        spawn.score = IVAL(4, ins->i[n + 3]);
        spawn.item = IVAL(5, ins->i[n + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        spawn.mirrored = 1;
        EnemyManager_Spawn_0040cfb0(&spawn, data_00477704, &ins->s[4]);
        return 0;
    }
    case 0x10c:
        if (data_00477704->boss[0] != 0) break;
    case 0x105: {
        int n = (ins->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.position.x = FloatValue_00412aa0(1, ins->f[n]);
        spawn.position.y = FloatValue_00412aa0(2, ins->f[n + 1]);
        spawn.life = IVAL(3, ins->i[n + 2]);
        spawn.score = IVAL(4, ins->i[n + 3]);
        spawn.item = IVAL(5, ins->i[n + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        spawn.mirrored = 1;
        EnemyManager_Spawn_0040cfb0(&spawn, data_00477704, &ins->s[4]);
        return 0;
    }
    case 0x102:
        anm_file = IOP(0);
        return 0;
    case 0x103: {
        int slot = IOP(0);
        int script = IOP(1);
        anm[slot].Release_00449630();
        if (script < 0) break;
        AnmHandle handle;
        anm[slot] = *Anm_CreateFront_00448e30(data_00477704->anm[anm_file], &handle, IOP(1), 5);
        if (slot == 0) {
            anm_main_script = IOP(1);
            anm_main_file = anm_file;
        }
        AnmVm* vm = Anm_Resolve_00449450(&anm[slot]);
        if (slot == 0) {
            hitbox_width = vm->sprite_width * vm->scale.y;
            hitbox_height = vm->sprite_height * vm->scale.x;
        }
        if (flags & 0x10) anm[slot].Show_004495e0();
        return 0;
    }
    case 0x107: {
        int file = IOP(0);
        AnmHandle handle;
        Anm_CreateFront_00448e30(data_00477704->anm[file], &handle, IOP(1), 6);
        AnmVm* vm = Anm_Resolve_00449450(&handle);
        if (!(flags & 0x40000)) vm->offset = *OffsetPoint_00418810(&position);
        else vm->offset = position;
        return 0;
    }
    case 0x110: {
        int file = IOP(0);
        AnmHandle handle;
        Anm_CreateBack_00448d00(data_00477704->anm[file], &handle, IOP(1), 6);
        AnmVm* vm = Anm_Resolve_00449450(&handle);
        if (!(flags & 0x40000)) vm->offset = *OffsetPoint_00418810(&position);
        else vm->offset = position;
        return 0;
    }
    case 0x108: {
        int file = IOP(0);
        AnmHandle handle;
        Anm_CreateFront_00448e30(data_00477704->anm[file], &handle, IOP(1), 6);
        return 0;
    }
    case 0x111: {
        int file = IOP(0);
        AnmHandle handle;
        Anm_CreateFront_00448e30(data_00477704->anm[file], &handle, IOP(1), 6);
        AnmVm* vm = Anm_Resolve_00449450(&handle);
        if (!(flags & 0x40000)) vm->offset = *OffsetPoint_00418810(&position);
        else vm->offset = position;
        vm->rotation.z = FOP(2);
        vm->flags |= 4;
        return 0;
    }
    case 0x106: {
        int slot = IOP(0);
        int script = IOP(1);
        anm[slot].Release_00449630();
        AnmHandle handle;
        anm[slot] = *Anm_CreateFront_00448e30(data_00477704->anm[anm_file], &handle, script, 5);
        AnmVm* vm = Anm_Resolve_00449450(&anm[slot]);
        if (slot == 0) {
            hitbox_width = vm->sprite_width * vm->scale.y;
            hitbox_height = vm->sprite_height * vm->scale.x;
        }
        if (flags & 0x10) anm[slot].Show_004495e0();
        if (slot == 0) {
            flags |= 0x1000;
            anm_base_script = script;
            anm_main_script = script;
            anm_main_file = anm_file;
            anm_f8 = 0;
        }
        return 0;
    }
    case 0x10d: {
        int slot = IOP(0);
        anm[slot].Release_00449630();
        AnmHandle handle;
        anm[slot] = *Anm_CreateFront_00448e30(data_00477704->anm[anm_file], &handle, anm_base_script + 5, 5);
        AnmVm* vm = Anm_Resolve_00449450(&anm[slot]);
        if (slot == 0) {
            hitbox_width = vm->sprite_width * vm->scale.y;
            hitbox_height = vm->sprite_height * vm->scale.x;
        }
        if (flags & 0x10) anm[slot].Show_004495e0();
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
        interp->control_1 = g_zero_vector_00491c14;
        interp->control_2 = g_zero_vector_00491c14;
        interp->mode = IOP(1);
        interp->initial = motion->position;
        interp->goal = Float3(x > UNSET ? x : motion->position.x, y > UNSET ? y : motion->position.y, 0.0f);
        interp->Restart_004050d0();
        motion->flags &= ~1u;
        return 0;
    }
    case 0x11c:
    case 0x11e: {
        EnemyMotion* motion = ins->id == 0x11c ? &absolute : &relative;
        Float2 polar;
        polar.x = FOP(0);
        polar.y = FOP(1);
        if (polar.x > UNSET) {
            if (flags & 0x800) polar.x = Angle_Normalize(1.5707964f - Angle_Normalize(polar.x - 1.5707964f));
            Motion_SetAngle_00413170(motion, polar.x);
        }
        if (polar.y > UNSET) motion->speed = polar.y;
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
            goal.x = angle > UNSET ? ((flags & 0x800) ? Angle_Normalize(1.5707964f - Angle_Normalize(angle - 1.5707964f)) : angle) : motion->angle;
            goal.y = speed > UNSET ? speed : motion->speed;
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
        interp->control_1 = g_zero_vector2_00491c20;
        interp->control_2 = g_zero_vector2_00491c20;
        interp->initial = initial;
        interp->goal = goal;
        interp->Restart_00412db0();
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
        if (angle > UNSET) Motion_SetAngle_00413170(motion, angle);
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
        direction->control_1 = g_zero_vector2_00491c20;
        direction->control_2 = g_zero_vector2_00491c20;
        direction->mode = mode;
        direction->initial = initial;
        direction->goal = goal;
        direction->Restart_00412db0();
        orbit->end_time = end_time;
        orbit->control_1 = g_zero_vector2_00491c20;
        orbit->control_2 = g_zero_vector2_00491c20;
        orbit->mode = mode;
        orbit->initial = orbit_initial;
        orbit->goal = orbit_goal;
        orbit->Restart_00412db0();
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
        absolute.position = data_00477704->boss[0]->body.position;
        return 0;
    case 0x127:
        relative.position = data_00477704->boss[0]->body.position;
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
            angle = g_effect_rng_004918b0.NextFloatSigned_0044bb90() * (3.1415927f / 3.0f);
        } else if (bounds_width * 0.25f + bounds_x < position.x) {
            angle = Angle_Normalize(g_effect_rng_004918b0.NextAngle() * 0.33333334f + 3.1415927f);
        } else if (position.x < g_player->position.x) {
            angle = g_effect_rng_004918b0.NextFloatSigned_0044bb90() * (3.1415927f / 2.0f);
        } else {
            angle = Angle_Normalize(g_effect_rng_004918b0.NextAngle() * 0.5f + 3.1415927f);
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
        interp->control_1 = g_zero_vector2_00491c20;
        interp->control_2 = g_zero_vector2_00491c20;
        interp->initial = initial;
        interp->goal = goal;
        interp->Restart_00412db0();
        motion->flags &= ~1u;
        return 0;
    }
    case 0x15b:
        data_0047770c->SetMarker(IOP(0), max_life, FOP(1), IOP(2));
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
            for (int i = 0; i < 10; ++i) anm[i].Show_004495e0();
        }
        return 0;
    case 0x143:
        flags &= ~IOP(0);
        if (!(flags & 0x10)) {
            for (int i = 0; i < 10; ++i) anm[i].Hide_00449590();
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
        Drops_Flush_0040c9a0(&position, &drops);
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
            data_0047770c->markers[i].ratio = 0.0f;
            data_0047770c->markers[i].value = 0;
        }
        f13c8 = life;
        return 0;
    }
    case 0x14c: {
        int index = IOP(0);
        if (index < 0) {
            if (flags & 0x8000) data_00477704->boss[boss_index] = 0;
            flags &= ~0x8000u;
        } else {
            flags |= 0x8000;
            data_00477704->boss[index] = ecl;
            boss_index = index;
        }
        return 0;
    }
    case 0x14f:
        timer_141c.Set_00405410(IOP(0));
        return 0;
    case 0x169:
        timer_1430.Set_00405410(IOP(0));
        return 0;
    case 0x159:
        EnemyManager_SweepDeaths_0040e6a0(data_00477704);
        return 0;
    case 0x163:
        switch (g_difficulty_00474c74) {
        case 0: *IntDest_00412a10(0) = IOP(1); return 0;
        case 1: *IntDest_00412a10(0) = IOP(2); return 0;
        case 2: *IntDest_00412a10(0) = IOP(3); return 0;
        case 3:
        case 4: *IntDest_00412a10(0) = IOP(4); return 0;
        }
        break;
    case 0x164:
        switch (g_difficulty_00474c74) {
        case 0: *FloatDest(0) = FOP(1); return 0;
        case 1: *FloatDest(0) = FOP(2); return 0;
        case 2: *FloatDest(0) = FOP(3); return 0;
        case 3: *FloatDest(0) = FOP(4); return 0;
        case 4: *FloatDest(0) = FOP(4); return 0;
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
        shooters[index].Shoot_004073e0(data_004776f0);
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
        if (g_difficulty_00474c74 == 0) value = FOP(1);
        else if (g_difficulty_00474c74 == 1) value = FOP(2);
        else if (g_difficulty_00474c74 == 2) value = FOP(3);
        else value = FOP(4);
        shooters[index].speed_1 = value;
        if (g_difficulty_00474c74 == 0) value = FOP(5);
        else if (g_difficulty_00474c74 == 1) value = FOP(6);
        else if (g_difficulty_00474c74 == 2) value = FOP(7);
        else value = FOP(8);
        shooters[index].speed_2 = value;
        return 0;
    }
    case 0x1b4: {
        int index = IOP(0);
        int value;
        if (g_difficulty_00474c74 == 0) value = IOP(1);
        else if (g_difficulty_00474c74 == 1) value = IOP(2);
        else if (g_difficulty_00474c74 == 2) value = IOP(3);
        else value = IOP(4);
        shooters[index].count_1 = value;
        if (g_difficulty_00474c74 == 0) value = IOP(5);
        else if (g_difficulty_00474c74 == 1) value = IOP(6);
        else if (g_difficulty_00474c74 == 2) value = IOP(7);
        else value = IOP(8);
        shooters[index].count_2 = value;
        return 0;
    }
    case 0x1a6: {
        int index = IOP(0);
        if (g_rank_00474c98 >= 0x200) {
            shooters[index].speed_1 = FOP(5);
            shooters[index].speed_2 = FOP(6);
            return 0;
        }
        if (g_rank_00474c98 >= -0x200) {
            shooters[index].speed_1 = FOP(3);
            shooters[index].speed_2 = FOP(4);
        } else {
            shooters[index].speed_1 = FOP(1);
            shooters[index].speed_2 = FOP(2);
        }
        return 0;
    }
    case 0x1a7: {
        int index = IOP(0);
        if (g_rank_00474c98 >= 600) {
            shooters[index].speed_1 = FOP(9);
            shooters[index].speed_2 = FOP(10);
            return 0;
        }
        if (g_rank_00474c98 >= 200) {
            shooters[index].speed_1 = FOP(7);
            shooters[index].speed_2 = FOP(8);
            return 0;
        }
        if (g_rank_00474c98 >= -200) {
            shooters[index].speed_1 = FOP(5);
            shooters[index].speed_2 = FOP(6);
            return 0;
        }
        if (g_rank_00474c98 >= -600) {
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
        shooters[index].speed_1 = ((float)g_rank_00474c98 + 1024.0f) * (high_1 - low_1) / 2048.0f + low_1;
        shooters[index].speed_2 = ((float)g_rank_00474c98 + 1024.0f) * (high_2 - low_2) / 2048.0f + low_2;
        return 0;
    }
    case 0x1a9: {
        int index = IOP(0);
        if (g_rank_00474c98 >= 0x200) {
            shooters[index].count_1 = IOP(5);
            shooters[index].count_2 = IOP(6);
            return 0;
        }
        if (g_rank_00474c98 >= -0x200) {
            shooters[index].count_1 = IOP(3);
            shooters[index].count_2 = IOP(4);
        } else {
            shooters[index].count_1 = IOP(1);
            shooters[index].count_2 = IOP(2);
        }
        return 0;
    }
    case 0x1aa: {
        int index = IOP(0);
        if (g_rank_00474c98 >= 600) {
            shooters[index].count_1 = IOP(9);
            shooters[index].count_2 = IOP(10);
            return 0;
        }
        if (g_rank_00474c98 >= 200) {
            shooters[index].count_1 = IOP(7);
            shooters[index].count_2 = IOP(8);
            return 0;
        }
        if (g_rank_00474c98 >= -200) {
            shooters[index].count_1 = IOP(5);
            shooters[index].count_2 = IOP(6);
            return 0;
        }
        if (g_rank_00474c98 >= -600) {
            shooters[index].count_1 = IOP(3);
            shooters[index].count_2 = IOP(4);
        } else {
            shooters[index].count_1 = IOP(1);
            shooters[index].count_2 = IOP(2);
        }
        return 0;
    }
    case 0x1ab: {
        int index = IOP(0);
        int low_1 = IOP(1);
        int low_2 = IOP(2);
        int high_1 = IOP(3);
        int high_2 = IOP(4);
        shooters[index].count_1 = (high_1 - low_1) * (g_rank_00474c98 + 1024) / 2048 + low_1;
        shooters[index].count_2 = (high_2 - low_2) * (g_rank_00474c98 + 1024) / 2048 + low_2;
        return 0;
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
        ShooterEx* ex = &shooters[index].ex[entry];
        ex->f = IOP(2);
        ex->e = IOP(3);
        ex->c = IOP(4);
        ex->d = IOP(5);
        ex->a = FOP(6);
        ex->b = FOP(7);
        return 0;
    }
    case 0x14d:
        timer_11c.Set_00405410(0);
        return 0;
    case 0x14e:
        Enemy_BindSlot_00412720(ecl, IOP(0), IOP(1), IOP(2), &ins->s[0x10]);
        return 0;
    case 0x155:
        ecl->body.slots[IOP(0)].cursor = &ins->s[8];
        return 0;
    case 0x19a:
        data_004776f0->Sweep_00408210(1);
        g_laser_manager->Cleanup_0041c850(1);
        return 0;
    case 0x150:
        data_00492590.QueuePan_0043dd10(IOP(0), position.x);
        return 0;
    case 0x151:
        CreateScreenEffect_0043c8b0(0x31, 1, IOP(0), IOP(1), IOP(2), 0);
        return 0;
    case 0x152:
        data_0047770c->CreateScoreDisplay_00415db0(IOP(0));
        data_004776f0->Sweep_00408210(0);
        g_laser_manager->Cleanup_0041c850(0);
        EnemyManager_SweepDeaths_0040e6a0(data_00477704);
        return 0;
    case 0x153:
        if (data_0047770c->message != 0 && data_0047770c->message->f78 == 0) return -1;
        break;
    case 0x154:
        if (data_00477704->boss[0] != 0) return -1;
        break;
    case 0x156:
    case 0x15c:
    case 0x165:
    case 0x166:
    case 0x167: {
        char name[128];
        int length = ins->i[3];
        unsigned char key = 0x77;
        unsigned char step = 7;
        const char* text = &ins->s[0x10];
        for (int i = 0; i < length; ++i) {
            name[i] = text[i] ^ key;
            key += step;
            step += 0x10;
        }
        int id = IOP(0);
        switch (ins->id) {
        case 0x165: id += g_difficulty_00474c74; break;
        case 0x166: id += g_difficulty_00474c74 - 1; break;
        case 0x167: id += g_difficulty_00474c74 - 2; break;
        }
        SpellCard_Start_00409280(data_004776f4, id, name, IOP(1), IOP(2));
        return 0;
    }
    case 0x157:
        data_004776f4->End_00409c00();
        return 0;
    case 0x16a:
        data_004776f4->flags |= 8;
        return 0;
    case 0x16b:
        data_004776f4->StopAnimation_0040cea0();
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
        g_laser_manager->Spawn_0041c510(&params, 0);
        return 0;
    }
    case 0x19d:
    case 0x1b0: {
        BeamLaserParams params;
        int* result = IntDest_00412a10(0);
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
        int id = g_laser_manager->Spawn_0041c510(&params, 1);
        if (result) *result = id;
        return 0;
    }
    case 0x1ac:
    case 0x1b1: {
        LineLaserParams params;
        memset(&params, 0, sizeof(params));
        if (ins->id == 0x1b1) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = IntArg_00412a00(0);
        params.color = IntArg_00412a00(1);
        params.f0c = FOP(2);
        params.f20 = FOP(3);
        params.f14 = FOP(4);
        params.f10 = FOP(5);
        params.f18 = FOP(6);
        params.f1c = FOP(7);
        params.flags &= ~1u;
        g_laser_manager->Spawn_0041c510(&params, 0);
        return 0;
    }
    case 0x1ad:
    case 0x1b2: {
        BeamLaserParams params((BeamLaserParams::Raw()));
        params.Construct_0040cf40();
        int* result = IntDest_00412a10(0);
        if (ins->id == 0x1b2) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = IntArg_00412a00(1);
        params.color = IntArg_00412a00(2);
        params.f18 = FOP(3);
        params.f24 = FOP(4);
        params.f20 = FOP(5);
        params.f30 = IntArg_00412a00(6);
        params.f34 = IntArg_00412a00(7);
        params.f38 = IntArg_00412a00(8);
        params.f3c = IntArg_00412a00(9);
        params.f28 = FOP(10);
        params.flags = IntArg_00412a00(11) & ~2u;
        int id = g_laser_manager->Spawn_0041c510(&params, 1);
        if (result) *result = id;
        return 0;
    }
    case 0x19e: {
        Laser* laser = g_laser_manager->FindById_0040cf90(IntArg_00412a00(0));
        if (laser) laser->f24 = Float3(FOP(1), FOP(2), 0.0f);
        return 0;
    }
    case 0x19f: {
        Laser* laser = g_laser_manager->FindById_0040cf90(IntArg_00412a00(0));
        if (laser) laser->SetVector_0040cf60(Float3(FOP(1), FOP(2), 0.0f));
        return 0;
    }
    case 0x1a0: {
        Laser* laser = g_laser_manager->FindById_0040cf90(IntArg_00412a00(0));
        if (laser) laser->f48 = FOP(1);
        return 0;
    }
    case 0x1a1: {
        Laser* laser = g_laser_manager->FindById_0040cf90(IntArg_00412a00(0));
        if (laser) laser->f44 = FOP(1);
        return 0;
    }
    case 0x1a2: {
        Laser* laser = g_laser_manager->FindById_0040cf90(IntArg_00412a00(0));
        if (laser) laser->f3c = FOP(1);
        return 0;
    }
    case 0x1a3: {
        Laser* laser = g_laser_manager->FindById_0040cf90(IntArg_00412a00(0));
        if (laser) laser->f440 = FOP(1);
        return 0;
    }
    case 0x1a4: {
        float radius = FOP(0);
        data_004776f0->Check_00408100(&position, radius, 1, 0);
        g_laser_manager->Evaluate_0041c800(&position, radius, 1);
        return 0;
    }
    case 0x1a5: {
        float radius = FOP(0);
        data_004776f0->Check_00408100(&position, radius, 0, 0);
        g_laser_manager->Evaluate_0041c800(&position, radius, 0);
        return 0;
    }
    case 0x158:
        Score_SetMode_00412ed0(&data_00474c40, IntArg_00412a00(0));
        return 0;
    case 0x15d:
        if (g_rank_00474c98 >= 0x200) *FloatDest(0) = FOP(2);
        else if (g_rank_00474c98 > -0x200) *FloatDest(0) = FOP(0);
        else *FloatDest(0) = FOP(0);
        return 0;
    case 0x15e:
        if (g_rank_00474c98 >= 600) {
            *FloatDest(0) = FOP(4);
            return 0;
        }
        if (g_rank_00474c98 >= 200) {
            *FloatDest(0) = FOP(3);
            return 0;
        }
        if (g_rank_00474c98 >= -200) {
            *FloatDest(0) = FOP(2);
            return 0;
        }
        if (g_rank_00474c98 >= -400) {
            *FloatDest(0) = FOP(1);
        } else {
            *FloatDest(0) = FOP(0);
        }
        return 0;
    case 0x15f: {
        float low = FOP(1);
        float high = FOP(2);
        *FloatDest(0) = ((float)g_rank_00474c98 + 1024.0f) * (high - low) / 2048.0f + low;
        return 0;
    }
    case 0x160:
        if (g_rank_00474c98 >= 0x200) *IntDest_00412a10(0) = IntArg_00412a00(2);
        else if (g_rank_00474c98 > -0x200) *IntDest_00412a10(0) = IntArg_00412a00(0);
        else *IntDest_00412a10(0) = IntArg_00412a00(0);
        return 0;
    case 0x161:
        if (g_rank_00474c98 >= 600) {
            *IntDest_00412a10(0) = IntArg_00412a00(4);
            return 0;
        }
        if (g_rank_00474c98 >= 200) {
            *IntDest_00412a10(0) = IntArg_00412a00(3);
            return 0;
        }
        if (g_rank_00474c98 >= -200) {
            *IntDest_00412a10(0) = IntArg_00412a00(2);
            return 0;
        }
        if (g_rank_00474c98 >= -400) {
            *IntDest_00412a10(0) = IntArg_00412a00(1);
        } else {
            *IntDest_00412a10(0) = IntArg_00412a00(0);
        }
        return 0;
    case 0x162: {
        int low = IntArg_00412a00(1);
        int high = IntArg_00412a00(2);
        *IntDest_00412a10(0) = (high - low) * (g_rank_00474c98 + 1024) / 2048 + low;
        return 0;
    }
    case 0x168:
        data_0047770c->f9e90 = IntArg_00412a00(0);
        return 0;
    case 0x16d:
        g_laser_manager->MarkEligible_0041c7d0();
        return 0;
    case 0x16e:
        f20 = IntArg_00412a00(0);
        f1448 = IntArg_00412a00(1);
        f21 = 0;
        f144c = anm_base_script;
        return 0;
    case 0x16f:
        g_game_speed_00476f78 = FOP(0);
        return 0;
    case 0x1ae:
        *FloatDest(0) = (float)atan2(g_player->position.y - FOP(2), g_player->position.x - FOP(1));
        return 0;
    case 0x170: {
        float wait;
        if (g_difficulty_00474c74 == 0) wait = (float)IntArg_00412a00(0);
        else if (g_difficulty_00474c74 == 1) wait = (float)IntArg_00412a00(1);
        else if (g_difficulty_00474c74 == 2) wait = (float)IntArg_00412a00(2);
        else wait = (float)IntArg_00412a00(3);
        ecl->active->time -= wait;
        break;
    }
    }
    return 0;
}

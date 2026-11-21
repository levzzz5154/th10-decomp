// 0x0040E770: execute one enemy-specific ECL instruction.
#include "th10/runtime/game/enemy/enemy_execute.hpp"

// Keep the double literal: motion operands use a strict greater-than test.
#define UNSET_MOTION_COMPONENT (-999999.0)

static __forceinline Float3 operator-(const Float3& a, const Float3& b) {
    return Float3(a.x - b.x, a.y - b.y, a.z - b.z);
}

static __forceinline void SubtractWait(EnemyFull* enemy, float wait) { enemy->active->time -= wait; }
static __forceinline float OperandRange(float low, float high) { return high - low; }
static __forceinline float SquaredLength(float x, float y) { return x * x + y * y; }
static __forceinline float DistanceSquared(const Float3& a, const Float3& b) { return SquaredLength(a.x - b.x, a.y - b.y); }
__declspec(noinline) int __stdcall ShooterShoot(BulletManager* manager, Shooter* shooter);

// Enemy-specific ECL opcodes (0x100..0x1B4) dispatched from EclVm::Run.
enum EnemyEclOpcode {
    // Spawning (boss-guarded variants skip spawn when boss[0] != 0)
    ECL_ENEMY_CREATE = 0x100,
    ECL_ENEMY_CREATE_ABS = 0x101,
    ECL_ENEMY_CREATE_MIRRORED = 0x104,
    ECL_ENEMY_CREATE_ABS_MIRRORED = 0x105,
    ECL_ENEMY_CREATE_NO_BOSS = 0x109,
    ECL_ENEMY_CREATE_ABS_NO_BOSS = 0x10a,
    ECL_ENEMY_CREATE_MIRRORED_NO_BOSS = 0x10b,
    ECL_ENEMY_CREATE_ABS_MIRRORED_NO_BOSS = 0x10c,
    ECL_ENEMY_CREATE_3D = 0x10e,
    ECL_ENEMY_CREATE_3D_NO_BOSS = 0x10f,

    // Animations & effects
    ECL_ANM_SELECT = 0x102,
    ECL_ANM_SET_SLOT = 0x103,
    ECL_ANM_SET_MAIN = 0x106,
    ECL_ANM_SPAWN_FRONT_AT = 0x107,
    ECL_ANM_SPAWN_FRONT = 0x108,
    ECL_ANM_SET_SLOT_ALT = 0x10d,
    ECL_ANM_SPAWN_BACK_AT = 0x110,
    ECL_ANM_SPAWN_FRONT_ROTATED = 0x111,

    // Motion (even = absolute, odd = relative where paired)
    ECL_MOVE_POS_ABS = 0x118,
    ECL_MOVE_POS_TIME_ABS = 0x119,
    ECL_MOVE_POS_REL = 0x11a,
    ECL_MOVE_POS_TIME_REL = 0x11b,
    ECL_MOVE_VEL_ABS = 0x11c,
    ECL_MOVE_VEL_TIME_ABS = 0x11d,
    ECL_MOVE_VEL_REL = 0x11e,
    ECL_MOVE_VEL_TIME_REL = 0x11f,
    ECL_MOVE_ORBIT_ABS = 0x120,
    ECL_MOVE_ORBIT_TIME_ABS = 0x121,
    ECL_MOVE_ORBIT_REL = 0x122,
    ECL_MOVE_ORBIT_TIME_REL = 0x123,
    ECL_MOVE_RAND_ABS = 0x124,
    ECL_MOVE_RAND_REL = 0x125,
    ECL_MOVE_TO_BOSS_ABS = 0x126,
    ECL_MOVE_TO_BOSS_REL = 0x127,
    ECL_MOVE_ADD_ABS = 0x128,
    ECL_MOVE_ADD_REL = 0x129,
    ECL_MOVE_ORIGIN_ABS = 0x12a,
    ECL_MOVE_ORIGIN_REL = 0x12b,

    // Hitboxes, flags, bounds, drops, life & boss state
    ECL_SET_HITBOX = 0x140,
    ECL_SET_CONTACT_BOX = 0x141,
    ECL_FLAGS_SET = 0x142,
    ECL_FLAGS_CLEAR = 0x143,
    ECL_SET_BOUNDS = 0x144,
    ECL_CLEAR_BOUNDS = 0x145,
    ECL_DROP_CLEAR_EXTRA = 0x146,
    ECL_DROP_ADD_EXTRA = 0x147,
    ECL_DROP_SET_SPREAD = 0x148,
    ECL_DROP_FLUSH = 0x149,
    ECL_DROP_SET_MAIN = 0x14a,
    ECL_SET_LIFE = 0x14b,
    ECL_SET_BOSS = 0x14c,
    ECL_RESET_TIMER = 0x14d,
    ECL_BIND_INTERRUPT = 0x14e,
    ECL_SET_INVULN_TIMER = 0x14f,
    ECL_PLAY_SOUND = 0x150,
    ECL_SCREEN_EFFECT = 0x151,
    ECL_STAGE_CLEAR_BONUS = 0x152,
    ECL_WAIT_DIALOGUE = 0x153,
    ECL_WAIT_BOSS_CLEAR = 0x154,
    ECL_SET_INTERRUPT_CURSOR = 0x155,
    ECL_SPELL_START = 0x156,
    ECL_SPELL_END = 0x157,
    ECL_SCORE_SET_MODE = 0x158,
    ECL_KILL_ALL_ENEMIES = 0x159,
    ECL_SET_SHOOT_RANGE = 0x15a,
    ECL_SET_LIFE_MARKER = 0x15b,
    ECL_SPELL_START_ALT = 0x15c,
    ECL_RANK_SELECT_F3 = 0x15d,
    ECL_RANK_SELECT_F5 = 0x15e,
    ECL_RANK_LERP_F = 0x15f,
    ECL_RANK_SELECT_I3 = 0x160,
    ECL_RANK_SELECT_I5 = 0x161,
    ECL_RANK_LERP_I = 0x162,
    ECL_DIFF_SELECT_I = 0x163,
    ECL_DIFF_SELECT_F = 0x164,
    ECL_SPELL_START_DIFF = 0x165,
    ECL_SPELL_START_DIFF_M1 = 0x166,
    ECL_SPELL_START_DIFF_M2 = 0x167,
    ECL_FRONT_SET_STATE = 0x168,
    ECL_SET_CONTACT_TIMER = 0x169,
    ECL_SPELL_MARK_FLAG = 0x16a,
    ECL_SPELL_STOP_ANIM = 0x16b,
    ECL_SET_FLAG_19 = 0x16c,
    ECL_LASER_MARK_ELIGIBLE = 0x16d,
    ECL_SET_COVERED_SCRIPT = 0x16e,
    ECL_SET_GAME_SPEED = 0x16f,
    ECL_WAIT_BY_DIFF = 0x170,

    // Shooters & lasers
    ECL_SHOOTER_RESET = 0x190,
    ECL_SHOOTER_FIRE = 0x191,
    ECL_SHOOTER_TYPE = 0x192,
    ECL_SHOOTER_OFFSET = 0x193,
    ECL_SHOOTER_ANGLE = 0x194,
    ECL_SHOOTER_SPEED = 0x195,
    ECL_SHOOTER_COUNT = 0x196,
    ECL_SHOOTER_AIM = 0x197,
    ECL_SHOOTER_SOUND = 0x198,
    ECL_SHOOTER_EX = 0x199,
    ECL_CLEAR_BULLETS_TO_ITEMS = 0x19a,
    ECL_SHOOTER_COPY = 0x19b,
    ECL_LASER_LINE = 0x19c,
    ECL_LASER_BEAM = 0x19d,
    ECL_LASER_SET_POS = 0x19e,
    ECL_LASER_SET_VEC = 0x19f,
    ECL_LASER_SET_F48 = 0x1a0,
    ECL_LASER_SET_F44 = 0x1a1,
    ECL_LASER_SET_F3C = 0x1a2,
    ECL_LASER_SET_F440 = 0x1a3,
    ECL_CLEAR_RADIUS_ITEMS = 0x1a4,
    ECL_CLEAR_RADIUS = 0x1a5,
    ECL_SHOOTER_SPEED_RANK3 = 0x1a6,
    ECL_SHOOTER_SPEED_RANK5 = 0x1a7,
    ECL_SHOOTER_SPEED_RANK_LERP = 0x1a8,
    ECL_SHOOTER_COUNT_RANK3 = 0x1a9,
    ECL_SHOOTER_COUNT_RANK5 = 0x1aa,
    ECL_SHOOTER_COUNT_RANK_LERP = 0x1ab,
    ECL_LASER_LINE_UNFLAGGED = 0x1ac,
    ECL_LASER_BEAM_UNFLAGGED = 0x1ad,
    ECL_ANGLE_TO_PLAYER = 0x1ae,
    ECL_LASER_LINE_EX = 0x1af,
    ECL_LASER_BEAM_EX = 0x1b0,
    ECL_LASER_LINE_EX_UNFLAGGED = 0x1b1,
    ECL_LASER_BEAM_EX_UNFLAGGED = 0x1b2,
    ECL_SHOOTER_SPEED_DIFF = 0x1b3,
    ECL_SHOOTER_COUNT_DIFF = 0x1b4
};

// Subset of EnemyTick::flags (th10/game/enemy_data_start.hpp) used by Execute2.
enum EnemyExecFlags {
    ENEMY_FLAG_INTANGIBLE = 0x10,
    ENEMY_FLAG_LIMITED = 0x200,
    ENEMY_FLAG_MIRRORED = 0x800,
    ENEMY_FLAG_FACES = 0x1000,
    ENEMY_FLAG_BOSS = 0x8000,
    ENEMY_FLAG_UNSCROLLED = 0x40000
};

#pragma code_seg(".text$0040e770_fn")
int Enemy::Execute2() {
    // The three layer-5 creation sites use distinct out-parameters.
    AnmHandle slot_handle_outputs[3];
    EclInstr* instruction = (*(EclVm* const volatile*)&ecl->active)->instr;
    switch (instruction->id) {
    // Spawning. Each boss-guarded variant falls through to the corresponding
    // spawn when boss slot zero is empty. Numeric operands follow the packed name.
    case ECL_ENEMY_CREATE_NO_BOSS:
        if (g_enemy_ctrl->boss[0] != 0) break;
    // -----------------------------------------------------------------------
    // Enemy spawning (0x100..0x10f)
    // -----------------------------------------------------------------------
    case ECL_ENEMY_CREATE: {
        int first_numeric_word = (instruction->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        if (!(flags & ENEMY_FLAG_UNSCROLLED)) {
            float x = position.x;
            spawn.position.x = x + FloatValue2(1, instruction->f[first_numeric_word]);
            float y = position.y;
            spawn.position.y = y + FloatValue2(2, instruction->f[first_numeric_word + 1]);
        } else {
            Float3 world;
            float x = position.x;
            world.x = x + FloatValue2(1, instruction->f[first_numeric_word]);
            float y = position.y;
            world.y = y + FloatValue2(2, instruction->f[first_numeric_word + 1]);
            world.z = position.z;
            g_application.SelectStage2(0);
            D3DXVec3Project2(&spawn.position, &world, g_projection_matrix,
                             g_projection_view_matrix, g_projection_world_matrix, g_enemy_project_viewport);
            spawn.position.x -= 224.0f;
            spawn.position.z = 0.0f;
            spawn.position.y -= 16.0f;
        }
        spawn.life = IntValue(3, instruction->i[first_numeric_word + 2]);
        spawn.score = IntValue(4, instruction->i[first_numeric_word + 3]);
        spawn.item = IntValue(5, instruction->i[first_numeric_word + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &instruction->s[4]);
        return 0;
    }
    case ECL_ENEMY_CREATE_ABS_NO_BOSS:
        if (g_enemy_ctrl->boss[0] != 0) break;
    case ECL_ENEMY_CREATE_ABS: {
        int first_numeric_word = (instruction->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.position.x = FloatValue2(1, instruction->f[first_numeric_word]);
        spawn.position.y = FloatValue2(2, instruction->f[first_numeric_word + 1]);
        spawn.life = IntValue(3, instruction->i[first_numeric_word + 2]);
        spawn.score = IntValue(4, instruction->i[first_numeric_word + 3]);
        spawn.item = IntValue(5, instruction->i[first_numeric_word + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &instruction->s[4]);
        return 0;
    }
    case ECL_ENEMY_CREATE_3D_NO_BOSS:
        if (g_enemy_ctrl->boss[0] != 0) break;
    case ECL_ENEMY_CREATE_3D: {
        int first_numeric_word = (instruction->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.position.x = FloatValue2(1, instruction->f[first_numeric_word]) + g_camera_offset.x;
        spawn.position.y = FloatValue2(2, instruction->f[first_numeric_word + 1]) + g_camera_offset.y;
        spawn.position.z = FloatValue2(3, instruction->f[first_numeric_word + 2]);
        spawn.life = IntValue(4, instruction->i[first_numeric_word + 3]);
        spawn.score = IntValue(5, instruction->i[first_numeric_word + 4]);
        spawn.item = IntValue(6, instruction->i[first_numeric_word + 5]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        spawn.flags |= 1;
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &instruction->s[4]);
        return 0;
    }
    case ECL_ENEMY_CREATE_MIRRORED_NO_BOSS:
        if (g_enemy_ctrl->boss[0] != 0) break;
    case ECL_ENEMY_CREATE_MIRRORED: {
        int first_numeric_word = (instruction->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        float x = position.x;
        spawn.position.x = x + FloatValue2(1, instruction->f[first_numeric_word]);
        float y = position.y;
        spawn.position.y = y + FloatValue2(2, instruction->f[first_numeric_word + 1]);
        spawn.life = IntValue(3, instruction->i[first_numeric_word + 2]);
        spawn.score = IntValue(4, instruction->i[first_numeric_word + 3]);
        spawn.item = IntValue(5, instruction->i[first_numeric_word + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        spawn.mirrored = 1;
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &instruction->s[4]);
        return 0;
    }
    case ECL_ENEMY_CREATE_ABS_MIRRORED_NO_BOSS:
        if (g_enemy_ctrl->boss[0] != 0) break;
    case ECL_ENEMY_CREATE_ABS_MIRRORED: {
        int first_numeric_word = (instruction->i[0] + 4) / 4;
        EnemySpawn spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.position.x = FloatValue2(1, instruction->f[first_numeric_word]);
        spawn.position.y = FloatValue2(2, instruction->f[first_numeric_word + 1]);
        spawn.life = IntValue(3, instruction->i[first_numeric_word + 2]);
        spawn.score = IntValue(4, instruction->i[first_numeric_word + 3]);
        spawn.item = IntValue(5, instruction->i[first_numeric_word + 4]);
        memcpy(spawn.variables, variables, sizeof(spawn.variables));
        spawn.mirrored = 1;
        EnemyCtrl_Spawn(&spawn, g_enemy_ctrl, &instruction->s[4]);
        return 0;
    }

    // Animation files, attached slots and independent effects.
    // -----------------------------------------------------------------------
    // Animations & visual effects (0x102..0x111)
    // -----------------------------------------------------------------------
    case ECL_ANM_SELECT:
        anm_file = Int(0);
        return 0;
    case ECL_ANM_SET_SLOT: {
        int slot = Int(0);
        int script = Int(1);
        anm[slot].Release2();
        if (script < 0) break;
        anm[slot] = *Anm_CreateFront(g_enemy_ctrl->Anm(anm_file), &slot_handle_outputs[0], Int(1), 5);
        if (slot == 0) {
            anm_main_script = Int(1);
            anm_main_file = anm_file;
        }
        AnmVm* vm = Anm_Resolve2(&anm[slot]);
        if (slot == 0) {
            // Retail swaps the axes here: visible_width (+0x13A4) takes sprite_height * scale.y
            // and visible_height (+0x13A8) takes sprite_width * scale.x.
            visible_width = vm->sprite_height * vm->scale.y;
            visible_height = vm->sprite_width * vm->scale.x;
        }
        if (flags & ENEMY_FLAG_INTANGIBLE) anm[slot].Show2();
        return 0;
    }
    case ECL_ANM_SPAWN_FRONT_AT: {
        int file = Int(0);
        AnmHandle handle;
        Anm_CreateFront(g_enemy_ctrl->Anm(file), &handle, Int(1), 6);
        AnmVm* vm = Anm_Resolve2(&handle);
        if (!(flags & ENEMY_FLAG_UNSCROLLED)) vm->offset = *OffsetPoint2(&position);
        else vm->offset = position;
        goto finish_instruction;
    }
    case ECL_ANM_SPAWN_BACK_AT: {
        int file = Int(0);
        AnmHandle handle;
        Anm_CreateBack(g_enemy_ctrl->anm[file], &handle, Int(1), 6);
        AnmVm* vm = Anm_Resolve2(&handle);
        if (!(flags & ENEMY_FLAG_UNSCROLLED)) vm->offset = *OffsetPoint2(&position);
        else vm->offset = position;
        goto leave_dispatch;
    }
    case ECL_ANM_SPAWN_FRONT: {
        int file = Int(0);
        AnmHandle handle;
        Anm_CreateFront(g_enemy_ctrl->Anm(file), &handle, Int(1), 6);
        return 0;
    }
    case ECL_ANM_SPAWN_FRONT_ROTATED: {
        int file = Int(0);
        AnmHandle handle;
        Anm_CreateFront(g_enemy_ctrl->Anm(file), &handle, Int(1), 6);
        AnmVm* vm = Anm_Resolve2(&handle);
        if (!(flags & ENEMY_FLAG_UNSCROLLED)) vm->offset = *OffsetPoint2(&position);
        else vm->offset = position;
        vm->rotation.z = Float(2);
        vm->flags |= 4;
        return 0;
    }
    case ECL_ANM_SET_MAIN: {
        int slot = Int(0);
        int script = Int(1);
        anm[slot].Release2();
        anm[slot] = *Anm_CreateFront(g_enemy_ctrl->Anm(anm_file), &slot_handle_outputs[2], script, 5);
        AnmVm* vm = Anm_Resolve2(&anm[slot]);
        if (slot == 0) {
            visible_width = vm->sprite_height * vm->scale.y;
            visible_height = vm->sprite_width * vm->scale.x;
        }
        if (flags & ENEMY_FLAG_INTANGIBLE) anm[slot].Show2();
        if (slot == 0) {
            flags |= ENEMY_FLAG_FACES;
            anm_base_script = script;
            anm_main_script = script;
            anm_f8 = 0;
            anm_main_file = anm_file;
        }
        return 0;
    }
    case ECL_ANM_SET_SLOT_ALT: {
        int slot = Int(0);
        anm[slot].Release2();
        AnmLoaded* resource = g_enemy_ctrl->anm[anm_file];
        anm[slot] = *Anm_CreateFront(resource, &slot_handle_outputs[1], anm_base_script + 5, 5);
        AnmVm* vm = Anm_Resolve2(&anm[slot]);
        if (slot == 0) {
            visible_width = vm->sprite_height * vm->scale.y;
            visible_height = vm->sprite_width * vm->scale.x;
        }
        if (flags & ENEMY_FLAG_INTANGIBLE) anm[slot].Show2();
        return 0;
    }

    // Motion. Paired opcodes select absolute or relative state before applying
    // the same operation. An unset component leaves the current value in place
    // or supplies the mode-specific interpolation default.
    // -----------------------------------------------------------------------
    // Motion & trajectories (0x118..0x12b)
    // -----------------------------------------------------------------------
    case ECL_MOVE_POS_ABS:
    case ECL_MOVE_POS_REL: {
        EnemyMotion* motion = instruction->id == ECL_MOVE_POS_ABS ? &absolute : &relative;
        float x = Float(0);
        float y = Float(1);
        if (x > UNSET_MOTION_COMPONENT) motion->position.x = x;
        if (y > UNSET_MOTION_COMPONENT) motion->position.y = y;
        motion->flags &= ~1u;
        position = relative.position + absolute.position;
        return 0;
    }
    case ECL_MOVE_ADD_ABS:
    case ECL_MOVE_ADD_REL: {
        EnemyMotion* motion = instruction->id == ECL_MOVE_ADD_ABS ? &absolute : &relative;
        float x = Float(0);
        float y = Float(1);
        float z = Float(2);
        motion->position.x += x;
        motion->position.y += y;
        motion->position.z += z;
        return 0;
    }
    case ECL_MOVE_POS_TIME_ABS:
    case ECL_MOVE_POS_TIME_REL: {
        EnemyMotion* motion = instruction->id == ECL_MOVE_POS_TIME_ABS ? &absolute : &relative;
        Float3Interp* interp = instruction->id == ECL_MOVE_POS_TIME_ABS ? &absolute_position_interp : &relative_position_interp;
        float x = Float(2);
        float y = Float(3);
        interp->end_time = Int(0);
        interp->control_1 = g_zero_vector3f;
        interp->control_2 = g_zero_vector3f;
        interp->mode = Int(1);
        interp->initial = motion->position;
        interp->goal = Float3(x > UNSET_MOTION_COMPONENT ? x : motion->position.x,
                              y > UNSET_MOTION_COMPONENT ? y : motion->position.y, 0.0f);
        interp->Restart2();
        motion->flags &= ~1u;
        return 0;
    }
    case ECL_MOVE_VEL_ABS:
    case ECL_MOVE_VEL_REL: {
        EnemyMotion* motion = instruction->id == ECL_MOVE_VEL_ABS ? &absolute : &relative;
        float angle;
        float speed;
        angle = Float(0);
        speed = Float(1);
        if (angle > UNSET_MOTION_COMPONENT) {
            if (flags & ENEMY_FLAG_MIRRORED) angle = Angle_Normalize(1.5707964f - Angle_Normalize(angle - 1.5707964f));
            Motion_SetAngle(motion, angle);
        }
        if (speed > UNSET_MOTION_COMPONENT) motion->speed = speed;
        motion->flags &= ~1u;
        return 0;
    }
    case ECL_MOVE_VEL_TIME_ABS:
    case ECL_MOVE_VEL_TIME_REL: {
        EnemyMotion* motion = instruction->id == ECL_MOVE_VEL_TIME_ABS ? &absolute : &relative;
        Float2Interp* interp = instruction->id == ECL_MOVE_VEL_TIME_ABS ? &absolute_direction_interp : &relative_direction_interp;
        float angle = Float(2);
        float speed = Float(3);
        interp->mode = Int(1);
        Float2 goal;
        if (interp->mode != 7) {
            {
                float goal_angle;
                goal_angle = angle > UNSET_MOTION_COMPONENT
                    ? ((flags & ENEMY_FLAG_MIRRORED) ? Angle_Normalize(1.5707964f - Angle_Normalize(angle - 1.5707964f)) : angle)
                    : motion->angle;
                goal.x = goal_angle;
            }
            {
                float goal_speed;
                goal_speed = speed > UNSET_MOTION_COMPONENT ? speed : motion->speed;
                goal.y = goal_speed;
            }
        } else {
            if (angle > UNSET_MOTION_COMPONENT) goal.x = angle;
            else goal.x = 0.0f;
            if (speed > UNSET_MOTION_COMPONENT) goal.y = speed;
            else goal.y = 0.0f;
        }
        Float2 initial(motion->angle, motion->speed);
        if (fabs(initial.x - goal.x) >= 3.1415927f) {
            if (initial.x < goal.x) initial.x += 6.2831855f;
            else goal.x += 6.2831855f;
        }
        interp->end_time = Int(0);
        interp->control_1 = g_zero_vector22;
        interp->control_2 = g_zero_vector22;
        interp->initial = initial;
        interp->goal = goal;
        interp->Restart3();
        motion->flags &= ~1u;
        return 0;
    }
    case ECL_MOVE_ORBIT_ABS:
    case ECL_MOVE_ORBIT_REL: {
        EnemyMotion* motion = instruction->id == ECL_MOVE_ORBIT_ABS ? &absolute : &relative;
        float angle = Float(0);
        float speed = Float(1);
        float radial = Float(2);
        float angular = Float(3);
        if (!(motion->flags & 1)) motion->origin = motion->position;
        if (angle > UNSET_MOTION_COMPONENT) Motion_SetAngle(motion, angle);
        if (speed > UNSET_MOTION_COMPONENT) motion->speed = speed;
        if (radial > UNSET_MOTION_COMPONENT) motion->radial_speed = radial;
        if (angular > UNSET_MOTION_COMPONENT) motion->angular_speed = angular;
        motion->flags |= 1;
        return 0;
    }
    case ECL_MOVE_ORBIT_TIME_ABS:
    case ECL_MOVE_ORBIT_TIME_REL: {
        EnemyMotion* motion = instruction->id == ECL_MOVE_ORBIT_TIME_ABS ? &absolute : &relative;
        Float2Interp* direction = instruction->id == ECL_MOVE_ORBIT_TIME_ABS ? &absolute_direction_interp : &relative_direction_interp;
        Float2Interp* orbit = instruction->id == ECL_MOVE_ORBIT_TIME_ABS ? &absolute_orbit_interp : &relative_orbit_interp;
        float angle = Float(2);
        float speed = Float(3);
        float radial = Float(4);
        float angular = Float(5);
        Float2 goal(angle > UNSET_MOTION_COMPONENT ? angle : motion->angle,
                    speed > UNSET_MOTION_COMPONENT ? speed : motion->speed);
        Float2 initial(motion->angle, motion->speed);
        Float2 orbit_goal(radial > UNSET_MOTION_COMPONENT ? radial : motion->radial_speed,
                          angular > UNSET_MOTION_COMPONENT ? angular : motion->angular_speed);
        Float2 orbit_initial(motion->radial_speed, motion->angular_speed);
        int end_time = Int(0);
        int mode = Int(1);
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
    case ECL_MOVE_ORIGIN_ABS:
    case ECL_MOVE_ORIGIN_REL: {
        EnemyMotion* motion = instruction->id == ECL_MOVE_ORIGIN_ABS ? &absolute : &relative;
        float x = Float(0);
        float y = Float(1);
        if (x > UNSET_MOTION_COMPONENT) motion->origin.x = x;
        if (y > UNSET_MOTION_COMPONENT) motion->origin.y = y;
    }
    // Fall through after changing the orbit origin: the absolute position
    // is then copied from boss slot zero in both cases.
    case ECL_MOVE_TO_BOSS_ABS:
        absolute.position = g_enemy_ctrl->boss[0]->body.position;
        return 0;
    case ECL_MOVE_TO_BOSS_REL:
        relative.position = g_enemy_ctrl->boss[0]->body.position;
        return 0;

    // Movement bounds, firing range and bounded random direction.
    case ECL_SET_BOUNDS:
        flags |= ENEMY_FLAG_LIMITED;
        bounds_x = Float(0);
        bounds_y = Float(1);
        bounds_width = Float(2);
        bounds_height = Float(3);
        return 0;
    case ECL_CLEAR_BOUNDS:
        flags &= ~(unsigned int)ENEMY_FLAG_LIMITED;
        return 0;
    case ECL_SET_SHOOT_RANGE: {
        float range = Float(0);
        shoot_range_squared = range * range;
        break;
    }
    case ECL_MOVE_RAND_ABS:
    case ECL_MOVE_RAND_REL: {
        EnemyMotion* motion = instruction->id == ECL_MOVE_RAND_ABS ? &absolute : &relative;
        Float2Interp* interp = instruction->id == ECL_MOVE_RAND_ABS ? &absolute_direction_interp : &relative_direction_interp;
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
        interp->mode = Int(1);
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
        initial.y = Float(2);
        interp->end_time = Int(0);
        interp->control_1 = g_zero_vector22;
        interp->control_2 = g_zero_vector22;
        interp->initial = initial;
        interp->goal = goal;
        interp->Restart3();
        motion->flags &= ~1u;
        return 0;
    }

    // Life markers, enemy state and animation visibility.
    case ECL_SET_LIFE_MARKER:
        g_front->SetMarker(Int(0), MaxLife(), Float(1), Int(2));
        return 0;
    // -----------------------------------------------------------------------
    // Hitboxes, bounds, drops, boss/spell state & difficulty (0x140..0x170)
    // -----------------------------------------------------------------------
    case ECL_SET_HITBOX:
        fb0 = Float(0);
        fb4 = Float(1);
        return 0;
    case ECL_SET_CONTACT_BOX:
        fb8 = Float(0);
        fbc = Float(1);
        return 0;
    case ECL_FLAGS_SET:
        flags |= Int(0);
        if (flags & ENEMY_FLAG_INTANGIBLE) {
            for (int i = 0; i < 10; ++i) anm[i].Show2();
        }
        return 0;
    case ECL_FLAGS_CLEAR:
        flags &= ~Int(0);
        if (!(flags & ENEMY_FLAG_INTANGIBLE)) {
            for (int i = 0; i < 10; ++i) anm[i].Hide2();
        }
        return 0;

    // Item drops: extra counts, spread, flush and main item.
    case ECL_DROP_CLEAR_EXTRA:
        memset(&drops.items[1], 0, 12 * sizeof(int));
        return 0;
    case ECL_DROP_ADD_EXTRA: {
        int kind = Int(0);
        if (flags & ENEMY_FLAG_BOSS) {
            if (kind == 1) kind = 10;
            else if (kind == 4) kind = 11;
        }
        drops.items[kind] = Int(1);
        return 0;
    }
    case ECL_DROP_SET_SPREAD:
        SetSpread(Float(0), Float(1));
        return 0;
    case ECL_DROP_FLUSH:
        Drops_Flush(&drops, &position);
        return 0;
    case ECL_DROP_SET_MAIN: {
        int kind = Int(0);
        if (flags & ENEMY_FLAG_BOSS) {
            if (kind == 1) kind = 10;
            else if (kind == 4) kind = 11;
        }
        drops.items[0] = kind;
        return 0;
    }

    // Life, boss registration and timers.
    case ECL_SET_LIFE: {
        life = Int(0);
        max_life = life;
        for (int i = 0; i < 4; ++i) {
            g_front->markers[i].ratio = 0.0f;
            g_front->markers[i].value = 0;
        }
        f13c8 = life;
        return 0;
    }
    case ECL_SET_BOSS: {
        int index = Int(0);
        if (index < 0) {
            if (flags & ENEMY_FLAG_BOSS) g_enemy_ctrl->boss[boss_index] = 0;
            flags &= ~(unsigned int)ENEMY_FLAG_BOSS;
        } else {
            flags |= ENEMY_FLAG_BOSS;
            g_enemy_ctrl->boss[index] = ecl;
            boss_index = index;
        }
        return 0;
    }
    case ECL_SET_INVULN_TIMER:
        timer_141c.Set2(Int(0));
        return 0;
    case ECL_SET_CONTACT_TIMER:
        timer_1430.Set2(Int(0));
        return 0;
    case ECL_KILL_ALL_ENEMIES:
        EnemyCtrl_SweepDeaths(g_enemy_ctrl);
        return 0;

    // Select an integer or float operand by difficulty.
    case ECL_DIFF_SELECT_I:
        switch (g_difficulty) {
        case 0:
            *IntDest2(0) = Int(1);
            goto finish_instruction;
        case 1:
            *IntDest2(0) = Int(2);
            goto finish_instruction;
        case 2:
            *IntDest2(0) = Int(3);
            goto finish_instruction;
        case 3:
        case 4:
            *IntDest2(0) = Int(4);
            goto finish_instruction;
        }
        break;
    case ECL_DIFF_SELECT_F:
        switch (g_difficulty) {
        case 0:
            *FloatDest(0) = Float(1);
            goto finish_instruction;
        case 1:
            *FloatDest(0) = Float(2);
            goto finish_instruction;
        case 2:
            *FloatDest(0) = Float(3);
            goto finish_instruction;
        case 3:
            *FloatDest(0) = Float(4);
            goto finish_instruction;
        case 4:
            *FloatDest(0) = Float(4);
            goto finish_instruction;
        }
        break;

    // Shooter slots: reset, copy, fire and configure the shot.
    // -----------------------------------------------------------------------
    // Bullet shooters & lasers (0x190..0x1b4)
    // -----------------------------------------------------------------------
    case ECL_SHOOTER_RESET: {
        int index = Int(0);
        memset(&shooters[index], 0, sizeof(Shooter));
        shooters[index].angle_1 = 0.0f;
        shooters[index].count_1 = 1;
        shooters[index].count_2 = 1;
        shooters[index].speed_1 = 2.0f;
        shooters[index].sound = 7;
        shooters[index].sound_2 = 0x18;
        shooters[index].flags = 0x203;
        shoot_offset[index].x = 0.0f;
        shoot_offset[index].y = 0.0f;
        return 0;
    }
    case ECL_SHOOTER_COPY:
        shooters[Int(0)] = shooters[Int(1)];
        return 0;
    case ECL_SHOOTER_FIRE: {
        int index = Int(0);
        shooters[index].position = shoot_offset[index] + position;
        if (shoot_range_squared != 0.0f) {
            if (!(shoot_range_squared <= DistanceSquared(shooters[index].position, g_player->position))) break;
        }
        ShooterShoot(g_bullet_manager, &shooters[index]);
        return 0;
    }
    case ECL_SHOOTER_TYPE: {
        int index = Int(0);
        shooters[index].type = Int(1);
        shooters[index].color = Int(2);
        return 0;
    }
    case ECL_SHOOTER_OFFSET: {
        int index = Int(0);
        shoot_offset[index].x = Float(1);
        shoot_offset[index].y = Float(2);
        return 0;
    }
    case ECL_SHOOTER_ANGLE: {
        int index = Int(0);
        shooters[index].angle_1 = Float(1);
        shooters[index].angle_2 = Float(2);
        return 0;
    }
    case ECL_SHOOTER_SPEED: {
        int index = Int(0);
        shooters[index].speed_1 = Float(1);
        shooters[index].speed_2 = Float(2);
        return 0;
    }
    case ECL_SHOOTER_COUNT: {
        int index = Int(0);
        shooters[index].count_1 = Int(1);
        shooters[index].count_2 = Int(2);
        return 0;
    }

    // Shooter speed/count variants select operand pairs by difficulty or rank.
    case ECL_SHOOTER_SPEED_DIFF: {
        int index = Int(0);
        float value;
        if (g_difficulty == 0) value = Float(1);
        else if (g_difficulty == 1) value = Float(2);
        else if (g_difficulty == 2) value = Float(3);
        else value = Float(4);
        shooters[index].speed_1 = value;
        if (g_difficulty == 0) value = Float(5);
        else if (g_difficulty == 1) value = Float(6);
        else if (g_difficulty == 2) value = Float(7);
        else value = Float(8);
        shooters[index].speed_2 = value;
        return 0;
    }
    case ECL_SHOOTER_COUNT_DIFF: {
        int index = Int(0);
        int value;
        if (g_difficulty == 0) value = Int(1);
        else if (g_difficulty == 1) value = Int(2);
        else if (g_difficulty == 2) value = Int(3);
        else value = Int(4);
        shooters[index].count_1 = value;
        if (g_difficulty == 0) value = Int(5);
        else if (g_difficulty == 1) value = Int(6);
        else if (g_difficulty == 2) value = Int(7);
        else value = Int(8);
        shooters[index].count_2 = value;
        goto leave_dispatch;
    }
    case ECL_SHOOTER_SPEED_RANK3: {
        int index = Int(0);
        if (g_rank >= 0x200) {
            shooters[index].speed_1 = Float(5);
            shooters[index].speed_2 = Float(6);
            goto finish_instruction;
        }
        if (g_rank >= -0x200) {
            shooters[index].speed_1 = Float(3);
            shooters[index].speed_2 = Float(4);
            goto leave_dispatch;
        } else {
            shooters[index].speed_1 = Float(1);
            shooters[index].speed_2 = Float(2);
            goto finish_instruction;
        }
    }
    case ECL_SHOOTER_SPEED_RANK5: {
        int index = Int(0);
        if (g_rank >= 600) {
            shooters[index].speed_1 = Float(9);
            shooters[index].speed_2 = Float(10);
            return 0;
        }
        if (g_rank >= 200) {
            shooters[index].speed_1 = Float(7);
            shooters[index].speed_2 = Float(8);
            return 0;
        }
        if (g_rank >= -200) {
            shooters[index].speed_1 = Float(5);
            shooters[index].speed_2 = Float(6);
            return 0;
        }
        if (g_rank >= -600) {
            shooters[index].speed_1 = Float(3);
            shooters[index].speed_2 = Float(4);
            goto leave_dispatch;
        } else {
            shooters[index].speed_1 = Float(1);
            shooters[index].speed_2 = Float(2);
            goto finish_instruction;
        }
    }
    case ECL_SHOOTER_SPEED_RANK_LERP: {
        int index = Int(0);
        float low_1 = Float(1);
        float low_2 = Float(2);
        float high_1 = Float(3);
        float high_2 = Float(4);
        shooters[index].speed_1 = ((float)g_rank + g_enemy_rank_midpoint) * (high_1 - low_1) / 2048.0f + low_1;
        shooters[index].speed_2 = ((float)g_rank + g_enemy_rank_midpoint) * OperandRange(low_2, high_2) / 2048.0f + low_2;
        return 0;
    }
    case ECL_SHOOTER_COUNT_RANK3: {
        int index = Int(0);
        if (g_rank >= 0x200) {
            shooters[index].count_1 = Int(5);
            shooters[index].count_2 = Int(6);
            goto finish_instruction;
        }
        if (g_rank >= -0x200) {
            shooters[index].count_1 = Int(3);
            shooters[index].count_2 = Int(4);
        } else {
            shooters[index].count_1 = Int(1);
            shooters[index].count_2 = Int(2);
        }
        goto finish_instruction;
    }
    case ECL_SHOOTER_COUNT_RANK5: {
        int index = Int(0);
        if (g_rank >= 600) {
            shooters[index].count_1 = Int(9);
            shooters[index].count_2 = Int(10);
            goto leave_dispatch;
        }
        if (g_rank >= 200) {
            shooters[index].count_1 = Int(7);
            shooters[index].count_2 = Int(8);
            goto leave_dispatch;
        }
        if (g_rank >= -200) {
            shooters[index].count_1 = Int(5);
            shooters[index].count_2 = Int(6);
            goto leave_dispatch;
        }
        if (g_rank >= -600) {
            shooters[index].count_1 = Int(3);
            shooters[index].count_2 = Int(4);
        } else {
            shooters[index].count_1 = Int(1);
            shooters[index].count_2 = Int(2);
        }
        goto leave_dispatch;
    }
    case ECL_SHOOTER_COUNT_RANK_LERP: {
        int index = Int(0);
        int low_1 = Int(1);
        int low_2 = Int(2);
        int high_1 = Int(3);
        int high_2 = Int(4);
        shooters[index].count_1 = (high_1 - low_1) * (g_rank + 1024) / 2048 + low_1;
        shooters[index].count_2 = (high_2 - low_2) * (g_rank + 1024) / 2048 + low_2;
        goto leave_dispatch;
    }

    // Shooter aim, sound and extended parameters.
    case ECL_SHOOTER_AIM: {
        int index = Int(0);
        shooters[index].aim_mode = Int(1);
        return 0;
    }
    case ECL_SHOOTER_SOUND: {
        int index = Int(0);
        shooters[index].sound = Int(1);
        shooters[index].sound_2 = Int(2);
        return 0;
    }
    case ECL_SHOOTER_EX: {
        int index = Int(0);
        int entry = Int(1);
        shooters[index].ex[entry].f = Int(2);
        shooters[index].ex[entry].e = Int(3);
        shooters[index].ex[entry].c = Int(4);
        shooters[index].ex[entry].d = Int(5);
        shooters[index].ex[entry].a = Float(6);
        shooters[index].ex[entry].b = Float(7);
        return 0;
    }

    // Enemy script slots, manager commands and wait conditions.
    case ECL_RESET_TIMER:
        timer_11c.Set2(0);
        return 0;
    case ECL_BIND_INTERRUPT:
        Enemy_BindSlot(ecl, Int(0), Int(1), Int(2), &instruction->s[0x10]);
        return 0;
    case ECL_SET_INTERRUPT_CURSOR:
        ecl->body.slots[Int(0)].cursor = &instruction->s[8];
        return 0;
    case ECL_CLEAR_BULLETS_TO_ITEMS:
        g_bullet_manager->Sweep2(1);
        g_laser_manager->Cleanup2(1);
        return 0;
    case ECL_PLAY_SOUND:
        g_sound_manager.QueuePan2(Int(0), position.x);
        return 0;
    case ECL_SCREEN_EFFECT:
        Screen_Create(0x31, 1, Int(0), Int(1), Int(2), 0);
        return 0;
    case ECL_STAGE_CLEAR_BONUS:
        g_front->CreateScoreDisplay2(Int(0));
        g_bullet_manager->Sweep2(0);
        g_laser_manager->Cleanup2(0);
        EnemyCtrl_SweepDeaths(g_enemy_ctrl);
        return 0;
    case ECL_WAIT_DIALOGUE:
        if (g_front->message != 0 && g_front->message->f78 == 0) return -1;
        break;
    case ECL_WAIT_BOSS_CLEAR:
        if (g_enemy_ctrl->boss[0] != 0) return -1;
        break;

    // Card commands. The start variants decode a packed name and may adjust
    // the card ID for the current difficulty.
    case ECL_SPELL_START:
    case ECL_SPELL_START_ALT:
    case ECL_SPELL_START_DIFF:
    case ECL_SPELL_START_DIFF_M1:
    case ECL_SPELL_START_DIFF_M2: {
        char name[128];
        const char* text = &instruction->s[0x10];
        unsigned char key = 0x77;
        unsigned char step = 7;
        int length = instruction->i[3];
        for (int i = 0; i < length; ++i) {
            name[i] = text[i] ^ key;
            key += step;
            step += 0x10;
        }
        int id = Int(0);
        switch (instruction->id) {
        case ECL_SPELL_START_DIFF:
            id += g_difficulty;
            break;
        case ECL_SPELL_START_DIFF_M1:
            id += g_difficulty - 1;
            break;
        case ECL_SPELL_START_DIFF_M2:
            id += g_difficulty - 2;
            break;
        }
        Card_Start(g_card, id, name, Int(1), Int(2));
        return 0;
    }
    case ECL_SPELL_END:
        g_card->End2();
        return 0;
    case ECL_SPELL_MARK_FLAG:
        g_card->flags |= 8;
        return 0;
    case ECL_SPELL_STOP_ANIM:
        g_card->StopAnimation();
        return 0;
    case ECL_SET_FLAG_19:
        f19 = Int(0);
        return 0;

    // Laser creation. Paired opcodes optionally copy shooter zero's extended
    // parameters; line and beam lasers have different parameter layouts.
    case ECL_LASER_LINE:
    case ECL_LASER_LINE_EX: {
        LineLaserParams params;
        memset(&params, 0, sizeof(params));
        if (instruction->id == ECL_LASER_LINE_EX) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = Int(0);
        params.color = Int(1);
        params.f0c = Float(2);
        params.f20 = Float(3);
        params.f14 = Float(4);
        params.f10 = Float(5);
        params.f18 = Float(6);
        params.f1c = Float(7);
        params.flags |= 1;
        g_laser_manager->Spawn2(&params, 0);
        return 0;
    }
    case ECL_LASER_BEAM:
    case ECL_LASER_BEAM_EX: {
        BeamLaserParams params;
        int* result = IntDest2(0);
        if (instruction->id == ECL_LASER_BEAM_EX) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = Int(1);
        params.color = Int(2);
        params.f18 = Float(3);
        params.f24 = Float(4);
        params.f20 = Float(5);
        params.f30 = Int(6);
        params.f34 = Int(7);
        params.f38 = Int(8);
        params.f3c = Int(9);
        params.f28 = Float(10);
        params.flags = Int(11) | 2;
        int id = g_laser_manager->Spawn2(&params, 1);
        if (result) *result = id;
        return 0;
    }
    case ECL_LASER_LINE_UNFLAGGED:
    case ECL_LASER_LINE_EX_UNFLAGGED: {
        LineLaserParams params;
        memset(&params, 0, sizeof(params));
        if (instruction->id == ECL_LASER_LINE_EX_UNFLAGGED) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = IntArg(0);
        params.color = IntArg(1);
        params.f0c = Float(2);
        params.f20 = Float(3);
        params.f14 = Float(4);
        params.f10 = Float(5);
        params.f18 = Float(6);
        params.f1c = Float(7);
        params.flags &= ~1u;
        g_laser_manager->Spawn2(&params, 0);
        return 0;
    }
    case ECL_LASER_BEAM_UNFLAGGED:
    case ECL_LASER_BEAM_EX_UNFLAGGED: {
        BeamLaserParams params((BeamLaserParams::Raw()));
        params.Construct2();
        int* result = IntDest2(0);
        if (instruction->id == ECL_LASER_BEAM_EX_UNFLAGGED) memcpy(params.ex, shooters[0].ex, sizeof(params.ex));
        params.position = shoot_offset[0] + position;
        params.type = IntArg(1);
        params.color = IntArg(2);
        params.f18 = Float(3);
        params.f24 = Float(4);
        params.f20 = Float(5);
        params.f30 = IntArg(6);
        params.f34 = IntArg(7);
        params.f38 = IntArg(8);
        params.f3c = IntArg(9);
        params.f28 = Float(10);
        params.flags = IntArg(11) & ~2u;
        int id = g_laser_manager->Spawn2(&params, 1);
        if (result) *result = id;
        return 0;
    }

    // Updates to an existing laser and radius checks against bullets/lasers.
    case ECL_LASER_SET_POS: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f24 = Float3(Float(1), Float(2), 0.0f);
        return 0;
    }
    case ECL_LASER_SET_VEC: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->SetVector(Float3(Float(1), Float(2), 0.0f));
        return 0;
    }
    case ECL_LASER_SET_F48: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f48 = Float(1);
        return 0;
    }
    case ECL_LASER_SET_F44: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f44 = Float(1);
        return 0;
    }
    case ECL_LASER_SET_F3C: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f3c = Float(1);
        return 0;
    }
    case ECL_LASER_SET_F440: {
        Laser* laser = g_laser_manager->FindById2(IntArg(0));
        if (laser) laser->f440 = Float(1);
        return 0;
    }
    case ECL_CLEAR_RADIUS_ITEMS: {
        float radius = Float(0);
        g_bullet_manager->Check2(&position, radius, 1, 0);
        g_laser_manager->Evaluate2(&position, radius, 1);
        return 0;
    }
    case ECL_CLEAR_RADIUS: {
        float radius = Float(0);
        g_bullet_manager->Check2(&position, radius, 0, 0);
        g_laser_manager->Evaluate2(&position, radius, 0);
        return 0;
    }
    case ECL_SCORE_SET_MODE:
        Score_SetMode2(&g_globals, IntArg(0));
        return 0;

    // Select or interpolate a value by rank. The integer and float forms
    // deliberately keep their own thresholds and arithmetic.
    case ECL_RANK_SELECT_F3:
        if (g_rank >= 0x200) *FloatDest(0) = Float(2);
        else if (g_rank <= -0x200) *FloatDest(0) = Float(0);
        else *FloatDest(0) = Float(0);
        goto finish_instruction;
    case ECL_RANK_SELECT_F5:
        if (g_rank >= 600) {
            *FloatDest(0) = Float(4);
            goto leave_dispatch;
        }
        if (g_rank >= 200) {
            *FloatDest(0) = Float(3);
            break;
        }
        if (g_rank >= -200) {
            *FloatDest(0) = Float(2);
            goto leave_dispatch;
        }
        if (g_rank >= -400) {
            *FloatDest(0) = Float(1);
        } else {
            *FloatDest(0) = Float(0);
        }
        goto finish_instruction;
    case ECL_RANK_LERP_F: {
        float low = Float(1);
        float high = Float(2);
        *FloatDest(0) = ((float)g_rank + g_enemy_rank_midpoint) * OperandRange(low, high) / 2048.0f + low;
        return 0;
    }
    case ECL_RANK_SELECT_I3:
        if (g_rank >= 0x200) *IntDest2(0) = IntArg(2);
        else if (g_rank > -0x200) *IntDest2(0) = IntArg(0);
        else *IntDest2(0) = IntArg(0);
        goto leave_dispatch;
    case ECL_RANK_SELECT_I5:
        if (g_rank >= 600) {
            *IntDest2(0) = IntArg(4);
            goto leave_dispatch;
        }
        if (g_rank >= 200) {
            *IntDest2(0) = IntArg(3);
            goto leave_dispatch;
        }
        if (g_rank >= -200) {
            *IntDest2(0) = IntArg(2);
            goto leave_dispatch;
        }
        if (g_rank >= -400) {
            *IntDest2(0) = IntArg(1);
        } else {
            *IntDest2(0) = IntArg(0);
        }
        goto leave_dispatch;
    case ECL_RANK_LERP_I: {
        int low = IntArg(1);
        int high = IntArg(2);
        *IntDest2(0) = (high - low) * (g_rank + 1024) / 2048 + low;
        return 0;
    }

    // Additional game state, player direction and VM timing.
    case ECL_FRONT_SET_STATE:
        g_front->f9e90 = IntArg(0);
        return 0;
    case ECL_LASER_MARK_ELIGIBLE:
        g_laser_manager->MarkEligible2();
        return 0;
    case ECL_SET_COVERED_SCRIPT:
        f20 = IntArg(0);
        f1448 = IntArg(1);
        f21 = 0;
        f144c = anm_base_script;
        return 0;
    case ECL_SET_GAME_SPEED:
        g_game_speed = Float(0);
        return 0;
    case ECL_ANGLE_TO_PLAYER: {
        // Operand evaluation separates the two reads of the global player pointer.
        const Float3* player_for_x = &g_player->position;
        float origin_x = Float(1);
        const Float3* player_for_y = &g_player->position;
        *FloatDest(0) = (float)atan2(player_for_y->y - Float(2), player_for_x->x - origin_x);
        goto finish_instruction;
    }
    case ECL_WAIT_BY_DIFF: {
        float wait;
        if (g_difficulty == 0) wait = (float)IntArg(0);
        else if (g_difficulty == 1) wait = (float)IntArg(1);
        else if (g_difficulty == 2) wait = (float)IntArg(2);
        else wait = (float)IntArg(3);
        SubtractWait(ecl, wait);
        break;
    }
    // Certain opcode tails share the switch exit rather than the final return.
    leave_dispatch:
        break;
    }
finish_instruction:
    return 0;
}

#pragma code_seg()

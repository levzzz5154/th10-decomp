// 0x0043EE30..0x0044151B: the ANM VM interpreter. Runs every instruction of
// the VM's script that is due at the current frame, then advances the
// interpolators and the script clock. Returns 1 when the script has ended.
//
// Built in the anm_vm_tick LTCG cluster, which compiles the callee bodies
// beside it so the whole-program link derives retail's private conventions.
#include "th10/runtime/core/sprtanim/anm_vm_tick.hpp"
#pragma intrinsic(sin, cos, tan, acos, atan, fmod, memcpy)

// READ_* evaluates a masked slot through the VM; a raw ins->i/f/b/w access
// reads the instruction payload as encoded. Don't cache or combine reads:
// a float variable can draw from the RNG.
#define READ_INT(n) ((ins->var_mask & (1 << (n))) ? vm->IntVar(ins->i[n]) : ins->i[n])
#define READ_FLOAT(n) ((ins->var_mask & (1 << (n))) ? vm->FloatVar(ins->f[n]) : ins->f[n])
// Slot zero is the destination. If it doesn't name writable VM storage,
// the resolver returns a pointer into the instruction itself.
#define INT_DEST_PTR() Anm_IntRef(&ins->i[0], vm, 0, ins->var_mask)
#define FLOAT_DEST_PTR() Anm_FloatRef(vm, 0, &ins->f[0], ins->var_mask)

enum AnmOpcode {
    ANM_SCRIPT_END = -1,
    ANM_NOP = 0,
    ANM_DELETE = 1,
    ANM_STOP = 2,
    ANM_SET_SPRITE = 3,
    ANM_JMP = 4,
    ANM_JMP_DEC = 5,
    ANM_SET_INT = 6,
    ANM_SET_FLOAT = 7,
    ANM_ADD_INT = 8,
    ANM_ADD_FLOAT = 9,
    ANM_SUB_INT = 10,
    ANM_SUB_FLOAT = 11,
    ANM_MUL_INT = 12,
    ANM_MUL_FLOAT = 13,
    ANM_DIV_INT = 14,
    ANM_DIV_FLOAT = 15,
    ANM_MOD_INT = 16,
    ANM_MOD_FLOAT = 17,
    ANM_ADD_INT_3 = 18,
    ANM_ADD_FLOAT_3 = 19,
    ANM_SUB_INT_3 = 20,
    ANM_SUB_FLOAT_3 = 21,
    ANM_MUL_INT_3 = 22,
    ANM_MUL_FLOAT_3 = 23,
    ANM_DIV_INT_3 = 24,
    ANM_DIV_FLOAT_3 = 25,
    ANM_MOD_INT_3 = 26,
    ANM_MOD_FLOAT_3 = 27,
    ANM_JMP_EQ_INT = 28,
    ANM_JMP_EQ_FLOAT = 29,
    ANM_JMP_NE_INT = 30,
    ANM_JMP_NE_FLOAT = 31,
    ANM_JMP_LT_INT = 32,
    ANM_JMP_LT_FLOAT = 33,
    ANM_JMP_LE_INT = 34,
    ANM_JMP_LE_FLOAT = 35,
    ANM_JMP_GT_INT = 36,
    ANM_JMP_GT_FLOAT = 37,
    ANM_JMP_GE_INT = 38,
    ANM_JMP_GE_FLOAT = 39,
    ANM_RAND_INT = 40,
    ANM_RAND_FLOAT = 41,
    ANM_SIN = 42,
    ANM_COS = 43,
    ANM_TAN = 44,
    ANM_ACOS = 45,
    ANM_ATAN = 46,
    ANM_NORMALIZE_ANGLE = 47,
    ANM_SET_POS = 48,
    ANM_SET_ROT = 49,
    ANM_SET_SCALE = 50,
    ANM_SET_ALPHA = 51,
    ANM_SET_COLOR = 52,
    ANM_SET_ANGULAR_VEL = 53,
    ANM_SET_SCALE_GROWTH = 54,
    ANM_FADE_ALPHA_TO_ZERO = 55,
    ANM_INTERP_POS = 56,
    ANM_INTERP_COLOR = 57,
    ANM_INTERP_ALPHA = 58,
    ANM_INTERP_ROT = 59,
    ANM_INTERP_SCALE = 60,
    ANM_FLIP_X = 61,
    ANM_FLIP_Y = 62,
    ANM_WAIT_INTERRUPT = 63,
    ANM_INTERRUPT_LABEL = 64,
    ANM_SET_ANCHOR = 65,
    ANM_SET_BLEND = 66,
    ANM_SET_DRAW_TYPE = 67,
    ANM_SET_LAYER = 68,
    ANM_HIDE_AND_WAIT = 69,
    ANM_SET_SCROLL_X = 70,
    ANM_SET_SCROLL_Y = 71,
    ANM_SET_VISIBLE = 72,
    ANM_SET_FLAG_11 = 73,
    ANM_SET_SCROLL_OFFSET = 74,
    ANM_WAIT = 75,
    ANM_SET_COLOR2 = 76,
    ANM_SET_ALPHA2 = 77,
    ANM_INTERP_COLOR2 = 78,
    ANM_INTERP_ALPHA2 = 79,
    ANM_SET_FLAG_15 = 80,
    ANM_RETURN_INTERRUPT = 81,
    ANM_SET_FLAG_27 = 82,
    ANM_BAKE_OFFSET = 83,
    ANM_ALLOC_STRIP = 84,
    ANM_SET_FLAG_28 = 85,
    ANM_SET_IGNORE_SPEED = 86,
    ANM_SET_REPLAY_RNG = 87,
    ANM_SPAWN_PRIMARY_BACK = 88,
    ANM_SET_FLAG_31 = 89,
    ANM_SPAWN_SECONDARY_BACK = 90,
    ANM_SPAWN_PRIMARY_FRONT = 91,
    ANM_SPAWN_SECONDARY_FRONT = 92
};

enum AnmFlagBits {
    ANM_FLAG_SCALED = 0x8,
    ANM_FLAG_FLIP_X = 0x200,
    ANM_FLAG_FLIP_Y = 0x400
};

enum AnmDrawType {
    ANM_DRAW_STRIP = 9,
    ANM_DRAW_RING = 10
};

// The PC is byte-addressed. Keep the calculation at the use site: extra
// inlined functions can change the x87 operand order in the strip loop.
#define INSTRUCTION_AT(base, byte_offset) ((AnmInstr*)((char*)(base) + (byte_offset)))

static __forceinline void AttachChild(AnmVm* vm, AnmHandle* handle) {
    AnmVm* child = Anm_Resolve(handle);
    List_InsertAfter(&vm->node, &child->node);
    child->position2 = vm->position;
    child->offset = vm->offset;
}

static __forceinline Float3 operator+(const Float3& a, const Float3& b) {
    return Float3(a.x + b.x, a.y + b.y, a.z + b.z);
}
static __forceinline Float3& operator+=(Float3& a, const Float3& b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

#pragma code_seg(".text$0043ee30_fn")
int __stdcall AnmVm::Tick(AnmVm* vm) {
    if (vm->pc == 0) return 1;
    if (vm->paused) return 0;

    // Sample the speed override once; opcode 86 changes it for later ticks.
    float saved_speed = g_game_speed;
    if (vm->f29) g_game_speed = 1.0f;
    AnmInstr* ins;
    if (vm->pending_interrupt != 0) goto dispatch_interrupt;

    // break consumes this instruction. A taken jump installs its own PC and
    // continues here to check the target's timestamp before executing it.
    while ((ins = vm->pc)->time <= vm->time.current) {
        switch (ins->id) {
        case ANM_SCRIPT_END:
        case ANM_DELETE:
            vm->visible = 0;
            // Fall through: ANM_STOP ends the script without changing visibility.
        case ANM_STOP:
            vm->pc = 0;
            g_game_speed = saved_speed;
            return 1;
        case ANM_SET_IGNORE_SPEED:
            vm->f29 = READ_INT(0);
            break;

        // Spawn on either list, front or back, and inherit position and offset.
        case ANM_SPAWN_PRIMARY_BACK: {
            AnmHandle handle;
            Anm_CreatePrimaryBack(vm->anm, &handle, READ_INT(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case ANM_SPAWN_PRIMARY_FRONT: {
            AnmHandle handle;
            Anm_CreatePrimaryFront(vm->anm, &handle, READ_INT(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case ANM_SPAWN_SECONDARY_BACK: {
            AnmHandle handle;
            Anm_CreateSecondaryBack(vm->anm, &handle, READ_INT(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case ANM_SPAWN_SECONDARY_FRONT: {
            AnmHandle handle;
            Anm_CreateSecondaryFront(vm->anm, &handle, READ_INT(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }

        case ANM_SET_SPRITE:
            vm->visible = 1;
            vm->anm->SetSprite(vm, READ_INT(0));
            vm->sprite_time = vm->time.current;
            break;
        case ANM_SET_SCALE:
            vm->scale.x = READ_FLOAT(0);
            vm->scale.y = READ_FLOAT(1);
            vm->scaled = 1;
            break;
        case ANM_SET_ALPHA:
            vm->alpha = READ_INT(0);
            break;
        case ANM_SET_COLOR:
            vm->red = READ_INT(0);
            vm->green = READ_INT(1);
            vm->blue = READ_INT(2);
            break;
        case ANM_SET_ALPHA2:
            vm->alpha2 = READ_INT(0);
            break;
        case ANM_SET_COLOR2:
            vm->red2 = READ_INT(0);
            vm->green2 = READ_INT(1);
            vm->blue2 = READ_INT(2);
            break;

        // The target is a byte offset from the script base, paired with a frame.
        case ANM_JMP:
            vm->time.Set(ins->i[1]);
            vm->pc = INSTRUCTION_AT(vm->script, ins->i[0]);
            continue;
        case ANM_JMP_DEC:
            --*INT_DEST_PTR();
            // Test through the read path after writing the destination.
            if (READ_INT(0) > 0) {
                vm->time.Set(ins->i[2]);
                vm->pc = INSTRUCTION_AT(vm->script, ins->i[1]);
                continue;
            }
            break;

        // Toggle the flip bit and mark the scale dirty in the same flag word.
        // MATCH: retail writes the updated flag word both before and after negating scale.
        case ANM_FLIP_X: {
            unsigned int f = vm->flags ^ ANM_FLAG_FLIP_X | ANM_FLAG_SCALED;
            vm->flags = f;
            vm->scale.x = vm->scale.x * -1.0f;
            vm->flags = f;
            break;
        }
        case ANM_FLIP_Y: {
            unsigned int f = vm->flags ^ ANM_FLAG_FLIP_Y | ANM_FLAG_SCALED;
            vm->flags = f;
            vm->scale.y = vm->scale.y * -1.0f;
            vm->flags = f;
            break;
        }
        case ANM_SET_ROT:
            vm->rotation.x = READ_FLOAT(0);
            vm->rotation.y = READ_FLOAT(1);
            vm->rotation.z = READ_FLOAT(2);
            vm->rotated = 1;
            break;
        case ANM_SET_ANGULAR_VEL:
            vm->angular_velocity.x = READ_FLOAT(0);
            vm->angular_velocity.y = READ_FLOAT(1);
            vm->angular_velocity.z = READ_FLOAT(2);
            vm->rotated = 1;
            break;
        case ANM_SET_SCALE_GROWTH:
            vm->scale_growth.x = READ_FLOAT(0);
            vm->scale_growth.y = READ_FLOAT(1);
            break;
        case ANM_FADE_ALPHA_TO_ZERO:
            vm->StartAlpha(READ_INT(1), 0, vm->alpha, ins->b[0]);
            break;
        case ANM_SET_BLEND:
            vm->blend = ins->i[0];
            break;
        case ANM_SET_POS:
            if (!vm->alt_position)
                vm->position = Float3(READ_FLOAT(0), READ_FLOAT(1), READ_FLOAT(2));
            else
                vm->position2 = Float3(READ_FLOAT(0), READ_FLOAT(1), READ_FLOAT(2));
            break;

        case ANM_NOP:
        case ANM_INTERRUPT_LABEL:
            break;
        case ANM_WAIT:
            vm->time.Decrement(READ_INT(0));
            break;

        case ANM_HIDE_AND_WAIT:
            vm->visible = 0;
            // Fall through to the same wait as ANM_WAIT_INTERRUPT, now hidden.
        case ANM_WAIT_INTERRUPT:
            if (vm->pending_interrupt == 0) {
                vm->stopped = 1;
                // Keep the PC here. Back up one tick before the common
                // frame update, which still animates the VM and ticks time.
                vm->time.Advance(-1.0f);
                goto update_frame;
            }
        // Entry also jumps here if an interrupt was pending before fetch.
        dispatch_interrupt: {
            AnmInstr* cursor = vm->script;
            AnmInstr* fallback = 0;
            // First exact label wins; otherwise use the last -1 label seen.
            for (;;) {
                if (cursor->id == ANM_INTERRUPT_LABEL && vm->pending_interrupt == cursor->i[0]) break;
                if (cursor->id == ANM_SCRIPT_END) break;
                if (cursor->id == ANM_INTERRUPT_LABEL && cursor->i[0] == -1) fallback = cursor;
                cursor = INSTRUCTION_AT(cursor, cursor->size);
            }
            vm->pending_interrupt = 0;
            vm->stopped = 0;
            if (cursor->id != ANM_INTERRUPT_LABEL) {
                if (fallback == 0) {
                    vm->time.Advance(-1.0f);
                    goto update_frame;
                }
                cursor = fallback;
            }
            // Save the interrupted instruction itself (not its successor).
            // The handler starts just after the label, on the label's frame.
            vm->saved_time = vm->time;
            vm->saved_pc = vm->pc;
            vm->time.Set(cursor->time);
            vm->pc = INSTRUCTION_AT(cursor, cursor->size);
            vm->visible = 1;
            continue;
        }
        case ANM_RETURN_INTERRUPT:
            vm->time = vm->saved_time;
            vm->pc = vm->saved_pc;
            continue;

        case ANM_SET_VISIBLE:
            vm->visible = ins->i[0];
            break;
        case ANM_SET_ANCHOR:
            vm->scroll_x_mode = ins->w[0];
            vm->scroll_y_mode = ins->w[1];
            break;
        case ANM_SET_SCROLL_X:
            vm->uv_scroll_speed.x = READ_FLOAT(0);
            break;
        case ANM_SET_SCROLL_Y:
            vm->uv_scroll_speed.y = READ_FLOAT(0);
            break;
        case ANM_SET_FLAG_11:
            vm->f11 = ins->i[0];
            break;
        case ANM_SET_SCROLL_OFFSET:
            vm->f13 = ins->i[0];
            break;
        case ANM_SET_FLAG_31:
            vm->f31 = ins->i[0];
            break;

        // Arm interpolators now; their first evaluation is in the frame update.
        case ANM_INTERP_POS:
            vm->position_interp.end_time = READ_INT(0);
            vm->position_interp.control_1 = g_zero_vector;
            vm->position_interp.control_2 = g_zero_vector;
            vm->position_interp.mode = ins->i[1];
            if (!vm->alt_position)
                vm->position_interp.initial = vm->position;
            else
                vm->position_interp.initial = vm->position2;
            vm->position_interp.goal = Float3(READ_FLOAT(2), READ_FLOAT(3), READ_FLOAT(4));
            vm->position_interp.Restart();
            break;
        case ANM_INTERP_COLOR: {
            Rgb from;
            from.b = vm->blue;
            from.g = vm->green;
            from.r = vm->red;
            Rgb to(READ_INT(2), READ_INT(3), READ_INT(4));
            vm->StartColor(&from.b, &to.b, READ_INT(0), ins->b[4]);
            break;
        }
        case ANM_INTERP_ALPHA:
            vm->StartAlpha(READ_INT(0), ins->b[4], vm->alpha, READ_INT(2));
            break;
        case ANM_INTERP_COLOR2: {
            Rgb from;
            from.b = vm->blue2;
            from.g = vm->green2;
            from.r = vm->red2;
            Rgb to(READ_INT(2), READ_INT(3), READ_INT(4));
            vm->StartColor2(&from.b, &to.b, READ_INT(0), ins->b[4]);
            break;
        }
        case ANM_INTERP_ALPHA2:
            vm->StartAlpha2(READ_INT(0), ins->b[4], vm->alpha2, READ_INT(2));
            break;
        case ANM_INTERP_ROT: {
            Float3 goal(READ_FLOAT(2), READ_FLOAT(3), READ_FLOAT(4));
            vm->rotation_interp.end_time = READ_INT(0);
            vm->rotation_interp.control_1 = g_zero_vector;
            vm->rotation_interp.control_2 = g_zero_vector;
            vm->rotation_interp.mode = ins->i[1];
            vm->rotation_interp.initial = vm->rotation;
            vm->rotation_interp.goal = goal;
            vm->rotation_interp.Restart();
            vm->rotated = 1;
            break;
        }
        case ANM_INTERP_SCALE: {
            Float2 goal(READ_FLOAT(2), READ_FLOAT(3));
            int time = READ_INT(0);
            vm->StartScale(time, ins->b[4], &vm->scale, &goal);
            vm->scaled = 1;
            break;
        }

        case ANM_SET_DRAW_TYPE:
            vm->type = ins->i[0];
            if (vm->type == ANM_DRAW_RING) vm->InitRing();
            break;
        case ANM_BAKE_OFFSET:
            vm->position = vm->offset;
            vm->offset.x = 0.0f;
            vm->offset.y = 0.0f;
            vm->offset.z = 0.0f;
            break;
        case ANM_ALLOC_STRIP:
            vm->type = ANM_DRAW_STRIP;
            vm->strip = (AnmVertex*)malloc(READ_INT(0) * sizeof(AnmVertex) * 2);
            break;

        // Assignment, then three-operand arithmetic: slot 0 = slot 1 op slot 2.
        case ANM_SET_INT: {
            int value = READ_INT(1);
            *INT_DEST_PTR() = value;
            break;
        }
        case ANM_SET_FLOAT: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = value;
            break;
        }
        case ANM_ADD_INT_3: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a + b;
            break;
        }
        case ANM_ADD_FLOAT_3: {
            float a = READ_FLOAT(1);
            float b = READ_FLOAT(2);
            *FLOAT_DEST_PTR() = a + b;
            break;
        }
        case ANM_SUB_INT_3: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a - b;
            break;
        }
        case ANM_SUB_FLOAT_3: {
            float a = READ_FLOAT(1);
            float b = READ_FLOAT(2);
            *FLOAT_DEST_PTR() = a - b;
            break;
        }
        case ANM_MUL_INT_3: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a * b;
            break;
        }
        case ANM_MUL_FLOAT_3: {
            float a = READ_FLOAT(1);
            float b = READ_FLOAT(2);
            *FLOAT_DEST_PTR() = a * b;
            break;
        }
        case ANM_DIV_INT_3: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a / b;
            break;
        }
        case ANM_DIV_FLOAT_3: {
            float a = READ_FLOAT(1);
            float b = READ_FLOAT(2);
            *FLOAT_DEST_PTR() = a / b;
            break;
        }
        case ANM_MOD_INT_3: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a % b;
            break;
        }
        case ANM_MOD_FLOAT_3: {
            // Both float remainder forms read the divisor before the dividend.
            float b = READ_FLOAT(2);
            float a = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)fmod(a, b);
            break;
        }

        // In-place forms: slot 0 is both the input and the destination.
        case ANM_ADD_INT: {
            int value = READ_INT(1);
            *INT_DEST_PTR() += value;
            break;
        }
        case ANM_ADD_FLOAT: {
            float value = READ_FLOAT(1);
            float* target = FLOAT_DEST_PTR();
            *target = *target + value;
            break;
        }
        case ANM_SUB_INT: {
            int value = READ_INT(1);
            *INT_DEST_PTR() -= value;
            break;
        }
        case ANM_SUB_FLOAT: {
            float value = READ_FLOAT(1);
            float* target = FLOAT_DEST_PTR();
            *target = *target - value;
            break;
        }
        case ANM_MUL_INT: {
            int value = READ_INT(1);
            *INT_DEST_PTR() *= value;
            break;
        }
        case ANM_MUL_FLOAT: {
            float value = READ_FLOAT(1);
            float* target = FLOAT_DEST_PTR();
            *target = *target * value;
            break;
        }
        case ANM_DIV_INT: {
            int value = READ_INT(1);
            *INT_DEST_PTR() /= value;
            break;
        }
        case ANM_DIV_FLOAT: {
            float value = READ_FLOAT(1);
            float* target = FLOAT_DEST_PTR();
            *target = *target / value;
            break;
        }
        case ANM_MOD_INT: {
            int value = READ_INT(1);
            *INT_DEST_PTR() %= value;
            break;
        }
        case ANM_MOD_FLOAT: {
            float b = READ_FLOAT(1);
            float a = READ_FLOAT(0);
            *FLOAT_DEST_PTR() = (float)fmod(a, b);
            break;
        }

        // RNG selection is per VM; the remaining cases here are unary math.
        case ANM_RAND_INT:
            *INT_DEST_PTR() = vm->f30 ? g_replay_rng.NextModulo(READ_INT(1))
                                     : g_effect_rng.NextModulo(READ_INT(1));
            break;
        case ANM_RAND_FLOAT: {
            float value = vm->f30 ? READ_FLOAT(1) * g_replay_rng.NextFloat()
                                  : READ_FLOAT(1) * g_effect_rng.NextFloat();
            *FLOAT_DEST_PTR() = value;
            break;
        }
        case ANM_SIN: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)sin(value);
            break;
        }
        case ANM_COS: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)cos(value);
            break;
        }
        case ANM_TAN: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)tan(value);
            break;
        }
        case ANM_ACOS: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)acos(value);
            break;
        }
        case ANM_ATAN: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)atan(value);
            break;
        }
        case ANM_NORMALIZE_ANGLE: {
            float value = READ_FLOAT(0);
            *FLOAT_DEST_PTR() = Angle_NormalizeSum(value, 0.0f);
            break;
        }

        // These settings take the literal low byte, not a resolved integer.
        case ANM_SET_FLAG_28: vm->f28 = ins->b[0]; break;
        case ANM_SET_LAYER: vm->layer = ins->b[0]; break;
        case ANM_SET_FLAG_15: vm->f15 = ins->b[0]; break;
        case ANM_SET_FLAG_27: vm->f27 = ins->b[0]; break;
        case ANM_SET_REPLAY_RNG: vm->f30 = ins->b[0]; break;

        // Compare slots 0 and 1. Every taken branch shares the offset/frame
        // tail in ANM_JMP_GE_FLOAT; a failed comparison consumes just this instruction.
        case ANM_JMP_EQ_INT: {
            int a = READ_INT(0);
            if (a == READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_EQ_FLOAT: {
            float a = READ_FLOAT(0);
            if (a == READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_NE_INT: {
            int a = READ_INT(0);
            if (a != READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_NE_FLOAT: {
            float a = READ_FLOAT(0);
            if (a != READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_LT_INT: {
            int a = READ_INT(0);
            if (a < READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_LT_FLOAT: {
            float a = READ_FLOAT(0);
            if (a < READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_LE_INT: {
            int a = READ_INT(0);
            if (a <= READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_LE_FLOAT: {
            float a = READ_FLOAT(0);
            if (a <= READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_GT_INT: {
            int a = READ_INT(0);
            if (a > READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_GT_FLOAT: {
            float a = READ_FLOAT(0);
            if (a > READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_GE_INT: {
            int a = READ_INT(0);
            if (a >= READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case ANM_JMP_GE_FLOAT: {
            float a = READ_FLOAT(0);
            if (a >= READ_FLOAT(1)) {
            take_comparison_jump:
                vm->time.Set(ins->i[3]);
                vm->pc = INSTRUCTION_AT(vm->script, ins->i[2]);
                continue;
            }
            break;
        }
        }
        vm->pc = INSTRUCTION_AT(ins, ins->size);
    }
    goto update_frame;
update_frame:
    // A future timestamp, a wait, and an unhandled interrupt all reach this
    // update. Apply motion before interpolation overwrites active channels.
    if (vm->angular_velocity.x != 0.0f) {
        vm->rotation.x = Angle_NormalizeSum(vm->rotation.x, g_game_speed * vm->angular_velocity.x);
        vm->rotated = 1;
    }
    if (vm->angular_velocity.y != 0.0f) {
        vm->rotation.y = Angle_NormalizeSum(vm->rotation.y, g_game_speed * vm->angular_velocity.y);
        vm->rotated = 1;
    }
    if (vm->angular_velocity.z != 0.0f) {
        vm->rotation.z = Angle_NormalizeSum(vm->rotation.z, g_game_speed * vm->angular_velocity.z);
        vm->rotated = 1;
    }
    if (vm->scale_growth.y != 0.0f) {
        vm->scale.y += g_game_speed * vm->scale_growth.y;
        vm->scaled = 1;
    }
    if (vm->scale_growth.x != 0.0f) {
        vm->scale.x += g_game_speed * vm->scale_growth.x;
        vm->scaled = 1;
        vm->rotated = 1;
    }

    // Wrap each UV component by at most one texture width/height per frame.
    vm->uv_scroll.x += g_game_speed * vm->uv_scroll_speed.x;
    if (vm->uv_scroll.x >= 1.0f)
        vm->uv_scroll.x -= 1.0f;
    else if (vm->uv_scroll.x < 0.0f)
        vm->uv_scroll.x += 1.0f;
    vm->uv_scroll.y += g_game_speed * vm->uv_scroll_speed.y;
    if (vm->uv_scroll.y >= 1.0f)
        vm->uv_scroll.y -= 1.0f;
    else if (vm->uv_scroll.y < 0.0f)
        vm->uv_scroll.y += 1.0f;
    if (vm->f13) {
        vm->offset.x += g_scroll_step.x;
        vm->offset.y += g_scroll_step.y;
        vm->offset.z += g_scroll_step.z;
    }

    if (vm->position_interp.end_time != 0) {
        if (!vm->alt_position)
            vm->position = vm->position_interp.Evaluate();
        else
            vm->position2 = vm->position_interp.Evaluate();
    }
    if (vm->color_interp.end_time != 0) {
        Int3 color = vm->color_interp.Evaluate();
        vm->red = color.b;
        vm->green = color.g;
        vm->blue = color.r;
    }
    if (vm->alpha_interp.end_time != 0) vm->alpha = vm->alpha_interp.Evaluate();
    if (vm->scale_interp.end_time != 0) {
        vm->scale = vm->scale_interp.Evaluate();
        vm->scaled = 1;
    }
    if (vm->rotation_interp.end_time != 0) {
        vm->rotation = vm->rotation_interp.Evaluate();
        vm->rotated = 1;
    }
    if (vm->color2_interp.end_time != 0) {
        Int3 color = vm->color2_interp.Evaluate();
        vm->red2 = color.b;
        vm->green2 = color.g;
        vm->blue2 = color.r;
    }
    if (vm->alpha2_interp.end_time != 0) vm->alpha2 = vm->alpha2_interp.Evaluate();

    // Generate two vertices at each angle. The final pair repeats the first
    // positions at the ending V coordinate to close the strip's texture seam.
    if (vm->type == ANM_DRAW_STRIP) {
        int count = vm->int_vars[0];
        AnmVertex* vertex = vm->strip;
        float angle = vm->rotation.z;
        float v = 0.0f;
        float angle_step = 6.2831855f / (float)(count - 1);
        float v_step = (float)vm->int_vars[1] / (float)(count - 1);
        for (int i = 0; i < count - 1; ++i) {
            vertex->w = 1.0f;
            vertex->color = *(unsigned int*)&vm->blue;
            vertex->u = vm->sprite->u0 + vm->uv_scroll.x;
            vertex->v = v + vm->uv_scroll.y;
            vertex->SetPolar(angle, vm->scale.x * 0.5f + vm->scale.y);
            vertex->position.z = 0.0f;
            vertex->position += vm->offset + vm->position;
            ++vertex;
            vertex->w = 1.0f;
            vertex->color = *(unsigned int*)&vm->blue;
            vertex->u = vm->sprite->u1 + vm->uv_scroll.x;
            vertex->v = v + vm->uv_scroll.y;
            vertex->SetPolar(angle, vm->scale.y - vm->scale.x * 0.5f);
            vertex->position.z = 0.0f;
            vertex->position += vm->offset + vm->position;
            ++vertex;
            v += v_step;
            angle = Angle_NormalizeSum(angle, angle_step);
        }
        vertex[0] = vm->strip[0];
        vertex[0].v = v + vm->uv_scroll.y;
        vertex[1] = vm->strip[1];
        vertex[1].v = v + vm->uv_scroll.y;
    }

    // Keep the VM's speed override in effect through the final clock tick.
    vm->time.Tick();
    g_game_speed = saved_speed;
    return 0;
}
#pragma code_seg()

#undef READ_INT
#undef READ_FLOAT
#undef INT_DEST_PTR
#undef FLOAT_DEST_PTR
#undef INSTRUCTION_AT

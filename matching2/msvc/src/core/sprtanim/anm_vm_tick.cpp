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

#define SCRIPT_END_OPCODE (-1)
#define INTERRUPT_LABEL_OPCODE 64
#define STRIP_DRAW_TYPE 9
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
        case SCRIPT_END_OPCODE:
        case 1:
            vm->visible = 0;
            // Fall through: case 2 ends the script without changing visibility.
        case 2:
            vm->pc = 0;
            g_game_speed = saved_speed;
            return 1;
        case 86:
            vm->f29 = READ_INT(0);
            break;

        // Spawn on either list, front or back, and inherit position and offset.
        case 88: {
            AnmHandle handle;
            Anm_CreatePrimaryBack(vm->anm, &handle, READ_INT(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case 91: {
            AnmHandle handle;
            Anm_CreatePrimaryFront(vm->anm, &handle, READ_INT(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case 90: {
            AnmHandle handle;
            Anm_CreateSecondaryBack(vm->anm, &handle, READ_INT(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case 92: {
            AnmHandle handle;
            Anm_CreateSecondaryFront(vm->anm, &handle, READ_INT(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }

        case 3:
            vm->visible = 1;
            vm->anm->SetSprite(vm, READ_INT(0));
            vm->sprite_time = vm->time.current;
            break;
        case 50:
            vm->scale.x = READ_FLOAT(0);
            vm->scale.y = READ_FLOAT(1);
            vm->scaled = 1;
            break;
        case 51:
            vm->alpha = READ_INT(0);
            break;
        case 52:
            vm->red = READ_INT(0);
            vm->green = READ_INT(1);
            vm->blue = READ_INT(2);
            break;
        case 77:
            vm->alpha2 = READ_INT(0);
            break;
        case 76:
            vm->red2 = READ_INT(0);
            vm->green2 = READ_INT(1);
            vm->blue2 = READ_INT(2);
            break;

        // The target is a byte offset from the script base, paired with a frame.
        case 4:
            vm->time.Set(ins->i[1]);
            vm->pc = INSTRUCTION_AT(vm->script, ins->i[0]);
            continue;
        case 5:
            --*INT_DEST_PTR();
            // Test through the read path after writing the destination.
            if (READ_INT(0) > 0) {
                vm->time.Set(ins->i[2]);
                vm->pc = INSTRUCTION_AT(vm->script, ins->i[1]);
                continue;
            }
            break;

        // Toggle the flip bit and mark the scale dirty in the same flag word.
        case 61: {
            unsigned int f = vm->flags ^ 0x200 | 8;
            vm->flags = f;
            vm->scale.x = vm->scale.x * -1.0f;
            vm->flags = f;
            break;
        }
        case 62: {
            unsigned int f = vm->flags ^ 0x400 | 8;
            vm->flags = f;
            vm->scale.y = vm->scale.y * -1.0f;
            vm->flags = f;
            break;
        }
        case 49:
            vm->rotation.x = READ_FLOAT(0);
            vm->rotation.y = READ_FLOAT(1);
            vm->rotation.z = READ_FLOAT(2);
            vm->rotated = 1;
            break;
        case 53:
            vm->angular_velocity.x = READ_FLOAT(0);
            vm->angular_velocity.y = READ_FLOAT(1);
            vm->angular_velocity.z = READ_FLOAT(2);
            vm->rotated = 1;
            break;
        case 54:
            vm->scale_growth.x = READ_FLOAT(0);
            vm->scale_growth.y = READ_FLOAT(1);
            break;
        case 55:
            vm->StartAlpha(READ_INT(1), 0, vm->alpha, ins->b[0]);
            break;
        case 66:
            vm->blend = ins->i[0];
            break;
        case 48:
            if (!vm->alt_position)
                vm->position = Float3(READ_FLOAT(0), READ_FLOAT(1), READ_FLOAT(2));
            else
                vm->position2 = Float3(READ_FLOAT(0), READ_FLOAT(1), READ_FLOAT(2));
            break;

        case 0:
        case INTERRUPT_LABEL_OPCODE:
            break;
        case 75:
            vm->time.Decrement(READ_INT(0));
            break;

        case 69:
            vm->visible = 0;
            // Fall through to the same wait as case 63, now hidden.
        case 63:
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
                if (cursor->id == INTERRUPT_LABEL_OPCODE && vm->pending_interrupt == cursor->i[0]) break;
                if (cursor->id == SCRIPT_END_OPCODE) break;
                if (cursor->id == INTERRUPT_LABEL_OPCODE && cursor->i[0] == -1) fallback = cursor;
                cursor = INSTRUCTION_AT(cursor, cursor->size);
            }
            vm->pending_interrupt = 0;
            vm->stopped = 0;
            if (cursor->id != INTERRUPT_LABEL_OPCODE) {
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
        case 81:
            vm->time = vm->saved_time;
            vm->pc = vm->saved_pc;
            continue;

        case 72:
            vm->visible = ins->i[0];
            break;
        case 65:
            vm->scroll_x_mode = ins->w[0];
            vm->scroll_y_mode = ins->w[1];
            break;
        case 70:
            vm->uv_scroll_speed.x = READ_FLOAT(0);
            break;
        case 71:
            vm->uv_scroll_speed.y = READ_FLOAT(0);
            break;
        case 73:
            vm->f11 = ins->i[0];
            break;
        case 74:
            vm->f13 = ins->i[0];
            break;
        case 89:
            vm->f31 = ins->i[0];
            break;

        // Arm interpolators now; their first evaluation is in the frame update.
        case 56:
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
        case 57: {
            Rgb from;
            from.b = vm->blue;
            from.g = vm->green;
            from.r = vm->red;
            Rgb to(READ_INT(2), READ_INT(3), READ_INT(4));
            vm->StartColor(&from.b, &to.b, READ_INT(0), ins->b[4]);
            break;
        }
        case 58:
            vm->StartAlpha(READ_INT(0), ins->b[4], vm->alpha, READ_INT(2));
            break;
        case 78: {
            Rgb from;
            from.b = vm->blue2;
            from.g = vm->green2;
            from.r = vm->red2;
            Rgb to(READ_INT(2), READ_INT(3), READ_INT(4));
            vm->StartColor2(&from.b, &to.b, READ_INT(0), ins->b[4]);
            break;
        }
        case 79:
            vm->StartAlpha2(READ_INT(0), ins->b[4], vm->alpha2, READ_INT(2));
            break;
        case 59: {
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
        case 60: {
            Float2 goal(READ_FLOAT(2), READ_FLOAT(3));
            int time = READ_INT(0);
            vm->StartScale(time, ins->b[4], &vm->scale, &goal);
            vm->scaled = 1;
            break;
        }

        case 67:
            vm->type = ins->i[0];
            if (vm->type == 10) vm->InitRing();
            break;
        case 83:
            vm->position = vm->offset;
            vm->offset.x = 0.0f;
            vm->offset.y = 0.0f;
            vm->offset.z = 0.0f;
            break;
        case 84:
            vm->type = STRIP_DRAW_TYPE;
            vm->strip = (AnmVertex*)malloc(READ_INT(0) * sizeof(AnmVertex) * 2);
            break;

        // Assignment, then three-operand arithmetic: slot 0 = slot 1 op slot 2.
        case 6: {
            int value = READ_INT(1);
            *INT_DEST_PTR() = value;
            break;
        }
        case 7: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = value;
            break;
        }
        case 18: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a + b;
            break;
        }
        case 19: {
            float a = READ_FLOAT(1);
            float b = READ_FLOAT(2);
            *FLOAT_DEST_PTR() = a + b;
            break;
        }
        case 20: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a - b;
            break;
        }
        case 21: {
            float a = READ_FLOAT(1);
            float b = READ_FLOAT(2);
            *FLOAT_DEST_PTR() = a - b;
            break;
        }
        case 22: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a * b;
            break;
        }
        case 23: {
            float a = READ_FLOAT(1);
            float b = READ_FLOAT(2);
            *FLOAT_DEST_PTR() = a * b;
            break;
        }
        case 24: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a / b;
            break;
        }
        case 25: {
            float a = READ_FLOAT(1);
            float b = READ_FLOAT(2);
            *FLOAT_DEST_PTR() = a / b;
            break;
        }
        case 26: {
            int a = READ_INT(1);
            int b = READ_INT(2);
            *INT_DEST_PTR() = a % b;
            break;
        }
        case 27: {
            // Both float remainder forms read the divisor before the dividend.
            float b = READ_FLOAT(2);
            float a = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)fmod(a, b);
            break;
        }

        // In-place forms: slot 0 is both the input and the destination.
        case 8: {
            int value = READ_INT(1);
            *INT_DEST_PTR() += value;
            break;
        }
        case 9: {
            float value = READ_FLOAT(1);
            float* target = FLOAT_DEST_PTR();
            *target = *target + value;
            break;
        }
        case 10: {
            int value = READ_INT(1);
            *INT_DEST_PTR() -= value;
            break;
        }
        case 11: {
            float value = READ_FLOAT(1);
            float* target = FLOAT_DEST_PTR();
            *target = *target - value;
            break;
        }
        case 12: {
            int value = READ_INT(1);
            *INT_DEST_PTR() *= value;
            break;
        }
        case 13: {
            float value = READ_FLOAT(1);
            float* target = FLOAT_DEST_PTR();
            *target = *target * value;
            break;
        }
        case 14: {
            int value = READ_INT(1);
            *INT_DEST_PTR() /= value;
            break;
        }
        case 15: {
            float value = READ_FLOAT(1);
            float* target = FLOAT_DEST_PTR();
            *target = *target / value;
            break;
        }
        case 16: {
            int value = READ_INT(1);
            *INT_DEST_PTR() %= value;
            break;
        }
        case 17: {
            float b = READ_FLOAT(1);
            float a = READ_FLOAT(0);
            *FLOAT_DEST_PTR() = (float)fmod(a, b);
            break;
        }

        // RNG selection is per VM; the remaining cases here are unary math.
        case 40:
            *INT_DEST_PTR() = vm->f30 ? g_replay_rng.NextModulo(READ_INT(1))
                                     : g_effect_rng.NextModulo(READ_INT(1));
            break;
        case 41: {
            float value = vm->f30 ? READ_FLOAT(1) * g_replay_rng.NextFloat()
                                  : READ_FLOAT(1) * g_effect_rng.NextFloat();
            *FLOAT_DEST_PTR() = value;
            break;
        }
        case 42: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)sin(value);
            break;
        }
        case 43: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)cos(value);
            break;
        }
        case 44: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)tan(value);
            break;
        }
        case 45: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)acos(value);
            break;
        }
        case 46: {
            float value = READ_FLOAT(1);
            *FLOAT_DEST_PTR() = (float)atan(value);
            break;
        }
        case 47: {
            float value = READ_FLOAT(0);
            *FLOAT_DEST_PTR() = Angle_NormalizeSum(value, 0.0f);
            break;
        }

        // These settings take the literal low byte, not a resolved integer.
        case 85: vm->f28 = ins->b[0]; break;
        case 68: vm->layer = ins->b[0]; break;
        case 80: vm->f15 = ins->b[0]; break;
        case 82: vm->f27 = ins->b[0]; break;
        case 87: vm->f30 = ins->b[0]; break;

        // Compare slots 0 and 1. Every taken branch shares the offset/frame
        // tail in case 39; a failed comparison consumes just this instruction.
        case 28: {
            int a = READ_INT(0);
            if (a == READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case 29: {
            float a = READ_FLOAT(0);
            if (a == READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case 30: {
            int a = READ_INT(0);
            if (a != READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case 31: {
            float a = READ_FLOAT(0);
            if (a != READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case 32: {
            int a = READ_INT(0);
            if (a < READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case 33: {
            float a = READ_FLOAT(0);
            if (a < READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case 34: {
            int a = READ_INT(0);
            if (a <= READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case 35: {
            float a = READ_FLOAT(0);
            if (a <= READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case 36: {
            int a = READ_INT(0);
            if (a > READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case 37: {
            float a = READ_FLOAT(0);
            if (a > READ_FLOAT(1)) goto take_comparison_jump;
            break;
        }
        case 38: {
            int a = READ_INT(0);
            if (a >= READ_INT(1)) goto take_comparison_jump;
            break;
        }
        case 39: {
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
    if (vm->type == STRIP_DRAW_TYPE) {
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
#undef SCRIPT_END_OPCODE
#undef INTERRUPT_LABEL_OPCODE
#undef STRIP_DRAW_TYPE
#undef INSTRUCTION_AT

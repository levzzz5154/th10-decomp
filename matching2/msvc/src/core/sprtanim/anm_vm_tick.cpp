// Equivalent recovery of the ANM VM tick at 0x0043EE30. The default build
// compiles this into the executable once tools/matching/equivalence.py has
// checked that it differs from the exact bytes only as recorded in
// build_support/layout/equivalent/anm_vm_tick.json. The inline assembly in
// build_support/exact/core/sprtanim/anm_vm_tick.cpp supplies those exact bytes and `make EXACT=1`.
#include "th10/runtime/core/sprtanim/anm_vm_tick.hpp"
#pragma intrinsic(sin, cos, tan, acos, atan, fmod, memcpy)

#define IARG(n) ((ins->var_mask & (1 << (n))) ? vm->IntVar(ins->i[n]) : ins->i[n])
#define FARG(n) ((ins->var_mask & (1 << (n))) ? vm->FloatVar(ins->f[n]) : ins->f[n])
#define IREF Anm_IntRef(&ins->i[0], vm, 0, ins->var_mask)
#define FREF Anm_FloatRef(vm, 0, &ins->f[0], ins->var_mask)

static __forceinline void AttachChild(AnmVm* vm, AnmHandle* handle) {
    AnmVm* child = Anm_Resolve(handle);
    List_InsertAfter(&vm->node, &child->node);
    child->position2 = vm->position;
    child->offset = vm->offset;
}

static __forceinline Float3 operator+(const Float3& a, const Float3& b) { return Float3(a.x + b.x, a.y + b.y, a.z + b.z); }
int __stdcall AnmVm::Tick(AnmVm* vm) {
    if (vm->pc == 0) return 1;
    if (vm->paused) return 0;
    float saved_speed = g_game_speed;
    if (vm->f29) g_game_speed = 1.0f;
    AnmInstr* ins;
    if (vm->pending_interrupt != 0) goto interrupt;
    while ((ins = vm->pc)->time <= vm->time.current) {
        switch (ins->id) {
        case -1:
        case 1:
            vm->visible = 0;
        case 2:
            vm->pc = 0;
            g_game_speed = saved_speed;
            return 1;
        case 86:
            vm->f29 = IARG(0);
            break;
        case 88: {
            AnmHandle handle;
            Anm_CreatePrimaryBack(vm->anm, &handle, IARG(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case 91: {
            AnmHandle handle;
            Anm_CreatePrimaryFront(vm->anm, &handle, IARG(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case 90: {
            AnmHandle handle;
            Anm_CreateSecondaryBack(vm->anm, &handle, IARG(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case 92: {
            AnmHandle handle;
            Anm_CreateSecondaryFront(vm->anm, &handle, IARG(0), vm->layer);
            AttachChild(vm, &handle);
            break;
        }
        case 3:
            vm->visible = 1;
            vm->anm->SetSprite(vm, IARG(0));
            vm->sprite_time = vm->time.current;
            break;
        case 50:
            vm->scale.x = FARG(0);
            vm->scale.y = FARG(1);
            vm->scaled = 1;
            break;
        case 51:
            vm->alpha = IARG(0);
            break;
        case 52:
            vm->red = IARG(0);
            vm->green = IARG(1);
            vm->blue = IARG(2);
            break;
        case 77:
            vm->alpha2 = IARG(0);
            break;
        case 76:
            vm->red2 = IARG(0);
            vm->green2 = IARG(1);
            vm->blue2 = IARG(2);
            break;
        case 4:
            vm->time.Set(ins->i[1]);
            vm->pc = (AnmInstr*)((char*)vm->script + ins->i[0]);
            continue;
        case 5:
            --*IREF;
            if (IARG(0) > 0) {
                vm->time.Set(ins->i[2]);
                vm->pc = (AnmInstr*)((char*)vm->script + ins->i[1]);
                continue;
            }
            break;
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
            vm->rotation.x = FARG(0);
            vm->rotation.y = FARG(1);
            vm->rotation.z = FARG(2);
            vm->rotated = 1;
            break;
        case 53:
            vm->angular_velocity.x = FARG(0);
            vm->angular_velocity.y = FARG(1);
            vm->angular_velocity.z = FARG(2);
            vm->rotated = 1;
            break;
        case 54:
            vm->scale_growth.x = FARG(0);
            vm->scale_growth.y = FARG(1);
            break;
        case 55:
            vm->StartAlpha(IARG(1), 0, vm->alpha, ins->b[0]);
            break;
        case 66:
            vm->blend = ins->i[0];
            break;
        case 48:
            if (!vm->alt_position)
                vm->position = Float3(FARG(0), FARG(1), FARG(2));
            else
                vm->position2 = Float3(FARG(0), FARG(1), FARG(2));
            break;
        case 0:
        case 64:
            break;
        case 75:
            vm->time.Decrement(IARG(0));
            break;
        case 69:
            vm->visible = 0;
        case 63:
            if (vm->pending_interrupt == 0) {
                vm->stopped = 1;
                // Both stop paths step the timer back themselves; the late
                // tail merge joins them, with retail's receiver-then-push order.
                vm->time.Advance(-1.0f);
                goto done;
            }
        interrupt: {
            AnmInstr* cursor = vm->script;
            AnmInstr* fallback = 0;
            for (;;) {
                if (cursor->id == 64 && vm->pending_interrupt == cursor->i[0]) break;
                if (cursor->id == -1) break;
                if (cursor->id == 64 && cursor->i[0] == -1) fallback = cursor;
                cursor = (AnmInstr*)((char*)cursor + cursor->size);
            }
            vm->pending_interrupt = 0;
            vm->stopped = 0;
            if (cursor->id != 64) {
                if (fallback == 0) {
                    vm->time.Advance(-1.0f);
                    goto done;
                }
                cursor = fallback;
            }
            vm->saved_time = vm->time;
            vm->saved_pc = vm->pc;
            vm->time.Set(cursor->time);
            vm->pc = (AnmInstr*)((char*)cursor + cursor->size);
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
            vm->uv_scroll_speed.x = FARG(0);
            break;
        case 71:
            vm->uv_scroll_speed.y = FARG(0);
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
        case 56:
            vm->position_interp.end_time = IARG(0);
            vm->position_interp.control_1 = g_zero_vector;
            vm->position_interp.control_2 = g_zero_vector;
            vm->position_interp.mode = ins->i[1];
            if (!vm->alt_position)
                vm->position_interp.initial = vm->position;
            else
                vm->position_interp.initial = vm->position2;
            vm->position_interp.goal = Float3(FARG(2), FARG(3), FARG(4));
            vm->position_interp.Restart();
            break;
        case 57: {
            Rgb from;
            from.b = vm->blue;
            from.g = vm->green;
            from.r = vm->red;
            Rgb to(IARG(2), IARG(3), IARG(4));
            vm->StartColor(&from.b, &to.b, IARG(0), ins->b[4]);
            break;
        }
        case 58:
            vm->StartAlpha(IARG(0), ins->b[4], vm->alpha, IARG(2));
            break;
        case 78: {
            Rgb from;
            from.b = vm->blue2;
            from.g = vm->green2;
            from.r = vm->red2;
            Rgb to(IARG(2), IARG(3), IARG(4));
            vm->StartColor2(&from.b, &to.b, IARG(0), ins->b[4]);
            break;
        }
        case 79:
            vm->StartAlpha2(IARG(0), ins->b[4], vm->alpha2, IARG(2));
            break;
        case 59: {
            Float3 goal(FARG(2), FARG(3), FARG(4));
            vm->rotation_interp.end_time = IARG(0);
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
            float gy = FARG(3);
            int time;
            if (ins->var_mask & 1)
                time = vm->IntVar(ins->i[0]);
            else
                time = ins->i[0];
            float gx = FARG(2);
            Float2 goal(gx, gy);
            vm->StartScale(&vm->scale, &goal, time, ins->b[4]);
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
            vm->type = 9;
            vm->strip = (AnmVertex*)malloc(IARG(0) * sizeof(AnmVertex) * 2);
            break;
        case 6: {
            int value = IARG(1);
            *IREF = value;
            break;
        }
        case 7: {
            float value = FARG(1);
            *FREF = value;
            break;
        }
        case 18: {
            int a = IARG(1);
            int b = IARG(2);
            *IREF = a + b;
            break;
        }
        case 19: {
            float a = FARG(1);
            float b = FARG(2);
            *FREF = a + b;
            break;
        }
        case 20: {
            int a = IARG(1);
            int b = IARG(2);
            *IREF = a - b;
            break;
        }
        case 21: {
            float a = FARG(1);
            float b = FARG(2);
            *FREF = a - b;
            break;
        }
        case 22: {
            int a = IARG(1);
            int b = IARG(2);
            *IREF = a * b;
            break;
        }
        case 23: {
            float a = FARG(1);
            float b = FARG(2);
            *FREF = a * b;
            break;
        }
        case 24: {
            int a = IARG(1);
            int b = IARG(2);
            *IREF = a / b;
            break;
        }
        case 25: {
            float a = FARG(1);
            float b = FARG(2);
            *FREF = a / b;
            break;
        }
        case 26: {
            int a = IARG(1);
            int b = IARG(2);
            *IREF = a % b;
            break;
        }
        case 27: {
            float b = FARG(2);
            float a = FARG(1);
            *FREF = (float)fmod(a, b);
            break;
        }
        case 8: {
            int value = IARG(1);
            *IREF += value;
            break;
        }
        case 9: {
            float value = FARG(1);
            float* target = FREF;
            *target = *target + value;
            break;
        }
        case 10: {
            int value = IARG(1);
            *IREF -= value;
            break;
        }
        case 11: {
            float value = FARG(1);
            float* target = FREF;
            *target = *target - value;
            break;
        }
        case 12: {
            int value = IARG(1);
            *IREF *= value;
            break;
        }
        case 13: {
            float value = FARG(1);
            float* target = FREF;
            *target = *target * value;
            break;
        }
        case 14: {
            int value = IARG(1);
            *IREF /= value;
            break;
        }
        case 15: {
            float value = FARG(1);
            float* target = FREF;
            *target = *target / value;
            break;
        }
        case 16: {
            int value = IARG(1);
            *IREF %= value;
            break;
        }
        case 17: {
            float b = FARG(1);
            float a = FARG(0);
            *FREF = (float)fmod(a, b);
            break;
        }
        case 40:
            *IREF = vm->f30 ? g_replay_rng.NextModulo(IARG(1)) : g_effect_rng.NextModulo(IARG(1));
            break;
        case 41: {
            float value = vm->f30 ? FARG(1) * g_replay_rng.NextFloat() : FARG(1) * g_effect_rng.NextFloat();
            *FREF = value;
            break;
        }
        case 42: {
            float value = FARG(1);
            *FREF = (float)sin(value);
            break;
        }
        case 43: {
            float value = FARG(1);
            *FREF = (float)cos(value);
            break;
        }
        case 44: {
            float value = FARG(1);
            *FREF = (float)tan(value);
            break;
        }
        case 45: {
            float value = FARG(1);
            *FREF = (float)acos(value);
            break;
        }
        case 46: {
            float value = FARG(1);
            *FREF = (float)atan(value);
            break;
        }
        case 47: {
            float value = FARG(0);
            *FREF = Angle_NormalizeSum(value, 0.0f);
            break;
        }
        case 85:
            vm->f28 = ins->b[0];
            break;
        case 68:
            vm->layer = ins->b[0];
            break;
        case 80:
            vm->f15 = ins->b[0];
            break;
        case 82:
            vm->f27 = ins->b[0];
            break;
        case 87:
            vm->f30 = ins->b[0];
            break;
        case 28: {
            int a = IARG(0);
            if (a == IARG(1)) goto jump;
            break;
        }
        case 29: {
            float a = FARG(0);
            if (a == FARG(1)) goto jump;
            break;
        }
        case 30: {
            int a = IARG(0);
            if (a != IARG(1)) goto jump;
            break;
        }
        case 31: {
            float a = FARG(0);
            if (a != FARG(1)) goto jump;
            break;
        }
        case 32: {
            int a = IARG(0);
            if (a < IARG(1)) goto jump;
            break;
        }
        case 33: {
            float a = FARG(0);
            if (a < FARG(1)) goto jump;
            break;
        }
        case 34: {
            int a = IARG(0);
            if (a <= IARG(1)) goto jump;
            break;
        }
        case 35: {
            float a = FARG(0);
            if (a <= FARG(1)) goto jump;
            break;
        }
        case 36: {
            int a = IARG(0);
            if (a > IARG(1)) goto jump;
            break;
        }
        case 37: {
            float a = FARG(0);
            if (a > FARG(1)) goto jump;
            break;
        }
        case 38: {
            int a = IARG(0);
            if (a >= IARG(1)) goto jump;
            break;
        }
        case 39: {
            float a = FARG(0);
            if (a >= FARG(1)) {
            jump:
                vm->time.Set(ins->i[3]);
                vm->pc = (AnmInstr*)((char*)vm->script + ins->i[2]);
                continue;
            }
            break;
        }
        }
        vm->pc = (AnmInstr*)((char*)ins + ins->size);
    }
    goto done;
done:
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
    if (vm->type == 9) {
        int i = vm->int_vars[0] - 1;
        AnmVertex* vertex = vm->strip;
        float angle = vm->rotation.z;
        float v = 0.0f;
        float angle_step = 6.2831855f / (float)(vm->int_vars[0] - 1);
        float v_step = (float)vm->int_vars[1] / (float)(vm->int_vars[0] - 1);
        for (; i > 0; --i) {
            vertex->w = 1.0f;
            vertex->color = *(unsigned int*)&vm->blue;
            vertex->u = vm->sprite->u0 + vm->uv_scroll.x;
            vertex->v = v + vm->uv_scroll.y;
            vertex->SetPolar(angle, vm->scale.x * 0.5f + vm->scale.y);
            vertex->z = 0.0f;
            {
                Float3 origin = vm->offset + vm->position;
                vertex->position_xy.x += origin.x;
                vertex->position_xy.y += origin.y;
                vertex->z = origin.z;
            }
            ++vertex;
            vertex->w = 1.0f;
            vertex->color = *(unsigned int*)&vm->blue;
            vertex->u = vm->sprite->u1 + vm->uv_scroll.x;
            vertex->v = v + vm->uv_scroll.y;
            vertex->SetPolar(angle, vm->scale.y - vm->scale.x * 0.5f);
            vertex->z = 0.0f;
            {
                Float3 origin = vm->offset + vm->position;
                vertex->position_xy.x += origin.x;
                vertex->position_xy.y += origin.y;
                vertex->z = origin.z;
            }
            ++vertex;
            v += v_step;
            angle = Angle_NormalizeSum(angle, angle_step);
        }
        vertex[0] = vm->strip[0];
        vertex[0].v = v + vm->uv_scroll.y;
        vertex[1] = vm->strip[1];
        vertex[1].v = v + vm->uv_scroll.y;
    }
    vm->time.Tick();
    g_game_speed = saved_speed;
    return 0;
}

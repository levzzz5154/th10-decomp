// =============================================================================
// anm_vm_tick.cpp - ANM script VM per-frame execution
// =============================================================================
#include "th10/script/anm_vm_tick.hpp"

namespace {

const unsigned char* InstructionAt(const unsigned char* pc,
                                   AnmInstructionView* view) {
    view->opcode = static_cast<unsigned short>(pc[0] | (pc[1] << 8));
    view->size = static_cast<unsigned short>(pc[2] | (pc[3] << 8));
    view->time = static_cast<short>(pc[4] | (pc[5] << 8));
    view->arg_mask = pc[6];
    view->args = pc + 8;
    return pc + view->size;
}

int IntArg(const AnmVmHooks* hooks, AnmVmState* vm,
           const AnmInstructionView* ins, int index) {
    return hooks->read_int_arg(hooks->context, vm, ins->args + index * 4,
                               (ins->arg_mask >> index) & 1);
}

float FloatArg(const AnmVmHooks* hooks, AnmVmState* vm,
               const AnmInstructionView* ins, int index) {
    return hooks->read_float_arg(hooks->context, vm, ins->args + index * 4,
                                 (ins->arg_mask >> index) & 1);
}

float* PositionOf(AnmVmState* vm) {
    return (vm->flags & ANM_FLAG_ANCHOR_ALT_POS) != 0 ? vm->alt_position
                                                      : vm->position;
}

// Interrupt dispatch (retail LAB_0043F62D): find the opcode-0x40 handler for
// the pending id (or the -1 catch-all), save the register file, and jump.
void DispatchInterrupt(AnmVmState* vm, const AnmVmHooks* hooks) {
    int id = vm->pending_interrupt;
    const unsigned char* handler = 0;
    const unsigned char* fallback = 0;
    short handler_time = 0;
    short fallback_time = 0;
    const unsigned char* cursor = vm->script_base;
    AnmInstructionView view;
    while (cursor != 0) {
        const unsigned char* next = InstructionAt(cursor, &view);
        if (view.opcode == 0xFFFF || view.size < 8)
            break;
        if (view.opcode == 0x40) {
            int label = static_cast<int>(view.args[0]) |
                        (static_cast<int>(view.args[1]) << 8) |
                        (static_cast<int>(view.args[2]) << 16) |
                        (static_cast<int>(view.args[3]) << 24);
            if (label == id) {
                handler = next;
                handler_time = view.time;
            } else if (label == -1 && fallback == 0) {
                fallback = next;
                fallback_time = view.time;
            }
        }
        cursor = next;
    }
    if (handler == 0) {
        handler = fallback;
        handler_time = fallback_time;
    }
    vm->pending_interrupt = 0;
    if (handler == 0) {
        if (id == 0)
            vm->flags |= ANM_FLAG_WAITING;
        hooks->set_time(hooks->context, vm, -1.0f);
        return;
    }
    vm->saved_time = vm->time;
    vm->saved_accumulator = vm->time_accumulator;
    vm->saved_previous_time = vm->previous_time;
    vm->saved_pc = vm->pc;
    hooks->set_time(hooks->context, vm, static_cast<float>(handler_time));
    vm->pc = handler;
    vm->flags |= ANM_FLAG_INTERRUPTED;
    vm->flags &= ~static_cast<unsigned int>(ANM_FLAG_WAITING);
}

} // namespace

// 0x0043EAC0 - AnmVm_ReadSpecialValue: resolve one script float reference.
// Ids 10000..0x2719 map to the VM float slots, 0x271A..0x271C are the RNG
// taps, 0x271D..0x271F read the live position, and 0x2720..0x2725 read the
// camera globals; anything else evaluates to the literal fallback.
float AnmVm_ReadSpecialValue(int id, float fallback,
                             const AnmSpecialValueHooks* hooks) {
    if (id >= ANM_VAR_FLOAT_BASE && id <= 0x2719)
        return hooks->vm_float_slots[id - ANM_VAR_FLOAT_BASE];
    switch (id) {
    case ANM_VAR_RAND_ANGLE:
        return hooks->rand_unit(hooks->context, hooks->alt_rng) * 6.2831853f;
    case ANM_VAR_RAND_SIGNED:
        return hooks->rand_signed(hooks->context);
    case ANM_VAR_RAND_UNIT:
        return hooks->rand_unit(hooks->context, hooks->alt_rng);
    case ANM_VAR_POS_X:
    case ANM_VAR_POS_Y:
    case ANM_VAR_POS_Z:
        return hooks->vm_position[id - ANM_VAR_POS_X];
    default:
        if (id >= ANM_VAR_CAMERA_BASE && id <= 0x2725)
            return hooks->camera_globals[id - ANM_VAR_CAMERA_BASE];
        return fallback;
    }
}

// 0x0043EE30 - AnmVm_Tick: run the VM for one frame. Handles the pending
// interrupt, executes every instruction whose timestamp has been reached
// (full opcode set 0x00..0x5C), then applies the per-frame velocity,
// rotation, scroll, interpolator, and ring-vertex updates before advancing
// the frame clock. Returns 1 when the script has ended.
int AnmVm_Tick(AnmVmState* vm, const AnmVmHooks* hooks) {
    if (vm->pc == 0)
        return 1;
    if ((vm->flags & ANM_FLAG_PAUSED) != 0)
        return 0;
    float speed = (vm->flags & ANM_FLAG_SPEED_OVERRIDE) != 0 ? 1.0f
                                                             : vm->speed;
    if (vm->pending_interrupt != 0)
        DispatchInterrupt(vm, hooks);
    bool hold_time = (vm->flags & ANM_FLAG_WAITING) != 0;

    int alt_rng = (vm->flags & ANM_FLAG_ALT_RNG) != 0;
    bool run = !hold_time;
    while (run && vm->pc != 0) {
        AnmInstructionView ins;
        const unsigned char* next = InstructionAt(vm->pc, &ins);
        if (static_cast<int>(ins.time) > vm->time)
            break; // per-frame update below
        switch (ins.opcode) {
        case 0xFFFF:
        case 1:
            vm->flags &= ~static_cast<unsigned int>(ANM_FLAG_INTERRUPTED);
            // fallthrough: retail case 2 ends the script
            [[fallthrough]];
        case 2:
            vm->pc = 0;
            return 1;
        case 3:
            vm->flags |= ANM_FLAG_INTERRUPTED;
            hooks->set_sprite(hooks->context, vm, IntArg(hooks, vm, &ins, 0));
            break;
        case 4: // absolute jump with time reload
            hooks->set_time(hooks->context, vm,
                            static_cast<float>(IntArg(hooks, vm, &ins, 1)));
            next = vm->script_base + IntArg(hooks, vm, &ins, 0);
            break;
        case 5: { // decrement-and-jump
            int* counter = hooks->int_var_slot(hooks->context, vm,
                                               IntArg(hooks, vm, &ins, 2));
            *counter -= 1;
            if (*counter > 0) {
                hooks->set_time(hooks->context, vm,
                                static_cast<float>(IntArg(hooks, vm, &ins,
                                                          1)));
                next = vm->script_base + IntArg(hooks, vm, &ins, 0);
            }
            break;
        }
        case 6: *hooks->int_var_slot(hooks->context, vm,
                                     IntArg(hooks, vm, &ins, 0)) =
                    IntArg(hooks, vm, &ins, 1);
            break;
        case 7: *hooks->float_var_slot(hooks->context, vm,
                                       IntArg(hooks, vm, &ins, 0)) =
                    FloatArg(hooks, vm, &ins, 1);
            break;
        case 8: *hooks->int_var_slot(hooks->context, vm,
                                     IntArg(hooks, vm, &ins, 0)) +=
                    IntArg(hooks, vm, &ins, 1);
            break;
        case 9: *hooks->float_var_slot(hooks->context, vm,
                                       IntArg(hooks, vm, &ins, 0)) +=
                    FloatArg(hooks, vm, &ins, 1);
            break;
        case 0xA: *hooks->int_var_slot(hooks->context, vm,
                                       IntArg(hooks, vm, &ins, 0)) -=
                      IntArg(hooks, vm, &ins, 1);
            break;
        case 0xB: *hooks->float_var_slot(hooks->context, vm,
                                         IntArg(hooks, vm, &ins, 0)) -=
                      FloatArg(hooks, vm, &ins, 1);
            break;
        case 0xC: *hooks->int_var_slot(hooks->context, vm,
                                       IntArg(hooks, vm, &ins, 0)) *=
                      IntArg(hooks, vm, &ins, 1);
            break;
        case 0xD: *hooks->float_var_slot(hooks->context, vm,
                                         IntArg(hooks, vm, &ins, 0)) *=
                      FloatArg(hooks, vm, &ins, 1);
            break;
        case 0xE: {
            int divisor = IntArg(hooks, vm, &ins, 1);
            if (divisor != 0)
                *hooks->int_var_slot(hooks->context, vm,
                                     IntArg(hooks, vm, &ins, 0)) /= divisor;
            break;
        }
        case 0xF: {
            float divisor = FloatArg(hooks, vm, &ins, 1);
            if (divisor != 0.0f)
                *hooks->float_var_slot(hooks->context, vm,
                                       IntArg(hooks, vm, &ins, 0)) /= divisor;
            break;
        }
        case 0x10: {
            int divisor = IntArg(hooks, vm, &ins, 1);
            if (divisor != 0)
                *hooks->int_var_slot(hooks->context, vm,
                                     IntArg(hooks, vm, &ins, 0)) %= divisor;
            break;
        }
        case 0x11: {
            float divisor = FloatArg(hooks, vm, &ins, 1);
            float* slot = hooks->float_var_slot(hooks->context, vm,
                                                IntArg(hooks, vm, &ins, 0));
            if (divisor != 0.0f)
                *slot = *slot - divisor *
                        static_cast<float>(static_cast<int>(*slot / divisor));
            break;
        }
        // Binary three-operand forms: dest = a OP b.
        case 0x12: case 0x14: case 0x16: case 0x18: case 0x1A: {
            int a = IntArg(hooks, vm, &ins, 1);
            int b = IntArg(hooks, vm, &ins, 2);
            int value = ins.opcode == 0x12 ? a + b
                       : ins.opcode == 0x14 ? a - b
                       : ins.opcode == 0x16 ? a * b
                       : ins.opcode == 0x18 ? (b != 0 ? a / b : a)
                                            : (b != 0 ? a % b : a);
            *hooks->int_var_slot(hooks->context, vm,
                                 IntArg(hooks, vm, &ins, 0)) = value;
            break;
        }
        case 0x13: case 0x15: case 0x17: case 0x19: case 0x1B: {
            float a = FloatArg(hooks, vm, &ins, 1);
            float b = FloatArg(hooks, vm, &ins, 2);
            float value = ins.opcode == 0x13 ? a + b
                        : ins.opcode == 0x15 ? a - b
                        : ins.opcode == 0x17 ? a * b
                        : ins.opcode == 0x19 ? (b != 0.0f ? a / b : a)
                        : (b != 0.0f
                               ? a - b * static_cast<float>(
                                             static_cast<int>(a / b))
                               : a);
            *hooks->float_var_slot(hooks->context, vm,
                                   IntArg(hooks, vm, &ins, 0)) = value;
            break;
        }
        // Conditional jumps: args are (target, time, a, b).
        case 0x1C: case 0x1E: case 0x20: case 0x22: case 0x24: case 0x26: {
            int a = IntArg(hooks, vm, &ins, 2);
            int b = IntArg(hooks, vm, &ins, 3);
            bool taken = ins.opcode == 0x1C ? a == b
                       : ins.opcode == 0x1E ? a != b
                       : ins.opcode == 0x20 ? a < b
                       : ins.opcode == 0x22 ? a <= b
                       : ins.opcode == 0x24 ? a > b
                                            : a >= b;
            if (taken) {
                hooks->set_time(hooks->context, vm,
                                static_cast<float>(IntArg(hooks, vm, &ins,
                                                          1)));
                next = vm->script_base + IntArg(hooks, vm, &ins, 0);
            }
            break;
        }
        case 0x1D: case 0x1F: case 0x21: case 0x23: case 0x25: case 0x27: {
            float a = FloatArg(hooks, vm, &ins, 2);
            float b = FloatArg(hooks, vm, &ins, 3);
            bool taken = ins.opcode == 0x1D ? a == b
                       : ins.opcode == 0x1F ? a != b
                       : ins.opcode == 0x21 ? a < b
                       : ins.opcode == 0x23 ? a <= b
                       : ins.opcode == 0x25 ? a > b
                                            : a >= b;
            if (taken) {
                hooks->set_time(hooks->context, vm,
                                static_cast<float>(IntArg(hooks, vm, &ins,
                                                          1)));
                next = vm->script_base + IntArg(hooks, vm, &ins, 0);
            }
            break;
        }
        case 0x28: { // rand int in [0, range)
            int range = IntArg(hooks, vm, &ins, 1);
            unsigned int raw = hooks->rand_u32(hooks->context, alt_rng);
            *hooks->int_var_slot(hooks->context, vm,
                                 IntArg(hooks, vm, &ins, 0)) =
                range != 0 ? static_cast<int>(raw % static_cast<unsigned>(
                                                       range))
                           : 0;
            break;
        }
        case 0x29:
            *hooks->float_var_slot(hooks->context, vm,
                                   IntArg(hooks, vm, &ins, 0)) =
                hooks->rand_float(hooks->context, alt_rng) *
                FloatArg(hooks, vm, &ins, 1);
            break;
        case 0x2A: case 0x2B: case 0x2C: case 0x2D: case 0x2E: case 0x2F: {
            float value = FloatArg(hooks, vm, &ins, 1);
            float* slot = hooks->float_var_slot(hooks->context, vm,
                                                IntArg(hooks, vm, &ins, 0));
            switch (ins.opcode) {
            case 0x2A: *slot = __builtin_sinf(value); break;
            case 0x2B: *slot = __builtin_cosf(value); break;
            case 0x2C: *slot = __builtin_tanf(value); break;
            case 0x2D: *slot = __builtin_acosf(value); break;
            case 0x2E: *slot = __builtin_atanf(value); break;
            default: *slot = hooks->wrap_angle(hooks->context, value); break;
            }
            break;
        }
        case 0x30: {
            float* position = PositionOf(vm);
            for (int axis = 0; axis < 3; ++axis)
                position[axis] = FloatArg(hooks, vm, &ins, axis);
            break;
        }
        case 0x31:
            for (int axis = 0; axis < 3; ++axis)
                vm->scale[axis] = FloatArg(hooks, vm, &ins, axis);
            vm->flags |= ANM_FLAG_DIRTY_SCALE;
            break;
        case 0x32:
            vm->growth[0] = FloatArg(hooks, vm, &ins, 0);
            vm->growth[1] = FloatArg(hooks, vm, &ins, 1);
            vm->flags |= ANM_FLAG_DIRTY_GROWTH;
            break;
        case 0x33:
            vm->color[3] = static_cast<unsigned char>(IntArg(hooks, vm, &ins,
                                                             0));
            break;
        case 0x34:
            for (int channel = 0; channel < 3; ++channel)
                vm->color[2 - channel] = static_cast<unsigned char>(
                    IntArg(hooks, vm, &ins, channel));
            break;
        case 0x35:
            for (int axis = 0; axis < 3; ++axis)
                vm->scale_velocity[axis] = FloatArg(hooks, vm, &ins, axis);
            break;
        case 0x36:
            vm->growth_velocity[0] = FloatArg(hooks, vm, &ins, 0);
            vm->growth_velocity[1] = FloatArg(hooks, vm, &ins, 1);
            break;
        case 0x38: { // position interpolation start
            Interp3F* interp = &vm->position_interp;
            float* position = PositionOf(vm);
            interp->duration = IntArg(hooks, vm, &ins, 0);
            interp->mode = IntArg(hooks, vm, &ins, 1);
            interp->elapsed = 0;
            for (int axis = 0; axis < 3; ++axis) {
                interp->start[axis] = position[axis];
                interp->target[axis] = FloatArg(hooks, vm, &ins, 2 + axis);
            }
            break;
        }
        case 0x39: { // color interpolation start
            Interp3I* interp = &vm->color_interp;
            interp->duration = IntArg(hooks, vm, &ins, 0);
            interp->mode = IntArg(hooks, vm, &ins, 1);
            interp->elapsed = 0;
            for (int channel = 0; channel < 3; ++channel) {
                interp->start[channel] = vm->color[channel];
                interp->target[channel] = IntArg(hooks, vm, &ins,
                                                 2 + channel);
            }
            break;
        }
        case 0x3A: { // alpha interpolation start
            Interp1I* interp = &vm->alpha_interp;
            interp->duration = IntArg(hooks, vm, &ins, 0);
            interp->mode = IntArg(hooks, vm, &ins, 1);
            interp->elapsed = 0;
            interp->start = vm->color[3];
            interp->target = IntArg(hooks, vm, &ins, 2);
            break;
        }
        case 0x3B: { // scale interpolation start
            Interp3F* interp = &vm->scale_interp;
            interp->duration = IntArg(hooks, vm, &ins, 0);
            interp->mode = IntArg(hooks, vm, &ins, 1);
            interp->elapsed = 0;
            for (int axis = 0; axis < 3; ++axis) {
                interp->start[axis] = vm->scale[axis];
                interp->target[axis] = FloatArg(hooks, vm, &ins, 2 + axis);
            }
            vm->flags |= ANM_FLAG_DIRTY_SCALE;
            break;
        }
        case 0x3C: { // growth interpolation start
            Interp2F* interp = &vm->growth_interp;
            interp->duration = IntArg(hooks, vm, &ins, 0);
            interp->mode = IntArg(hooks, vm, &ins, 1);
            interp->elapsed = 0;
            for (int axis = 0; axis < 2; ++axis) {
                interp->start[axis] = vm->growth[axis];
                interp->target[axis] = FloatArg(hooks, vm, &ins, 2 + axis);
            }
            vm->flags |= ANM_FLAG_DIRTY_GROWTH;
            break;
        }
        case 0x3D:
            vm->growth[0] *= 0.5f;
            vm->flags ^= 0x200u | ANM_FLAG_DIRTY_GROWTH;
            break;
        case 0x3E:
            vm->growth[1] *= 0.5f;
            vm->flags ^= 0x400u | ANM_FLAG_DIRTY_GROWTH;
            break;
        case 0x45:
            vm->flags &= ~static_cast<unsigned int>(ANM_FLAG_INTERRUPTED);
            [[fallthrough]];
        case 0x3F: // wait
            if (vm->pending_interrupt == 0) {
                vm->flags |= ANM_FLAG_WAITING;
                hooks->set_time(hooks->context, vm, -1.0f);
                next = vm->pc;
                hold_time = true;
                run = false;
            } else {
                DispatchInterrupt(vm, hooks);
                next = vm->pc;
            }
            break;
        case 0x40: // interrupt label: skipped during normal execution
            break;
        case 0x41:
            hooks->set_blend_bits(hooks->context, vm, 0xC0000u | 0x300000u,
                                  (static_cast<unsigned int>(
                                       IntArg(hooks, vm, &ins, 0)) << 0x12) |
                                  (static_cast<unsigned int>(
                                       IntArg(hooks, vm, &ins, 1)) << 0x14));
            break;
        case 0x42:
            hooks->set_blend_bits(hooks->context, vm, 0x30u,
                                  static_cast<unsigned int>(
                                      IntArg(hooks, vm, &ins, 0)) << 4);
            break;
        case 0x43: {
            unsigned int value = static_cast<unsigned int>(
                IntArg(hooks, vm, &ins, 0)) << 0x16;
            hooks->set_blend_bits(hooks->context, vm, 0x3C00000u, value);
            if ((vm->flags & 0x3C00000u) == 0x2800000u)
                hooks->start_ring_mode(hooks->context, vm);
            break;
        }
        case 0x44:
            vm->layer = IntArg(hooks, vm, &ins, 0);
            break;
        case 0x46:
            vm->rotation_speed_z = FloatArg(hooks, vm, &ins, 0);
            break;
        case 0x47:
            vm->rotation_speed_w = FloatArg(hooks, vm, &ins, 0);
            break;
        case 0x48: case 0x49: case 0x4A: case 0x50: case 0x52: case 0x55:
        case 0x56: case 0x57: case 0x59: { // single-bit flag writes
            static const struct { unsigned short opcode; int shift; }
                kBits[] = {{0x48, 0}, {0x49, 0xB}, {0x4A, 0xD}, {0x50, 0xF},
                           {0x52, 0x1B}, {0x55, 0x1C}, {0x56, 0x1D},
                           {0x57, 0x1E}, {0x59, 0x1F}};
            for (const auto& bit : kBits)
                if (bit.opcode == ins.opcode) {
                    unsigned int mask = 1u << bit.shift;
                    if (IntArg(hooks, vm, &ins, 0) != 0)
                        vm->flags |= mask;
                    else
                        vm->flags &= ~mask;
                }
            break;
        }
        case 0x4C:
            for (int channel = 0; channel < 3; ++channel)
                vm->color2[2 - channel] = static_cast<unsigned char>(
                    IntArg(hooks, vm, &ins, channel));
            break;
        case 0x4D:
            vm->color2[3] = static_cast<unsigned char>(
                IntArg(hooks, vm, &ins, 0));
            break;
        case 0x4E: { // color2 interpolation start
            Interp3I* interp = &vm->color2_interp;
            interp->duration = IntArg(hooks, vm, &ins, 0);
            interp->mode = IntArg(hooks, vm, &ins, 1);
            interp->elapsed = 0;
            for (int channel = 0; channel < 3; ++channel) {
                interp->start[channel] = vm->color2[channel];
                interp->target[channel] = IntArg(hooks, vm, &ins,
                                                 2 + channel);
            }
            break;
        }
        case 0x4F: { // alpha2 interpolation start
            Interp1I* interp = &vm->alpha2_interp;
            interp->duration = IntArg(hooks, vm, &ins, 0);
            interp->mode = IntArg(hooks, vm, &ins, 1);
            interp->elapsed = 0;
            interp->start = vm->color2[3];
            interp->target = IntArg(hooks, vm, &ins, 2);
            break;
        }
        case 0x51: // interrupt return: restore the saved register file
            vm->time = vm->saved_time;
            vm->time_accumulator = vm->saved_accumulator;
            vm->previous_time = vm->saved_previous_time;
            next = vm->saved_pc;
            vm->flags &= ~static_cast<unsigned int>(ANM_FLAG_INTERRUPTED);
            break;
        case 0x53:
            for (int axis = 0; axis < 3; ++axis) {
                vm->position[axis] += vm->velocity[axis];
                vm->velocity[axis] = 0.0f;
            }
            break;
        case 0x54: // switch to ring-vertex mode
            vm->flags = (vm->flags & 0xFE7FFFFFu) | ANM_FLAG_RING_MODE;
            hooks->start_ring_mode(hooks->context, vm);
            break;
        case 0x58: case 0x5A: case 0x5B: case 0x5C: {
            int variant = ins.opcode == 0x58 ? 0
                        : ins.opcode == 0x5A ? 2
                        : ins.opcode == 0x5B ? 1 : 3;
            hooks->spawn_child(hooks->context, vm, variant,
                               IntArg(hooks, vm, &ins, 0));
            break;
        }
        default:
            break;
        }
        vm->pc = next;
        if (vm->pc == 0)
            return 1;
    }

    // Per-frame update (retail LAB_00440E42).
    if (vm->scale_velocity[0] != 0.0f || vm->scale_velocity[1] != 0.0f ||
        vm->scale_velocity[2] != 0.0f) {
        for (int axis = 0; axis < 3; ++axis)
            vm->scale[axis] += vm->scale_velocity[axis] * speed;
        vm->flags |= ANM_FLAG_DIRTY_SCALE;
    }
    if (vm->growth_velocity[0] != 0.0f || vm->growth_velocity[1] != 0.0f) {
        vm->growth[0] += vm->growth_velocity[0] * speed;
        vm->growth[1] += vm->growth_velocity[1] * speed;
        vm->flags |= ANM_FLAG_DIRTY_GROWTH;
    }
    if (vm->rotation_speed_z != 0.0f)
        vm->rotation[2] = hooks->wrap_angle(
            hooks->context, vm->rotation[2] + vm->rotation_speed_z * speed);
    if (vm->rotation_speed_w != 0.0f)
        vm->rotation[1] = hooks->wrap_angle(
            hooks->context, vm->rotation[1] + vm->rotation_speed_w * speed);
    if ((vm->flags & ANM_FLAG_SCROLL) != 0 && hooks->scroll_delta != 0)
        for (int axis = 0; axis < 3; ++axis)
            vm->position[axis] += hooks->scroll_delta[axis];

    vm->position_interp.speed = speed;
    vm->scale_interp.speed = speed;
    if (vm->position_interp.duration > 0 || vm->position_interp.mode == 7 ||
        vm->position_interp.mode == 0x11) {
        Interp3F_Tick(&vm->position_interp);
        float* position = PositionOf(vm);
        for (int axis = 0; axis < 3; ++axis)
            position[axis] = vm->position_interp.position[axis];
    }
    if (vm->color_interp.duration > 0) {
        Interp3I_Tick(&vm->color_interp);
        for (int channel = 0; channel < 3; ++channel)
            vm->color[channel] = static_cast<unsigned char>(
                vm->color_interp.value[channel]);
    }
    if (vm->alpha_interp.duration > 0) {
        Interp1I_Tick(&vm->alpha_interp);
        vm->color[3] = static_cast<unsigned char>(vm->alpha_interp.value);
    }
    if (vm->growth_interp.duration > 0) {
        Interp2F_Tick(&vm->growth_interp);
        vm->growth[0] = vm->growth_interp.value[0];
        vm->growth[1] = vm->growth_interp.value[1];
        vm->flags |= ANM_FLAG_DIRTY_GROWTH;
    }
    if (vm->scale_interp.duration > 0) {
        Interp3F_Tick(&vm->scale_interp);
        for (int axis = 0; axis < 3; ++axis)
            vm->scale[axis] = vm->scale_interp.position[axis];
        vm->flags |= ANM_FLAG_DIRTY_SCALE;
    }
    if (vm->color2_interp.duration > 0) {
        Interp3I_Tick(&vm->color2_interp);
        for (int channel = 0; channel < 3; ++channel)
            vm->color2[channel] = static_cast<unsigned char>(
                vm->color2_interp.value[channel]);
    }
    if (vm->alpha2_interp.duration > 0) {
        Interp1I_Tick(&vm->alpha2_interp);
        vm->color2[3] = static_cast<unsigned char>(vm->alpha2_interp.value);
    }
    if ((vm->flags & ANM_FLAG_RING_MODE_MASK) == ANM_FLAG_RING_MODE)
        hooks->update_ring_vertices(hooks->context, vm);

    // Wait freezes the script clock but not the per-frame interpolators.
    if (hold_time)
        return 0;

    // Timer advance: fractional speeds accumulate; unit speed steps by one.
    vm->previous_time = vm->time;
    if (speed != 1.0f) {
        vm->time_accumulator += speed;
        vm->time = static_cast<int>(vm->time_accumulator);
    } else {
        vm->time += 1;
        vm->time_accumulator += 1.0f;
    }
    return 0;
}

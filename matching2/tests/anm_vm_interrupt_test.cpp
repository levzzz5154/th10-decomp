#include "th10/script/anm_vm_tick.hpp"

#include <cassert>
#include <cstring>

namespace {

float g_float_slot;

void Write16(unsigned char* out, unsigned int value) {
    out[0] = static_cast<unsigned char>(value);
    out[1] = static_cast<unsigned char>(value >> 8);
}

void Write32(unsigned char* out, int value) {
    std::memcpy(out, &value, sizeof(value));
}

unsigned char* Instruction(unsigned char* out, unsigned int opcode,
                           unsigned int size) {
    Write16(out, opcode);
    Write16(out + 2, size);
    return out + size;
}

} // namespace

int main() {
    unsigned char script[52] = {};
    unsigned char* cursor = script;
    cursor = Instruction(cursor, 0, 8);       // valid opcode, not terminator
    Write32(cursor + 8, 7);
    cursor = Instruction(cursor, 0x40, 12);    // interrupt label 7
    Write32(cursor + 8, 123);
    cursor = Instruction(cursor, 3, 12);       // set sprite 123
    cursor = Instruction(cursor, 1, 8);        // end handler
    Instruction(cursor, 0xFFFF, 0);            // real list terminator

    int integer_slot = 0;
    float scroll[3] = {};
    AnmVmHooks hooks = {};
    hooks.context = &integer_slot;
    hooks.read_int_arg = [](void*, AnmVmState*, const void* slot, int) {
        int value;
        std::memcpy(&value, slot, sizeof(value));
        return value;
    };
    hooks.read_float_arg = [](void*, AnmVmState*, const void* slot, int) {
        float value;
        std::memcpy(&value, slot, sizeof(value));
        return value;
    };
    hooks.int_var_slot = [](void* context, AnmVmState*, int) {
        return static_cast<int*>(context);
    };
    hooks.float_var_slot = [](void*, AnmVmState*, int) {
        return &g_float_slot;
    };
    hooks.set_sprite = [](void*, AnmVmState* vm, int sprite) {
        vm->sprite = sprite;
    };
    hooks.set_time = [](void*, AnmVmState* vm, float time) {
        vm->time = static_cast<int>(time);
        vm->time_accumulator = time;
    };
    hooks.rand_float = [](void*, int) { return 0.5f; };
    hooks.rand_u32 = [](void*, int) { return 0x80000000u; };
    hooks.wrap_angle = [](void*, float value) { return value; };
    hooks.start_ring_mode = [](void*, AnmVmState*) {};
    hooks.spawn_child = [](void*, AnmVmState*, int, int) {};
    hooks.update_ring_vertices = [](void*, AnmVmState*) {};
    hooks.set_blend_bits =
        [](void*, AnmVmState* vm, unsigned int mask, unsigned int value) {
            vm->flags = (vm->flags & ~mask) | (value & mask);
        };
    hooks.scroll_delta = scroll;

    AnmVmState vm = {};
    vm.script_base = script;
    vm.pc = script;
    vm.pending_interrupt = 7;
    vm.speed = 1.0f;
    assert(AnmVm_Tick(&vm, &hooks) == 1);
    assert(vm.sprite == 123);

    unsigned char waiting_script[52] = {};
    cursor = waiting_script;
    cursor = Instruction(cursor, 0x3F, 8);
    Write32(cursor + 8, 6);
    cursor = Instruction(cursor, 0x40, 12);
    Write32(cursor + 8, 55);
    cursor = Instruction(cursor, 3, 12);
    cursor = Instruction(cursor, 1, 8);
    Instruction(cursor, 0xFFFF, 0);

    vm = {};
    vm.script_base = waiting_script;
    vm.pc = waiting_script;
    vm.speed = 1.0f;
    assert(AnmVm_Tick(&vm, &hooks) == 0);
    assert((vm.flags & ANM_FLAG_WAITING) != 0);
    const unsigned char* waiting_pc = vm.pc;
    for (int frame = 0; frame < 180; ++frame) {
        assert(AnmVm_Tick(&vm, &hooks) == 0);
        assert(vm.pc == waiting_pc);
    }
    vm.pending_interrupt = 6;
    assert(AnmVm_Tick(&vm, &hooks) == 1);
    assert(vm.sprite == 55);

    unsigned char animated_wait_script[36] = {};
    cursor = animated_wait_script;
    unsigned char* alpha = cursor;
    cursor = Instruction(cursor, 0x3A, 20);
    Write32(alpha + 8, 10);
    Write32(alpha + 12, 0);
    Write32(alpha + 16, 255);
    cursor = Instruction(cursor, 0x3F, 8);
    Instruction(cursor, 0xFFFF, 0);

    vm = {};
    vm.script_base = animated_wait_script;
    vm.pc = animated_wait_script;
    vm.speed = 1.0f;
    assert(AnmVm_Tick(&vm, &hooks) == 0);
    waiting_pc = vm.pc;
    for (int frame = 0; frame < 15; ++frame) {
        assert(AnmVm_Tick(&vm, &hooks) == 0);
        assert(vm.pc == waiting_pc);
        assert(vm.time == -1);
    }
    assert(vm.color[3] == 255);
    // Destination ids must be decoded without first reading the variable.
    // Each VM owns its registers, including mixed integer/float reads.
    unsigned char variables[48] = {};
    Instruction(variables, 6, 16);
    variables[6] = 1;
    Write32(variables + 8, 10000);
    Write32(variables + 12, 41);
    Instruction(variables + 16, 7, 16);
    variables[22] = 1;
    const float float_id = 10004.0f, float_value = -12.75f;
    std::memcpy(variables + 24, &float_id, 4);
    std::memcpy(variables + 28, &float_value, 4);
    Instruction(variables + 32, 1, 8);
    hooks.int_var_slot = AnmVm_IntSlot;
    hooks.float_var_slot = AnmVm_FloatSlot;
    hooks.read_int_arg = AnmVm_ReadIntArg;
    vm = {};
    vm.pc = vm.script_base = variables;
    vm.integer_variables[0] = 123;
    assert(AnmVm_Tick(&vm, &hooks) == 1);
    assert(vm.integer_variables[0] == 41);
    assert(vm.float_variables[0] == -12.75f);
    int id = 10004;
    assert(AnmVm_ReadIntArg(0, &vm, &id, 1) == -12);
    AnmVmState other = {};
    assert(other.integer_variables[0] == 0 && other.float_variables[0] == 0);

    // Clear masks and unknown ids store into the instruction operand itself.
    variables[6] = 0;
    variables[22] = 0;
    vm.pc = variables;
    assert(AnmVm_Tick(&vm, &hooks) == 1);
    int written;
    std::memcpy(&written, variables + 8, 4);
    assert(written == 41);
    float written_float;
    std::memcpy(&written_float, variables + 24, 4);
    assert(written_float == float_value);
    variables[6] = 1;
    Write32(variables + 8, 12345);
    vm.pc = variables;
    assert(AnmVm_Tick(&vm, &hooks) == 1);
    std::memcpy(&written, variables + 8, 4);
    assert(written == 41);

    const float camera[] = {1, 2, 3, 4, 5, 6};
    AnmSpecialValueHooks special = {};
    special.vm_int_slots = vm.integer_variables;
    special.vm_float_slots = vm.float_variables;
    special.vm_position = vm.position;
    special.camera_globals = camera;
    special.rand_unit = [](void*, int alt) { return alt ? 0.75f : 0.25f; };
    special.rand_signed = [](void*, int alt) { return alt ? 0.5f : -0.5f; };
    assert(AnmVm_ReadSpecialValue(10000, 0, &special) == 41);
    assert(AnmVm_ReadSpecialValue(10004, 0, &special) == -12.75f);
    volatile float angle = AnmVm_ReadSpecialValue(10010, 0, &special);
    assert(angle > -1.5707965f && angle < -1.5707963f);
    assert(AnmVm_ReadSpecialValue(10011, 0, &special) == 0.25f);
    assert(AnmVm_ReadSpecialValue(10012, 0, &special) == -0.5f);
    special.alt_rng = 1;
    angle = AnmVm_ReadSpecialValue(10010, 0, &special);
    assert(angle > 1.5707963f && angle < 1.5707965f);
    assert(AnmVm_ReadSpecialValue(10011, 0, &special) == 0.75f);
    assert(AnmVm_ReadSpecialValue(10012, 0, &special) == 0.5f);
    for (int i = 0; i < 6; ++i)
        assert(AnmVm_ReadSpecialValue(10016 + i, 0, &special) == camera[i]);
    assert(AnmVm_ReadSpecialValue(999, 17.0f, &special) == 17.0f);

    Interp3F curve = {};
    curve.speed = 0.5f;
    curve.duration = 2;
    curve.mode = 8;
    curve.target[0] = 16;
    curve.velocity[0] = 8;
    curve.acceleration[0] = -8;
    assert(Interp3F_Tick(&curve) == 1);
    assert(curve.elapsed == 0 && curve.elapsed_fraction == 0.5f);
    assert(curve.position[0] == 4.0f); // Hermite at t=1/4
    assert(Interp3F_Tick(&curve) == 1 && curve.position[0] == 10.0f);
    assert(Interp3F_Tick(&curve) == 1);
    assert(Interp3F_Tick(&curve) == 0 && curve.position[0] == 16.0f);
    Interp3I channels = {};
    channels.speed = 1;
    channels.duration = 4;
    channels.start[0] = -3;
    channels.target[0] = 0;
    assert(Interp3I_Tick(&channels) == 1 && channels.value[0] == -3);
    Interp1I alpha_curve = {};
    alpha_curve.speed = 1;
    alpha_curve.duration = 4;
    alpha_curve.start = -3;
    alpha_curve.target = 0;
    assert(Interp1I_Tick(&alpha_curve) == 1 && alpha_curve.value == -2);
    channels = {};
    channels.speed = 1;
    channels.duration = 2;
    channels.mode = 8;
    channels.start[0] = channels.target[0] = 1;
    assert(Interp3I_Tick(&channels) == 1 && channels.value[0] == 0);
    alpha_curve = {};
    alpha_curve.speed = 1;
    alpha_curve.duration = 2;
    alpha_curve.mode = 8;
    alpha_curve.start = alpha_curve.target = 1;
    assert(Interp1I_Tick(&alpha_curve) == 1 && alpha_curve.value == 1);
    curve = {};
    curve.mode = 17;
    curve.start[0] = 10;
    curve.acceleration[0] = 2;
    curve.target[0] = 3;
    assert(Interp3F_Tick(&curve) == 1 && curve.position[0] == 12);
    assert(curve.acceleration[0] == 5);
    assert(Interp3F_Tick(&curve) == 1 && curve.position[0] == 17);
    return 0;
}

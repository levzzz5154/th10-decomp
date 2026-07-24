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
    return 0;
}

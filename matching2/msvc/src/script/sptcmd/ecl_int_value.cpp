// Resolve a supplied integer: immediate, frame-relative, popped or owned by the VM.
#include "th10/runtime/script/sptcmd/ecl_core_interpreter.hpp"

int EclVm::IntValue(int selector, int value) {
    if ((instr->mask & (1 << selector)) != 0) {
        if (value >= 0) {
            EclStack* frame = &stack;
            return *reinterpret_cast<int*>(&frame->data[frame->base + value]);
        } else if (value == -1) {
            stack.PopInt(&value);
            return value;
        } else {
            return owner->ResolveInt(value);
        }
    }
    return value;
}

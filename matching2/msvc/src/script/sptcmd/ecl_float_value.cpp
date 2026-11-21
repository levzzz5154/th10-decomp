// Resolve a supplied floating operand through the complete VM and its tagged stack.
#include "th10/runtime/script/sptcmd/ecl_core_interpreter.hpp"

__declspec(noinline) float EclVm::FloatValue(int selector, EclVm* vm, float value) {
    unsigned short mask = vm->instr->mask;
    if (mask & (1 << selector)) {
        if (value >= flt_0) {
            return *(float*)&vm->stack.data[vm->stack.base + (int)value];
        } else if (value == flt_neg1) {
            vm->stack.PopFloat(&value);
        } else {
            return vm->owner->ResolveFloat((int)value);
        }
    }
    return value;
}

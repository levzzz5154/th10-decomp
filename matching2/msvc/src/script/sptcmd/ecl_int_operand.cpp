// Read an integer operand of the current instruction, resolving indirect selectors.
#include "th10/runtime/script/sptcmd/ecl_core_interpreter.hpp"

int EclVm::IntOperand(int selector) {
    EclInstr* table = instr;
    unsigned short mask = table->mask;
    if ((mask & (1 << selector)) != 0) {
        int value = table->i[selector];
        if (value >= 0) {
            return *reinterpret_cast<int*>(&stack.data[stack.base + value]);
        } else if (value == -1) {
            int offset;
            if (stack.sp - 4 >= 0) {
                stack.sp -= 4;
                offset = stack.sp;
                selector = *reinterpret_cast<int*>(&stack.data[offset]);
                stack.sp -= 4;
                offset = stack.sp;
                if (stack.data[offset] == 'f')
                    return static_cast<int>(*reinterpret_cast<float*>(&selector));
            }
            return selector;
        } else {
            return owner->ResolveInt(value);
        }
    }
    return table->i[selector];
}

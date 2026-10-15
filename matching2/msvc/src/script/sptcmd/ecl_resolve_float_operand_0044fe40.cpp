// 0x0044FE40: resolve a float operand from its literal, frame displacement,
// tagged scratch value, or external variable. Native LTCG puts the VM in EAX
// and selector in ECX; the result remains in x87 until the caller consumes it.
// The underflow path keeps the original unwritten local slot. Initializing it
// changes the retail body; valid scratch reads pop a value word and tag word.
#include "th10/script/ecl_float_values.hpp"

#pragma code_seg(".text$01accessor")
float EclFloatVm::ResolveFloatOperand(int selector) {
    EclFloatOperandTable* operands = table;
    unsigned short mask = operands->indirect_mask;
    if (mask & (1 << selector)) {
        const float& displacement = operands->values[selector];
        if (displacement >= data_00470b04) {
            return *(float*)&stack.data[stack.frame_base + (int)displacement];
        } else if (displacement == data_00470b60) {
            union { int integer; float real; } value;
            if (stack.cursor - 4 >= 0) {
                stack.cursor -= 4;
                value.integer = *(int*)&stack.data[stack.cursor];
                stack.cursor -= 4;
                char tag = stack.data[stack.cursor];
                if (tag == 'f') return value.real;
                if (tag == 'i') return (float)value.integer;
            }
            return value.real;
        } else {
            return stack.context->ResolveFloat((int)displacement);
        }
    }
    return operands->values[selector];
}
#pragma code_seg()

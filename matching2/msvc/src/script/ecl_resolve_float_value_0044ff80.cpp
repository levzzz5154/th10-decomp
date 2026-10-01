// 0x0044FF80: resolve an already supplied float operand. An indirect operand
// denotes a frame displacement, -1 for a tagged scratch pop, or an external
// variable. Native LTCG puts the VM in EAX and selector in CL, preserving the
// float stack argument and RET 4. Integer-tagged values round to float in that
// argument slot before the final x87 load, as retail does.
#include "th10/script/ecl_float_values.hpp"

#pragma code_seg(".text$05value")
float EclFloatVm::ResolveFloatValue(int selector, float value) {
    unsigned short mask = table->indirect_mask;
    if (mask & (1 << selector)) {
        if (value >= data_00470b04) {
            return *(float*)&stack.data[stack.frame_base + (int)value];
        } else if (value == data_00470b60) {
            if (stack.cursor - 4 >= 0) {
                stack.cursor -= 4;
                *(int*)&value = *(int*)&stack.data[stack.cursor];
                stack.cursor -= 4;
                char tag = stack.data[stack.cursor];
                if (tag != 'f' && tag == 'i') value = (float)*(int*)&value;
            }
        } else {
            return stack.context->ResolveFloat((int)value);
        }
    }
    return value;
}
#pragma code_seg()

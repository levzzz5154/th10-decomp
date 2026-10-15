#include "th10/source_views/ecl_core_interpreter_exact_0.hpp"
#include "th10/source_views/ecl_core_interpreter_exact_1.hpp"
int __fastcall ECL_ResolveIntOperand_0044fdb0(
        int unused, EclFrame* frame, int selector) {
    EclOperandTable* table = frame->operand_table;
    unsigned short mask = table->indirect_mask;
    if ((mask & (1 << selector)) != 0) {
        int value = table->slots[selector];
        if (value >= 0) {
            return *(int*)&frame->stack.data[frame->stack.frame_base + value];
        } else if (value == -1) {
            int stack_offset;
            if (frame->stack.stack_pointer - 4 >= 0) {
                frame->stack.stack_pointer -= 4;
                stack_offset = frame->stack.stack_pointer;
                selector = *(int*)&frame->stack.data[stack_offset];
                frame->stack.stack_pointer -= 4;
                stack_offset = frame->stack.stack_pointer;
                if (frame->stack.data[stack_offset] == 'f') {
                    return (int)*(float*)&selector;
                }
            }
            return selector;
        } else {
            return frame->stack.context->ResolveSlot(value);
        }
    }
    return table->slots[selector];
}


#include "../../../include/th10/source_views/ecl_core_interpreter_exact_2.hpp"
#include "th10/source_views/ecl_core_interpreter_exact_0.hpp"
#include "th10/source_views/ecl_core_interpreter_exact_1.hpp"
#include "th10/source_views/ecl_core_interpreter_exact_2.hpp"
int __fastcall ECL_ResolveIntValue_0044ff00(int unused, EclFrame* frame, int selector, int value) {
    EclOperandTable* table = frame->operand_table;
    unsigned short mask = table->indirect_mask;
    int result = value;
    if ((mask & (1 << selector)) != 0) {
        if (value >= 0) {
            EclStack* stack = &frame->stack;
            result = *(int*)&stack->data[stack->frame_base + value];
        } else if (value == -1) {
            if (frame->stack.stack_pointer - 4 >= 0) {
                frame->stack.stack_pointer -= 4;
                int raw = *(int*)&frame->stack.data[frame->stack.stack_pointer];
                frame->stack.stack_pointer -= 4;
                float typed = *(float*)&raw;
                if (frame->stack.data[frame->stack.stack_pointer] == 0x66)
                    result = (int)typed;
                else
                    result = raw;
            }
        } else {
            result = frame->stack.context->ResolveSlot(value);
        }
    }
    return result;
}


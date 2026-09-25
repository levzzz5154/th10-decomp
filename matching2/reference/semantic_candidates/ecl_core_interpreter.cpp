// Readable models removed from matching2/msvc/src/script/ecl_core_interpreter.cpp: they compiled but did
// not reproduce the retail bytes, so that file keeps the exact assembly.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include <math.h>

// 0x0044FDB0..0x0044FE3F: ?ECL_ResolveIntOperand@@
// Ghidra's call references show an ignored ECX value, the VM in EDX, and one
// selector pushed on the stack. The three-parameter fastcall signature keeps
// that private ABI: ECX is the unused first parameter, EDX is the frame, and
// the selector is stack-passed and removed by RET 4.
int __fastcall ECL_ResolveIntOperand_0044fdb0(
        int unused, EclFrame* frame, int selector) {
    EclOperandTable* table = frame->operand_table;
    int value = table->slots[selector];

    if ((table->indirect_mask & (1 << selector)) == 0) {
        return value;
    }

    if (value >= 0) {
        return *(int*)&frame->stack.data[frame->stack.frame_base + value];
    }

    if (value == -1) {
        int result = selector;
        int stack_offset = frame->stack.stack_pointer - 4;
        if (stack_offset >= 0) {
            frame->stack.stack_pointer = stack_offset;
            result = *(int*)&frame->stack.data[stack_offset];
            stack_offset -= 4;
            frame->stack.stack_pointer = stack_offset;
            if (frame->stack.data[stack_offset] == 'f') {
                result = (int)*(float*)&result;
            }
        }
        return result;
    }

    return frame->stack.context->ResolveSlot(value);
}

// 0x004501B0..0x004501CD: ?ECL_SetPolarVector@@
// Ghidra confirms __thiscall: receiver in ECX, angle and scale on the stack.
// The source-level math preserves component behavior; it does not claim the
// retail FSINCOS instruction or identical x87 rounding.
struct EclPolarVector2_004501B0 {
    float x;
    float y;

    __declspec(noinline) void SetPolar(float angle, float scale);
};

void EclPolarVector2_004501B0::SetPolar(float angle, float scale) {
    x = cosf(angle) * scale;
    y = sinf(angle) * scale;
}

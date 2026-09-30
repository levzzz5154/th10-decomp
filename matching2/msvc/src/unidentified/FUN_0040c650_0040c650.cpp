// 0x0040C650: resolve a float operand through the interpreter an operand slot
// records. The slot arrives in EAX; the selector passes through in ECX and the
// resolver's x87 result is returned by a tail jump.
#include "th10/script/ecl_operand_thunks.hpp"

#pragma code_seg(".text$01slot_operand")
__declspec(noinline) float ResolveSlotFloatOperand_0040c650(EclOperandSlot* slot, int selector) {
    return asm_ECL_ResolveFloatOperand_0044fe40(slot->interpreter, selector);
}
#pragma code_seg()

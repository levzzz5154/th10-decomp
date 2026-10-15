// 0x0040C680: resolve a float value through the interpreter an operand slot
// records. The slot arrives in EDX; the selector in ECX and the stack operand
// pass through to the resolver unchanged, so the body is a load and a tail jump.
#include "th10/script/ecl_operand_thunks.hpp"

#pragma code_seg(".text$03slot_value")
__declspec(noinline) float __fastcall ResolveSlotFloatValue(
        int selector, EclOperandSlot* slot, float operand) {
    return asm_ECL_ResolveFloatValue_0044ff80(slot->interpreter, selector, operand);
}
#pragma code_seg()

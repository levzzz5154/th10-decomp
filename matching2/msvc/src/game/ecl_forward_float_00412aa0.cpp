// 0x00412AA0: resolve a float through the entity VM's current operand slot.
// Native LTCG supplies the entity in EAX, the selector and float on the stack,
// and RET 8. Naming the slot keeps both pointer loads in EAX while ECX copies
// the float argument and then carries the selector to the real resolver.
#include "th10/script/ecl_float_values.hpp"
#pragma code_seg(".text$01bridge")
__declspec(noinline) float __stdcall ForwardEclFloat(EclFloatEntityVm* vm, int selector, float operand) {
    EclFloatOperandSlot* slot = vm->current; return slot->interpreter->ResolveFloatValue(selector, operand);
}
#pragma code_seg()

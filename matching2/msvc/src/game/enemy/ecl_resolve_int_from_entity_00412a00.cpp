// 0x00412A00: resolve an integer operand for an entity's ECL VM. The VM
// arrives in EAX and the selector in ECX; the VM's current operand slot hands
// its interpreter to 0x0044FDB0 in EDX, with the selector on the stack.
#include "th10/script/ecl_operand_thunks.hpp"

#pragma code_seg(".text$05entity_int")
__declspec(noinline) int ResolveEntityIntOperand(EclEntityVm* vm, int selector) {
    EclOperandSlot* slot = vm->slot;
    return ECL_ResolveIntOperand(selector, (EclFrame*)slot->interpreter, selector);
}
#pragma code_seg()

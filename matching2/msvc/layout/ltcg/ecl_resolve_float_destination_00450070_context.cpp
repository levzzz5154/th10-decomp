// Compiler context only; never selected as recovered game code.  The integer
// lookup at 0x00450030 is a separate translation unit of this link.
#include "../../src/script/sptcmd/ecl_resolve_float_destination_00450070.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) float* __stdcall EclResolveFloatDestinationContext(
        EclVm_00450070** items, int index, int count) {
    float* last = 0;
    while (count--) {
        EclVm_00450070* vm = *items++;
        last = vm->ResolveFloatDestination(index);
        last += *vm->ResolveIntDestination(index);
        last += *vm->ResolveIntDestination(count);
    }
    return last;
}
#pragma code_seg()

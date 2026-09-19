// Compiler context only; never selected as recovered game code.
#include "../../src/script/ecl_resolve_float_destination_00450070.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) float* __stdcall EclResolveFloatDestinationContext(
        EclVm_00450070** items, int index, int count) {
    float* last = 0;
    while (count--) {
        last = (*items++)->ResolveFloatDestination(index);
    }
    return last;
}
#pragma code_seg()

// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/ecl_resolve_int_destination.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int* __stdcall EclResolveIntDestinationContext(
        EclInterpreter2** items, int index, int count) {
    int* last = 0;
    while (count--) {
        last = (*items++)->ResolveIntDestination(index);
    }
    return last;
}
#pragma code_seg()

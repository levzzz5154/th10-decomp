// Compiler context only; never selected as recovered game code.
//
// The synthetic caller walks an array of state records and calls all seven
// accessors on each.  Loading the record from the array into a register and
// passing it straight on is what makes the whole-program register allocator
// hand each leaf its record in EAX, the convention retail has and no C++
// declaration can name.
#include "../../../src/unreferenced/unassigned_00421c90.cpp"

#pragma code_seg(".text$20context")
extern "C" int __stdcall UiStateAccessorCompilerContext_00421c90(
        UiState_00421c90** states, int count) {
    int total = 0;
    while (count--) {
        UiState_00421c90* state = *states++;
        total += UiState_00421c90_Flag6(state);
        total += UiState_00421c90_Flag5(state);
        total += UiState_00421c90_Flag3(state);
        total += UiState_00421c90_Flag1(state);
        total += (int)UiState_00421c90_Mode(state);
        total += UiState_00421c90_Flag0(state);
        total += UiState_00421c90_Flag2(state);
    }
    return total;
}
#pragma code_seg()

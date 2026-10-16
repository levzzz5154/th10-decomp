// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_441ec0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ResolveLookupContext_00441ec0(
        LookupObject** objects, LookupManager** managers,
        int count) {
    int result = 0;
    while (count--)
        result += ResolveLookup(*objects++, *managers++);
    return result;
}
#pragma code_seg()

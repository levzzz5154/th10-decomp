// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00441ec0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ResolveLookupContext_00441ec0(
        LookupObject_00441ec0** objects, LookupManager_00441ec0** managers,
        int count) {
    int result = 0;
    while (count--)
        result += ResolveLookup_00441ec0(*objects++, *managers++);
    return result;
}
#pragma code_seg()

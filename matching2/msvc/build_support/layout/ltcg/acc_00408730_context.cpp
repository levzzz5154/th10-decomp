// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_408730.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00408730** items, Vec313* other) {
    int n = 4;
    while (n--) {
        (*items++)->Apply(other);
    }
    return 0;
}
#pragma code_seg()

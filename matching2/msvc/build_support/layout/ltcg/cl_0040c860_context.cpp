// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0040c860.cpp"

#pragma code_seg(".text$03context")
int __stdcall ReleaseContext_0040c860(ResourceOwner_0040c860** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->ReleaseBlock();
    }
    return 0;
}
#pragma code_seg()

// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass keep the
// record in ESI.
#include "../../../src/unreferenced/unassigned_4050a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall WordColorRefreshCompilerContext(WordColor2** items, int count) {
    while (count--) {
        WordColor2* item = *items++;
        item->UpdateChannels();
        item->UpdateChannels();
    }
    return 0;
}
#pragma code_seg()

#include "../../src/unidentified/FUN_00406140_00406140.cpp"

#pragma code_seg(".text$03context")
int __stdcall ReleaseManagedItemCompilerContext(ManagedItem** items, int count) {
    ManagedItem* first = *items;
    for (int index = 0; index < count; ++index) {
        ReleaseManagedItem(first);
        ReleaseManagedItem(items[index]);
    }
    return 0;
}
#pragma code_seg()

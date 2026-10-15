#include "../../../src/game/bullet/bullet_manager_delete.cpp"

#pragma code_seg(".text$03context")
int __stdcall ReleaseManagedItemCompilerContext(BulletManager** items, int count) {
    BulletManager* first = *items;
    for (int index = 0; index < count; ++index) {
        BulletManager_Delete(first);
        BulletManager_Delete(items[index]);
    }
    return 0;
}
#pragma code_seg()

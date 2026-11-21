// Compiler context only; never selected as recovered game code.
#include "../../../src/game/bullet/bullet_manager_on_update.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoverySlotRearmCompilerContext(BulletSlotTable* tables, int count) {
    BulletSlotTable* table = tables;
    typedef int (BulletSlotTable::*CanRearmMethod)();
    CanRearmMethod can_rearm = &BulletSlotTable::OnUpdate;
    int total = 0;
    do {
        total += (table->*can_rearm)();
        total += table->active;
        table = table + 1;
    } while (--count != 0);
    return total;
}
#pragma code_seg()

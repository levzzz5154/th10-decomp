// Compiler context only; never selected as recovered game code.
#include "../../../src/game/bullet/bullet_manager_on_update.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoverySlotRearmCompilerContext(RecoverySlotTable_004065c0* tables, int count) {
    RecoverySlotTable_004065c0* table = tables;
    typedef int (RecoverySlotTable_004065c0::*CanRearmMethod)();
    CanRearmMethod can_rearm = &RecoverySlotTable_004065c0::OnUpdate;
    int total = 0;
    do {
        total += (table->*can_rearm)();
        total += table->active;
        table = table + 1;
    } while (--count != 0);
    return total;
}
#pragma code_seg()

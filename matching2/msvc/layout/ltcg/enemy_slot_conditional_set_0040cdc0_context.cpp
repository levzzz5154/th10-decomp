// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0040cdc0.cpp"

#pragma code_seg(".text$03context")
int __stdcall SlotSetterCompilerContext(EnemySlotWriter_0040cdc0** items, int count,
                                        void* value) {
    while (count--) {
        (*items++)->SetEnemyIfUnmirrored(value);
    }
    return 0;
}
#pragma code_seg()

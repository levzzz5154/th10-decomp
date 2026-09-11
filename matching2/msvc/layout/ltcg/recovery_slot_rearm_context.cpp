// Compiler context only; never selected as recovered game code.
#include "../../src/game/fun_004065c0_004065c0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoverySlotRearmCompilerContext(RecoverySlotTable_004065c0* tables, int count) {
    RecoverySlotTable_004065c0* table = tables;
    int total = 0;
    do {
        total += table->Rearm();
        total += table->active;
        table = table + 1;
    } while (--count != 0);
    return total;
}
#pragma code_seg()

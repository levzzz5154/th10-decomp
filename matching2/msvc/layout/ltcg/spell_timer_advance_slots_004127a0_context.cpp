// Compiler context only.
#include "../../src/game/spell_timer.cpp"
#pragma code_seg(".text$03context")
int __stdcall SpellTimerContext(SpellTimerState_004127a0 **items,int count) {
 int total=0; for(int i=0;i<count;++i) total += items[i]->AdvanceSlots()!=0; return total;
}
#pragma code_seg()

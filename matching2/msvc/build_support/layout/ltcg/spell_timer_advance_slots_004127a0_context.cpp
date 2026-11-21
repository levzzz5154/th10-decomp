// Compiler context only.
#include "../../../src/game/enemy/spell_timer.cpp"
#pragma code_seg(".text$03context")
int __stdcall SpellTimerContext(EnemyInterruptState **items,int count) {
 int total=0; for(int i=0;i<count;++i) total += items[i]->CheckInterrupts()!=0; return total;
}
#pragma code_seg()

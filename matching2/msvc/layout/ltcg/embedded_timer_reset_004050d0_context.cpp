#include "../../src/game/background/embedded_timer_reset_004050d0.cpp"
#pragma code_seg(".text$03context")
int __stdcall EmbeddedTimerReset004050d0CompilerContext(EmbeddedTimer_004050d0** timers, int count) {
    while (count--) { EmbeddedTimer_004050d0* timer = *timers++; timer->Reset(); timer->Reset(); }
    return 0;
}
#pragma code_seg()

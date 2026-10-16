#include "../../../src/game/background/embedded_timer_reset.cpp"
#pragma code_seg(".text$03context")
int __stdcall EmbeddedTimerReset004050d0CompilerContext(EmbeddedTimer** timers, int count) {
    while (count--) { EmbeddedTimer* timer = *timers++; timer->Reset(); timer->Reset(); }
    return 0;
}
#pragma code_seg()

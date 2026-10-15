// Compiler context only; never selected as recovered game code.
//
// The array walk keeps the counter object in a callee-saved register across the
// FrameTimer_GetDelta call, which is the whole-program decision that reproduces
// retail's ESI receiver.
#include "../../src/game/fps/fps_update.cpp"

#pragma code_seg(".text$03context")
int __stdcall FrameRateCounterCompilerContext(FPS* counters, int count) {
    int total = 0;
    do {
        total += counters->Update();
        counters = counters + 1;
    } while (--count != 0);
    return total;
}
#pragma code_seg()

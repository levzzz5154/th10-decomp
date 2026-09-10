// Compiler context only: this caller is not a recovered application function.
// Keeping all uses in one LTCG unit lets MSVC choose the verified internal
// register conventions. The build selects only the three FrameTimer methods.
#include "../../src/math/frame_timer.cpp"

#pragma code_seg(".text$70context")
void __stdcall FrameTimerCompilerContext(FrameTimer* timers, int count, int delta) {
    for (int index = 0; index < count; ++index) {
        timers[index].Tick();
        timers[index].Advance(float(delta));
        timers[index].Decrement(delta);
    }
}
#pragma code_seg()

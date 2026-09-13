// Compiler context only: this caller is not a recovered application function.
// Keeping all uses in one LTCG unit lets MSVC choose the verified internal
// register conventions. The build selects the three FrameTimer methods and
// the separately compiled animation-cursor caller.
#include "../../src/math/frame_timer.cpp"

struct AnimationCursor_0043c230 {
    int Tick();
};

#pragma code_seg(".text$09context")
void __stdcall FrameTimerCompilerContext(
        FrameTimer* timers, int count, int delta,
        AnimationCursor_0043c230* cursor) {
    for (int index = 0; index < count; ++index) {
        timers[index].Tick();
        timers[index].Advance(float(delta));
        timers[index].Decrement(delta);
    }
    if (cursor != 0)
        cursor->Tick();
}
#pragma code_seg()

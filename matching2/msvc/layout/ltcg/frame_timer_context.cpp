// Compiler context only: this caller is not a recovered application function.
// One native-LTCG unit reaches the FrameTimer methods, all three animation
// cursors, the scheduler store and the gauge-timer clamp, so MSVC selects the
// verified internal register conventions: ECX cursor entries, EAX for the
// scheduler receiver, ESI for the embedded timers and EDI for the score state
// whose gauge timer survives the advance call.  The cursors are additional
// linker roots, which keeps their public ECX entry while their internal calls
// stay private.
#include "../../src/math/frame_timer.cpp"
#include "th10/game/score.hpp"
#include "th10/game/stage_schedule.hpp"
#pragma code_seg(".text$12d_rng")
#include "th10/math/rng.hpp"
#pragma code_seg()

struct PlayerSchedulerRecord {
    void SetSchedulerValue(int value);
};
struct AnimationCursor_0043bd40 { int Tick(); };
struct AnimationCursor_0043c230 { int Tick(); };
struct AnimationCursor_0043c460 { int Tick(); };

#pragma code_seg(".text$15context")
extern "C" void __stdcall AnimationTimerSchedulerCompilerContext(
        FrameTimer* timers, int count, int delta,
        AnimationCursor_0043bd40* cursor_bd40,
        AnimationCursor_0043c230* cursor_c230,
        AnimationCursor_0043c460* cursor_c460,
        PlayerSchedulerRecord* scheduler,
        ScoreState* scores, StageSequence* sequence,
        EntityScriptRng_0043cb80* rng) {
    for (int index = 0; index < count; ++index) {
        timers[index].Tick();
        timers[index].Advance(float(delta));
        timers[index].Decrement(delta);
    }
    if (cursor_bd40 != 0)
        cursor_bd40->Tick();
    if (cursor_c230 != 0)
        cursor_c230->Tick();
    if (cursor_c460 != 0)
        cursor_c460->Tick();
    if (scheduler != 0)
        scheduler->SetSchedulerValue(delta);
    if (scores != 0) {
        for (int index = 0; index < count; ++index)
            scores[index].DecayGauge();
    }
    if (scores != 0) {
        for (int index = 0; index < count; ++index)
            scores[index].AdvanceGaugeTimer(delta);
    }
    if (rng != 0) {
        for (int index = 0; index < count; ++index)
            rng[index].NextRandomModulo(delta + index);
    }
}
#pragma code_seg()

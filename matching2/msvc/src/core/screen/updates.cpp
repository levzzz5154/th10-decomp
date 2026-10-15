// The screen effect's fade, flash and envelope-shake update tasks. They are
// compiled together with FrameTimer in the frame_timer native-LTCG cluster,
// which gives the embedded timer its retail ESI receiver.
#include "th10/math/timer.hpp"
#include "th10/math/rng.hpp"
#include "th10/core/screen.hpp"

extern "C" int g_screen_effects_frozen;  // 0x004918A4
extern "C" float flt_255;  // 0x00470BF8

// 0x0043BD40: the fade-in update task (Screen modes 0 and 3):
// the alpha falls from 255 to 0 over the length. The object embeds a FrameTimer at
// +0x30; native LTCG supplies the retail internal ESI receiver for that call.
struct ScreenFadeIn {
    unsigned char pad_00[0x18];
    int value;                   // +0x18
    int length;                  // +0x1C
    unsigned char pad_20[0x10];
    int previous;                // +0x30, owned by the embedded timer
    int frame;                   // +0x34
    volatile float elapsed;      // +0x38; preserves retail x87 load order
    const float* delta;          // +0x3C

    __declspec(noinline) int Tick();
};

typedef char AnimationCursor_0043bd40_size_must_be_40[
    sizeof(ScreenFadeIn) == 0x40 ? 1 : -1];

#pragma code_seg(".text$07bd40")
int ScreenFadeIn::Tick() {
    if (g_screen_effects_frozen != 0)
        return 7;

    int divisor = length;
    if (divisor != 0) {
        int next = int(flt_255 - elapsed * flt_255 / divisor);
        value = next;
        if (next < 0)
            value = 0;
    }

    if (frame >= divisor)
        return 7;

    reinterpret_cast<FrameTimer*>(reinterpret_cast<unsigned char*>(this) + 0x30)->Tick();
    return 1;
}
#pragma code_seg()

// 0x0043C230..0x0043C2B4: the fade-out update task (Screen
// modes 2 and 5): the alpha rises from 0 to 255 over the length.
// The cursor owns a FrameTimer at +0x30.  Its retail caller supplies that
// timer in ESI; the native-LTCG frame_timer cluster selects the same private
// convention when both definitions are visible to one link.
extern "C" int g_screen_effects_frozen;
struct GameScene_00477810 {
    unsigned char pad_00[0x58];
    unsigned int flags;  // +0x58
};
// The game scene (0x00477810); the effects stop while it is paused.
extern "C" GameScene_00477810* g_game;
extern "C" float flt_255;

struct ScreenFadeOut {
    unsigned char pad_00[0x18];
    int value;
    int length;
    unsigned char pad_20[0x10];
    int previous;
    int frame;
    volatile float elapsed;
    const float* delta;

    __declspec(noinline) int Tick();
};

typedef char AnimationCursor_0043c230_size_must_fit[
    sizeof(ScreenFadeOut) == 0x40 ? 1 : -1];

#pragma code_seg(".text$09c230")
int ScreenFadeOut::Tick() {
    if (g_screen_effects_frozen != 0)
        return 7;

    int divisor = length;
    if (divisor != 0) {
        if (frame < divisor) {
            value = (int)(elapsed * flt_255 / divisor);
        } else {
            value = 255;
        }
        if (value < 0)
            value = 0;
    }

    if (frame >= divisor + 2)
        return 7;

    void* state = g_game;
    if (state == 0 || (((*(unsigned int*)((char*)state + 0x58) >> 2) |
                        *(unsigned int*)((char*)state + 0x58)) & 1) == 0) {
        reinterpret_cast<FrameTimer*>(reinterpret_cast<unsigned char*>(this) +
                                      0x30)->Tick();
    }
    return 1;
}
#pragma code_seg()

extern "C" int g_screen_effects_frozen;  // 0x004918A4

// 0x0043C460: the flash update task (Screen mode 4): the alpha
// falls from its start value to 0, then holds for a countdown.  The record embeds the scheduler and
// the FrameTimer at +0x30; native LTCG supplies the retail EAX receiver for
// the scheduler store and the ESI receiver for the embedded timer, exactly as
// for the 0x0043C230 cursor.
struct PlayerSchedulerRecord {
    int field_00;    // +0x00, stored one below the raw value
    int field_04;    // +0x04
    float field_08;  // +0x08, value converted to float
    int field_0C;    // +0x0C, default marker
    int flags_10;    // +0x10, initialised flag

    __declspec(noinline) void SetSchedulerValue(int value);
};

struct ScreenFlash {
    unsigned char pad_00[0x18];
    int value;                 // +0x18
    int length;                // +0x1C
    int countdown;             // +0x20
    unsigned char pad_24[0xC];
    int previous;              // +0x30, embedded FrameTimer::previous
    int frame;                 // +0x34, embedded FrameTimer::current
    float elapsed;             // +0x38, embedded FrameTimer::elapsed
    const float* delta;        // +0x3C, embedded FrameTimer::speed

    __declspec(noinline) int Tick();
};

typedef char AnimationCursor_0043c460_size_must_fit[
    sizeof(ScreenFlash) == 0x40 ? 1 : -1];

#pragma code_seg(".text$11c460")
int ScreenFlash::Tick() {
    int mode = *(unsigned char*)((unsigned char*)this + 0x27);
    if (g_screen_effects_frozen != 0)
        return 0;

    int divisor = length;
    if (frame < divisor) {
        unsigned int amount = (unsigned int)mode;
        int scaled = int(float(amount) * elapsed / divisor);
        value = mode - scaled;
        if (value < 0)
            value = 0;
    } else {
        value = 0;
        if (--countdown <= 0)
            return 0;
        reinterpret_cast<PlayerSchedulerRecord*>(reinterpret_cast<unsigned char*>(this) + 0x30)
            ->SetSchedulerValue(0);
    }

    reinterpret_cast<FrameTimer*>(reinterpret_cast<unsigned char*>(this) + 0x30)->Tick();
    return 1;
}
#pragma code_seg()

// The out-of-line copy of the header-inline RNG member is emitted by this
// unit, after the screen effects, as in retail (0x0043CB80).
#pragma code_seg(".text$12d_rng")
#pragma code_seg()

extern "C" int g_screen_effects_frozen;                     // 0x004918A4, effects frozen
extern "C" EntityScriptRng_0043cb80 g_rng;  // 0x004918B0, effect RNG
extern "C" float g_screen_shake_x;                   // 0x00491E64, screen shake x
extern "C" float g_screen_shake_y;                   // 0x00491E68, screen shake y

// 0x0043C710 - screen shake with an attack/sustain/release envelope. The
// shared parameters are the attack, sustain and release lengths in frames;
// each axis is randomly displaced by zero, plus or minus the current amount.
#pragma code_seg(".text$12b_shake")
int Screen::UpdateEnvelopeShake() {
    if (g_screen_effects_frozen)
        return 7;
    if (!g_game ||
        (((g_game->flags >> 2) | g_game->flags) & 1) ||
        (g_game->flags & 0x72))
        return 1;

    timer.Tick();
    float ratio;
    if (timer.current < parameter20)
        ratio = timer.Elapsed() / parameter20;
    else if (timer.current < parameter20 + parameter24)
        ratio = 1.0f;
    else if (timer.current < parameter20 + parameter24 + parameter28)
        ratio = ((unsigned int)parameter28 + (unsigned int)parameter24 +
                 (unsigned int)parameter20 - timer.Elapsed()) /
                (unsigned int)parameter28;
    else
        return 7;

    float amount = duration_or_strength * ratio;
    switch (g_rng.NextRandomModulo(3)) {
    case 0: g_screen_shake_x = 0.0f; break;
    case 1: g_screen_shake_x = amount; break;
    case 2: g_screen_shake_x = -amount; break;
    }
    switch (g_rng.NextRandomModulo(3)) {
    case 0: g_screen_shake_y = 0.0f; break;
    case 1: g_screen_shake_y = amount; break;
    case 2: g_screen_shake_y = -amount; break;
    }
    return 1;
}
#pragma code_seg()

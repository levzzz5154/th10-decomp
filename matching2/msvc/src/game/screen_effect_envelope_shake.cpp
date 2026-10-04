// The out-of-line copy of the header-inline RNG member is emitted by this
// unit, after the screen effects, as in retail (0x0043CB80).
#pragma code_seg(".text$12d_rng")
#include "th10/math/rng.hpp"
#pragma code_seg()
#include "th10/game/runtime_selector_0043c970.hpp"

struct GameScene_00477810 {
    unsigned char pad_00[0x58];
    unsigned int flags;  // +0x58
};

extern "C" int data_004918a4;                     // 0x004918A4, effects frozen
extern "C" GameScene_00477810* data_00477810;     // 0x00477810
extern "C" EntityScriptRng_0043cb80 data_004918b0;  // 0x004918B0, effect RNG
extern "C" float data_00491e64;                   // 0x00491E64, screen shake x
extern "C" float data_00491e68;                   // 0x00491E68, screen shake y

// 0x0043C710 - screen shake with an attack/sustain/release envelope. The
// shared parameters are the attack, sustain and release lengths in frames;
// each axis is randomly displaced by zero, plus or minus the current amount.
#pragma code_seg(".text$12b_shake")
int ScreenEffectController_0043c970::UpdateEnvelopeShake() {
    if (data_004918a4)
        return 7;
    if (!data_00477810 ||
        (((data_00477810->flags >> 2) | data_00477810->flags) & 1) ||
        (data_00477810->flags & 0x72))
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
    switch (data_004918b0.NextRandomModulo(3)) {
    case 0: data_00491e64 = 0.0f; break;
    case 1: data_00491e64 = amount; break;
    case 2: data_00491e64 = -amount; break;
    }
    switch (data_004918b0.NextRandomModulo(3)) {
    case 0: data_00491e68 = 0.0f; break;
    case 1: data_00491e68 = amount; break;
    case 2: data_00491e68 = -amount; break;
    }
    return 1;
}
#pragma code_seg()

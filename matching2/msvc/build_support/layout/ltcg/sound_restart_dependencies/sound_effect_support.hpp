#pragma once

struct SoundEffectSetting {
    int source;
    short volume;
    short priority;
};

extern "C" {
    extern volatile SoundEffectSetting g_sound_effect_settings[];
}

// MSVC's x87 conversion returns a signed 64-bit result; callers retain EAX.
// The behavioral Clang profile uses 80-bit long double for x87 intermediates.
__forceinline unsigned int TruncatedSoundLowWord(long double value) {
    const long double limit = 9223372036854775808.0L;
    // Masked invalid conversion produces integer-indefinite (low word zero).
    // Keep out-of-range/NaN conversions out of C++'s undefined conversion case.
    if (!(value >= -limit && value < limit))
        return 0;
    return static_cast<unsigned int>(static_cast<__int64>(value));
}

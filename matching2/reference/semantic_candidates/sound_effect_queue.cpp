// Sound-effect producers: 0x0043DD10 (149 bytes) and 0x0043DDB0 (52 bytes).
// Retail uses ESI manager, EBX sound ID + stack float / EDI stop ID, respectively.
// Explicit stdcall candidates; native private-entry matching remains pending.
#include "sound_wave_types.hpp"
#include "sound_effect_support.hpp"

extern "C" {
    extern const float g_sound_pan_scale;
}

extern "C" void __stdcall Sound_QueueEffect_0043dd10(WaveSoundManager* manager, int index, float pan) {
    int priority = g_sound_effect_settings[index].priority;
    unsigned int request = TruncatedSoundLowWord(static_cast<long double>(pan) * g_sound_pan_scale);
    for (unsigned int pending = 0; pending < 12; ++pending) {
        int existing = manager->pending_sound_indices[pending];
        if (existing < 0) {
            manager->pending_sound_indices[pending] = index;
            unsigned int priority_address = reinterpret_cast<unsigned int>(manager) + 0x408 +
                static_cast<unsigned int>(index) * 4;
            *reinterpret_cast<volatile int*>(priority_address) = priority;
            manager->pending_pan[pending][0] = static_cast<int>(request);
            manager->pending_pan_count[pending] = static_cast<int>(
                static_cast<unsigned int>(manager->pending_pan_count[pending]) + 1);
            return;
        }
        if (existing == index) {
            int count = manager->pending_pan_count[pending];
            if (count < 128) {
                // Negative counts are accepted and may alias other queue fields.
                unsigned int address = reinterpret_cast<unsigned int>(manager) + 0x680 +
                    pending * 512 + static_cast<unsigned int>(count) * 4;
                *reinterpret_cast<volatile unsigned int*>(address) = request;
                manager->pending_pan_count[pending] = static_cast<int>(
                    static_cast<unsigned int>(manager->pending_pan_count[pending]) + 1);
            }
            return;
        }
    }
}

extern "C" unsigned int __stdcall Sound_QueueEffectStop_0043ddb0(WaveSoundManager* manager, int index) {
    for (unsigned int pending = 0; pending < 12; ++pending) {
        int existing = manager->pending_sound_indices[pending];
        if (existing < 0) {
            manager->pending_sound_indices[pending] = index;
            manager->pending_pan_count[pending] = -1;
            return pending;
        }
        if (existing == index) {
            manager->pending_pan_count[pending] = -1;
            return pending;
        }
    }
    return 12;
}

// 0x0043DB60, complete 295-byte retail region (including interior alignment).
// Retail receives the manager in EBX, plain RET. Explicit stdcall candidate.
#include "sound_wave_types.hpp"
#include "sound_effect_support.hpp"

extern "C" {
    extern WaveSoundManager g_wave_sound_manager;
    extern volatile signed char g_music_volume_setting;
    extern volatile signed char g_effect_volume_setting;
    extern const float g_sound_volume_scale;
    extern const float g_sound_volume_one;
    extern const float g_sound_volume_range;
    int __stdcall Sound_StopPreloadWorkers_0043cc40(WaveSoundManager*);
}

extern "C" int __stdcall Sound_InitializeEffects_0043db60(WaveSoundManager* manager) {
    for (unsigned int index = 0; index < 12; ++index)
        *static_cast<volatile int*>(&manager->pending_sound_indices[index]) = -1;
    // This call intentionally uses the global manager, not the receiver.
    Sound_StopPreloadWorkers_0043cc40(&g_wave_sound_manager);
    if (!manager->device_owner)
        return -1;
    if (!manager->device)
        return 0;

    for (unsigned int index = 0; index < 47; ++index) {
        unsigned int source_address = reinterpret_cast<unsigned int>(manager) + 8 +
            static_cast<unsigned int>(g_sound_effect_settings[index].source) * 4;
        WaveSecondaryBuffer* source = *reinterpret_cast<WaveSecondaryBuffer* const volatile*>(source_address);
        WaveDirectSoundDevice* device = manager->device;
        WaveSecondaryBuffer** output = &manager->secondary_buffers[128 + index];
        device->methods->duplicate_buffer(device, source, output);
        WaveSecondaryBuffer* buffer = *output;
        buffer->methods->set_position(buffer, 0);
        int volume = g_sound_effect_settings[index].volume;
        buffer = *output;
        buffer->methods->set_volume(buffer, volume);
    }
    manager->volume_a = static_cast<int>(g_music_volume_setting);
    int effect_volume = g_effect_volume_setting;
    manager->volume_b = effect_volume;
    if (effect_volume) {
        long double factor = static_cast<long double>(g_sound_volume_one) -
            static_cast<long double>(static_cast<int>(manager->volume_a)) * g_sound_volume_scale;
        long double squared = factor * factor;
        unsigned int curved = TruncatedSoundLowWord((static_cast<long double>(g_sound_volume_one) -
            squared * squared) * g_sound_volume_range);
        manager->volume_attenuation = static_cast<int>(static_cast<unsigned int>(-5000) - curved);
    } else
        manager->volume_attenuation = -10000;
    return 0;
}

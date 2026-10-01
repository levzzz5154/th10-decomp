// 0x0043DB60, complete 295-byte retail region (including interior alignment).
// Retail receives the manager in EBX, plain RET. This native candidate emits
// 300 bytes and currently selects an EDI receiver; it is not production code.
#include "../../layout/ltcg/sound_effects/sound_wave_types.hpp"
#include "../../layout/ltcg/sound_effects/workers.hpp"
struct SoundEffectSetting { int source; short volume; short priority; };
extern "C" volatile SoundEffectSetting g_sound_effect_settings[];

extern "C" {
    extern WaveSoundManager g_wave_sound_manager;
    extern volatile signed char g_music_volume_setting;
    extern volatile signed char g_effect_volume_setting;
    extern const float g_sound_volume_one;

}


#pragma code_seg(".text$03effects")
int WaveSoundManager::InitializeEffects() {
    WaveSoundManager* manager = this;
    *static_cast<volatile int*>(&manager->pending_sound_indices[0]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[1]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[2]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[3]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[4]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[5]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[6]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[7]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[8]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[9]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[10]) = -1;
    *static_cast<volatile int*>(&manager->pending_sound_indices[11]) = -1;
    // This call intentionally uses the global manager, not the receiver.
    reinterpret_cast<SoundWorkerPair_0043cc40*>(&g_wave_sound_manager)->Stop();
    if (!manager->device_owner)
        return -1;
    if (!manager->device)
        return 0;

    for (unsigned int index = 0; index < 47; ++index) {
        WaveSecondaryBuffer* source = manager->secondary_buffers[g_sound_effect_settings[index].source];
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
        float factor = 1.0f -
            static_cast<float>(manager->volume_a) * 0.01f;
        float squared = factor * factor;
        unsigned int curved = static_cast<unsigned int>(static_cast<__int64>((1.0f -
            squared * squared) * -5000.0f));
        manager->volume_attenuation = static_cast<int>(static_cast<unsigned int>(-5000) - curved);
    } else
        manager->volume_attenuation = -10000;
    return 0;
}

#pragma code_seg()

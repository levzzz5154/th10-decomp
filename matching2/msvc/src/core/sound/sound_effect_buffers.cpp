// 0x0043DB60: prepare the sound effect buffers. Clears the pending effect
// slots, stops the preload workers, duplicates one secondary buffer per effect
// from its source wave and applies the effect's own volume, then caches the
// configured volumes and the music attenuation derived from them.
//
// Retail receives the manager in EBX with a plain RET; the title worker at
// 0x0041F990 is its only caller.
#include "th10/app/supervisor.hpp"
#include "../../../build_support/layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"
#include "../../../build_support/layout/ltcg/title_assets_dependencies/workers.hpp"

struct SoundEffectSetting {
    int source;          // index of the wave the effect is duplicated from
    short volume;
    short priority;
};

extern "C" {
extern SoundEffectSetting g_sound_effect_settings[47];
extern WaveSoundManager g_wave_sound_manager;
}

#pragma code_seg(".text$06effects")
int WaveSoundManager::InitializeEffects() {
    for (int slot = 0; slot < 12; ++slot)
        pending_sound_indices[slot] = -1;
    // The workers always belong to the global manager, whatever the receiver.
    reinterpret_cast<SoundWorkerPair_0043cc40*>(&g_wave_sound_manager)->Stop();
    if (!device_owner)
        return -1;
    if (!device)
        return 0;
    for (unsigned int index = 0; index < 47; ++index) {
        device->methods->duplicate_buffer(device,
            secondary_buffers[g_sound_effect_settings[index].source],
            &secondary_buffers[128 + index]);
        secondary_buffers[128 + index]->methods->set_position(secondary_buffers[128 + index], 0);
        secondary_buffers[128 + index]->methods->set_volume(secondary_buffers[128 + index],
            g_sound_effect_settings[index].volume);
    }
    volume_a = g_supervisor.music_volume;
    volume_b = g_supervisor.effect_volume;
    if (volume_b) {
        float factor = 1.0f - volume_a * 0.01f;
        factor = factor * factor;
        volume_attenuation = -5000 - (unsigned int)((1.0f - factor * factor) * -5000.0f);
    } else
        volume_attenuation = -10000;
    return 0;
}
#pragma code_seg()

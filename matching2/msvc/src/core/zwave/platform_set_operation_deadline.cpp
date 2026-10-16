// 0x0044D4E0 - Set the first DirectSound buffer's volume using the global
// volume curve, or -10000 for the zero setting. Historical names are retained.
#include "th10/platform/sound_fade.hpp"

#pragma code_seg(".text$01deadline")
__declspec(noinline) int
PlatformInterfaceState2::SetOperationDeadline(int deadline) {
    if (g_options_music_volume != 0) {
        float factor = 1.0f - (float)g_options_music_volume * 0.01f;
        int value = (int)((1.0f - factor * factor) * (deadline + 5000));
        return entries_004[0]->set_deadline(value - 5000);
    }
    return entries_004[0]->set_deadline(-10000);
}
#pragma code_seg()
